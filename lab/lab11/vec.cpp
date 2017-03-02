/*
	Nicholas Barrs
	nbarrs
	CPSC 1021-003
	April 9, 2015
	lab 11 - vec.cpp
*/

#include "vec.h"
#include <stdio.h>
#include <stdlib.h>

/* construct a vector and initialize values to 0 */
vec_t::vec_t ()
{
	x = 0;
	y = 0;
	z = 0;
}

/* construct a vector and initialize values to parameters sent in */
vec_t::vec_t(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

/* subtract this vector from v2 with result in v3 */
void vec_t::vec_diff (const vec_t v2, vec_t &v3)
{
	v3.x = v2.x - this->x;
	v3.y = v2.y - this->y;
	v3.z = v2.z - this->z;
}

void vec_t::vec_diff (const vec_t *v2, vec_t &v3)
{
	v3.x = v2->x - this->x;
	v3.y = v2->y - this->y;
	v3.z = v2->z - this->z;
}

void vec_t::vec_diff (const vec_t &v2, vec_t *v3)
{
	v3->x = v2.x - this->x;
	v3->y = v2.y - this->y;
	v3->z = v2.z - this->z;
}

/* Use cin to read x, y, z components from stdin */
void vec_t::vec_read (void)
{
	cin >> x >> y >> z;
}

/* Print the label, x, y, z, and newline to the standard */
/* error IN THE FORMAT SHOWN in the example output */
void vec_t::vec_prn (const char *label)
{
	cerr << label <<  x << ", " << y << ", " << z << endl;
}

/* Return the dot product of this with the v2 vector */
double vec_t::vec_dot (const vec_t &v2)
{
	return ((this->x * v2.x) + (this->y * v2.y) + (this->z * v2.z));
}

double vec_t::vec_dot (const vec_t *v2)
{
	return ((this->x * v2->x) + (this->y * v2->y) + (this->z * v2->z));
}

/* Multiply x, y, z components by "fact" */
void vec_t::vec_scale (double fact)
{
	this->x = fact * this->x;
	this->y = fact * this->y;
	this->z = fact * this->z;
}

/* Return the length of this vector */
double vec_t::vec_len (void)
{
	return sqrt(vec_dot(this));
}


