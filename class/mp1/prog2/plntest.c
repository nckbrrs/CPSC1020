/* plntest.c */

#include "ray.h"

int main(int argc, char *argv[])
{
   model_t    mod;
   model_t    *model = &mod;
   material_t *mat;
   camera_t *cam;
   plane_t pln = {normal: {0, 1, 1}, point: {0, 0, -7}};
   object_t   *obj1;
   object_t   obj2 = {cookie: OBJ_COOKIE, 
                     priv: (void *)&pln, 
					 hits: plane_hits};
   
   char   entity[16];

   FILE *in;
   FILE *out;
   assert(argc >= 3);

   in = fopen(argv[1], "r");
   assert(in != NULL);
   out = fopen(argv[2], "w");
   assert(out != NULL);

	/* Create lists */
   model->mats = list_init();
   model->objs = list_init();

	/* Load the camera */
   fscanf(in, "%s", entity);
   camera_init(in, model, 0);
   cam = model->cam; 
   assert(cam->cookie == CAM_COOKIE);
   fprintf(stderr, "\nloaded %s \n", cam->name);

	/* Load the material definition */
   fscanf(in, "%s", entity);
   material_init(in, model, 0);
   mat = (material_t *)list_get_entity(model->mats);
   assert(mat->cookie == MAT_COOKIE);
   fprintf(stderr, "\nloaded %s \n", mat->name);

	/* Verify that worked */
   material_list_print(model, stderr);


	/* Now load the object definition */
   fscanf(in, "%s", entity);
   plane_init(in, model, 0);
   obj1 = (object_t *)list_get_entity(model->objs);
   assert(obj1->cookie == OBJ_COOKIE);
   fprintf(stderr, "\nloaded %s \n", obj1->obj_name);

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
   // dist = obj1->hits(obj1, &cam->view_point, &unit);

   fprintf(stderr, "\ndist to plane 1 %8.3lf \n", dist);
   vec_print(stderr, "hit point", &obj1->last_hit);

   vec_unit(&dir, &unit);
   memset(&obj2.last_hit, 0, sizeof(vec_t));
   dist = obj2.hits(&obj2, &view, &unit);
   // dist = obj2.hits(&obj2, &cam->view_point, &unit);

   fprintf(stderr, "\ndist to plane 2 %8.3lf \n", dist);
   vec_print(stderr, "hit point", &obj2.last_hit);

   /* Make sure we dont get a hit in +z space */
   dir.y = -2.1;
   vec_unit(&dir, &unit);
   memset(&obj2.last_hit, 0, sizeof(vec_t));
   dist = obj2.hits(&obj2, &view, &unit);
   // dist = obj2.hits(&obj2, &cam->view_point, &unit);
 
   fprintf(stderr, "\npositive z test \n");
   fprintf(stderr, "dist to plane 2 %8.3lf \n", dist);
   vec_print(stderr, "hit point", &obj2.last_hit);

   /* Make sure we don't get a hit on a miss... Shoot */
   /* straight down at backwall                       */
   dir.z = 0;
   vec_unit(&dir, &unit);
   memset(&obj1->last_hit, 0, sizeof(vec_t));
   dist = obj1->hits(obj1, &view, &unit);

   fprintf(stderr, "\nvertical ray test \n");
   fprintf(stderr, "dist to plane 1 %8.3lf \n", dist);
   vec_print(stderr, "hit point", &obj1->last_hit);


   list_reset(model->objs);
   image_create(model, out);
 
   return(0);

}

