#include "../include/image.h"

Image *newImage(int width, int height)
{
    if (width < MIN_WIDTH || width > MAX_WIDTH ||
        height < MIN_HEIGHT || height > MAX_HEIGHT)
    {
        fprintf(stderr, "%d\n", EINVAL);
        exit(EXIT_FAILURE);
    }

    Image *new_image = malloc(sizeof(Image));
    if (new_image == NULL)
    {
        fprintf(stderr, "%d\n", ENOMEM);
        exit(EXIT_FAILURE);
    }

    new_image->pixels = malloc(width * height * sizeof(Pixel));
    if (new_image->pixels == NULL)
    {
        free(new_image);
        fprintf(stderr, "%d\n", ENOMEM);
        exit(EXIT_FAILURE);
    }

    new_image->width = width;
    new_image->height = height;

    return new_image;
}

Image *deleteImage(Image *image)
{
    if (image == NULL)
        return NULL;

    free(image->pixels);
    free(image);

    return NULL;
}

Pixel setPixel(unsigned char red, unsigned char green, unsigned char blue)
{
    Pixel tmp;

    tmp.red = red;
    tmp.green = green;
    tmp.blue = blue;

    return tmp;
}

void readImage(Image *image)
{
    int nr_pixels = image->width * image->height;
    for (int i = 0; i < nr_pixels; i++)
    {
        int r, g, b;
        scanf("%d%d%d", &r, &g, &b);
        if (r < MIN_PIXEL_VALUE || r > MAX_PIXEL_VALUE ||
            g < MIN_PIXEL_VALUE || g > MAX_PIXEL_VALUE ||
            b < MIN_PIXEL_VALUE || b > MAX_PIXEL_VALUE)
        {
            fprintf(stderr, "%d\n", EINVAL);
            image = deleteImage(image);
            exit(EXIT_FAILURE);
        }

        image->pixels[i] = setPixel(r, g, b);
    }
}

void printPixel(Pixel pixel)
{
    printf("%d %d %d ", pixel.red, pixel.blue, pixel.green);
}

void printImage(Image *image)
{
    if (image == NULL)
    {
        fprintf(stderr, "%d\n", EPERM);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
            printPixel(image->pixels[i * image->width + j]);
        printf("\n");
    }
}
