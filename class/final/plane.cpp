/*
	Nicholas Barrs
	CPSC 1020-001
	nbarrs
	26 March 2015
	Short Assignment 2 - Convert to C++
	plane.cpp - raytracer plane functions
*/

///////////////////////////////////////////////////////////////////////////////
////										plane.cpp											////
///////////////////////////////////////////////////////////////////////////////

#include "ray.h"

// for the generalized parser
static pparm_t plane_parse[] = 
{
	{"normal", 3, sizeof(double), "%lf", 0},
	{"point", 3, sizeof(double), "%lf", 0}
};
#define NUM_ATTRS (sizeof(plane_parse) / sizeof(pparm_t))

//==============================================================================
// plane constructor - takes place of plane_init() function
//==============================================================================
plane_t::plane_t(FILE *in, model_t *model, int attrmax) : object_t (in, model)
{
	int mask;
	
	strcpy (obj_type, "plane");

	// The parser is fairly generic but the address of where
	// to put the data must be updated for each new object
	plane_parse[0].loc = &normal;
	plane_parse[1].loc = &point;
	mask = parser (in, plane_parse, NUM_ATTRS, attrmax);
	assert (mask == 3);

	vec_unit (&normal, &normal);
	vec_copy (&normal, &last_normal);

	ndotq = vec_dot (&point, &normal);
}

//=============================================================================
// plane hits - determine if a vector projected from location *base
//						in direction *dir hits the plane. If so, then return
//						value is the dist from base to point of contact
//=============================================================================
double plane_t::hits(vec_t *base, vec_t *dir)
{
	double ndotd;
	double dist = 0.0;
	double ndotb;
	vec_t hitpoint;

	ndotd = vec_dot (&normal, dir);

	/* ndotd = 0 -> ray is parallel to the plane */
	if (ndotd == 0)
		return -1;

	ndotb = vec_dot (&normal, base);
	ndotq = vec_dot (&normal, &point);

	dist = (ndotq - ndotb) / ndotd;

	if (dist <= 0)
		return -1;

	vec_scale (dist, dir, &hitpoint);
	vec_sum (&hitpoint, base, &hitpoint);
	
	if ((hitpoint.z > 0.0)) // && (strcmp(obj_type, "projector")))
		return -1;

	vec_copy (&hitpoint, &last_hitpt);
	vec_copy (&normal, &last_normal);

	return (dist);
}

//=============================================================================
// plane printer - prints plane attributes
//=============================================================================
void plane_t::printer (FILE *out)
{
	// print general object attributes
	object_t::printer(out);

	// print plane attributes
	fprintf (out, "%-12s %5.1lf %5.1lf %5.1lf", "normal",
												normal.x, normal.y, normal.z);
	fprintf (out, "\n%-12s %5.1lf %5.1lf %5.1lf\n", "point",
												point.x, point.y, point.z);
}

