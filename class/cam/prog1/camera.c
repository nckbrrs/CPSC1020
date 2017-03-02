/*
	Nicholas Barrs
	nbarrs
	CPSC 1020-001
	8 February 2015
	Short Assignment #1 - Camera
	camera.c - the basic functions that enable the raytracer camera to work
			   correctly
*/

/*  camera functions:
		camera_init() - initializes camera object
		camera_load_attributes() - loads attributes from input file
		camera_print() - prints value loaded from input file
		camera_getdir() - gets unit vector from viewpoint to pixel
		camera_store_pixel() - stores the converted pixel
		camera_write_image() - writes image to file
*/

#include "ray.h"

//=============================================================================
// ******* camera_init( ) *******
// 
// Initializes a camera structure
// calls camera_load_attributes( )
//=============================================================================
void camera_init(FILE *in, model_t *model, int attrmax) {
	int attribcount;

	// Allocate camera structure and store cookie code 
	camera_t *cam = (camera_t *)malloc(sizeof(camera_t));
	cam->cookie = CAM_COOKIE;

	// Read attributes into camera data structure 
	attribcount = camera_load_attributes(in, cam);
	assert(attribcount == 3);

	// Allocate an image structure to hold the ppm image data 
	cam->pixmap = (irgb_t *)malloc(sizeof(irgb_t) * 
							     cam->pixel_dim[X] * 
								 cam->pixel_dim[Y]);

	// Save camera pointer in model structure 
	model->cam = cam;

}

//=============================================================================
// ******* camera_load_attributes( ) *******
//
// reads the info in from the file that contains the 3 camera
// 	attributes: pixeldim, worlddim, and viewpoint 
// attrcount should be 3 after reading in 3 attributes
//=============================================================================
int camera_load_attributes(FILE *in, camera_t *cam) {
	char attrib_name[NAME_LEN];
	int count = 0;     // number of items read
	int attrcount = 0; // total number of attributes

	// First read camera name string into cam->name 
	count = fscanf(in, "%s", cam->name);
	assert(count == 1);

	// Now consume "{" 
	count = fscanf(in, "%s", attrib_name);
	assert(count == 1);
	assert(attrib_name[0] == '{');

	// Read first attribute name 
	count = fscanf(in, "%s", attrib_name);
	assert(count == 1);

	// '}' means end of the camera definition 
	while (attrib_name[0] != '}') {
		if (strcmp(attrib_name, "pixeldim") == 0) {
			count = fscanf(in, "%d %d", 
								&cam->pixel_dim[X], &cam->pixel_dim[Y]);
			assert(count == 2);
			attrcount += 1;
		}

		// fill in code for reading in worlddim and viewpoint
		else if (strcmp(attrib_name, "worlddim") == 0) {
            count = fscanf(in, "%lf %lf",
								&cam->world_dim[X],&cam->world_dim[Y]);
            assert (count == 2);
            attrcount += 1;
        }

		else if (strcmp(attrib_name, "viewpoint") == 0) {
            count=fscanf(in, "%lf %lf %lf", 
					&cam->view_point.x, &cam->view_point.y, &cam->view_point.z);
            assert (count == 3); 
            attrcount += 1;
        }

		else {
			fprintf(stderr,"Bad camera attribute: %s\n", attrib_name);
			exit(1);
		}

		// Read next attribute name 
		fscanf(in, "%s", attrib_name);
	}

	return(attrcount);
}

//=============================================================================
// ******* camera_print( ) *******
//
// will print to the file specified by "out"
// 	the attributes read in from camera.txt 
//=============================================================================
void camera_print (camera_t *cam, FILE *out) {
	assert(cam->cookie == CAM_COOKIE);

	// fprintf statements to out for printing the camera attributes:
	//		name, pixeldim, worlddim, viewpoint
	// 	using the formatting sent in the email

	fprintf(out, "%-12s %s\n", "camera", cam->name);
	fprintf(out, "%-12s %5i %5i\n", "pixeldim",
									cam->pixel_dim[X], cam->pixel_dim[Y]);
	fprintf(out, "%-12s %5.1lf %5.1lf\n", "worlddim",
									cam->world_dim[X], cam->world_dim[Y]);
	fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n\n", "viewpoint",
					cam->view_point.x, cam->view_point.y, cam->view_point.z);


}

