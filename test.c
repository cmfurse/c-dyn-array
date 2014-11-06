#include <stdio.h>
#include <string.h>
#include "dynarray.h"

typedef struct node
{
	char name[16];
	char description[32];
	int intval;
} NODE;

int main(void)
{
	DYN_ARRAY array;
	
	// initialize the array with the size of each entry
	init_array(&array, sizeof(NODE));
	
	// add some objects to the array
	NODE node1 = { .name = "node1", .description = "I am node #1", .intval = 5 };
	NODE node2 = { .name = "node2", .description = "I am node #2", .intval = 10 };
	NODE node3 = { .name = "node3", .description = "I am node #3", .intval = 2 };
	NODE node4 = { .name = "node4", .description = "I am node #4", .intval = 1 };
	NODE node5 = { .name = "node5", .description = "I am node #5", .intval = 11 };
	
	add_to_array(&array, node1);
	add_to_array(&array, node2);
	add_to_array(&array, node3);
	add_to_array(&array, node4);
	add_to_array(&array, node5);
	
	print_array(&array);
	
	// use custom sort
	sort_array(&array, compare_intval);
	
	// loop through array and print the name
	printf("After intval sort:\n");
	print_array(&array);
	
	// remove the first node
	remove_from_array(&array, 0);
	printf("After remove:\n");
	print_array(&array);
	
	// resort using alternate sort method
	sort_array(&array, compare_name);
	printf("After name sort:\n");
	print_array(&array);
	
	clear_array(&array);
	printf("array length after clear is: %d", array.count);
	
	// free the memory in the array
	free_array(&array);
	
    return 0;
}

void print_array(DYN_ARRAY *arrayPtr)
{
	int i;
	NODE *nodePtr;
	
	for (i=0; i<arrayPtr->count; i++)
	{
		nodePtr = (NODE *)get_from_array(arrayPtr, i);
		printf("Found node: %s intval: %d\n", nodePtr->name, nodePtr->intval);
	}
}

// SORT BY INTVAL
int compare_intval(const void *t1, const void *t2)
{
	if (((NODE *)t1)->intval < ((NODE *)t2)->intval)
    {
        return -1;
    }                                                                               
	else if (((NODE *)t1)->intval > ((NODE *)t2)->intval)
    {                                                                                   
		return 1;
    }

    return 0;
}

// SORT BY NAME
int compare_name(const void *t1, const void *t2)
{
    return strcmp(((NODE *)t1)->name,((ORDER *)t2)->name);
}
