
/* == camera.c funtions == */
/* Initialize viewpoint data */
void camera_init(FILE *in, model_t *model, int attrmax);

/* Load the camera data */
int camera_load_attributes(FILE *in, camera_t *cam);

void camera_getdir(camera_t *cam, int x, int y, vec_t *dir);

void camera_store_pixel(camera_t *cam, int x, int y, drgb_t *pix);
void scale_and_clamp(drgb_t *);

void camera_print(camera_t *cam, FILE *out);

void camera_write_image(camera_t *cam, FILE *out);


