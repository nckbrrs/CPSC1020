/*  main.c  */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

#include "entity.h"
#include "list.h"

void list_print(list_t  *elist)
{
   e_t    *eloc;

   fprintf(stderr, "\nPrinting list contents \n");
   elist->reset();
   while (elist->not_end())
   {
      eloc = (e_t *)elist->get_entity();
      eloc->eprint();
      elist->next_link();
   }
   printf("\n");
}


int main(int  argc, char  *argv[])
{
   list_t *elist;
   char name[NAME_LEN];
   e_t    *eloc;

   FILE *in;

   assert(argc >= 2);
   in = fopen(argv[1], "r");
   assert(in != NULL);

	/* Create new list */
   elist = new list_t();

	/* Insert first and only element */
   fscanf(in, "%s", name);
   eloc = new e_t(name, 13);
   elist->insert(eloc);

	/* Insert new element before "mmmm" */
	#if 1
  		fscanf(in, "%s", name);
  		eloc = new e_t(name, 6);
  		elist->insert(eloc);

		/* Insert new element before "ffff" */
  		fscanf(in, "%s", name);
  		eloc = new e_t(name, 3);
  		elist->insert(eloc);

		/* Insert element between "cccc" and "ffff" */
  		elist->next_link();       // make current "ffff"
  		fscanf(in, "%s", name);
  		eloc = new e_t(name, 4);
  		elist->insert(eloc);

		/* Insert "jjjjj" between "fffff" and "mmmmm" */
   	elist->next_link();       // make current "fffff"
   	elist->next_link();       // make current "mmmmm"
   	fscanf(in, "%s", name);
   	eloc = new e_t(name, 10);
   	elist->insert(eloc);

		/* Add "yyyyy" to end of list... this should   */
		/* make current point to "yyyyy"               */
   	fscanf(in, "%s", name);
   	eloc = new e_t(name, 25);
   	elist->add(eloc);

		/* Insert "wwwww" before "yyyyy"  */
   	fscanf(in, "%s", name);
   	eloc = new e_t(name, 23);
   	elist->insert(eloc);

		/* If this worked so far, the list should   */
		/* be in alphabetical order                 */
   	list_print(elist);
	#endif

	#if 1
		/* List now contains 7 elements .. so we reset */
		/* advance to last element                     */
   	elist->reset();
   	elist->next_link();
   	elist->next_link();
   	elist->next_link();
   	elist->next_link();
   	elist->next_link();
   	elist->next_link();

		/* Processing the list should have left current at the end */
		/* so we now try to delete the last element                */
   	delete (e_t *)elist->get_entity();
   	elist->remove();

		/* current and last should be pointing at "wwwww" now and  */
		/* we try to add a new last element                        */
   	fscanf(in, "%s", name);
   	eloc = new e_t(name, 26);
   	elist->add(eloc);

		/* Set current back to reset  and delete "ccccc"  */
   	elist->reset();
   	delete (e_t *)elist->get_entity();
   	elist->remove();

		/* insert a new first element */
   	fscanf(in, "%s", name);
   	eloc = new e_t(name, 2);
   	elist->insert(eloc);

		/* make current point to "fffff" and delete it */
   	elist->next_link();
   	elist->next_link();

   	delete (e_t *)elist->get_entity();
   	elist->remove();

   	list_print(elist);
	#endif

	#if 1
   	elist->reset();

   	delete (e_t *)elist->get_entity();
   	elist->remove();
   	delete (e_t *)elist->get_entity();
   	elist->remove();
   	delete (e_t *)elist->get_entity();
   	elist->remove();
   	delete (e_t *)elist->get_entity();
   	elist->remove();
   	delete (e_t *)elist->get_entity();
   	elist->remove();

		/* Should be down to one element now */
   	list_print(elist);

		/* Delete the last element */
   	elist->reset();
   	delete (e_t *)elist->get_entity();
   	elist->remove();

		/* Delete the list structure itself  */
   	delete elist;
	#endif

   printf("done\n");

	return 0;
}

