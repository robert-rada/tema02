#ifndef IMAGE_H
#define IMAGE_H

#include "error.h"

Image *newImage(int widht, int height);
Image *deleteImage(Image *image);
Image *cropImage(Image *image, int start_line, int start_col, 
        int end_line, int end_col);
Pixel *getPixel(Image *image, int line, int col);
Pixel setPixel(unsigned char red, unsigned char green,
        unsigned char blue);
void readImage(Image *image);
void resizeImage(Image *image, int width, int height);
void colorRegion(Image *image, int start_col, int start_line,
        int end_col, int end_line, int r, int g, int b);
void printImage(Image *image);
void printPixel(Pixel pixel);


#endif
