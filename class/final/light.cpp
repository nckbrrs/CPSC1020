/*
	Nicholas Barrs
	CPSC 1020-001
	nbarrs
	7 April 2015
	Final Assignment
	light.cpp - raytracer light functions
*/

///////////////////////////////////////////////////////////////////////////////
////										light.cpp											////
///////////////////////////////////////////////////////////////////////////////

#include "ray.h"

// for the generalized parser
static pparm_t light_parse[] = 
{
	{"location", 3, sizeof(double), "%lf", 0},
	{"emissivity", 3, sizeof(double), "%lf", 0},
};
#define NUM_ATTRS (sizeof(light_parse) / sizeof(pparm_t))


//=============================================================================
// light constructor - create a new light description
//=============================================================================
light_t::light_t(FILE *in, model_t *model, int attrmax) {
	char attrname[NAME_LEN];
	int count;
	int mask;

	cookie = LGT_COOKIE;

	/* Read the descriptive name of the light */
	count = fscanf (in, "%s", name);
	assert (count == 1);
	
	count = fscanf(in, "%s", attrname);
	assert(*attrname == '{');

	light_parse[0].loc = &location;
	light_parse[1].loc = &emissivity;

	// calls the generic parser
	mask = parser (in, light_parse, NUM_ATTRS, 0);
	assert (mask != 0);

	// add to list of lights
	model->lgts->add((void *)this);
}

//=============================================================================
// getemiss - getter function for emissivity
//=============================================================================
void light_t::getemiss(drgb_t * emiss)
{
	pix_copy (&emissivity, emiss);
}

//=============================================================================
// getloc -  getter function for location
//=============================================================================
void light_t::getloc (vec_t *loc)
{
	vec_copy (&location, loc);
}

//=============================================================================
// printer - prints a light
//=============================================================================
void light_t::printer (FILE *out)
{
	// print light atttributes
	fprintf (out, "%-12s %s\n", "light", name);
	fprintf (out, "%-12s %5.1lf %5.1lf %5.1lf", "location",
												location.x, location.y, location.z);
	fprintf (out, "\n%-12s %5.1lf %5.1lf %5.1lf\n", "emissivity",
												emissivity.r, emissivity.g, emissivity.b);
}

//=============================================================================
// light_list_print - produce a formatted print of the light list
//=============================================================================
void light_list_print(model_t *model, FILE *out)
{
	list_t *list;
	light_t *light;

	list = model->lgts;
	list->reset();

	while (list->not_end())
	{
		light = (light_t *)list->get_entity();
		light->printer(out);
		fprintf(out, "\n");
		list->next_link();
	}
}

//=============================================================================
// illuminate
//=============================================================================
void light_t::illuminate
(	model_t		*model, 
	vec_t			*base, 
	object_t		*hitobj,		// the object hit by the ray
	drgb_t		*pixel )		// add illumination here

{
	vec_t dir;			// unit direction to light from hitpt
	object_t *obj;		// closest object in dir to light
	double close;		// dist to closest object in dir to light
	double cos;			// of angle between normal and dir to light
	double dist;		// to the light from hitpoint
	drgb_t diffuse = {0.0, 0.0, 0.0};

	vec_t lasthit;
	vec_t lastnorm;
	drgb_t emiss = emissivity;

	// Compute the distance from the hit to the light (dist) and
	// and a unit vector in the direction of the light from hitpt (dir)

	hitobj->getlast_hitpt (&lasthit);

	vec_diff (&lasthit, &location, &dir);
	dist = vec_len(&dir);
	vec_unit (&dir, &dir);
	
	hitobj->getlast_normal (&lastnorm);
	vec_unit (&lastnorm, &lastnorm);

	/* Test the object for self-occlusion and return if occluded */
	cos = vec_dot (&dir, &lastnorm);
	if (cos <= 0) {
		return;
	}

	/* Ask find_closest_object() if a ray fired toward the light */
	/* hits another object. Pass "hitobj" as the "lasthit" */
	/* parameter so it won't be hit again at distance 0. */
	obj = find_closest_object (model, &lasthit, &dir, hitobj, &close);

	/* If an object is hit and the distance to the hit (close) is */
	/* closer to the hitpoint than the light, return */
	if ((obj != NULL) && (close < dist)) {
		return;
	}

	/* Arriving at this point means the light does illuminate */
	/* object. Ask hitobj->getdiff() to return diffuse reflectivity */
	hitobj->getdiffuse (&diffuse);

	/* Multiply component-wise the diffuse reflectivity by */
	/* the emissivity of the light. */
	pix_prod (&diffuse, &emiss, &diffuse);

	/* Scale the resulting diffuse reflectivity by cos/dist */
	pix_scale (cos/dist, &diffuse, &diffuse);

	/* Add scaled value to pixel. */
	pix_sum (&diffuse, pixel, pixel);

}

