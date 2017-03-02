/* main.c */

/* Test driver for plane-hits function */

#include "ray.h"

camera_t camera =
{
   view_point: {4, 3, 5}
};

vec_t direction;


int main(int argc, char *argv[]) {
   object_t *obj;
   camera_t *cam = &camera;
   vec_t    dir;
   model_t  *model;
   double   dist;

   FILE *in;
  
   assert(argc >= 2);
   in = fopen(argv[1], "r");
   assert (in != NULL);


   model = model_init(in);

   /* compute pln->ndotq for all statically declared plane_t objects */
	/*
   list = model->objs;
   list_reset(list);
   while(list_not_end(list))
   {
      pln = (plane_t *)list_get_entity(list);
      pln->ndotq = vec_dot(&pln->normal, &pln->point);
      list_next_link(list);
   }
	*/

   /* Read direction vectors from standard input and */
   /* perform hit computations                       */

   while (fscanf(in, "%lf %lf %lf", &dir.x, &dir.y, &dir.z) == 3)
   {
      fprintf(stderr, "\n");
      vec_print(stderr, "Ray direction:", &dir);
      vec_unit(&dir, &dir);

      obj = find_closest_object(model, &cam->view_point, &dir, NULL, &dist);
      if (dist > 0)
      {
         fprintf(stderr, "Hit: %-12s ", obj->obj_name);

         fprintf(stderr, "Dist = %8.3lf Loc = (%8.3lf %8.3lf %8.3lf)\n",
                dist, obj->last_hit.x,  obj->last_hit.y, obj->last_hit.z);
      }
      else
         fprintf(stderr, "Dist = %8.3lf \n", dist);

      fprintf(stderr, "\n");
      obj = find_closest_object(model, &cam->view_point, &dir, obj, &dist);
      if (dist > 0)
      {
         fprintf(stderr, "Hit: %-12s ", obj->obj_name);

         fprintf(stderr, "Dist = %8.3lf Loc = (%8.3lf %8.3lf %8.3lf)\n",
                dist, obj->last_hit.x,  obj->last_hit.y, obj->last_hit.z);
      }
      else
         fprintf(stderr, "Dist = %8.3lf \n", dist);


   }
   return(0);
}
