/*
	Nicholas Barrs
	CPSC 1020-003
	28 January 2015
	Lab 3
	list.c - inclues functions involved with creating, modifying, and
	navigating through lists
*/

#include "list.h"


/**/
/* malloc() a new list header and initialize it */
list_t *list_init(void)
{
	list_t *list = (list_t *)malloc(sizeof(list_t));
	list->first = NULL;
	list->last = NULL;
	list->current = NULL;
	return list;

}


/**/
/* add an element to the end of a list */
void list_add(list_t *list, void *entity)
{
	link_t *new = (link_t *)malloc(sizeof(link_t));
	
	if (list->first == NULL) {
		list->first = new;
		list->current = new;
		list->last = new;
		new->entity = entity;
	}
	else {
		list->last->next = new;
		new->next = NULL;
		list->last = new;
		list->current = new;
		new->entity = entity;
	}
		
}


/**/
/* set current pointer to first pointer */
void list_reset(list_t *list)
{
	if (list->first == NULL) {
		list->current = NULL;
	}
	else {
		list->current = list->first;
	}
}


/**/
/* return 1 if current pointer is pointing at a valid link */
/* return 0 if current pointer is NULL                     */
int list_not_end(list_t *list)
{
	if ((list->current) != NULL) {
		return 1;
	}
	else {
		return 0;
	}

}


/**/
/* advance current pointer to next link */
void list_next_link(list_t *list)
{
	assert(list->current != NULL);
	if (list->current == list->last) {
		list->current = NULL;
	}
	else {
		list->current = list->current->next;
	}

}


/**/
/* return address of entity pointed to by current link */
void *list_get_entity(list_t *list)
{
	assert(list->current != NULL);
	return list->current->entity;

}


/**/
/* free() all entities, links, and then the list header */
void list_del(list_t *list)
{
	list_reset(list);

	while (list_not_end(list)) {
		link_t *temp = list->current;
		list_next_link(list);
		free(temp);
	}
	
	free(list);
}
  
