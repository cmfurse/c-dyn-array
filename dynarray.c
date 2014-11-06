#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynarray.h"

void init_array(DYN_ARRAY *ar, int objsiz)
{
    ar->count = 0;
    ar->maxobj = INIT_ARRAY_SIZ;
    ar->objsiz = objsiz;
    // allocate memory for max objects
    ar->array = (void *)malloc(ar->maxobj * objsiz);
}

void free_array(DYN_ARRAY *ar)
{
    // clean up memory
    free(ar->array);
    ar->array = 0;
    ar->count = 0;
    ar->maxobj = INIT_ARRAY_SIZ;
}

void add_to_array(DYN_ARRAY *ar, void *obj)
{
    void *tmp;

    ar->count++;
    // resize array if we added more than max objects by doubling
    if (ar->count > ar->maxobj)
    {
        ar->maxobj *= ARRAY_RSIZ_MULT;
        ar->array = (void *)realloc(ar->array, (ar->maxobj * ar->objsiz));
    }

    // calculate offset of next element and memcpy, use tmp var as iterator
    tmp = ar->array;
    tmp += ar->objsiz * (ar->count - 1);
    memcpy(tmp, obj, ar->objsiz);
}

void* get_from_array(DYN_ARRAY *ar, int idx)
{
    void *tmp;
	
	// return null on invalid idx
    if (idx >= ar->count)
    {
        return (0);
    }

    // using tmp var as iterator, move to offset address, and return address
    tmp = ar->array;
    tmp += ar->objsiz * idx;
    return tmp;
}

void remove_from_array(DYN_ARRAY *ar, int idx)
{
    int i;
    void *new_array;
    void *from;
    void *to;

    new_array = (void *)malloc(ar->maxobj * ar->objsiz);
    to = new_array;
    from = ar->array;

    // copy data before idx
    memcpy(to, from, (ar->objsiz * idx));

    to += ar->objsiz * idx;
    from += ar->objsiz * (idx+1);

    // copy data after idx
    memcpy(to, from, (ar->objsiz * (ar->count - idx - 1)));

    free(ar->array);
    ar->array = new_array;
    ar->count--;
}

void sort_array(DYN_ARRAY *ar, int (*compare)(const void *, const void *))
{
    qsort(ar->array, ar->count, ar->objsiz, compare);
}

void clear_array(DYN_ARRAY *ar)
{
    ar->count = 0;

    // TODO do we want to free or memset the allocated memory?
}

