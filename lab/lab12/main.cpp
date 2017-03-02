/* main.c */

#include "vec.h"

int main()
{
   vec_t v1(1.0, 2.0, 3.0);
   vec_t v2(4.0, 5.0, 6.0);
   vec_t v3;
   vec_t v4;
   double len;

   cerr << "Enter value for v3: ";
   cin  >> v3;
   cout << "v1 = " << v1 << "v2 = " << v2 << "v3 = " << v3;

   len = !v3;
   cout << "\nv3 len = " << len << endl;

   v3  = v1 | v2;
   cout << "\nv1 | v2 = " << v3  << endl;

   v3  = v1 & v2;
   cout << "\nv1 & v2 = " << v3  << endl;

   v4 = v2 + v1;
   cout << "\nv2 + v1 = " << v4 << endl;

   v3 = v2 / v1;
   cout << "\nv2 / v1 = " << v3 << endl;

	return 0;
}
