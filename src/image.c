#include "../include/image.h"

Image *newImage(int width, int height)
{
    if (width < MIN_WIDTH || width > MAX_WIDTH ||
        height < MIN_HEIGHT || height > MAX_HEIGHT)
    {
        fprintf(stderr, "%d\n", EINVAL);
        exit(EXIT_FAILURE);
    }

    Image tmp;
    Image *new_image = malloc(sizeof(tmp));
    if (new_image == NULL)
    {
        fprintf(stderr, "%d\n", ENOMEM);
        exit(EXIT_FAILURE);
    }

    new_image->pixels = malloc(height * sizeof(Pixel*));
    if (new_image->pixels == NULL)
        errorMemory(new_image);

    for (int i = 0; i < height; i++)
    {
        new_image->pixels[i] = malloc(width * sizeof(Pixel));
        if (new_image->pixels[i] == NULL)
            errorMemory(new_image);
    }

    new_image->width = width;
    new_image->height = height;

    return new_image;
}

Image *deleteImage(Image *image)
{
    if (image == NULL)
        return NULL;

    for (int i = 0; i < image->height; i++)
        free(image->pixels[i]);
    free(image->pixels);
    free(image);

    return NULL;
}

/*
Pixel *getPixel(Image *image, int line, int col)
{
    return image->pixels + line * image->width + col;
}
*/

Image *cropImage(Image *image, int start_line, int start_col,
        int end_line, int end_col)
{
    if (image == NULL)
    {
        fprintf(stderr, "%d\n", EPERM);
        exit(EXIT_FAILURE);
    }
    if (start_line < 0 || start_line >= image->height ||
        start_col < 0 || start_col >= image->width ||
        end_line < 0 || end_line >= image->height ||
        end_col < 0 || end_col >= image->width ||
        start_line > end_line ||
        start_col > end_col)
    {
        image = deleteImage(image);
        fprintf(stderr, "%d\n", EINVAL);
        exit(EXIT_FAILURE);
    }

    Image *new_image = newImage(end_col - start_col + 1,
                                end_line - start_line + 1);

    for (int line = start_line; line <= end_line; line++)
    {
        memcpy(&new_image->pixels[line-start_line][0],
               &image->pixels[line][start_col],
               sizeof(Pixel) * (end_col - start_col + 1));
    }

    deleteImage(image);

    return new_image;
}

void resizeImage(Image *image, int width, int height)
{
    if (width < MIN_WIDTH || width > MAX_WIDTH ||
            height < MIN_HEIGHT || height > MAX_HEIGHT)
        errorPerm(image);

    for (int i = height; i < image->height; i++)
        free(image->pixels[i]);
    image->pixels = realloc(image->pixels, height * sizeof(Pixel*));
    if (image->pixels == NULL)
        errorMemory(image);

    for (int i = 0; i < height; i++)
    {
        image->pixels[i] = realloc(image->pixels[i], width * sizeof(Pixel));
        if (image->pixels[i] == NULL)
            errorMemory(image);
    }

    for (int i = image->height; i < height; i++)
        memset(image->pixels[i], 255, width * sizeof(Pixel));
    if (width > image->width)
        for (int i = 0; i < image->height; i++)
        {
            memset(&image->pixels[i][image->width], 255, 
                    (width - image->width) * sizeof(Pixel));
        }

    image->width = width;
    image->height = height;
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
    for (int i = 0; i < image->height; i++)
        for (int j = 0; j < image->width; j++)
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

            image->pixels[i][j] = setPixel(r, g, b);
        }
}

void printPixel(Pixel pixel)
{
    printf("%d %d %d ", pixel.red, pixel.green, pixel.blue);
}

void printImage(Image *image)
{
    if (image == NULL)
    {
        fprintf(stderr, "%d\n", EPERM);
        exit(EXIT_FAILURE);
    }

    printf("%d %d\n", image->width, image->height);

    for (int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
            printPixel(image->pixels[i][j]);
        printf("\n");
    }
}
