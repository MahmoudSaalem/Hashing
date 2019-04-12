#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Image.h"
#include "Files.h"
#include "LinearProbing.h"
#include "SeparateChaining.h"
#include "MainMenu.h"
#define MAX_IMAGES 1000
#define ROWS 28
#define COLOMNS 28
#define SIZE ROWS*COLOMNS

/// Global Variables
extern int images_in_file[MAX_IMAGES][SIZE+1];
extern image *image_in_file;
extern hash_item hashtable[MAX_IMAGES];
extern arrayItem chainingtable[MAX_IMAGES];
extern int imagesNum;
extern double chainingTime;
int size = 0;

void initSC()
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
            putSC(key, myImage, 0);
        }
        else
        {
            printf("HashTable is full, Can't insert more images!\n");
            break;
        }
    }
    end = clock();
    chainingTime = (double) (end - start) / CLOCKS_PER_SEC;
}

int find(node *list, int key)
{
	int found = 0;
	node *temp = list;
	while (temp != NULL)
    {
		if (temp->key == key)
        {
			return found;
		}
  		temp = temp->next;
		found++;
	}
	return -1;
}

node* get_element(node *list, int index)
{
	int i = 0;
	node *temp = list;
	while (i != index)
    {
		temp = temp->next;
		i++;
	}
	return temp;
}
void putSC(int key, image current_image, int var)
{
	int index = hashcode(current_image);
	node *list = (node*) chainingtable[index].head;
	int find_index = find(list, key);
	if(find_index!=-1)
    {
        printf("Image already exists\n");
        return;
    }
    if(size==MAX_IMAGES)
    {
        printf("HashTable is full, Can't insert more images!\n");
        return;
    }
	node *item = (node*) malloc(sizeof(struct node));
	item->key = key;
	item->value = current_image;
	item->next = NULL;
	if (list == NULL)
	{
		chainingtable[index].head = item;
		chainingtable[index].tail = item;
		size++;
	}
    else
	{
		if (find_index == -1)
        {
			chainingtable[index].tail->next = item;
			chainingtable[index].tail = item;
			size++;
		}
 	}
    if(var)
        printf("Image added successfully\nImage ID: %d\n", chainingtable[index].tail->value.ID);
}
image getSC(image img, int var)
{
    image myImage;
    myImage.ID = -5; // Not Found
    int key, position;
    position = hashcode(img);
    key = calc_key(img);
    arrayItem theList = chainingtable[position];
    node *temp = theList.head;
	while (temp != NULL)
	{
        if (temp->key == key)
        {
            myImage = temp->value;
            var ? printf("Image found successfully\nImage ID: %d\n", myImage.ID) : var;
            return myImage;
        }
            temp = temp->next;
	}
    printf("Image does not exist!\n");
	return myImage;
}
image remove_imgSC(image img)
{
    image myImage;
	int index = hashcode(img);
	int key = calc_key(img);
	struct node *list = (struct node*) chainingtable[index].head;
	if (list == NULL)
    {
        printf("Image does not exist!\n");
	}
    else
    {
        int find_index = find(list, key);
        if (find_index == -1)
        {
            printf("Image does not exist!\n");
		}
        else
        {
 			struct node *temp = list;
			if (temp->key == key)
            {
                myImage = temp->value;
  				chainingtable[index].head = temp->next;
  				size--;
                printf("Image has been removed successfully\nImage ID: %d\n", myImage.ID);
				return myImage;
			}
			while (temp->next->key != key)
            {
 				temp = temp->next;
			}
  			if (chainingtable[index].tail == temp->next)
            {
                myImage = temp->value;
				temp->next = NULL;
				chainingtable[index].tail = temp;
			}
            else
            {
                myImage = temp->value;
				temp->next = temp->next->next;
			}
            printf("Image has been removed successfully\nImage ID: %d\n", myImage.ID);
		}
	}
	return myImage;
}
