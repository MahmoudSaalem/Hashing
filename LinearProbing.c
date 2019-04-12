#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Image.h"
#include "Files.h"
#include "LinearProbing.h"
#include "SeparateChaining.h"
#define MAX_IMAGES 1000
#define ROWS 28
#define COLOMNS 28
#define SIZE ROWS*COLOMNS

/// Global Variables
extern int images_in_file[MAX_IMAGES][SIZE+1];
extern image *image_in_file;
extern hash_item hashtable[MAX_IMAGES];
extern int imagesNum;
extern double probingTime;

image makeImage(int img[])
{
    image myImage;
    int i;
    for(i=0; i<SIZE; i++)
    {
        myImage.img_arr[i] = img[i];
    }
    myImage.ID = img[i];
    return myImage;
}
void init()
{
    clock_t start, end;
    int i, key;
    image myImage;

    start = clock();
    for(i=0; i<imagesNum; i++)
    {
        if(i<MAX_IMAGES)
        {
            myImage = makeImage(images_in_file[i]);
            key = calc_key(myImage);
            put(key, myImage, 0);
        }
        else
        {
            printf("HashTable is full, Can't insert more images!\n");
            break;
        }
    }
    end = clock();
    probingTime = (double) (end - start) / CLOCKS_PER_SEC;
}
int calc_key(image img)
{
    int i;
    int key = 0;
    int sum = 0;
    int row = 1;
    for(i=0; i<SIZE; i++)
    {
        sum += img.img_arr[i];
        if((i+1)%28==0)
        {
            key += row * sum;
            sum = 0;
            row++;
        }
    }
    return key;
}

int hashcode(image img)
{
    int key = calc_key(img);
    return (key % MAX_IMAGES);
}
void put(int key, image current_image, int var)
{
    int index = hashcode(current_image);
    int i = index;

    data_item *new_item = (data_item*) malloc(sizeof(data_item));
    new_item->key = key;
    new_item->img = current_image;

    while (hashtable[i].flag == 1)
    {
		if (hashtable[i].data.key == key)
		{
			printf("Image already exists\n");
			return;
		}
		i = (i + 1) % MAX_IMAGES;
		if (i == index)
		{
			printf("Hash table is full, cannot insert any more item\n");
			return;
		}
    }
    hashtable[i].flag = 1;
    hashtable[i].data = *new_item;
    if(var)
        printf("Image added successfully\nImage ID: %d\n", hashtable[i].data.img.ID);
}
image get(image img)
{
    int index = hashcode(img);
    int  i = index;
    int key = calc_key(img);
    image myImage;
    myImage.ID = -1;

    while (hashtable[i].flag != 0)
    {
        if (hashtable[i].flag == 1  &&  hashtable[i].data.key == key )
        {
            printf("Image found successfully\nImage ID: %d\n", hashtable[i].data.img.ID);
            return hashtable[i].data.img;
        }
        i = (i + 1) % MAX_IMAGES;
        if (i == index)
        {
            break;
        }
    }
    printf("This image does not exist!\n");
    return myImage;
}
image remove_img(image img)
{
    int index = hashcode(img);
    int  i = index;
    int key = calc_key(img);
    image myImage;

    // The same logic as the get but instead of returning the image it is flagged as deleted
    while (hashtable[i].flag != 0)
    {
        if (hashtable[i].flag == 1  &&  hashtable[i].data.key == key )
        {
            hashtable[i].flag =  2;
            printf("Image has been removed successfully\nImage ID: %d\n", hashtable[i].data.img.ID);
            return hashtable[i].data.img;

        }
        i = (i + 1) % MAX_IMAGES;
        if (i == index)
        {
            break;
        }
    }
    printf("This image does not exist \n");
    return myImage;
}
