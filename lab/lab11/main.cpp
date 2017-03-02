/* main.c */

#include "vec.h"

using namespace std;

int main()
{
   vec_t v1(1.0, 2.0, 3.0);
   vec_t v2(4.0, 5.0, 6.0);
   vec_t v3;
   vec_t v4;
   double dot;
   double len;

   cout << "Enter 3 values for v3"  << endl;
   v3.vec_read();
   v3.vec_prn("v3 = ");

   v1.vec_diff(v3, v4);
   v4.vec_prn("v4 = ");

   v1.vec_diff(v3, &v4);
   v4.vec_prn("v4 = ");

   v1.vec_diff(&v3, v4);
   v4.vec_prn("v4 = ");

   v4.vec_scale(5);
   v4.vec_prn("v4 = ");

   dot = v4.vec_dot(v3);
   cerr << dot << '\n';

   len = v4.vec_len();
   cerr << len << '\n';

}
