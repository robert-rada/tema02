#include "../include/image.h"

void errorPerm(Image *image)
{
    deleteImage(image);
    fprintf(stderr, "%d\n", EPERM);
    exit(EXIT_FAILURE);
}

void errorInvalid(Image *image)
{
    deleteImage(image);
    fprintf(stderr, "%d\n", EINVAL);
    exit(EXIT_FAILURE);
}

void errorMemory(Image *image)
{
    deleteImage(image);
    fprintf(stderr, "%d\n", ENOMEM);
    exit(EXIT_FAILURE);
}
