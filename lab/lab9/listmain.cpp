#include <stdio.h>
#include "list.h"
#include <string.h>
#include <malloc.h>

#define NAME_LEN 16

/* A meaningless structure to put on the list */

class e_t
{
public:
   char e_name[NAME_LEN];    // entity name
   int  e_id;                // entity id code
};

int main(
int argc, 
char *argv[])
{
   list_t *elist;
   e_t    *eloc;
   char   name[NAME_LEN];
   int    count;

   FILE *in;
   FILE *out;
/* Create new list */

   elist = new list_t;

/* Read input file consisting of names and id codes
   adding entities to list .. This would not work
   if e_name and e_id were private                 */

   assert(argc >= 3);
   in = fopen(argv[1], "r");
   assert(in != NULL);

   out = fopen(argv[2], "w");
   assert(out != NULL);

   while (fscanf(in, "%s %d", name, &count) == 2)
   {
      eloc = new e_t;
      strcpy(eloc->e_name, name);
      eloc->e_id = count;
      elist->add((void *)eloc);
   }

/* Now play it back */

   elist->reset();
   while (elist->not_end())
   {
      eloc = (e_t *)elist->get_entity();
      fprintf(out, "%s %d \n", eloc->e_name, eloc->e_id);
      elist->next_link();
   }

/* Now free all the e_t structures */

   elist->reset();
   while (elist->not_end())
   {
      eloc = (e_t *)elist->get_entity();
      delete eloc;
      elist->next_link();
   }

/* Now delete the list and link structures */

   delete elist;
   fprintf(out, "done\n");
   fclose(in);
   fclose(out);
}
