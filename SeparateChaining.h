#ifndef SEPARATECHAINING_H_INCLUDED
#define SEPARATECHAINING_H_INCLUDED

typedef struct node
{
	int key;
	image value;
	struct node *next;
} node;
typedef struct arrayItem
{
	struct node *head;
	struct node *tail;
} arrayItem;

void initSC();
void putSC(int key, image current_image, int var);
image getSC(image img, int var);
image remove_imgSC(image img);


#endif // SEPARATECHAINING_H_INCLUDED
