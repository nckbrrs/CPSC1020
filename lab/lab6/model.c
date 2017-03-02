/* model.c */

/* This module provides a complete statically defined model that can */
/* be used to test the raytracing system for this lab.               */


#include "ray.h"

material_t mat1 =
{
   .cookie = MAT_COOKIE,
   .name =  "green",
   .ambient = {0, 5, 0},
};

material_t mat2 =
{
   .cookie = MAT_COOKIE,
   .name =  "yellow",
   .ambient = {6, 5, 0},
};

material_t mat3 =
{
   .cookie = MAT_COOKIE,
   .name = "gray",
   .ambient = {4, 4, 4},
};

plane_t plane1 =
{
   .normal = {3, 0, 1},
   .point =  {0, 0, 0},
};


plane_t plane2 =
{
   .normal = {-3, 0, 1},
   .point =  {8, 0, 0},
};


plane_t plane3 =
{
   .normal = {0, 1, 0},
   .point =  {0, 0, 0},
};


object_t object1 =
{
   .cookie =   OBJ_COOKIE,
   .obj_name =  "leftwall",
   .hits =     plane_hits,
   .priv =     (void *)&plane1,
   .mat =      &mat1,
};

object_t object2 =
{
   .cookie =   OBJ_COOKIE,
   .obj_name =  "rightwall",
   .hits =     plane_hits,
   .priv =     (void *)&plane2,
   .mat =      &mat2,
};

object_t object3 =
{
   .cookie =   OBJ_COOKIE,
   .obj_name =  "floor",
   .hits =     plane_hits,
   .priv =     (void *)&plane3,
   .mat =      &mat3,
};

link_t link1 =
{
   .next = NULL,
   .entity = (void *)&object2,
};

link_t link2 =
{
   .next = &link1,
   .entity = (void *)&object1,
};

link_t link3 =
{
   .next = &link2,
   .entity = (void *)&object3,
};



list_t list1 =
{
   .first = &link3,
   .last =  &link1,
   .current = &link1
};


model_t model =
{
   .objs = &list1,
};

model_t *model_init(
FILE *in)
{
   /* compute ndotq for all planes  */
   plane1.ndotq = vec_dot(&plane1.normal, &plane1.point);
   plane2.ndotq = vec_dot(&plane2.normal, &plane2.point);
   plane3.ndotq = vec_dot(&plane3.normal, &plane3.point);
   return(&model);
};

