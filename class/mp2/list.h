#include <malloc.h>
#include <assert.h>


// link struct (a node)
typedef struct link_type {
   struct link_type  *next;   /* Next link in the list   */
   void   *entity;            /* Entity owned by link    */
}  link_t;


// list struct 
typedef struct list_type {
   link_t  *first;           /* First link in the list */
   link_t  *last;            /* Last link in the list  */
   link_t  *current;
}  list_t;


/*******														  *******/
/******* Prototypes for list management functions *******/
/*******														  *******/


// malloc a new list header and initialize it
list_t *list_init(void);

// Add an element to the end of a list
void list_add(list_t  *list, void  *entity);

// Set current pointer to first pointer 
void list_reset(list_t  *list);

// Check to see if at the end of the list or not
// Return 1 is not at end; 0 if current pointer is NULL 
int list_not_end(list_t  *list);

// Advance current pointer to next link 
void list_next_link(list_t  *list);

// Return address of entity pointed to by current link 
void *list_get_entity(list_t  *list);

// Delete all of the list control structures
// and the entities they control
void list_del(list_t  *list);

