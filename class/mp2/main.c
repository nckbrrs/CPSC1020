/* main.c */

#include "ray.h"

int main(
int argc,
char *argv[])
{
   model_t *model;
  
   assert(argc > 2);

   FILE *in = fopen(argv[1], "r");
   assert(in != NULL);

   FILE *out = fopen(argv[2], "w");
   assert(out != NULL);

   /* Load and dump the model */

   model = model_init(in); 
   assert(model != NULL);
   model_print(model, stderr);

   /* Raytrace the image */

   image_create(model, out);

   return(0);
}

