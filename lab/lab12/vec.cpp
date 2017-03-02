/*
	Nicholas Barrs
	CPSC 1021-003
	nbarrs
	April 16, 2015
	lab 12 - vec.cpp
*/

#include "vec.h"
#include <iostream>
#include <math.h>

// set vec to (0, 0, 0)
vec_t::vec_t()
{
	x = 0;
	y = 0;
	z = 0;
}

// set vec to values provided (a, b, c)
vec_t::vec_t(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

// this + rhs
vec_t vec_t::operator+(vec_t &rhs)
{
	vec_t newvec;
	newvec.x = x + rhs.x;
	newvec.y = y + rhs.y;
	newvec.z = z + rhs.z;
	return newvec;
}

// projection of rhs on plane with normal this
vec_t vec_t::operator|(vec_t &rhs)
{
	vec_t temp;
	vec_t proj;
	double dotprod;

	// NdotV
	dotprod = sqrt((x * rhs.x) + (y * rhs.y) + (z * rhs.z));

	// (NdotV)N
	temp.x = dotprod * x;
	temp.y = dotprod * y;
	temp.z = dotprod * z;

	// P = V - (NdotV)N
	proj.x = rhs.x - temp.x;
	proj.y = rhs.y - temp.y;
	proj.z = rhs.z - temp.z;

	return proj;
}

// cross product of this and rhs
vec_t vec_t::operator&(vec_t &rhs)
{
	vec_t crossprod;
	crossprod.x = (y * rhs.z) - (z * rhs.y);
	crossprod.y = (z * rhs.x) - (x * rhs.z);
	crossprod.z = (x * rhs.y) - (y * rhs.x);
	return crossprod;
}

// length of this vector
double vec_t::operator!(void)
{
	return sqrt(((x * x) + (y * y) + (z * z)));
}

// output or input of an instance of a complete vec_t
ostream & operator<< (ostream &out, const vec_t &ovec)
{
	out << ovec.x << ", " << ovec.y << ", " << ovec.z << endl;
	return out;
}

istream & operator>> (istream &in, vec_t &ivec)
{
	in >> ivec.x >> ivec.y  >> ivec.z;
	return in;
}

// product of vector and scalar
vec_t operator* (const double val, const vec_t &rhs)
{
	vec_t prod;

	prod.x = val * rhs.x;
	prod.y = val * rhs.y;
	prod.z = val * rhs.z;

	return prod;
}

vec_t operator* (const vec_t &lhs, const double val)
{
	vec_t prod;
	
	prod.x = val * lhs.x;
	prod.y = val * lhs.y;
	prod.z = val * lhs.z;

	return prod;
}

// vector divided by scalar
vec_t operator/ (const vec_t &lhs, const double val)
{
	vec_t quot;

	quot.x = lhs.x / val;
	quot.y = lhs.y / val;
	quot.z = lhs.z / val;

	return quot;
}

// componentwise lhs / rhs
vec_t operator/ (const vec_t &lhs, const vec_t &rhs)
{
	vec_t quot;

	quot.x = lhs.x / rhs.x;
	quot.y = lhs.y / rhs.y;
	quot.z = lhs.z / rhs.z;

	return quot;
}

