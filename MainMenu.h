#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

void setcoordinates(int x, int y);
void color(int i);
void cursor(int showFlag);

void arrowHere(int realposition, int arrowposition);
void mainmenu();
void linearProbingMenu();
void separateChainingMenu();
void addMenu(char *filePath, int var);
void removeMenu(char *filePath, int var);
void searchMenu(char *filePath, int var);


#endif // MAINMENU_H_INCLUDED
