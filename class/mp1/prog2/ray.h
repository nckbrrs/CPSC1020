/* ray.h */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <memory.h>
#include <assert.h>

#define NAME_LEN   16        /* max length of entity names */

#define OBJ_COOKIE 12345678
#define MAT_COOKIE 32456123
#define LGT_COOKIE 30492344
#define CAM_COOKIE 49495923

#define MAX_DIST   32
#define AA_SAMPLES  1

#include "vector.h"
#include "pixel.h"
#include "list.h"


typedef struct camera_type
{
   int    cookie;
   char   name[NAME_LEN];
   int    pixel_dim[2];    /* Projection screen size in pix */
   double world_dim[2];    /* Screen size in world coords   */
   vec_t  view_point;      /* Viewpt Loc in world coords    */
   irgb_t *pixmap;         /* Build image here              */
}  camera_t;


typedef struct model_type
{
   camera_t   *cam;
   list_t  *mats;
   list_t  *objs;
   list_t  *lgts;
}  model_t;


typedef struct pparm_type
{
   char *attrname;          /* Attribut name                  */
   int  numvals;            /* Number of attribute values     */
   int  valsize;            /* Size of attribute in bytes     */
   char *fmtstr;            /* Format string to use           */
   void *loc;               /* Where to store first attribute */
}  pparm_t;


typedef struct material_type
{
   int     cookie;
   char    name[NAME_LEN];
   drgb_t  ambient;         /* Reflectivity for materials  */
   drgb_t  diffuse;
   double  specular;
}  material_t;


typedef struct light_type
{
   int     cookie;
   char    name[NAME_LEN];

   vec_t   location;
   drgb_t  emissivity;

   void    (*getemiss)(struct light_type *, drgb_t);
   void    (*getloc)(struct   light_type *, vec_t );
   int     (*vischeck)(struct light_type *, vec_t );

   void    *priv;
}  light_t;


typedef struct object_type
{
   int     cookie;
   char    obj_type[NAME_LEN];  /* entity type plane, sphere, ...       */
   char    obj_name[NAME_LEN];  /* entity name left_wall, center_sphere */


	/* Function pointers - can be overridden to provide polymorphic behavior */
   void    (*printer)(struct object_type *, FILE *);
   double  (*hits)(struct object_type *, vec_t *,  vec_t *);
   void    (*ambient) (struct object_type *, struct material_type *, drgb_t *);
   void    (*diffuse) (struct object_type *, struct material_type *, drgb_t *);
   double  (*specular)(struct object_type *, struct material_type *);


	/* Pointer to associated material structure  */
   material_t *mat;

   void    *priv;           /* Private type-dependent data */

   vec_t  last_hit;         /* Last hit point              */
   vec_t  last_normal;      /* Normal at hit point         */
} object_t;


typedef struct plane_type
{
   vec_t   normal;
   vec_t   point;
   double  ndotq;
   void    *priv;         /* Data for specialized types  */
}  plane_t;


typedef struct triangle_type
{
   vec_t   point1;
   vec_t   point2;
   vec_t   point3;
   void    *priv;         /* Data for specialized types  */
}  triangle_t;


typedef struct pplane_type
{
   int   shader;
}  pplane_t;


typedef struct pshader_type
{
	// void (*getamb)  (struct object_type *, drgb_t);
	// void (*getdiff) (struct object_type *, drgb_t);

   void (*getambient) (struct object_type *, struct material_type *, drgb_t);
   void (*getdiffuse) (struct object_type *, struct material_type *, drgb_t);
}  pshader_t;


/* Tile plane... descendant of plane */
typedef struct tplane_type
{
   char       matname[NAME_LEN];
   material_t *background;   /* background color    */
   vec_t      direction;     /* direction of tiling */
   double     dimension[2];  /* dimension of tiles  */
   vec_t      udir;          /* unit direction vec  */
   // mtx_t      rot;        /* rotation matrix     */
   // mtx_t      irot;       /* inverse rotation    */
}  tplane_t;


typedef struct sphere_type
{
   vec_t      center;
   double     radius;
   int        procndx;
   vec_t      scale;
}  sphere_t;



#include "rayfuns.h"
#include "rayhdrs.h"

