
/* camtest.c */

#include "ray.h"

int main(int argc, char *argv[])
{
   model_t   model;
   model_t   *mod = &model;
   camera_t  *cam;
   char      entity[16];
   vec_t     uvec;
   irgb_t    *ipix;
   drgb_t    dpix;
   int       row;
   int       col;
   int       x = 20;
   int       y = 50;

   FILE *in;
   FILE *out;

   assert(argc > 2);

   in = fopen(argv[1], "r");
   assert(in != NULL);

   out = fopen(argv[2], "w");
   assert(out != NULL);


   /* Consume word camera */
   /* no "&" in front of entity because entity is an */
   /* array name, so it already points to an address */
   fscanf(in, "%s", entity);


   /* Create new camera object */
   camera_init(in, &model, 0);
   cam = mod->cam;
   assert(cam->cookie == CAM_COOKIE);


   /* Make entire pixmap a light gray color */
   memset(cam->pixmap, 0xDC, sizeof(irgb_t) *
                  cam->pixel_dim[X] * cam->pixel_dim[Y]);


   /* Print camera attibutes */
   camera_print(cam, stderr);


   /* Verify getdir works */
   camera_getdir(cam, 0, 0, &uvec);
   vec_print(stderr, "unit_vector: ", &uvec);

   camera_getdir(cam, 300, 450, &uvec);
   vec_print(stderr, "unit_vector: ", &uvec);


   /* Store drgb_t equivalent to (64, 0, 255)  */
   dpix.r =  0.25;
   dpix.g = -0.3;
   dpix.b =  1.2;

   camera_store_pixel(cam, x, y, &dpix);


   /* Retrieve it directly and verify it's correct */
   row = cam->pixel_dim[Y] - y - 1;
   col = x;

   ipix =  cam->pixmap + row * cam->pixel_dim[X] + col;

   fprintf(stderr, "ipix is %d %d %d \n",
                    ipix->r, ipix->g, ipix->b);


   /* Put visible bright red (240, 18, 0) dot */
   /* in the middle of the picture */
   dpix.r =  0.94;
   dpix.g =  0.07; 
   dpix.b =  0.00;

   camera_store_pixel(cam, cam->pixel_dim[0] / 2,
                           cam->pixel_dim[1] / 2,  &dpix);


   /* Write out the image */
   camera_write_image(cam, out);

   return(0);
}


