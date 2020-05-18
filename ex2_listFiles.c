#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>

typedef struct stat stat_t;
void permisosBinario(int mode, char *buffer);

int main(int argc, char *argv[])
{
  DIR *dir;
  stat_t statObj;
  stat_t *pointerStatObj = &statObj;
  struct dirent *file;

  switch (argc)
  {
  case 1:
    //Para listar los archivos del current directory
    dir = opendir(".");
    while ((file = readdir(dir)) != NULL)
    {
      printf("%s\n", file->d_name);
    }
    printf("\n");
    closedir(dir);
    return 0;
    break;
  case 2:

    if (strcmp(argv[1], "-l") == 0)
    { // Listar los archivos y su info del current directory

      dir = opendir(".");
      while ((file = readdir(dir)) != NULL)
      {
        printf("%s\n", file->d_name);
        int statStatus = stat(file->d_name, pointerStatObj);
        if (statStatus == 0)
        {
          printf("[Dato del fichero]\nNombre de fichero: %s\n", file->d_name);
          printf("Tamaño (bytes): %ld\t", statObj.st_size);
          printf("Bloques: %ld\t", statObj.st_blocks);
          printf("Bloque E/S: %ld\t", statObj.st_blksize);
          printf("Tipo fichero: ");
          switch (statObj.st_mode & S_IFMT)
          {
          case S_IFBLK:
            printf("block device\n");
            break;
          case S_IFCHR:
            printf("character device\n");
            break;
          case S_IFDIR:
            printf("directory\n");
            break;
          case S_IFIFO:
            printf("FIFO/pipe\n");
            break;
          case S_IFLNK:
            printf("symlink\n");
            break;
          case S_IFREG:
            printf("regular file\n");
            break;
          case S_IFSOCK:
            printf("socket\n");
            break;
          default:
            printf("unknown? :c\n");
            break;
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
        }
      }
      printf("\n");
      closedir(dir);
      return 0;
    }
    else
    { // LIstar los nombres del directorio que se esta llamando
      dir = opendir(argv[1]);
      while ((file = readdir(dir)) != NULL)
      {
        printf("%s\n", file->d_name);
      }
      printf("\n");
      closedir(dir);
      return 0;
    }
    break;
  case 3:
    if (strcmp(argv[1], "-l") == 0)
    { // Listar los archivos y sus datos del directorio dado

      dir = opendir(argv[2]);
      while ((file = readdir(dir)) != NULL)
      {
        printf("%s\n", file->d_name);
        int statStatus = stat(file->d_name, pointerStatObj);
        if (statStatus == 0)
        {
          printf("[Dato del fichero]\nNombre de fichero: %s\n", file->d_name);
          printf("Tamaño (bytes): %ld\t", statObj.st_size);
          printf("Bloques: %ld\t", statObj.st_blocks);
          printf("Bloque E/S: %ld\t", statObj.st_blksize);
          printf("Tipo fichero: ");
          switch (statObj.st_mode & S_IFMT)
          {
          case S_IFBLK:
            printf("block device\n");
            break;
          case S_IFCHR:
            printf("character device\n");
            break;
          case S_IFDIR:
            printf("directory\n");
            break;
          case S_IFIFO:
            printf("FIFO/pipe\n");
            break;
          case S_IFLNK:
            printf("symlink\n");
            break;
          case S_IFREG:
            printf("regular file\n");
            break;
          case S_IFSOCK:
            printf("socket\n");
            break;
          default:
            printf("unknown? :c\n");
            break;
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
        }
      }
      printf("\n");
      closedir(dir);
      return 0;
    }
    break;
  
  default:
    printf("solo 3 argumentos");
  }
}

void permisosBinario(int mode, char *buffer)
{
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