#ifndef LINEARPROBING_H_INCLUDED
#define LINEARPROBING_H_INCLUDED

#include "Image.h"
#define MAX_IMAGES 1000
#define ROWS 28
#define COLOMNS 28
#define SIZE ROWS*COLOMNS

typedef struct data_item
{
    image img;
    int key;
} data_item;
typedef struct hash_item
{
    data_item data;
    int flag; // 0: Empty   1: Full     2: Deleted
} hash_item;

image makeImage(int img[]);
void init();
int calc_key(image img);

int hashcode(image img);
void put(int key, image current_image, int var);
image get(image img);
image remove_img(image img);


#endif // LINEARPROBING_H_INCLUDED
