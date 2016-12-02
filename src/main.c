#include "../include/image.h"

int main()
{
    Image *image = NULL;

    int running = 1;
    while (running)
    {
        int query_type;
        scanf("%d", &query_type);

        switch (query_type)
        {
            case 0:
                image = deleteImage(image);
                running = 0;
                break;
            case 1:
            {
                int width, height;
                scanf("%d%d", &width, &height);

                image = deleteImage(image);
                image = newImage(width, height);
                readImage(image);

                break;
            }
            case 2:
            {
                int start_line, end_line;
                int start_col, end_col;

                scanf("%d%d", &start_col, &start_line);
                scanf("%d%d", &end_col, &end_line);
                
                image = cropImage(image, start_line, start_col,
                        end_line, end_col);

                break;
            }
            case 3:
            {
                int width, height;
                scanf("%d%d", &width, &height);

                image = resizeImage(image, width, height);

                break;
            }
            case 4:
            {
                int start_line, end_line;
                int start_col, end_col;
                int r, g, b;

                scanf("%d%d", &start_col, &start_line);
                scanf("%d%d", &end_col, &end_line);
                scanf("%d%d%d", &r, &g, &b);

                colorRegion(image, start_col, start_line, end_col, end_line,
                        r, g, b);

                break;
            }
            case 5:
            {
                int nr;
                scanf("%d", &nr);

                blurImage(image, nr);

                break;
            }
            case 6:
            {
                int nr;
                scanf("%d", &nr);

                image = rotateClockwise(image, nr);

                break;
            }
            case 7:
            {
                int start_col, start_line;
                int r, g, b;

                scanf("%d%d", &start_col, &start_line);
                scanf("%d%d%d", &r, &g, &b);

                if (start_col < 0 || start_col >= image->width ||
                    start_line < 0 || start_line >= image->height ||
                    r < MIN_PIXEL_VALUE || r > MAX_PIXEL_VALUE ||
                    g < MIN_PIXEL_VALUE || g > MAX_PIXEL_VALUE ||
                    b < MIN_PIXEL_VALUE || b > MAX_PIXEL_VALUE)
                {
                    errorInvalid(image);
                }

                fill(image, start_line, start_col, setPixel(r, g, b));

                break;
            }
            case 8:
                printImage(image);

                break;
            default:
                errorPerm(image);
        } 
    } 

    return 0;
}
