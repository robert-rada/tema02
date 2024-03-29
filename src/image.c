#include "../include/image.h"

Image *newImage(int width, int height)
{
    if (width < MIN_WIDTH || width > MAX_WIDTH ||
        height < MIN_HEIGHT || height > MAX_HEIGHT)
    {
        errorInvalid(NULL);
    }

    Image *new_image = malloc(sizeof(Image));
    if (new_image == NULL)
        errorMemory(NULL);

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

Image *cropImage(Image *image, int start_line, int start_col,
        int end_line, int end_col)
{
    if (image == NULL)
        errorPerm(NULL);

    if (start_line < 0 || start_line >= image->height ||
        start_col < 0 || start_col >= image->width ||
        end_line < 0 || end_line >= image->height ||
        end_col < 0 || end_col >= image->width ||
        start_line > end_line ||
        start_col > end_col)
    {
        errorInvalid(image);
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

Image *rotateClockwise(Image *image, int nr)
{
    return rotateImage(image, 4 - nr);
}

Image *rotateImage(Image *image, int nr)
{
    if (image == NULL)
        errorPerm(NULL);
    if (nr < 1 || nr > 3)
        errorInvalid(image);

    if (nr > 1)
    {
        for (int i = 1; i <= nr; i++)
            image = rotateImage(image, 1);

        return image;
    }

    Image *new_image = newImage(image->height, image->width);
    for (int line = 0; line < new_image->height; line++)
        for (int col = 0; col < new_image->width; col++)
            new_image->pixels[line][col] = 
                image->pixels[col][image->width - line - 1];

    image = deleteImage(image);

    return new_image;
}

Image *resizeImage(Image *image, int width, int height)
{
    if (image == NULL)
        errorPerm(NULL);

    if (width < MIN_WIDTH || width > MAX_WIDTH ||
            height < MIN_HEIGHT || height > MAX_HEIGHT)
        errorInvalid(image);

    Image *new_image = newImage(width, height);

    if (width >= image->width)
    {
        for (int i = 0; i < height && i < image->height; i++)
            memcpy(new_image->pixels[i], image->pixels[i], 
                    image->width * sizeof(Pixel));
    }
    else
    {
        for (int i = 0; i < height && i < image->height; i++)
            memcpy(new_image->pixels[i], image->pixels[i],
                    width * sizeof(Pixel));
    }

    for (int i = image->height; i < height; i++)
        memset(new_image->pixels[i], 255, width * sizeof(Pixel));
    if (width > image->width)
        for (int i = 0; i < image->height && i < height; i++)
        {
            memset(&new_image->pixels[i][image->width], 255, 
                    (width - image->width) * sizeof(Pixel));
        }

    deleteImage(image);

    return new_image;
}

Pixel setPixel(unsigned char red, unsigned char green, unsigned char blue)
{
    Pixel tmp;

    tmp.red = red;
    tmp.green = green;
    tmp.blue = blue;

    return tmp;
}

Pixel pixelAverage(Image *image, int line, int col)
{
    int nr = 0;
    int r = 0, g = 0, b = 0;

    if (line != 0)
    {
        nr++;
        r += image->pixels[line-1][col].red;
        g += image->pixels[line-1][col].green;
        b += image->pixels[line-1][col].blue;
    }
    if (line != image->height-1)
    {
        nr++;
        r += image->pixels[line+1][col].red;
        g += image->pixels[line+1][col].green;
        b += image->pixels[line+1][col].blue;
    }
    if (col != 0)
    {
        nr++;
        r += image->pixels[line][col-1].red;
        g += image->pixels[line][col-1].green;
        b += image->pixels[line][col-1].blue;
    }
    if (col != image->width-1)
    {
        nr++;
        r += image->pixels[line][col+1].red;
        g += image->pixels[line][col+1].green;
        b += image->pixels[line][col+1].blue;
    }

    if (nr == 0)
        return image->pixels[line][col];

    return setPixel(r / nr, g / nr, b / nr);
}

void swapPointers(Pixel **a, Pixel **b)
{
    void *tmp = *a;
    *a = *b;
    *b = tmp;
}

void blurImage(Image *image, int nr)
{
    if (image == NULL)
        errorPerm(NULL);
    if (nr > 1)
    {
        for (int i = 1; i <= nr; i++)
            blurImage(image, 1);
        return;
    }
    
    if (nr == 0)
        return;
    if (nr < 0 || nr > 2000)
        errorInvalid(image);

    Pixel *new_line1 = malloc(image->width * sizeof(Pixel));
    if (new_line1 == NULL)
        errorMemory(image);
    Pixel *new_line2 = malloc(image->width * sizeof(Pixel));
    if (new_line2 == NULL)
        errorMemory(image);

    for (int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
            new_line2[j] = pixelAverage(image, i, j);

        if (i > 0)
            swapPointers(&image->pixels[i-1], &new_line1);
        swapPointers(&new_line1, &new_line2);
    }
    swapPointers(&image->pixels[image->height-1], &new_line1);

    free(new_line1);
    free(new_line2);
}

void readImage(Image *image)
{
    if (image == NULL)
        errorPerm(NULL);

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

void colorRegion(Image *image, int start_col, int start_line,
        int end_col, int end_line, int r, int g, int b)
{
    if (image == NULL)
        errorPerm(NULL);

    if (r < MIN_PIXEL_VALUE || r > MAX_PIXEL_VALUE ||
        g < MIN_PIXEL_VALUE || g > MAX_PIXEL_VALUE ||
        b < MIN_PIXEL_VALUE || b > MAX_PIXEL_VALUE ||
        start_line > end_line || start_col > end_col ||
        image->width < MIN_WIDTH || image->width > MAX_WIDTH ||
        image->height < MIN_HEIGHT || image->height > MAX_HEIGHT)
    {
        errorInvalid(image);
    }

    for (int line = start_line; line <= end_line; line++)
        for (int col = start_col; col <= end_col; col++)
            image->pixels[line][col] = setPixel(r, g, b);
}

void printPixel(Pixel pixel)
{
    printf("%d %d %d ", pixel.red, pixel.green, pixel.blue);
}

void printImage(Image *image)
{
    if (image == NULL)
        errorPerm(NULL);

    printf("%d %d\n", image->width, image->height);

    for (int i = 0; i < image->height; i++)
    {
        for (int j = 0; j < image->width; j++)
            printPixel(image->pixels[i][j]);
        printf("\n");
    }
}

int pixelCompare(Pixel a, Pixel b)
{
    if (a.red == b.red && a.green == b.green && a.blue == b.blue)
        return 1;
    return 0;
}

void fill(Image *image, short line, short col, Pixel pixel)
{
    Pixel original_color = image->pixels[line][col];
    image->pixels[line][col] = pixel;

    if (line > 0)
    {
        if (pixelCompare(image->pixels[line-1][col], original_color))
            fill(image, line-1, col, pixel);
    }
    if (line < image->height)
    {
        if (pixelCompare(image->pixels[line+1][col], original_color))
            fill(image, line+1, col, pixel);
    }
    if (col > 0)
    {
        if (pixelCompare(image->pixels[line][col-1], original_color))
            fill(image, line, col-1, pixel);
    }
    if (col < image->width)
    {
        if (pixelCompare(image->pixels[line][col+1], original_color))
            fill(image, line, col+1, pixel);
    }
}
