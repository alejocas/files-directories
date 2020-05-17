#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

typedef struct stat stat_t;

void formatearTiempo(time_t time, char *buffer);
void permisosBinario(int mode, char *buffer);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        if(argc == 1) printf("El comando debe ser usado así:\n\nex1_stat1.out [nombre_de_archivo]\n");
        if(argc > 2) printf("Ha ingresado muchos argumentos, solo debe ingresar el nombre del archivo luego del comando.\n");
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY, 0);
    if(fd < 0) {
        printf("La apertura del archivo %s ha fallado, intente luego.\n", argv[1]);
        exit(1);
    }
    stat_t statObj;
    stat_t *pointerStatObj = &statObj;
    //int stat(const char *pathname, struct stat *statbuf);
    //printf("Buffer size: %d\n", (int) sizeof(buffer));
    //int fileSize = read(fd, buffer, (int) sizeof(buffer));
    int statStatus = stat(argv[1], pointerStatObj);
    if(statStatus == 0) {
        printf("[stat personalizado]\nNombre de fichero: %s\n", argv[1]);
        printf("Tamaño (bytes): %ld\t", statObj.st_size);
        printf("Bloques: %ld\t", statObj.st_blocks);
        printf("Bloque E/S: %ld\t", statObj.st_blksize);
        printf("Tipo fichero: ");
        switch (statObj.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown? :c\n");             break;
        }
        printf("Nodo-i: %ld\t", statObj.st_ino);
        printf("Enlaces: %ld\n", statObj.st_nlink);
        char permisos[4];
        permisosBinario(statObj.st_mode, permisos);
        printf("Permisos: (%s / ", permisos);
        printf((S_ISDIR(statObj.st_mode)) ? "d" : "-");
        printf((statObj.st_mode & S_IRUSR) ? "r" : "-");
        printf((statObj.st_mode & S_IWUSR) ? "w" : "-");
        printf((statObj.st_mode & S_IXUSR) ? "x" : "-");
        printf((statObj.st_mode & S_IRGRP) ? "r" : "-");
        printf((statObj.st_mode & S_IWGRP) ? "w" : "-");
        printf((statObj.st_mode & S_IXGRP) ? "x" : "-");
        printf((statObj.st_mode & S_IROTH) ? "r" : "-");
        printf((statObj.st_mode & S_IWOTH) ? "w" : "-");
        printf((statObj.st_mode & S_IXOTH) ? "x" : "-");
        printf(")\t");
        printf("Uid: (%d)\tGid: (%d)\n", statObj.st_uid, statObj.st_gid);
        char accesoBuffer[100];
        char modificacionBuffer[100];
        formatearTiempo(statObj.st_atime, accesoBuffer);
        formatearTiempo(statObj.st_mtime, modificacionBuffer);
        printf("Acceso: %s", accesoBuffer);
        printf("Modificación:%s", modificacionBuffer);
        printf("Es enlace simbólico: %s\n", (S_ISLNK(statObj.st_mode)) ? "Sí" : "No");
    } else {
        printf("Hubo un error tratando de obtener el estado del fichero %s", argv[1]);
    }
    return 0;
}

void formatearTiempo(time_t tiempo, char *buffer) {
    char *bufferAux = ctime(&tiempo);
    strcpy(buffer, bufferAux);
    return;
}

void permisosBinario(int mode, char *buffer) {
    int user = 0;
    int group = 0;
    int others = 0;
    user += (mode & S_IRUSR) ? 4 : 0;
    user += (mode & S_IWUSR) ? 2 : 0;
    user += (mode & S_IXUSR) ? 1 : 0;
    group += (mode & S_IRGRP) ? 4 : 0;
    group += (mode & S_IWGRP) ? 2 : 0;
    group += (mode & S_IXGRP) ? 1 : 0;
    others += (mode & S_IROTH) ? 4 : 0;
    others += (mode & S_IWOTH) ? 2 : 0;
    others += (mode & S_IXOTH) ? 1 : 0;
    buffer[0] = S_ISDIR(mode) + '0';
    buffer[1] = user + '0';
    buffer[2] = group + '0';
    buffer[3] = others + '0';
    return;
}

