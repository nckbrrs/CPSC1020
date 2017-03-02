/*
	Nicholas Barrs
	CPSC 1020-001
	nbarrs
	26 March 2015
	Short Assignment 2 - Convert to C++
	camera.cpp - raytracer camera functions
*/

///////////////////////////////////////////////////////////////////////////////
//// 										camera.cpp											////
///////////////////////////////////////////////////////////////////////////////

#include "ray.h"

// for the generalized parser
static pparm_t cam_parse[] = 
{
	{"pixeldim", 2, sizeof(int),		"%d", 0},
	{"worlddim", 2, sizeof(double),	"%lf", 0},
	{"viewpoint", 3, sizeof(double),	"%lf", 0}
};
#define NUM_ATTRS (sizeof(cam_parse) / sizeof(pparm_t))

//=============================================================================
// camera constructor - takes place of cam_init() function
//=============================================================================
camera_t::camera_t(FILE *in)
{
	char attrname[NAME_LEN];
	int count;
	int mask;

	/* Create a new camera structure and intialize it */
	cookie = CAM_COOKIE;

	/* Read the descriptive name of the camera */
	count = fscanf (in, "%s", name);
	assert (count == 1);

	count = fscanf (in, "%s", attrname);
	assert (attrname[0] == '{');

	cam_parse[0].loc = &pixel_dim;
	cam_parse[1].loc = &world_dim;
	cam_parse[2].loc = &view_point;

	/* calls the generic parser */
	mask = parser (in, cam_parse, NUM_ATTRS, 0);
	assert (mask == 7);

	/* malloc pixmap */
	pixmap = (irgb_t *)malloc(sizeof(irgb_t ) * pixel_dim[X] * pixel_dim[Y]);
}

//=============================================================================
// camera printer - replaces camera_print()
//=============================================================================

void camera_t::camera_print (FILE *out)
{
	fprintf (out, "\n%-12s %s \n", "camera", name);
	fprintf (out, "%-12s %5i %5i\n", "pixeldim", 
																pixel_dim[X], pixel_dim[Y]);
	fprintf (out, "%-12s %5.1lf %5.1lf\n", "worlddim",
																world_dim[X], world_dim[Y]);
	fprintf (out, "%-12s %5.1lf %5.1lf %5.1lf \n\n", "viewpoint",
												view_point.x, view_point.y, view_point.z);
}

//=============================================================================
// camera getters
//=============================================================================

int camera_t::getxdim(void)
{
	assert (cookie == CAM_COOKIE);
	return (pixel_dim[0]);
}

int camera_t::getydim(void)
{
	assert (cookie == CAM_COOKIE);
	return (pixel_dim[1]);
}

void camera_t::getviewpt(vec_t *view)
{
	assert (cookie == CAM_COOKIE);
	vec_copy (&view_point, view);
}

//=============================================================================
// getdir - computes unit vector from viewpt to x,y coords, and dir is result
//=============================================================================

void camera_t::getdir(int x, int y, vec_t *dir)
{
	assert (cookie == CAM_COOKIE);

	vec_t world;

	// convert pixel coordinates to world screen coordinates
	world.x = (world_dim[X] * x) / (pixel_dim[X] - 1);
	world.y = (world_dim[Y] * y) / (pixel_dim[Y] - 1);
	world.z = 0.0;

	// compute vector from viewpt to world screen coords
	vec_diff (&view_point, &world, dir);

	// convert vector to unit length vector
	vec_unit (dir, dir);
}

//=============================================================================
// store_pixel -  converts a pixel from drgb_t to irgb_t and
//						stores it in the image associated with the camera
//=============================================================================
void camera_t::store_pixel(int x, int y, drgb_t *pix)
{
	assert (cookie == CAM_COOKIE);

	pix->r = (pix->r * 255.0 + 0.5);
	pix->g = (pix->g * 255.0 + 0.5);
	pix->b = (pix->b * 255.0 + 0.5);

	if (pix->r > 255)
		pix->r = 255.0;

	if (pix->g > 255)
		pix->g = 255.0;

	if (pix->b > 255)
		pix->b = 255.0;

	if (pix->r < 0)
		pix->r = 0.0;

	if (pix->g < 0)
		pix->g = 0.0;

	if (pix->b < 0)
		pix->b = 0.0;

	// compute the address of the irgb_t pixel
	int row = pixel_dim[Y] - 1 - y;
	int col = x;
	irgb_t *ipix = pixmap + row * pixel_dim[X] + col;

	// store the scaled and clamped values of the drgb_t pixel in the image
	ipix->r = pix->r;
	ipix->g = pix->g;
	ipix->b = pix->b;

}

//=============================================================================
// write_image - writes .ppm header and writes image to file
//=============================================================================
void camera_t::camera_write_image(FILE *out)
{
	assert (cookie = CAM_COOKIE);
	
	// prints header to file pointed to by "out" argument
	fprintf (out, "P6\n%i %i 255\n", pixel_dim[X], pixel_dim[Y]);

	// writes image pointed to by pixmap in cam, using sizeof each pixel
	// and X * Y dimensions, to the file pointed to by "out"
	fwrite (pixmap, sizeof(irgb_t), pixel_dim[X] * pixel_dim[Y], out);

}
