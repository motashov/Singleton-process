#ifndef _SINGLETON_PROCESS_
#define _SINGLETON_PROCESS_

#include <netinet/in.h>
#include <unistd.h>

int obtainSingletonLock(uint16_t magicNumber)
{
    int socket_fd = -1;
    int bindRC = -1;
    uint16_t port = magicNumber;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (socket_fd < 0)
    {
        perror("Could not open socket \n");
        return 0;
    }

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    bindRC = bind(socket_fd, (struct sockaddr*) &name, sizeof(name));
    if ((socket_fd > 0) && (0 == bindRC))
    {
        return 1;
    }
    return 0;
}


#endif // _SINGLETON_PROCESS_
