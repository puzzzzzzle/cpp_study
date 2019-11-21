//
// Created by khalidzhang on 2019/11/21.
//

#ifndef CPP_STUDY_ALL_SYSUNIQUE_HPP
#define CPP_STUDY_ALL_SYSUNIQUE_HPP

#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

class SysUnique
{
private:
    std::string strID;
    int iSocketFd;
    int iPid;
    sockaddr_un stSockaddrUn;
    int iIsFinishInit{false};
public:
    SysUnique() = delete;

    SysUnique(std::string _id)
    {
        strID = _id;
    }
    ~SysUnique(){
        if(iSocketFd>0){
            close(iSocketFd);
        }
        if(iIsFinishInit){
            unlink(stSockaddrUn.sun_path);
        }
    }
private:
    void InitSocketPath(sockaddr_un &stSockaddrUn)
    {
        memset(&stSockaddrUn, 0, sizeof(stSockaddrUn));
        stSockaddrUn.sun_family = AF_UNIX;
        snprintf(stSockaddrUn.sun_path, sizeof(stSockaddrUn.sun_path), "/tmp/%s.sock", strID.c_str());
        stSockaddrUn.sun_path[sizeof(stSockaddrUn.sun_path) - 1] = 0;
    }
public:
    bool Init()
    {
        iSocketFd = socket(PF_UNIX, SOCK_STREAM, 0);
        if (iSocketFd < 0)
        {
            return false;
        }
        InitSocketPath(stSockaddrUn);
        if (bind(iSocketFd, (sockaddr *) &stSockaddrUn, sizeof(stSockaddrUn))!=0
                 || listen(iSocketFd, 65536)!=0){
            printf("err reason : %s\n",strerror(errno));
            return false;
        }
        iIsFinishInit = true;
        return true;
    }

    std::string GetID()
    {
        return strID;
    }

    int GetPid(std::string _id)
    {
        return -1;
    }

    bool IsRun()
    {
        InitSocketPath(stSockaddrUn);
        int iClientFd = socket(PF_UNIX, SOCK_STREAM, 0);
        if (iClientFd < 0)
        {
            return false;
        }
        int iRet = connect(iClientFd, (sockaddr *) &stSockaddrUn, sizeof(stSockaddrUn));
        if(iRet){
            printf("err reason : %s\n",strerror(errno));
        }
        close(iClientFd);
        return iRet == 0;
    }

};

#endif //CPP_STUDY_ALL_SYSUNIQUE_HPP
