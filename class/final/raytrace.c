/*
	Nicholas Barrs
	CPSC 1021--003 
	18 February 2015
*/	

/*  raytrace.c  */

/*  find_closest_object() function
    arguments:
       model_t *model - the model structure
       vect_t *base - base of the ray (viewpoint)
       vect_t *dir - unit direction vector of the ray
       object_t *last_hit - the last hit object
       double *retdist - store distance to the hit point here

     	 if no object is hit, then retdist will have the value -1, 
	       and NULL will be returned 
		 if an object is hit, retdist will end up with the mindist
		    and minobj will be a non-NULL object that is returned 
*/


#include "ray.h"


object_t *find_closest_object(model_t  *model, vec_t  *base, vec_t  *dir,
                              object_t  *last_hit, double  *retdist)
{
	object_t *minobj = NULL;
	double mindist = -1.0;

	// other declarations
	double dist = -1;
	object_t *obj;
	list_t *list = model->objs;

	// process entire list of objects to see if any are hit by the ray
	// how do you process a list??
	list->reset();

	while (list->not_end()) {
		obj = (object_t *) list->get_entity();
		
		// 	if current object from the list is not the last_hit,
		//			get the distance
		if (last_hit != obj) {
			dist = obj->hits(base, dir);
			
			if (dist > 0) {
				if (dist < mindist || mindist == -1.0) {
					mindist = dist;
					minobj = obj;
				}
			}
		}

		// 		and if that distance is smaller than the last mindist
		//			i.e. the ray hits that object at a smaller distance
		//				- - then remember that distance in mindist 
		// 			- - and remember that object in minobj
		
		list->next_link ();

	}
	// save the mindist to retdist 
	*retdist = mindist;	

	// and return the minobj
	return minobj;

}

void add_illumination(
	model_t		*model,	/* object list								*/
	vec_t			*base,	/* base of ray.. not used yet			*/
	object_t		*hitobj,	/* object that was hit by the ray	*/
	drgb_t		*pixel)	/* where to add intensity				*/
{

	light_t	*light;
	list_t 	*list;

	list = model->lgts;
	list->reset();

	while (list->not_end())
	{
		light = (light_t *)list->get_entity();
		light->illuminate(model, base, hitobj, pixel); // resides in light.cpp
		list->next_link();
	}

}
