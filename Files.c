#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "Files.h"
#include "LinearProbing.h"
#include "SeparateChaining.h"
#define MAX_IMAGES 1000
#define ROWS 28
#define COLOMNS 28
#define SIZE ROWS*COLOMNS

/// Global Variables
extern int testImagesNum;
extern int images_in_file[MAX_IMAGES][SIZE+1];
extern image *image_in_file;
extern hash_item hashtable[MAX_IMAGES];
extern int imagesNum;

void filesCheck()
{
    FILE *f1;
    f1 = fopen("MNIST-data(datastructures_assignment3)_whitespace.txt", "r");
    //f2 = fopen("image.txt", "r");
    if(!f1)
    {
        printf("Missing Files!\n");
        fclose(f1);
        //fclose(f2);
        exit(1);
    }
    fclose(f1);
    //fclose(f2);
}
void loadData()
{
    FILE *f1;
    f1 = fopen("MNIST-data(datastructures_assignment3)_whitespace.txt", "r");
    int i, j;
    while(!feof(f1))
    {
        for(i=0; i<MAX_IMAGES; i++)
        {
            for(j=0; j<SIZE; j++)
            {
                fscanf(f1, "%d ", &images_in_file[i][j]);
            }
            fscanf(f1, "%d\n", &images_in_file[i][j]);
        }
    }
    fclose(f1);
    imagesNum = imagesNumInFile("MNIST-data(datastructures_assignment3)_whitespace.txt");
}
int loadImage(char *filePath)
{
    int i, j;
    int temp[SIZE+1];
    FILE *f1;
    f1 = fopen(filePath, "r");
    if(!f1)
    {
        printf("File does not exist!\n");
        fclose(f1);
        return 0;
    }
    testImagesNum = imagesNumInFile(filePath);
    if(!testImagesNum)
    {
        printf("File is empty!\n");
        return 0;
    }
    image_in_file = (image*) malloc(sizeof(image)*testImagesNum);
    while(!feof(f1))
    {
        for(i=0; i<testImagesNum; i++)
        {
            for(j=0; j<SIZE; j++)
            {
                (j == SIZE-1) ? fscanf(f1, "%d", &temp[j]) : fscanf(f1, "%d ", &temp[j]);
            }
            fscanf(f1, "\n");
            temp[j] = -1; // ID of a loaded image is set to -1
            image_in_file[i] = makeImage(temp);
        }
    }
    fclose(f1);
    return 1;
}
int imagesNumInFile(char *filePath)
{
    int ch=0;
    int lines=0;
    FILE *processesFile;
    processesFile = fopen(filePath, "r");
    lines++;
    while ((ch = fgetc(processesFile)) != EOF)
    {
      if (ch == '\n')
            lines++;
    }
    fclose(processesFile);
    return lines;
}
