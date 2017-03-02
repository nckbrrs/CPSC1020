/*
   Nicholas Barrs
   nbarrs
   CPSC 1020-001
   25 February 2015
   Major Assignment 1
*/



/* plane.c - skeleton file - fill in missing code */

/* plane functions:
      plane_init() - initializes a new plane object;
		   calls object_init() to create the object, then
		   call list_get_entity() to get the object so that
		   the plane can be attached to it; then load 
		   attributes and set polymorphic function pointers
		plane_load_attributes() - loads the attributes like
		   the other load_attribute functions
		plane_print() - prints a formatted dump of the plane 
		plane_hits() - determines if a vector projected from
		   location *base in direction *dir hits the plane; 
		   if so, returns the distance from the base to the
		   point of contact
*/

#include "ray.h"



//=============================================================================
// ******* plane_init( ) *******
// 
// creates a new plane and initializes it
//    calls object_init() 
//    calls list_get_entity to get the newly created object
//    attach plane to that object
//    call plane_load_attributes()
//    set polymorphic function pointers
//=============================================================================
void plane_init(FILE  *in, model_t  *model, int  attrmax)
{
   plane_t  *pln;
   object_t *obj;
   int count;


   /* Call the object_init()function to create the object_t */
   /* and process the "material" attribute                  */
	object_init (in, model);  

   /* Use list_get_entity() to make obj point to the newly  */
   /* created object_t structure.  Your list_add() function */
   /* MUST set current to the last element in the list for  */
   /* this to work correctly.                               */
  	obj = (object_t *)list_get_entity(model->objs);

   /* malloc a plane_t structure and set the priv pointer */
   /* in the object_t structure to point to the plane_t   */
	pln = (plane_t *)malloc(sizeof(plane_t));
	obj->priv = pln;

   /* Store the word "plane" in the object_type field of   */
   /* the object_t structure. Use the strcpy() function    */
 	strcpy (obj->obj_type, "plane");

   /* Ask plane_load_attributes to load the attributes */
   /* Attributes are normal and point                  */

	count = plane_load_attributes(in, pln, attrmax);
	assert(count == 2);

   /* Setup polymorphic function pointers in object_t */
	obj->hits = plane_hits;
	obj->printer = plane_print;


   /* pre-compute ndotq                               */
	pln->ndotq = vec_dot (&(pln->normal), &(pln->point));

}


//=============================================================================
// ******* plane_load_attributes( ) *******
// 
// loads the attributes as in other load_attribute functions
//=============================================================================
int plane_load_attributes(FILE  *in, plane_t  *pln, int  attrmax)
{
	char attrib_name[NAME_LEN];
	int count = 0;     // number of item read
	int attrcount = 0; // total number of attributes


	/* consume the attributes and their values */
	/* read first attribute name:              */
	count = fscanf(in, "%s", attrib_name);
	assert (count == 1);

	while (attrib_name[0] != '}') {
		if (strcmp(attrib_name, "normal") == 0) {
			count = fscanf (in, "%lf %lf %lf",
							&pln->normal.x, &pln->normal.y, &pln->normal.z);
			assert (count == 3);
			attrcount += 1;
		}

		else if (strcmp(attrib_name, "point") == 0) {
			count = fscanf (in, "%lf %lf %lf",
							&pln->point.x, &pln->point.y, &pln->point.z);
			assert (count == 3);
			attrcount += 1;
		}

		else {
			fprintf(stderr, "Bad plane attribute: %s \n", attrib_name);
			exit(1);
		}


		/* read next attribute name */
		fscanf(in, "%s", attrib_name);
	}

	return attrcount;
}


//=============================================================================
// ******* plane_print( ) *******
// 
// prints a formatted version of the plane structure
// format should be consistent with camera_print() or material_print()   
//=============================================================================
void plane_print(object_t  *obj, FILE  *out)
{
   plane_t *pln;

	/* print generic attributes */
	object_print(obj, out);

	/* Recover pln pointer from object_t and print */
	/* point and normal in usual format				  */
	pln = obj->priv;

	fprintf (out, "\n%-12s %5.1lf %5.1lf %5.1lf\n", "normal",
							pln->normal.x, pln->normal.y, pln->normal.z);
	fprintf (out, "\n%-12s %5.1lf %5.1lf %5.1lf\n", "point",
							pln->point.x, pln->point.y, pln->point.z);

}


//=============================================================================
// ******* plane_hits( ) *******
// 
// determine if a vector projected from location *base
//    in direction *dir hits the plane
//    (*dir is the unit direction vector)
// if so, the return value is the distance from the base
//    to the point of contact
//=============================================================================
double  plane_hits(object_t  *obj, vec_t  *base, vec_t  *dir)    
{
	plane_t *pln;

   /* other variables here */
	double ndotd;
	double ndotb;
	double dist = 0.0;
	vec_t hitpoint;

	assert(obj->cookie == OBJ_COOKIE);


   /* extract pln pointer from object structure */
	pln = (plane_t *)obj->priv;


   /* We will use the following notation in the comments below */
   /*  Q = point on the plane  (plane attribute )              */
   /*  N = normal to the plane (plane attribute )              */
   /*  B = base of ray (input parameter )                      */
   /*  D = direction of ray                                    */

   /*  ndotd = N dot D                                         */
   /*  ndotb = N dot B                                         */
   /*  ndotq = N dot Q --- which was precomputed in plane_init */
   /*  dist  = signed distance from base to hitpoint location  */


   /* Compute ndotd and if 0, return(-1.0); */
	ndotd = vec_dot (&pln->normal, dir);
	if (ndotd == 0)
		return (-1.0);

	
   /* Compute ndotb */
	ndotb = vec_dot (&pln->normal, base);
	pln->ndotq = vec_dot(&pln->normal, &pln->point);

   /* Compute dist = (ndotq - ndotb) / ndotd  using */
	/* the plane's ndotq value                       */
	dist = (pln->ndotq - ndotb) / ndotd;

	
   /* Only continue if dist is positive             */
	if (dist <= 0.0)
		return -1.0;

	
   /* Compute location of hit point by scaling dir  */
	/* by dist, and adding to base                   */
	vec_scale (dist, dir, &hitpoint);
	vec_sum (base, &hitpoint, &hitpoint);
	

   /* Only continue if hitpoint.z is negative       */
	if (hitpoint.z >= 0)
		return -1;

	
   /* Copy hitpoint_location to obj->last_hit       */
   /* and  pln->normal to obj->last_normal          */
	vec_copy(&hitpoint, &obj->last_hit);
	vec_copy(&pln->normal, &obj->last_normal);

   return(dist);
}


