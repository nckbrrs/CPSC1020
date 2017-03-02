/*  image.c  */

/*  functions:
    	ray_trace() - code to add
		make_pixel() - complete function provided
		make_row() - code to add
		image_create() - code to add
*/

#include "ray.h"


//=============================================================================
// ******* ray_trace( ) *******
// 
// 
//=============================================================================
void ray_trace (
	model_t *model,
	vec_t *base,                // view point
	vec_t *dir,                 // unit direction vector
	drgb_t *pix,                // pixel return location
	double total_dist,          // distance ray has travelled so far
	object_t *last_hitobj )        // most recently hit object
{
	double mindist;
	// double specref = 0.0;
	drgb_t thispix = {0.0, 0.0, 0.0};
	object_t *closest;

	/* Get the object (plane or sphere).        */
	closest = find_closest_object(model, base, dir, NULL, &mindist);

	if (total_dist > MAX_DIST)
		return;

	if (closest != NULL) {
		#ifdef DBG_HIT
			fprintf (stderr, "%-12s HIT:(%5.11f, %5.11f, %5.11f)",
					closest->obj_name, closest->last_hitobj.x,
					closest->last_hitobj.y, closest->last_hitobj.z);
		#endif

		/* get the distance and the color */
		mindist = closest->hits(base, dir);

		closest->getambient(&thispix); //add ambient reflectivity
		add_illumination(model, base, closest, &thispix);
	}

	/*	check to see if object was hit.  if so
		1)  add this distance to the total distance travelled so far
		2)  scale thispix by 1/total_distance
		3)  add thispix to pix
	*/   

	if (mindist != -1) {
		total_dist += mindist;
		pix_scale (1.0 / total_dist, &thispix, &thispix);
		pix_sum (pix, &thispix, pix);
	}

}


//=============================================================================
// ******* make_pixel( ) *******
//=============================================================================
void make_pixel(model_t  *model, int  x, int  y) {
	vec_t raydir;
	vec_t viewpt;
	camera_t *cam = model->cam;
	drgb_t pix = {0.0, 0.0, 0.0};

	cam->getdir(x, y, &raydir);
	cam->getviewpt(&viewpt);

	/*  The ray_trace function determines the pixel color in */
	/*  d_rgb units.   The last two parameters are used ONLY */
	/*  in the case of specular (bouncing) rays              */
    ray_trace(model, &viewpt, &raydir, &pix, 0.0, NULL);

    cam->store_pixel(x, y, &pix);

	return;
}


//=============================================================================
// ******* make_row( ) *******
//=============================================================================
void make_row(model_t  *model, int  y) 
{
	int x;
	camera_t *cam = model->cam;

	int pixel_dimX = cam->getxdim();

	/*  for each pixel in the row, invoke make_pixel() */
	/*  to paint the pixel.                            */
	//  CODE HERE   
	for (x = 0; x <= pixel_dimX; x++) {
		make_pixel (model, x, y);
	}

}


//=============================================================================
// ******* image_create( ) *******
//=============================================================================
void image_create(model_t  *model, FILE  *out) 
{
	int y;
	camera_t *cam = model->cam;

	int pixel_dimY = cam->getydim();

	/*  fire rays through each pixel in the window; */
	/*  for each row, invoke make_row() to paint    */
	/*  the row of pixels.                          */
	//  CODE HERE 
	for (y = 0; y < pixel_dimY; y++) {
		make_row (model, y);
	}

	/*  write the image                           */
	cam->camera_write_image(out);
}

