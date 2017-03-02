/*
	Nicholas Barrs
	CPSC 1021-003
	5 February 2015
	Lab 4
*/



/* material.c */

#include "ray.h"

/**/
/* Create a new material description;   */
/* calls material_load_attributes().    */
/* Ignore the attrmax argument for now. */
void material_init(FILE *in, model_t *model, int attrmax)    
{
   material_t *mat;

   /* malloc() a material_t structure, use memset() to */
   /* initialize it to 0, and store the MAT_COOKIE     */

   // --- CODE GOES HERE ---
	mat = (material_t *)malloc(sizeof(material_t));
	memset(mat, 0, sizeof(material_t));

	mat->cookie = MAT_COOKIE;

   /* Load attributes as in camera.c                      */
   /* Unlike the camera, the number of attributes is      */
   /* optional. Attributes should be initialized to 0.0.  */

   material_load_attributes(in, mat);

   /* Ask list_add to add the material entity to the   */
   /* end of the mats list in the model structure.     */

   // --- CODE GOES HERE --- 
	list_add(model->mats, (void *)mat); 	


}


/**/
/* Read the info from the file that contains the attributes */ 
/* for the materials. Unlike camera, materials may have 1,  */
/* 2, or 3 attributes, so will not need to count the total  */
/* number of attributes that were read in.                  */
void material_load_attributes(FILE *in, material_t *mat)
{

   /* Use same basic approach as camera_load_attributes()  */

   // --- CODE GOES HERE ---
	assert(mat->cookie = MAT_COOKIE);
	char attrib_name[NAME_LEN];
    int count = 0;     // number of items read

    // First read material name string into mat->name 
    count = fscanf(in, "%s", mat->name);
    assert(count == 1);

    // Now consume "{" 
    count = fscanf(in, "%s", attrib_name);
    assert(count == 1);
    assert(attrib_name[0] == '{');

    // Read first attribute name 
    count = fscanf(in, "%s", attrib_name);
    assert(count == 1);

    // '}' means end of the material definition 
    while (attrib_name[0] != '}') {
        if (strcmp(attrib_name, "ambient") == 0) {
            count = fscanf(in, "%lf %lf %lf", 
											&mat->ambient.r, 
											&mat->ambient.g, 
											&mat->ambient.b);
            assert (count == 3);
        }

        else if (strcmp(attrib_name, "diffuse") == 0) {
            count = fscanf(in, "%lf %lf %lf", 
											&mat->diffuse.r, 
											&mat->diffuse.g, 
											&mat->diffuse.b);
            assert (count == 3);
        }

        else if (strcmp(attrib_name, "specular") == 0) {
            count=fscanf(in, "%lf", &mat->specular);
            assert (count == 1);
        }

		else {
			fprintf (stderr, "Bad component: %s\n", attrib_name);
			exit (1);	
		}
		
		fscanf (in, "%s", attrib_name);
    }

}


/**/
/* Search the materials list for the given name, for  */
/* example, if name is "yellow", search the list for  */
/* the material with that name.                       */ 
material_t *material_getbyname(model_t *model, char *name)    
{
   material_t *mat;

   // --- CODE GOES HERE --- 
	list_reset(model->mats);

	while (list_not_end(model->mats)) {
		mat = (material_t *) list_get_entity(model->mats);
		assert(mat->cookie == MAT_COOKIE);

		if(strcmp(mat->name, name) == 0) {
			return (mat);
		}

		list_next_link(model->mats);
	}
	
	return (NULL);
}


/**/
/* Print a material_t struct with the attributes read in      */
/* from the input file in the following format:  	           */ 
/* all keywords left justified in a field of 12 wide          */
/* int/float values - field width of 5; 1 place after decimal */
/*  
	material     green
	ambient        0.0   0.0   0.0
	diffuse        0.0   5.0   0.0
	specular       1.0
*/
/* This function is called from material_list_print() to */
/* print the values for each individual material (node). */
void material_print(material_t *mat, FILE *out)
{ 
   assert(mat->cookie == MAT_COOKIE);
  
   // --- CODE GOES HERE ---

	fprintf (out, "\n%-12s %s\n", "material", mat->name);
	
	if (&(mat->ambient) != NULL) {
		fprintf (out, "%-12s %5.1lf %5.1lf %5.1lf\n", "ambient",
											mat->ambient.r,
											mat->ambient.g,
											mat->ambient.b);
	}

	if (&(mat->diffuse) != NULL) {
		fprintf (out, "%-12s %5.1lf %5.1lf %5.1lf\n", "diffuse",
											mat->diffuse.r,
											mat->diffuse.g,
											mat->diffuse.b);
	}

	if (&(mat->specular) != NULL) {
		fprintf (out, "%-12s %5.1lf\n\n", "specular", mat->specular);

	}
}


/**/
/* Produce a formatted dump of the material list.  This */
/* funcion steps through the list of materials, and for */
/* each material (node) that it gets to, it calls the   */
/* material_print() function to actually print the      */
/* values of that material_t object.                    */
void material_list_print(model_t *model, FILE *out)
{
   // --- CODE GOES HERE ---
	list_reset (model->mats);

	material_t *temp;

	while (list_not_end(model->mats)) {
		temp = list_get_entity (model->mats);
		assert(temp->cookie = MAT_COOKIE);
		material_print (temp, out);
		list_next_link (model->mats);
	}
	
}


/**/
/* Copy the ambient values to the destination drgb_t.  */
void material_getambient(object_t *obj, material_t *mat, drgb_t *dest)   
{
   // --- CODE GOES HERE ---
	assert(mat->cookie = MAT_COOKIE);
	pix_copy(&(mat->ambient), dest);

}


/**/
/* Copy the diffuse values to the destination drgb_t.  */
void material_getdiffuse(object_t *obj, material_t *mat, drgb_t *dest)
{
   // --- CODE GOES HERE ---
	assert(mat->cookie = MAT_COOKIE);
	pix_copy(&(mat->diffuse), dest);

 
}


/**/
/* Return the specular value, rather than copy it to  */
/* a destination argument that will hold the value as */
/* with the above two functions.                      */
double material_getspecular(object_t *obj, material_t *mat)
{
   // --- CODE GOES HERE --- 
	assert(mat->cookie = MAT_COOKIE);
	return (mat->specular);


}
