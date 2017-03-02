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
	object_t *last_hit )        // most recently hit object
{
	double dist;
	drgb_t thispix = {0.0, 0.0, 0.0};
	object_t *obj;

	/* Get the object (plane or sphere).        */
	/* Later we will use find_closest_object()  */
	/* to get the closest object                */
	obj = (object_t *)list_get_entity(model->objs);

	/* get the distance and the color */
	dist = obj->hits(obj, base, dir);  
	obj->ambient(obj, obj->mat, &thispix);

	/**  check to see if object was hit.  if so
        1)  add this distance to the total distance travelled so far
        2)  scale thispix by 1/total_distance
        3)  add thispix to pix
	**/   
	//  CODE HERE
	if (dist != -1) {
		total_dist += dist;
		pix_scale (1.0 / total_dist, &thispix, &thispix);
		pix_sum (pix, &thispix, pix);
	}
		
}


//=============================================================================
// ******* make_pixel( ) *******
// 
// 
//=============================================================================
void make_pixel(model_t  *model, int  x, int  y) {
	vec_t raydir;
	drgb_t pix = {0.0, 0.0, 0.0};
	camera_t *cam = model->cam;

	camera_getdir(cam, x, y, &raydir);


	/*  The ray_trace function determines the pixel color in */
	/*  d_rgb units.   The last two parameters are used ONLY */
	/*  in the case of specular (bouncing) rays              */
    ray_trace(model, &cam->view_point, &raydir, &pix, 0.0, NULL);

    camera_store_pixel(cam, x, y, &pix);

	return;
}


//=============================================================================
// ******* make_row( ) *******
// 
// 
//=============================================================================
void make_row(model_t  *model, int  y) 
{
	int x;
	camera_t *cam = model->cam;

	/*  for each pixel in the row, invoke make_pixel() */
	/*  to paint the pixel.                            */
	//  CODE HERE   
	for (x = 0; x <= cam->pixel_dim[X]; x++) {
		make_pixel (model, x, y);
	}

}


//=============================================================================
// ******* image_create( ) *******
// 
// 
//=============================================================================
void image_create(model_t  *model, FILE  *out) 
{
	int y;
	camera_t *cam = model->cam;

	/*  fire rays through each pixel in the window; */
	/*  for each row, invoke make_row() to paint    */
	/*  the row of pixels.                          */
	//  CODE HERE 
	for (y = 0; y < cam->pixel_dim[Y]; y++) {
		make_row (model, y);
	}

	/*  write the image                           */
	camera_write_image(model->cam, out);
}

