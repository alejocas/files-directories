#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SIZE_OF_BUFFER_TO_READ 1

typedef struct stat stat_t;

int main(int argc, char *argv[]) {
    if(argc != 3) {
        if(argc < 3) printf("Debe ingresar todos los argumentos necesarios.\nEl uso del programa es: ./ex3_tail.out -[n] [nombre fichero]");
        if(argc > 3) printf("Ha ingresado más de los argumentos necesarios.\nEl uso del programa es: ./ex3_tail.out -[n] [nombre fichero]");
        exit(1);
    }
    if(argv[1][0] != '-') {
        printf("El formato esperado para ingresar el número de líneas que quiere visualizar debe empezar con un guión (-).\n");
        exit(1);
    }
    char *numberInString = &(argv[1])[1];
    int numberOfLines = atoi(numberInString);
    stat_t statObj;
    stat_t *pointerStatObj = &statObj;
    int fd = open(argv[2], O_RDONLY, 0);
    if(stat(argv[2], pointerStatObj) != 0){
        printf("Algo salió mal tratando de obtener la información del archivo. Intente más tarde.\n");
        exit(1);
    }
    char bufferToRead[SIZE_OF_BUFFER_TO_READ];
    off_t actualOffset = (off_t) statObj.st_size - 1;
    int entireLinesReaded = -1;
    int readedChars = 0;
    while(entireLinesReaded < numberOfLines) {
        actualOffset = lseek(fd, actualOffset, SEEK_SET); // Posicionando cursor al final del archivo
        read(fd, bufferToRead, (size_t) SIZE_OF_BUFFER_TO_READ);
        if(bufferToRead[0] == '\n') {
            entireLinesReaded++;
        }
        actualOffset--;
        if(actualOffset < 0) {
            printf("[=====ALERTA=====] Ha solicitado más líneas que las que tiene el archivo, se muestra todo el contenido.\n");
            break;
        }
        readedChars++;
    }
    actualOffset++;
    char bufferToTail[readedChars + 1];
    bufferToTail[readedChars] = '\0';
    lseek(fd, actualOffset, SEEK_SET);
    read(fd, bufferToTail, (size_t) readedChars);
    printf("[tail personalizado]\n%s\n", bufferToTail);
    close(fd);
    return 0;
}