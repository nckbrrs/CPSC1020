/*
	Nicholas Barrs
	CPSC 1020-001
	nbarrs
	26 March 2015
	Short Assignment 2 - Convert to C++
	sphere.cpp - raytracer sphere functions
*/

///////////////////////////////////////////////////////////////////////////////
////											sphere.cpp										////
///////////////////////////////////////////////////////////////////////////////

#include "ray.h"

// for the generalized parser
static pparm_t sphere_parse[] = 
{
	{"center", 3, sizeof(double), "%lf", 0},
	{"radius", 1, sizeof(double), "%lf", 0},
};
#define NUM_ATTRS (sizeof(sphere_parse) / sizeof(pparm_t))

//=============================================================================
// sphere constructor - takes place of sphere_init() function
//=============================================================================
sphere_t::sphere_t(FILE *in, model_t* model, int attrmax) : object_t (in, model)
{
	int mask;

	strcpy (obj_type, "sphere");

	// The parser is fairly generic but the address of where
	// to put the data must be updated for each new object
	sphere_parse[0].loc = &center;
	sphere_parse[1].loc = &radius;
	mask = parser (in, sphere_parse, NUM_ATTRS, attrmax);
	assert (mask == 3);

}

//=============================================================================
// sphere hits - determine if a vector projected from location *base
//						in direction *dir hits the plane. If so, then return
//						value is the dist from base to point of contact
//=============================================================================
double sphere_t::hits(vec_t *base, vec_t *dir)
{
	double dist, a, b, c, discrim;
	vec_t newBase, hitpoint, unitNorm;

	vec_diff (&center, base, &newBase);

	a = vec_dot (dir, dir);
	if (a == 0)
		return -1.0;

	b = (vec_dot (&newBase, dir)) * 2.0;
	c = (vec_dot (&newBase, &newBase) - (radius * radius));
	discrim = ((b * b) - (4 * a * c));

	if (discrim <= 0)
		return -1.0;
	else
		dist = ((-b - sqrt(b * b - 4 * a * c)) / (2 * a));

	// compute hitpoint
	vec_scale (dist, dir, &hitpoint);
	vec_sum (base, &hitpoint, &hitpoint);
	last_hitpt = hitpoint;

	// determine surface normal at hitpoint
	vec_diff (&center, &hitpoint, &unitNorm);
	vec_scale (1 / vec_len(&unitNorm), &unitNorm, &unitNorm);
	last_normal = unitNorm;

	// return distance
	return dist;

}

//=============================================================================
// sphere printer - prints sphere attributes
//=============================================================================
void sphere_t::printer (FILE *out)
{
	// print general object attributes
	object_t::printer(out);

	// print sphere attributes
	fprintf (out, "%-12s %5.1lf %5.1lf %5.1lf", "center",
																center.x, center.y, center.z);

	fprintf (out, "\n%-12s %5.1lf\n", "radius", radius);

}
