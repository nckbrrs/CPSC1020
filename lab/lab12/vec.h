/* vec.cpp */

/* C++ vector class implementation*/

#include <iostream>
#include <math.h>

using namespace std;

class vec_t
{
	private:
   	double x;
   	double y;
   	double z;

	public:
   	vec_t();                        // set vec to (0, 0, 0)
   	vec_t(double, double, double);  // set vec to values provided
	
   	void vec_unit(vec_t &); 
   	vec_t operator+(vec_t &rhs);   // this + rhs
   	vec_t operator|(vec_t &rhs);   // projection of rhs on plane with
   	                               // normal this

   	vec_t  operator&(vec_t &rhs);  // cross product of this and rhs
	
   	double operator!(void);        // length of this vector

		/* Output or input of an instance of a complete vec_t  */
   	friend ostream & operator<<(ostream &out, const vec_t &ovec);
   	friend istream & operator>>(istream &in, vec_t &ivec);

		/* Product of vector and scalar */
   	friend vec_t operator*(const double val, const vec_t &rhs);
   	friend vec_t operator*(const vec_t &lhs, const double val);

		/* Vector divided by scalar */
   	friend vec_t operator/(const vec_t &lhs, const double val);

		/* Componentwise lhs / rhs */
   	friend vec_t operator/(const vec_t &lhs, const vec_t &rhs);
};


