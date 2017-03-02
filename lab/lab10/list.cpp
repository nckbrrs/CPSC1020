/*
	Nicholas Barrs
	CPSC 1021-003
	nbarrs
	26 March 2015
	list.cpp - list.c functions converted to C++
*/



/* list.c */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include "entity.h"

link_t::link_t(void)
{
	next = NULL;
	entity = NULL;
}


link_t::link_t(void *newentity)
{
	next = NULL;
	entity = newentity;

}

link_t::~link_t(void)
{
   fprintf(stderr, "in link destructor \n");
}

void link_t::set_next(link_t *new_next)
{
	next = new_next;

}

link_t * link_t::get_next()
{
	return next;

}

void * link_t::get_entity()
{
	return entity;

}


list_t::list_t()
{
	first = NULL;
	last = NULL;
	current = NULL;

}


void list_t::add(void *entity)
{

/* Create a new link passing it the entity pointer */
	link_t *newlink = new link_t(entity);


/* Now add the link to the list using generally the */
/* same approach as the C version */
	
	if (first == NULL) {
		this->first = newlink;
		this->current = newlink;
		this->last = newlink;
	}

	else {
		this->last->set_next(newlink);
		this->last = newlink;
		this->current = newlink;
	}

}

void list_t::reset(void)
{
	current = first;

}

int list_t::not_end(void)
{
	return (current != NULL);
	
}

void list_t::next_link(void)
{
   assert(current != NULL);
	current = current->get_next();
}

void *list_t::get_entity(void)
{
   assert(current != NULL);
	return current->get_entity();

}

list_t::~list_t()
{
   current = first;
	link_t *kill;
   fprintf(stderr, "in list destructor \n");

/* Delete each link_t in the list */
	while (not_end() != 0) {
		kill = current;
		next_link();
		delete kill;
	}
}

void list_t::insert(void *entity)
{
	link_t *traverse = first;
	link_t *newlink = new link_t (entity);
	
	if (first == NULL) {
		add(entity);
	}

	else if (current == first) {
		newlink->set_next(first);
		first = newlink;
		current = newlink;
	}

	else {

		while (traverse->get_next() != current && traverse->get_next() != NULL) {
			traverse = traverse->get_next();
		}
		
		traverse->set_next(newlink);
		newlink->set_next(current);
		current = newlink;
		
	}
}

void list_t::remove(void)
{
	link_t *traverse = first;

	if (first == NULL) {

	}

	else if (last == first && current == first) {
		delete first;
		first = NULL;
		current = NULL;
		last = NULL;
	}

	else if (current == first) {
		current = current->get_next();
		delete first;
		first = current;
	}

	else if (current == last) {
		while (traverse->get_next() != last) {
			traverse = traverse->get_next();
		}

		last = traverse;
		delete current;
		current = traverse;
	}

	else {
		while (traverse->get_next() != current && traverse->get_next() != NULL) {
			traverse = traverse->get_next();
		}

		traverse->set_next(current->get_next());
		delete current;
		current = traverse;

		}
}
