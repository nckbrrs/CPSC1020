/*
	Nicholas Barrs
	nbarrs	
	CPSC 1020-001
	11 March 2015	
*/

/* tplane.c - tiled plane */

#include "ray.h"

void tplane_init (FILE *in, model_t *model)
{
	object_t *obj;
	tplane_t *tpln = (tplane_t *)malloc(sizeof(tplane_t));

	// Call plane_init to create plane_t and object_t structures
	// the 2 tells plane_init not to process more than 2 attributes
	plane_init (in, model, 2);

	// Recover a pointer to an object in model->objs
	// Recover a pointer to the plane from obj->priv
	// Set the priv pointer from pln to tpln
	obj = (object_t *)list_get_entity (model->objs);
	tpln = (tplane_t *)obj->priv;

	// Parse the attributed data
	tplane_load_attributes(in, tpln, 2);
	
	// Set the "ambient" pointer in object_t to tplane_ambient function
	obj->ambient = tplane_ambient;

	// Get background color
	tpln->background = material_getbyname(model, tpln->matname);

	// Set printer function to tplane_print
	obj->printer = tplane_print;
	
	// Set obj_type to "tiled plane"
	strcpy (obj->obj_type, "tiled plane");

}

int tplane_load_attributes (FILE *in, tplane_t *tpln, int attrmax)
{
	char attrib_name[NAME_LEN];
	int count = 0;		// number of items read
	int attrcount = 0;	// total number of attributes

	// plane_load_attributes is consuming "dimension", so
	// set first quantities read in to dimension's values
	count = fscanf (in, "%lf %lf",  &(tpln->dimension[X]), 
									&(tpln->dimension[Y]));
	assert (count == 2);
	attrcount += 1;

	// read in component and make sure it is "altmaterial"
	// if so, read in the material; if otherwise, error message
	//while (attrib_name[0] != '}') {

	count = fscanf (in, "%s", attrib_name);
	if (strcmp (attrib_name, "altmaterial") == 0) {
		count = fscanf (in, "%s", tpln->matname);
		assert (count == 1);	
		attrcount += 1;
	}

	else {
		fprintf(stderr, "Bad tplane attribute: %s \n", attrib_name);
		exit(1);
	}

	return attrcount;

}

void tplane_print (object_t *obj, FILE *out)
{
	// recover tpln pointer from obj->priv
	tplane_t *tpln = (tplane_t *)obj->priv;
	
	// print generic attributes and plane attributes
	plane_print(obj, out);
	
	fprintf (out, "\n%-12s %5.1lf %5.1lf", "dimension", 
										tpln->dimension[X],
										tpln->dimension[Y]);

	fprintf (out, "\n%-12s %-12s\n", "altmaterial", tpln->matname);

}

void tplane_ambient (object_t *obj, material_t *mat, drgb_t *value)
{
	// recover tpln pointer from obj->priv
	tplane_t *tpln = (tplane_t *)obj->priv;

	int foreground = tplane_foreground(obj);

	if (foreground)
		material_getambient(obj, obj->mat, value);
	else
		material_getambient(obj, tpln->background, value);

	//material_print (mat, stderr);
}

int tplane_foreground (object_t *obj)
{
	//plane_t *pln = (plane_t *)obj->priv;
	tplane_t *tpln = (tplane_t *)obj->priv;
	
	int x_ndx = (obj->last_hit.x + 10000) / tpln->dimension[X];
	int z_ndx = (obj->last_hit.z + 10000) / tpln->dimension[Y];

	if ((x_ndx + z_ndx) % 2 == 0)
		return 1;
	else
		return 0;
}
