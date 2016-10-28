#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sstream>
#include <string>

using namespace std;

int sock;
struct sockaddr_in client;
int PORT = 80;

int main(void){

    struct hostent * host = gethostbyname("hangang.dkserver.wo.tc");
    if ( (host == NULL) || (host->h_addr == NULL) ) {
        cout << "Error retrieving DNS information." << endl;
        exit(1);
    }

    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons( PORT );
    memcpy(&client.sin_addr, host->h_addr, host->h_length);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        cout << "Error creating socket." << endl;
        exit(1);
    }

    if ( connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
        close(sock);
        cout << "Could not connect" << endl;
        exit(1);
    }

    stringstream ss;
    ss << "GET /" << " HTTP/1.0\r\n"
       << "Host: hangang.dkserver.wo.tc\r\n"
       << "Accept: application/json\r\n"
       << "\r\n\r\n";

    string request = ss.str();

    if (send(sock, request.c_str(), request.length(), 0) != (int)request.length()) {
        cout << "Error sending request." << endl;
        exit(1);
    }

    char cur;
    while ( read(sock, &cur, 1) > 0 ) {
        cout << cur;
    }

    return 0;
}