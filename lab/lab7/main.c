#include <stdio.h>

#include <math.h>
#include <memory.h>

#include "vector.h"

int main()
{
   vec_t v1 = {1.0, 0.0, 1.0};
   vec_t v2 = {1.0, 1.0, 1.0};
   vec_t v7 = {2.0, 1.0, 0.5};
   vec_t v3;
   vec_t v4;
   vec_t v5;
   mtx_t m1;
   mtx_t m2;

	/* Convert initial vectors to unit vecs and print */
   vec_unit(&v1, &v1);
   vec_unit(&v2, &v2);
   
   fprintf(stderr, "\n   Unit vectors\n");
   vec_print(stderr, "v1 ", &v1);
   vec_print(stderr, "v2 ", &v2);

   vec_cross(&v2, &v7, &v7);
   fprintf(stderr, "\n   Cross product\n");
   vec_print(stderr, "v7 ", &v7);

	/* Reflect -v7 off plane whose normal is v2  */
   vec_unit(&v7, &v7);
   vec_reflect(&v2, &v7, &v7);
   fprintf(stderr, "\n   Reflected vector\n");
   vec_print(stderr,"v7 ", &v7);

	/* Project v1 onto plane whose normal is v2  */
   vec_project(&v2, &v1, &v5);
   vec_unit(&v5, &v5);
   fprintf(stderr, "\n   Projected vector\n");
   vec_print(stderr, "v5 ", &v5);

	/* Now create a matrix that will rotate v2 into the z-axis */
	/* v1 into the x = 0 plane with positive y component       */
   vec_cross(&v1, &v2, &m1.row[0]);
   vec_unit(&m1.row[0], &m1.row[0]);  // DON"T FORGET ME

   vec_copy(&v2, &m1.row[2]);
   vec_cross(&m1.row[2], &m1.row[0], &m1.row[1]);

   fprintf(stderr,"\n   Rotation Matrix \n");
   vec_print(stderr, "r0 ", &m1.row[0]);
   vec_print(stderr, "r1 ", &m1.row[1]);
   vec_print(stderr, "r2 ", &m1.row[2]);

	/* Verify that it worked */
   vec_xform(&m1, &v1, &v3);
   vec_xform(&m1, &v2, &v4);

   fprintf(stderr, "\n   Transformed v1 v2\n");
   vec_print(stderr, "v3 ", &v3);
   vec_print(stderr, "v4 ", &v4);

	/* Build the inverse of the rotation */
   mtx_transpose(&m1, &m2);

   fprintf(stderr,"\n   Transpose Matrix \n");
   vec_print(stderr, "r0 ", &m2.row[0]);
   vec_print(stderr, "r1 ", &m2.row[1]);
   vec_print(stderr, "r2 ", &m2.row[2]);

	/* And verify that it all worked */
   vec_xform(&m2, &v3, &v3);
   vec_xform(&m2, &v4, &v4);

   fprintf(stderr, "\n   Inverse transform\n");
   vec_print(stderr, "v3 ", &v3);
   vec_print(stderr, "v4 ", &v4);
   
   return 0;
}


