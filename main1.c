#include "fdf.h"

int main (int argc, char **argv)
{
    int fd = open(argv[1],O_RDONLY | 0666);
     if (fd == -1)
    {
        printf("Error\n");
        exit(1);
    }

    holishiiit(fd);
}