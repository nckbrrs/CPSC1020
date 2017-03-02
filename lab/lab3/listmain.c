#include <stdio.h>
#include "list.h"
#include <string.h>
#include <malloc.h>

#define NAME_LEN 16


/* A meaningless structure to put on the list */

typedef struct student_type
{
   char name[NAME_LEN];    
   int  cuid;             
   int grade;
}  student_t;

int main()
{
   list_t *list;
   student_t  *student;
   char   name[NAME_LEN];
   int    id;
   int    grade;

   /* Create new list */
   list = list_init();

   /* Read input file consisting of names and id codes
      adding entities to list */
   while (scanf("%s %d %d", name, &id, &grade) == 3)
   {
      student = malloc(sizeof(student_t));
      strcpy(student->name, name);
      student->cuid = id;
      student->grade = grade;
      list_add(list, (void *)student);
   }

   /* Now play it back */
   list_reset(list);

   printf("\nList data: \n");
   while (list_not_end(list))
   {
      student = (student_t *)list_get_entity(list);
      printf("%-7s %d  %d\n", student->name, student->cuid, 
              student->grade);
      list_next_link(list);
   }

   /* Try it again...  */
   printf("\nPrinting list again: \n");
   list_reset(list);

   while (list_not_end(list))
   {
      student = (student_t *)list_get_entity(list);
      printf("%-7s %d  %d\n", student->name, student->cuid, 
              student->grade);
      list_next_link(list);
   }

   /* Now free all list control structures and the */
   /* e_t structures as well.                      */
   list_del(list);
   printf("\nDeleted list\n");

   /* See if we trashed malloc's control structures */
   list = list_init();

   /* Nope ... see if we can delete an empty list */
   list_del(list);

   /* prove we survived */
   printf("done\n");

   return 0;
}


