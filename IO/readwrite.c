#define _GNU_SOURCE
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char* read_untilEnd(int fd, char delimiter, char endline, int* isEnd){
    int i = 0;
    char aux = delimiter - 1;
    char* buffer = NULL;
    while(aux != delimiter && aux != endline){
        read(fd, &aux, 1);
        if (i == 0){
            buffer = malloc(sizeof(char));
        } else {
            buffer = realloc(buffer, sizeof(char) * (i+2));
        }
        buffer[i] = aux;
        i++;   
    }

    if (aux == endline){
        *isEnd = 1;
    }
    buffer[i-1]  = '\0';
    return buffer;
}

void * fromBinaryToArray(int fd, int* size, int objectSize){
    void* array = NULL;
    int i = 0;
    void* aux = malloc(objectSize);
    while(read(fd, aux, objectSize) > 0){
        if (i == 0){
            array = malloc(objectSize);
        } else {
            array = realloc(array, objectSize * (i + 1));
        }
        //array[i] = *aux;
        char *dest = (char *)array + (i * objectSize);
        char *src  = (char *)aux;
        for (int j = 0; j < objectSize; j++)
            dest[j] = src[j];
        i++;
    }
    free(aux);
    *size = i;
    return array;
}