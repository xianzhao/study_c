#include <stdio.h>
#include <string.h>
#include <netinet/in.h>

int main(void)
{
    struct sockaddr_in servaddr;
    int sockfd, n;

    char content[4096];
    char* header = "GET /index.html HTTP/1.1\r\nHOST:192.168.10.101\r\n\r\n";

    printf("%s", header);

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(80);

    inet_pton(AF_INET, "192.168.10.101", &servaddr.sin_addr);

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error.");
    } else {
        printf("socket success...\n");
    }

    if ( connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
        printf("connect error.");
    } else {
        printf("connect success...\n");
    }


    if ( send(sockfd, header, strlen(header), 0) < 0 ) {
        printf("write error.");
    } else {
        printf("write success...\n");
    }


    while( (n = read(sockfd, content, 4095)) > 0 ) {
        content[n] = 0;
        fputs(content, stdout);

    }

    close(sockfd);


    return 0;

}
