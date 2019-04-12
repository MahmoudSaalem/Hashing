#include <stdio.h>
#include <stdlib.h>
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
int testImagesNum;
int imagesNum;
int images_in_file[MAX_IMAGES][SIZE+1];
image *image_in_file;
arrayItem chainingtable[MAX_IMAGES];
hash_item hashtable[MAX_IMAGES];
double probingTime;
double chainingTime;

void startup();

int main()
{
    startup();
    system("title Hashing");
    cursor(0);
    mainmenu();
    return 0;
}
void startup()
{
    filesCheck();
    loadData();
    init();
    initSC();
}
