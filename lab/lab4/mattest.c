/* mattest.c */

#include "ray.h"

int main(int argc, char *argv[])
{
   model_t    mod;
   model_t    *model = &mod;
   material_t *mat;
   object_t obj1;
   object_t *obj = &obj1;
   char       entity[16];
   drgb_t     dpix;
   int        count;

   FILE *in;

   assert(argc >= 2);
   in = fopen(argv[1], "r");
   assert(in != NULL);

	/* Create a material list */
   model->mats = list_init();

	/* Input should consist only of material definitions */
   count = fscanf(in, "%s", entity);

	/* but there can be any number of material defs in the file */
   while (count == 1)
   {
   	/* create material_t structure and read attributes */
      material_init(in, model, 0);

   	/* this test is designed to ensure that list_add  */
   	/* pointed current to the material just loaded    */
      mat = (material_t *)list_get_entity(model->mats);
      assert(mat->cookie == MAT_COOKIE);
      fprintf(stderr, "loaded %s \n", mat->name);
      count = fscanf(in, "%s", entity);
   }

	/* Read them all in .. now try to print them */
   material_list_print(model, stderr);

	/* See if we can find the first in the list */
   mat = material_getbyname(model, "blue");
   assert(mat->cookie == MAT_COOKIE);
   fprintf(stderr, "\nfound %s \n", mat->name);

   material_getambient(obj, mat, &dpix);
   pix_print(stderr, "ambient is: ", &dpix);

	/* See if we can find the last one */
   mat = material_getbyname(model, "yellow");
   assert(mat->cookie == MAT_COOKIE);
   fprintf(stderr, "\nfound %s \n", mat->name);

   material_getambient(obj, mat, &dpix);
   pix_print(stderr, "ambient is: ", &dpix);

	/* See what happens if we try to find a non-existent element */
   mat = material_getbyname(model, "chartreuse");
   assert(mat != NULL);

   fclose(in);
   return(0);

}

