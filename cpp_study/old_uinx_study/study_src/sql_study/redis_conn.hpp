//
// Created by tao on 18-11-26.
//

#ifndef UNIXSTUDYCPP_REDIS_CONN_HPP
#define UNIXSTUDYCPP_REDIS_CONN_HPP

#include <hiredis/hiredis.h>
#include <strings.h>
#include <wchar.h>

#include "../log4cplus_init/log_macro.h"
#include "../public_object/people.hpp"

static int test_01() {
    People p1("zzzz", 18, 80.0);

    auto *p_p2 = static_cast<People *>(malloc(sizeof(People)));
    memcpy(p_p2, &p1, sizeof(p1));
    People *p_p3 = new People("zzz1", 70, 87.01);

    INFO("p1:" << p1.to_string().data());
    INFO("p2:" << p_p2->to_string().data());
    INFO("p3:" << p_p3->to_string().data());

    //连接
    redisContext *conn = redisConnect("service.tao", 6379);

    if (nullptr == conn) {
        PERROR("conn fail!");
        return -1;
    } else if (conn->err != 0) {
        PERROR("conn fail!");
        redisFree(conn);
        return -2;
    }

    //存储 二进制
    const char *(argvs[3]);
    size_t argcs[3];

    argvs[0] = "set";
    argcs[0] = strlen(argvs[0]);

    argvs[1] = "blob_people_01";
    argcs[1] = strlen(argvs[1]);

    argvs[2]   = (const char *)p_p3;
    argcs[2]   = sizeof(People);
    auto reply = (redisReply *)redisCommandArgv(conn, sizeof(argcs) / sizeof(argcs[0]), argvs, argcs);
    if (nullptr == reply) {
        PERROR("no replay");
    } else if (strcasecmp("OK", reply->str) != 0) {
        ERROR("redis return wrong :" << reply->str);
        freeReplyObject(reply);
    } else {
        INFO("set blob OK, data :\t" << p_p3->to_string().data());
        freeReplyObject(reply);
    }

    //通用的存储方式，支持二进制
    reply = (redisReply *)redisCommand(conn, "set blob_people_02 %b", &p1, sizeof(p1));
    if (nullptr == reply) {
        PERROR("no replay");
    } else if (reply->type != REDIS_REPLY_STRING || strcasecmp("OK", reply->str) != 0) {
        ERROR("redis return wrong :" << reply->str);
        freeReplyObject(reply);
    } else {
        INFO("set blob OK, data :\t" << p_p3->to_string().data());
    }

    //获取二进制
    reply = (redisReply *)redisCommand(conn, "get blob_people_01");

    if (nullptr == reply) {
        PERROR("empty replay!");
    } else if (reply->type != REDIS_REPLY_STRING) {
        ERROR("redis type err : " << reply->str);
    } else if (reply->len != sizeof(People)) {
        ERROR("len mot match");
    } else {
        People *back = (People *)reply->str;
        INFO("back is :" << back->to_string().data());
    }

    reply = (redisReply *)redisCommand(conn, "get blob_people_02");

    if (nullptr == reply) {
        PERROR("empty replay!");
    } else if (reply->type != REDIS_REPLY_STRING) {
        ERROR("redis type err : " << reply->str);
    } else if (reply->len != sizeof(People)) {
        ERROR("len mot match");
    } else {
        People *back = (People *)reply->str;
        INFO("back is :" << back->to_string().data());
    }

    free(p_p2);
    delete (p_p3);
    redisFree(conn);

    return 0;
}

void test_redis_conn() { test_01(); }

#endif  // UNIXSTUDYCPP_REDIS_CONN_HPP
