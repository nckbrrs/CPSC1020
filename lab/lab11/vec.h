/* vec.h */

/* C++ vector class */

#include <iostream>
#include <math.h>

using namespace std;

class vec_t
{
public:
   vec_t();
   vec_t(double, double, double);

   /* subtract this vector from v2 with the result in v3 */

   void vec_diff(const vec_t  v2, vec_t &v3);
   void vec_diff(const vec_t *v2, vec_t &v3);
   void vec_diff(const vec_t &v2, vec_t *v3);

   /* Use cin to read x, y, z componentes from stdin */

   void vec_read(void);

   /* Print the label,  x, y, z and newline to the standard */
   /* error IN THE FORMAT SHOWN in the example output */

   void vec_prn(const char *label);

   /* Return the dot product of this with the v2 vector */

   double vec_dot(const vec_t &v2);
   double vec_dot(const vec_t *v2);

   /* multiply x, y, z components by "fact"  */

   void vec_scale(double fact);

   /* Return the length of this vector */

   double vec_len(void);

private:
   double x;
   double y;
   double z;
};


