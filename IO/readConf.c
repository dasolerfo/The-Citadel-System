#define _GNU_SOURCE
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <readwrite.c>

typedef struct _conf_maestre{
    char* name;
    char* port;
    char* dir;
    char* ip;
    ConfMaestre* routes;
}ConfMaestre;

ConfMaestre getMaestreConfig(char* filePath){
    int fd = open(filePath, O_RDONLY);
    ConfMaestre conf;
    conf.name = read_until_end(fd, '\n','\0', NULL);
    conf.dir = read_until_end(fd, '\n','\0', NULL);
    conf.ip = read_until_end(fd, '\n','\0', NULL);
    conf.port = read_until_end(fd, '\n','\0', NULL);
    // Llegim ROUTES
    read_until_end(fd, '\n','\0', NULL); 
    int numRoutes = 0;
    int reachedEnd = 0;
    while(reachedEnd == 0){
        if (numRoutes == 0){
            conf.routes = (ConfMaestre*) malloc(sizeof(ConfMaestre) * (numRoutes + 1));
        }else {
            conf.routes = (ConfMaestre*) realloc(conf.routes, sizeof(ConfMaestre) * (numRoutes + 1));
        }
        conf.routes[numRoutes].name = read_until_end(fd, ' ', '\n', &reachedEnd);
        conf.routes[numRoutes].ip = read_until_end(fd, ' ', '\n', &reachedEnd);
        conf.routes[numRoutes].port = read_until_end(fd, '\n', '\0', &reachedEnd);
        numRoutes++;
    }
    close(fd);
    return conf;
}

