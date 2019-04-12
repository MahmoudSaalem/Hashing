#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#define ROWS 28
#define COLOMNS 28
#define SIZE ROWS*COLOMNS

typedef struct image
{
    int img_arr[SIZE];
    int ID;
} image;


#endif // IMAGE_H_INCLUDED
