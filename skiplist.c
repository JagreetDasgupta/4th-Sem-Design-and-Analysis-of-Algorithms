#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEVEL 6 // Maximum level of the skip list

// Node structure
typedef struct Node
{
	int key;
	int value;
	struct Node *forward[MAX_LEVEL + 1];
} Node;
// Skip list structure
typedef struct SkipList
{
	int level;
	Node *header;
} SkipList;

// Function prototypes
SkipList *createSkipList();
Node *createNode(int key, int value, int level);
int randomLevel();
bool insert(SkipList *list, int key, int value);
bool delete(SkipList *list, int key);
Node *search(SkipList *list, int key);
void display(SkipList *list);

// Main function
int main()
{
	SkipList *list = createSkipList();
	insert(list, 3, 30);
	insert(list, 6, 60);
	insert(list, 9, 90);
	insert(list, 2, 20);
	insert(list, 5, 50);
	printf("Skip List after insertion:\n");
	display(list);
	delete (list, 6);
	printf("\nSkip List after deletion of key 6:\n");
	display(list);
	Node *result = search(list, 3);
	if (result)
		printf("\nKey 3 found with value %d\n", result->value);
	else
		printf("\nKey 3 not found\n");
	return 0;
}

// Create a new skip list
SkipList *createSkipList()
{
	SkipList *list = (SkipList *)malloc(sizeof(SkipList));
	list->level = 0;
	list->header = createNode(-1, -1, MAX_LEVEL);
	for (int i = 0; i <= MAX_LEVEL; i++)
	list->header->forward[i] = NULL;
	return list;
}

// Create a new node
Node *createNode(int key, int value, int level)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->key = key;
	newNode->value = value;
	for (int i = 0; i <= level; i++)
	newNode->forward[i] = NULL;
	return newNode;
}

// Generate a random level for a node
int randomLevel()
{
	int level = 0;
	while (rand() < RAND_MAX / 2 && level < MAX_LEVEL)
	level++;
	return level;
}

// Insert a key-value pair into the skip list
bool insert(SkipList *list, int key, int value)
{
	Node *update[MAX_LEVEL + 1];
	Node *current = list->header;
	for (int i = list->level; i >= 0; i--)
	{
		while (current->forward[i] != NULL && current->forward[i]->key < key)
		current = current->forward[i];
		update[i] = current;
	}
	current = current->forward[0];
	if (current == NULL || current->key != key)
	{
		int newLevel = randomLevel();
		if (newLevel > list->level)
		{
			for (int i = list->level + 1; i <= newLevel; i++)
				update[i] = list->header;
				list->level = newLevel;
		}
		Node *newNode = createNode(key, value, newLevel);
		for (int i = 0; i <= newLevel; i++)
		{
			newNode->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = newNode;
		}
		return true; // Insertion successful
	}
	return false; // Key already exists
}

// Delete a key from the skip list
bool delete(SkipList *list, int key)
{
	Node *update[MAX_LEVEL + 1];
	Node *current = list->header;
	for (int i = list->level; i >= 0; i--)
	{
		while (current->forward[i] != NULL && current->forward[i]->key < key)
			current = current->forward[i];
			update[i] = current;
	}
	current = current->forward[0];
	if (current != NULL && current->key == key)
	{
		for (int i = 0; i <= list->level; i++)
		{
			if (update[i]->forward[i] != current)
			break;
			update[i]->forward[i] = current->forward[i];
		}
		free(current);
		while (list->level > 0 && list->header->forward[list->level] == NULL)
			list->level--;
		return true; // Deletion successful
	}
	return false; // Key not found
}
// Search for a key in the skip list
Node *search(SkipList *list, int key)
{
	Node *current = list->header;
	for (int i = list->level; i >= 0; i--)
	{
		while (current->forward[i] != NULL && current->forward[i]->key < key)
		current = current->forward[i];
	}
	current = current->forward[0];
	if (current != NULL && current->key == key)
		return current; // Key found
	return NULL; // Key not found
}

// Display the skip list
void display(SkipList *list)
{
	printf("Level 0: ");
	Node *current = list->header->forward[0];
	while (current != NULL)
	{
		printf("(%d,%d) ", current->key, current->value);
		current = current->forward[0];
	}
	printf("\n");
}
