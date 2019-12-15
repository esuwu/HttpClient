#include "HttpGetClient.h"

using std::string;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;


HttpGetClient::HttpGetClient(string _url) : url(_url){
    protocol = GetProtocol();
    host = GetHost();
    action = GetAction();
}

std::string HttpGetClient::GetProtocol() {
    std::string protocol = "";
    for(int i = 0; i < url.size(); i++) {
        if(url[i] != '/' || url[i+1] != '/') {
            protocol += url[i];
        } else {
            protocol += "//";
            break;
        }
    }
    return protocol;
}

std::string HttpGetClient::GetHost() {
    std::string host = "";
    url.replace(0, protocol.size(), "");
    for(int i = 0; i < url.size(); i++) {
        if( url[i] != '/' ) {
            host += url[i];
        } else {
            break;
        }
    }
    return host;
}

std::string HttpGetClient::GetAction() {
    std::string parm = "";
    url.replace(0, protocol.size()+ host.size(), "");
    for(int i = 0; i < url.size(); i++) {
        if( url[i] != '?' && url[i] != '#' ) {
            parm += url[i];
        } else {
            break;
        }
    }
    return parm;
}

string HttpGetClient::GetRequest(){
    char buf[10000];
    std::string header = "";
    header += "GET ";
    header += protocol + host + action;
    header += (std::string)" HTTP/1.1" + "\r\n";
    header += (std::string)"Host: " + protocol + host + "/" + "\r\n";
    header += (std::string)"User-Agent: Mozilla/5.0" + "\r\n";
    header += (std::string)"Accept-Language: ru,en-us;q=0.7,en;q=0.3" + "\r\n";
    header += (std::string)"Accept-Charset: windows-1251,utf-8;q=0.7,*;q=0.7" + "\r\n";
    header += (std::string)"Connection: keep-alive " + "\r\n";
    header += "\r\n";
    int sock;
    struct sockaddr_in addr;
    struct hostent* raw_host;
    raw_host = gethostbyname( host.c_str() );
    if (raw_host == NULL)
    {
        std::cout<<"ERROR, no such host";
        exit(0);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);

    bcopy( (char*)raw_host->h_addr, (char*)&addr.sin_addr, raw_host->h_length );

    if( connect( sock, (struct sockaddr *)&addr, sizeof(addr) ) < 0)
    {
        std::cerr<<"connect error"<<std::endl;
        exit(2);
    }

    char * message = new char[ header.size() ];
    for(int i = 0; i < header.size(); i++)
    {
        message[i] = header[i];
    }

    send(sock, message, header.size(), 0);
    recv(sock, buf, sizeof(buf), 0);

    std::string answer = "";
    int j = 0;
    for(j = 0; buf[j] != EOF; j++) {
        answer += buf[j];
    }
    close(sock);
    return answer;

}

string HttpGetClient::printData() {
    return GetRequest();
}

void HttpGetClient::writeDataToFile(std::string filepath) {
    ofstream fout;
    fout.open(filepath, std::ios::binary);
    fout << GetRequest();
    fout.close();
}
