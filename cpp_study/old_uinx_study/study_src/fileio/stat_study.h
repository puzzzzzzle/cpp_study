//
// Created by tao on 18-10-8.
//

#ifndef UNIXSTUDY_STAT_STUDY_H
#define UNIXSTUDY_STAT_STUDY_H

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

void stat_std() {
    const char *dir_name = "./";
    DIR *p = NULL;
    struct dirent *buff;
    struct stat sbuff;
    if ((p = opendir(dir_name)) == NULL) {
        perror("ERROR: ");
        return;
    }

    while ((buff = readdir(p)) != NULL) {
        printf("file\t%s\t%d\t", buff->d_name, buff->d_type);
        if (lstat(buff->d_name, &sbuff) < 0) {
            perror("lstat error :");
        }
        printf("uid:%d\tblock:%ld", sbuff.st_uid, sbuff.st_blksize);
        if(S_ISDIR(sbuff.st_mode)){
            printf("\td\n");
        } else
        {
            printf("\n");
        }
    }

    closedir(p);
}

void access_std(const char *path) {
    printf("%s:\t", path);
    if (access(path, F_OK)>=0) {
        printf("F_OK\t");
    }
    if (access(path, R_OK)>=0) {
        printf("R_OK\t");
    }
    if (access(path, W_OK)>=0) {
        printf("W_OK\t");
    }
    if (access(path, X_OK)>=0) {
        printf("X_OK\t");
    }
    printf("\n");
}

#endif //UNIXSTUDY_STAT_STUDY_H
