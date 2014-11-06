#ifndef DYNARRAY
#define DYNARRAY

#define INIT_ARRAY_SIZ  64                                                      
#define ARRAY_RSIZ_MULT 2

// STRUCTURE FOR DYNAMICALLY RESIZING ARRAY
typedef struct dyn_array                                                        
{
	void *array;                                                                    
    int   count;        // number of elements
    int   maxobj;       // max elements that have been allocated
    int   objsiz;       // size of each object
} DYN_ARRAY;

void init_array(DYN_ARRAY *, int);                                              
void free_array(DYN_ARRAY *);
void add_to_array(DYN_ARRAY *, void *);
void* get_from_array(DYN_ARRAY *, int);
void remove_from_array(DYN_ARRAY *, int);
void sort_array(DYN_ARRAY *ar, int (*compare)(const void *, const void *));
void clear_array(DYN_ARRAY *ar);

#endif