//=============================================================================
// ******* camera_getdir( ) *******
// 
// computes the unit vector from the viewpoint to the 
// 	(x,y) pixel coordinates passed in as parameters
// vec_t *uvec is the resulting unit vector 
//=============================================================================
void camera_getdir(camera_t *cam, int x, int y, vec_t *uvec) {
	assert(cam->cookie == CAM_COOKIE);

	vec_t *world = (vec_t *)malloc(sizeof(vec_t));

	// convert pixel coordinates to world screen coordinates
	world->x = (cam->world_dim[X] * x) / (cam->pixel_dim[X] - 1);
	world->y = (cam->world_dim[Y] * y) / (cam->pixel_dim[Y] - 1);
	world->z = 0.0;

	// compute vector from viewpoint to world screen coordinates
	//		don't forget about the vector functions from your vector.c file

	vec_diff(&cam->view_point, world, uvec);

	// convert vector to unit length vector
	//		don't forget about the vector functions from your vector.c file

	vec_unit(uvec, uvec);
}

//=============================================================================
// ******* camera_store_pixel( ) *******
//
// converts a pixel from drgb_t to irgb_t and
// 	stores it in the image associated with the camera 
//=============================================================================
void camera_store_pixel(camera_t *cam, int x, int y, drgb_t *pix) {
	assert(cam->cookie == CAM_COOKIE);

	// scale and clamp pix values to integer values; formula given in notes
	/*
	ipix->r = pix->r * 255.0 + 0.5;
	ipix->g = pix->g * 255.0 + 0.5;
	ipix->b = pix->b * 255.0 + 0.5;
	*/

	pix->r = (pix->r * 255.0 + 0.5);
	pix->g = (pix->g * 255.0 + 0.5);
	pix->b = (pix->b * 255.0 + 0.5);

	if (pix->r > 255) { 
		pix->r = 255.0;
	}

	if (pix->g > 255) {
		pix->g = 255.0;
	}

	if (pix->b > 255) {
		pix->b = 255.0;
	}

	if (pix->r < 0) {
		pix->r = 0.0;
	}
	
	if (pix->g < 0) {
		pix->g = 0.0;
	}
	
	if (pix->b < 0) {
		pix->b = 0.0;
	}

	// compute the address of the irgb_t pixel; can copy lines of code from
	//		the camtest.c file given in the notes

	int row = cam->pixel_dim[Y] - 1 - y;
	int col = x;
	irgb_t *ipix = cam->pixmap + row * cam->pixel_dim[X] + col;

	// store the scaled and clamped values of the drgb_t pixel in the image
	
	ipix->r = pix->r;
	ipix->g = pix->g;
	ipix->b = pix->b;

}

//=============================================================================
// ******* camera_write_image( ) *******
//
// uses the fprintf( ) to write the .ppm header
// and fwrite() to write the image to the file
//=============================================================================
void camera_write_image(camera_t *cam, FILE *out) {

	// can use fprintf to print the header to file pointed to by out argument
	//		don't forget the \n after the 255...
	fprintf (out, "P6\n%i %i 255\n", cam->pixel_dim[X], cam->pixel_dim[Y]);


	// can use a single fwrite statement to write the image pointed to by
	//		the pixmap pointer in cam, using sizeof each pixel (which is an
	//		irgb_t), and the X * Y dimensions, to the file pointed to by out
	fwrite (cam->pixmap,sizeof(irgb_t),cam->pixel_dim[X]*cam->pixel_dim[Y],out);

}


