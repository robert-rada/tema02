#ifndef IMAGE_H
#define IMAGE_H

#include "error.h"

Image *newImage(int widht, int height);
Image *deleteImage(Image *image);
Image *cropImage(Image *image, int start_line, int start_col, 
        int end_line, int end_col);
Image *resizeImage(Image *image, int width, int height);
Pixel *getPixel(Image *image, int line, int col);
Pixel setPixel(unsigned char red, unsigned char green,
        unsigned char blue);
void readImage(Image *image);
void printImage(Image *image);
void printPixel(Pixel pixel);


#endif
