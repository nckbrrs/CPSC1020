/* 
	Nicholas Barrs
	CPSC 1020
	10 March 2015
	Major Assignment 2
	model.c - backbone for raytracer
*/

#include "ray.h"
#include "rayhdrs.h"

/* Init model data */

model_t * model_init (FILE *in)
{
	/* create model */
	model_t *model = malloc(sizeof(model_t));
	assert (model != NULL);
	memset (model, 0, sizeof(model_t));

	/* Create and initialize material structure list */
	model->mats = list_init();
	assert (model->mats != NULL);

	/* Create and initialize visible object structure list */
	model->objs = list_init();
	assert (model->objs != NULL);

	/* Create and initialize light structure list */
	//model->lgts = list_init();
	//assert (model->lgts != NULL);

	/* Read in the camera, materials, objects, lights */
	model_load_entities (in, model);
	return (model);
}

/* Load model entities */
void model_load_entities (FILE *in, model_t *model)
{
	char entityname[NAME_LEN];
	int count = 1;

	memset (entityname, 0, sizeof(entityname));

	/* Here, entityname should be one of "material", */
	/* "light", "plane", "camera", etc */
	count = fscanf (in, "%s", entityname);

	while (count == 1)
	{
		if (strcmp (entityname, "camera") == 0)
			camera_init(in, model, 3);

		else if (strcmp (entityname, "material") == 0)
			material_init(in, model, 2);

		else if (strcmp (entityname, "sphere") == 0) 
			sphere_init(in, model, 3);

		else if (strcmp (entityname, "plane") == 0)
			plane_init(in, model, 2);
		
		else if (strcmp (entityname, "tiled_plane") == 0)
			tplane_init(in, model);

		//else if (strcmp (entityname, "light") == 0)
			//light_init (in, model, 2);
	
		else
			fprintf (stderr, "Error: Bad entity %s", entityname);

		count = fscanf(in, "%s", entityname);	
	}
	
}

/* dump model data */
void model_print (model_t *model, FILE *out)
{
	camera_print (model->cam, out);
	material_list_print (model, out);
	object_list_print (model, out);
	//light_list_print (model, out);
}
