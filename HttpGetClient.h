#ifndef _HTTPGETCLIENT_H
#define _HTTPGETCLIENT_H

#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <sstream>
#include <unistd.h>
#include <fstream>

class HttpGetClient{
public:
    HttpGetClient(std::string _url);
    ~HttpGetClient() = default;
    void writeDataToFile(std::string filepath);
    std::string printData();
private:
    std::string GetProtocol();
    std::string GetHost();
    std::string GetAction();
    std::string GetRequest();
    std::string url;
    std::string protocol;
    std::string host;
    std::string action;
};


#endif //_HTTPGETCLIENT_H
