#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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
extern int testImagesNum;
extern int images_in_file[MAX_IMAGES][SIZE+1];
extern image *image_in_file;
extern hash_item hashtable[MAX_IMAGES];
extern int imagesNum;
extern double probingTime;
extern double chainingTime;

void setcoordinates(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void color(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
void cursor(int showFlag)
{
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void arrowHere(int realposition, int arrowposition)
{
    if ( realposition == arrowposition)
    {
        color(15);
    }
    else
    {
        color(8);
    }
}
void mainmenu()
{
    system("CLS");
    int position = 1;
    char Keypressed = 0;
    setcoordinates(0,0);
    color(10);
    printf("Use Arrows");
    while(Keypressed!=(char)13)
    {
        setcoordinates(0,1);
        arrowHere(1,position);
        printf("1.Linear Probing");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Separate Chaining");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Time");
        setcoordinates(0,4);
        arrowHere(4,position);
        printf("4.Exit");
        Keypressed=_getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 4)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    if(position==1)
        linearProbingMenu();
    else if(position == 2)
        separateChainingMenu();
    else if(position == 3)
    {
        system("CLS");
        color(15);
        printf("Time taken for Linear Probing is %lf seconds\n", probingTime);
        printf("Time taken for Separate Chaining is %lf seconds\n\n", chainingTime);
        color(8);
        printf("press any key to continue..");
        Keypressed = _getch();
        mainmenu();
    }
    else if(position == 4)
    {
        color(8);
        printf("\n");
        exit(1);
    }
}
void linearProbingMenu()
{
    system("CLS");
    int position = 1;
    char Keypressed = 0;
    setcoordinates(0,0);
    color(10);
    printf("Linear Probing");
    while(Keypressed!=(char)13)
    {
        setcoordinates(0,1);
        arrowHere(1,position);
        printf("1.Add");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Remove");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Search");
        setcoordinates(0,4);
        arrowHere(4,position);
        printf("4.Back");
        Keypressed=_getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 4)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    if(position==1)
    {
        system("CLS");
        color(15);
        char filePath[20];
        printf("Enter the name of the file containing the images: ");
        scanf("%s", filePath);
        system("CLS");
        if(loadImage(filePath))
        {
            addMenu(filePath, 1);
        }
    }
    else if(position == 2)
    {
        system("CLS");
        color(15);
        char filePath[20];
        printf("Enter the name of the file containing the images: ");
        scanf("%s", filePath);
        system("CLS");
        if(loadImage(filePath))
        {
            removeMenu(filePath, 1);
        }
    }
    else if(position == 3)
    {
        system("CLS");
        color(15);
        char filePath[20];
        printf("Enter the name of the file containing the images: ");
        scanf("%s", filePath);
        system("CLS");
        if(loadImage(filePath))
        {
            searchMenu(filePath, 1);
        }
    }
    else if(position == 4)
        mainmenu();
    color(8);
    printf("\nPress any key to continue..");
    Keypressed=_getch();
    linearProbingMenu();
}
void addMenu(char *filePath, int var)
{
    system("CLS");
    int i;
    int position = 1;
    char Keypressed = 0;
    setcoordinates(0,0);
    color(10);
    printf("Add");
    while(Keypressed!=(char)13)
    {
        for(i=1; i<=testImagesNum; i++)
        {
            setcoordinates(0,i);
            arrowHere(i,position);
            printf("%d.Image %d", i, i);
        }
        setcoordinates(0,i);
        arrowHere(i,position);
        printf("%d.Back", i);
        Keypressed=_getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != i)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    for(i=1; i<=testImagesNum; i++)
    {
        if(position==i)
        {
            system("CLS");
            color(15);
            if(loadImage(filePath))
            {
                int key = calc_key(image_in_file[i-1]);
                var ? put(key, image_in_file[i-1], 1) : putSC(key, image_in_file[i-1], 1);
            }
        }
    }
    if(position==i)
        linearProbingMenu();
    color(8);
    printf("\nPress any key to continue..");
    Keypressed=_getch();
    var ? linearProbingMenu() : separateChainingMenu();
}
void removeMenu(char *filePath, int var)
{
    system("CLS");
    int i;
    int position = 1;
    char Keypressed = 0;
    setcoordinates(0,0);
    color(10);
    printf("Remove");
    while(Keypressed!=(char)13)
    {
        for(i=1; i<=testImagesNum; i++)
        {
            setcoordinates(0,i);
            arrowHere(i,position);
            printf("%d.Image %d", i, i);
        }
        setcoordinates(0,i);
        arrowHere(i,position);
        printf("%d.Back", i);
        Keypressed=_getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != i)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    for(i=1; i<=testImagesNum; i++)
    {
        if(position==i)
        {
            system("CLS");
            color(15);
            if(loadImage(filePath))
            {
                var ? remove_img(image_in_file[i-1]) : remove_imgSC(image_in_file[i-1]);
            }
        }
    }
    if(position==i)
        linearProbingMenu();
    color(8);
    printf("\nPress any key to continue..");
    Keypressed=_getch();
    var ? linearProbingMenu() : separateChainingMenu();
}
void searchMenu(char *filePath, int var)
{
    system("CLS");
    int i;
    int position = 1;
    char Keypressed = 0;
    setcoordinates(0,0);
    color(10);
    printf("Search");
    while(Keypressed!=(char)13)
    {
        for(i=1; i<=testImagesNum; i++)
        {
            setcoordinates(0,i);
            arrowHere(i,position);
            printf("%d.Image %d", i, i);
        }
        setcoordinates(0,i);
        arrowHere(i,position);
        printf("%d.Back", i);
        Keypressed=_getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != i)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    for(i=1; i<=testImagesNum; i++)
    {
        if(position==i)
        {
            system("CLS");
            color(15);
            if(loadImage(filePath))
            {
                var ? get(image_in_file[i-1]) : getSC(image_in_file[i-1], 1);
            }
        }
    }
    if(position==i)
        linearProbingMenu();
    color(8);
    printf("\nPress any key to continue..");
    Keypressed=_getch();
    var ? linearProbingMenu() : separateChainingMenu();
}
void separateChainingMenu()
{
    system("CLS");
    int position = 1;
    char Keypressed = 0;
    setcoordinates(0,0);
    color(10);
    printf("Separate Chaining");
    while(Keypressed!=(char)13)
    {
        setcoordinates(0,1);
        arrowHere(1,position);
        printf("1.Add");
        setcoordinates(0,2);
        arrowHere(2,position);
        printf("2.Remove");
        setcoordinates(0,3);
        arrowHere(3,position);
        printf("3.Search");
        setcoordinates(0,4);
        arrowHere(4,position);
        printf("4.Back");
        Keypressed=_getch();
        if(Keypressed==(char)224)
        {
            Keypressed = _getch();
            if(Keypressed == (char)80 && position != 4)
                position++;
            else if(Keypressed == (char)72 && position != 1)
                position--;
            else
                position = position;
        }
    }
    if(position==1)
    {
        system("CLS");
        color(15);
        char filePath[20];
        printf("Enter the name of the file containing the images: ");
        scanf("%s", filePath);
        system("CLS");
        if(loadImage(filePath))
        {
            addMenu(filePath, 0);
        }
    }
    else if(position == 2)
    {
        system("CLS");
        color(15);
        char filePath[20];
        printf("Enter the name of the file containing the images: ");
        scanf("%s", filePath);
        system("CLS");
        if(loadImage(filePath))
        {
            removeMenu(filePath, 0);
        }
    }
    else if(position == 3)
    {
        system("CLS");
        color(15);
        char filePath[20];
        printf("Enter the name of the file containing the images: ");
        scanf("%s", filePath);
        system("CLS");
        if(loadImage(filePath))
        {
            searchMenu(filePath, 0);
        }
    }
    else if(position == 4)
        mainmenu();
    color(8);
    printf("\nPress any key to continue..");
    Keypressed=_getch();
    separateChainingMenu();
}
