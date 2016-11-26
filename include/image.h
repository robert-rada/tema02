#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <stdio.h>
#include "const.h"

typedef struct 
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

typedef struct 
{
    int width;
    int height;
    Pixel *pixels;
} Image;

Image *newImage(int widht, int height);
Image *deleteImage(Image *image);
Pixel setPixel(unsigned char red, unsigned char green, unsigned char blue);
void readImage(Image *image);
void printImage(Image *image);

#endif
