#ifndef IMAGE_H
#define IMAGE_H

#include "error.h"

Image *newImage(int widht, int height);
Image *deleteImage(Image *image);
Image *cropImage(Image *image, int start_line, int start_col, 
        int end_line, int end_col);
Image *rotateClockwise(Image *image, int nr);
Image *rotateImage(Image *image, int nr);
Pixel *getPixel(Image *image, int line, int col);
Pixel setPixel(unsigned char red, unsigned char green,
        unsigned char blue);
Pixel pixelAverage(Image *image, int line, int col);
void readImage(Image *image);
Image *resizeImage(Image *image, int width, int height);
void colorRegion(Image *image, int start_col, int start_line,
        int end_col, int end_line, int r, int g, int b);
void blurImage(Image *image, int nr);
void printImage(Image *image);
void printPixel(Pixel pixel);
void swapPointers(Pixel **a, Pixel **b);
void fill(Image *image, short line, short col, Pixel pixel);


#endif
