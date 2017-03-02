/* 
	Nicholas Barrs
	CPSC 1021
	January 21 2015
	updated: March 5, 2015
		 - update includes: 
			vec_cross,
			vec_project,
			vec_reflect,
			vec_xform,
			mtx_transpose
*/

/**  vector.c   **/

#include "vector.h"

/*  This file contains function definitions for    */
/*  for 3D vector operations                       */

/* Compute the sum of two vectors */
/* v3 = v2 + v1; */
void vec_sum(
vec_t *v1,   /* addend */
vec_t *v2,   /* addend */
vec_t *v3)   /* result */
{
	v3->x = v2->x + v1->x;
	v3->y = v2->y + v1->y;
	v3->z = v2->z + v1->z;
}

/* Compute the difference of two vectors */
/* v3 = v2 - v1 */
void vec_diff(
vec_t *v1,   /* subtrahend */
vec_t *v2,   /* minuend    */
vec_t *v3)   /* result     */
{
	v3->x = v2->x - v1->x;
	v3->y = v2->y - v1->y;
	v3->z = v2->z - v1->z;
}

/* Compute the componentwise product of two vectors */
/* v3 = v2 * v1; */
void vec_mult( 
vec_t *v1,   /* Input vector 1 */
vec_t *v2,   /* Input vector 2 */
vec_t *v3)   /* result         */
{
	v3->x = v2->x * v1->x;
	v3->y = v2->y * v2->y;
	v3->z = v2->z * v2->z;
}

/* Return the (dot) inner product of two input vectors     */
double vec_dot(
vec_t *v1,   /* Input vector 1 */
vec_t *v2)   /* Input vector 2 */
{
	double dotProd;
	dotProd = ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
	return dotProd;
}

/* Return length of a 3d vector */
double vec_len(
vec_t *v1)  /* Vector whose length is desired */
{
	double length;
	length = sqrt(((v1->x)*(v1->x))+((v1->y)*(v1->y))+((v1->z)*(v1->z)));
	return length;
}

/* Scale a 3d vector by multiplying each element by scale factor */
void vec_scale(
double fact,   /* Scale factor */
vec_t *v1,      /* Input vector */
vec_t *v2)      /* Output vector */
{
	v2->x = fact * v1->x;
	v2->y = fact * v1->y;
	v2->z = fact * v1->z;
}

/* Construct a unit vector v2 in direction of input vector v1 */
void vec_unit(
vec_t *v1,    /* Input vector      */
vec_t *v2)    /* output unit vec   */
{
	double scale = 1.0 / vec_len(v1);
	vec_scale (scale, v1, v2);
}

/* Copy vector v1 to v2 another */
void vec_copy(
vec_t *v1,   /* input vector */
vec_t *v2)   /* output vector */
{
	v2->x = v1->x;
	v2->y = v1->y;
	v2->z = v1->z;
}

/* Read in values of vector from file */
/* Return the # of items read	*/
int vec_read(
FILE *in,     /* input file  */
vec_t *v1)    /* vector from input file */
{
	int x = fscanf(in, "%lf %lf %lf", &v1->x, &v1->y, &v1->z); 
	if (x != 3) {
		printf ("Error: Incorrect number of values read in.\n");
		exit (0);
	}
	else
		return x;	
}

/* Print values of vector to file */
void vec_print(
FILE *out,		/* output file */
char *label,	/* label string */
vec_t *v1)		/* vector to print */
{
	fprintf (out, "%s %8.3lf %8.3lf %8.3lf \n", label, v1->x, v1->y, v1->z);

}

/* Computer the outer product of two input vectors */
void vec_cross (
vec_t *v1,	/* Left input vector */
vec_t *v2,	/* Right input vector */
vec_t *v3)	/* Output vector */
{
	vec_t temp;
	
	temp.x = (v1->y * v2->z) - (v1->z * v2->y);
	temp.y = (v1->z * v2->x) - (v1->x * v2->z);
	temp.z = (v1->x * v2->y) - (v1->y * v2->x);

	vec_copy (&temp, v3);
}

/* Project a vector onto a plane */
void vec_project (
vec_t *n,	/* plane normal */
vec_t *v,	/* input vector */
vec_t *p)	/* projected vector */

{

	vec_t temp;

	//Computes NdotV
	double ndotv = vec_dot (n, v);
	
	//Computes (NdotV)N
	vec_scale (ndotv, n, &temp);

	//Sets P =  V - (NdotV)N
	vec_diff (&temp, v, p);

}

/* Reflect a vector from a surface plane */
void vec_reflect (
vec_t *n,	/* surface normal */
vec_t *w,	/* incoming ray vector */
vec_t *v)	/* reflected vector */
{

	vec_t temp;
	vec_t U;
	double Udotn;

	//U is reversed input vector w
	vec_scale (-1.0, w, &U);

	//Computes UdotN
	Udotn = vec_dot (&U, n);

	//Computes 2N(UdotN) and stores as n
	vec_scale (2, n, &temp);
	vec_scale (Udotn, &temp, v);

	//Sets V = 2N(UdotN) - U
	vec_diff (&U, v, v);

}

/* Apply transform matrix to vector */
void vec_xform(
mtx_t *m,
vec_t *v1,
vec_t *v2)
{

	vec_t temp;

	temp.x = vec_dot (&(m->row[0]), v1);
	temp.y = vec_dot (&(m->row[1]), v1);
	temp.z = vec_dot (&(m->row[2]), v1);

	vec_copy (&temp, v2);
}

/* Compute the transpose of a matric */
void mtx_transpose (
mtx_t *m1,
mtx_t *m2)
{
	mtx_t temp;
	
	// Changes 1st column of m1 to 1st row of m2
	temp.row[0].x = m1->row[0].x;
	temp.row[0].y = m1->row[1].x;
	temp.row[0].z = m1->row[2].x;

	// Changes 2nd column of m1 to 2nd row of m2
	temp.row[1].x = m1->row[0].y;
	temp.row[1].y = m1->row[1].y;
	temp.row[1].z = m1->row[2].y;

	// Changes 3rd column of m1 to 3rd row of m2
	temp.row[2].x = m1->row[0].z;
	temp.row[2].y = m1->row[0].z;
	temp.row[2].z = m1->row[0].z;

	vec_copy (&temp.row[0], &m2->row[0]);
	vec_copy (&temp.row[1], &m2->row[1]);
	vec_copy (&temp.row[2], &m2->row[2]);

}
