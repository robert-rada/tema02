#include "../include/image.h"

int main()
{
    Image *image = NULL;

    while (1)
    {
        int query_type;
        scanf("%d", &query_type);

        switch (query_type)
        {
            case 1:
            {
                int width, height;
                scanf("%d%d", &width, &height);

                image = newImage(width, height);
                readImage(image);

                break;
            }
            case 8:
                printImage(image);

                break;
        } 
    } 

    return 0;
}
