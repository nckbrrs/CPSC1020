/* sphtest.c */

#include "ray.h"

int main(int argc, char *argv[])
{
   model_t    mod;
   model_t    *model = &mod;
   material_t *mat;
   // camera_t *cam;
   object_t *obj1;
   object_t *obj2;
   object_t *obj3;
 
   char       entity[16];

   FILE *in;
   assert(argc >= 2);

   in = fopen(argv[1], "r");
   assert(in != NULL);


	/* Create lists */
   model->mats = list_init();
   model->objs = list_init();


	/* Load the three material definitions */
   fscanf(in, "%s", entity);
   material_init(in, model, 0);
   mat = (material_t *)list_get_entity(model->mats);
   assert(mat->cookie == MAT_COOKIE);
   fprintf(stderr, "\nloaded %s \n", mat->name);

   fscanf(in, "%s", entity);
   material_init(in, model, 0);
   mat = (material_t *)list_get_entity(model->mats);
   assert(mat->cookie == MAT_COOKIE);
   fprintf(stderr, "\nloaded %s \n", mat->name);

   fscanf(in, "%s", entity);
   material_init(in, model, 0);
   mat = (material_t *)list_get_entity(model->mats);
   assert(mat->cookie == MAT_COOKIE);
   fprintf(stderr, "\nloaded %s \n", mat->name);


	/* Verify that worked */
   material_list_print(model, stderr);


	/* Now load the three object definitions */
   fscanf(in, "%s", entity);
   sphere_init(in, model, 0);
   obj1 = (object_t *)list_get_entity(model->objs);
   assert(obj1->cookie == OBJ_COOKIE);
   fprintf(stderr, "\nloaded %s \n", obj1->obj_name);

   fscanf(in, "%s", entity);
   sphere_init(in, model, 0);
   obj2 = (object_t *)list_get_entity(model->objs);
   assert(obj2->cookie == OBJ_COOKIE);
   fprintf(stderr, "\nloaded %s \n", obj2->obj_name);

   fscanf(in, "%s", entity);
   sphere_init(in, model, 0);
   obj3 = (object_t *)list_get_entity(model->objs);
   assert(obj3->cookie == OBJ_COOKIE);
   fprintf(stderr, "\nloaded %s \n", obj3->obj_name);


	/* Verify that worked */
   object_list_print(model, stderr);


	/* Now test the hits functions */
   vec_t      view = {4.0, 3.0, 5.0};
   vec_t      dir  = {0.0, 0.0, -1.0};
   double     dist = 0.0;
   vec_t      unit;

   vec_unit(&dir, &unit);
   memset(&obj1->last_hit, 0, sizeof(vec_t));
   dist = obj1->hits(obj1, &view, &unit);

   fprintf(stderr, "\ndist to sphere 1 %8.3lf \n", dist);
   vec_print(stderr, "hit point", &obj1->last_hit);

   vec_unit(&dir, &unit);

   memset(&obj2->last_hit, 0, sizeof(vec_t));
   dist = obj2->hits(obj2, &view, &unit);
   fprintf(stderr, "\ndist to sphere 2 %8.3lf \n", dist);
   vec_print(stderr, "hit point", &obj2->last_hit);

   memset(&obj3->last_hit, 0, sizeof(vec_t));
   dist = obj3->hits(obj3, &view, &unit);
   fprintf(stderr, "\ndist to sphere 3 %8.3lf \n", dist);
   vec_print(stderr, "hit point", &obj3->last_hit);

   dir.x = -0.05;
   vec_unit(&dir, &unit);
   memset(&obj2->last_hit, 0, sizeof(vec_t));
   dist = obj2->hits(obj2, &view, &unit);
  
   fprintf(stderr, "\nleft sphere test\n");
   fprintf(stderr, "\ndist to sphere 2 %8.3lf \n", dist);
   vec_print(stderr, "hit point", &obj2->last_hit);

   dir.x = 0.05;
   vec_unit(&dir, &unit);
   memset(&obj3->last_hit, 0, sizeof(vec_t));
   dist = obj3->hits(obj3, &view, &unit);
  
   fprintf(stderr, "\nright sphere test\n");
   fprintf(stderr, "\ndist to sphere 3 %8.3lf \n", dist);
   vec_print(stderr, "hit point", &obj3->last_hit);


   /* Make sure we dont get a hit on a miss ...   */
   /* Shoot straight up in the air                */
   dir.x = 0.0;
   dir.y = 1.0;
   dir.z = 0.0;

   vec_unit(&dir, &unit);
   memset(&obj2->last_hit, 0, sizeof(vec_t));
   dist = obj2->hits(obj2, &view, &unit);
 
   fprintf(stderr, "\nvertical ray test \n");
   fprintf(stderr, "dist to sphere 2 %8.3lf \n", dist);
   vec_print(stderr, "hit point", &obj2->last_hit);

   return(0);
}

