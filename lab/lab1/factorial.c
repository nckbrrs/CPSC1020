/* factorial.c
   example to use with gdb

	no segfault, but the program does not work
	- - why??
*/

#include <stdio.h>

long factorial(int n);

int main(void) {
	int n;
	long val;

	printf("enter a number: ");
	scanf("%i", &n);
	val = factorial(n);
	
	printf("val is %li\n\n", val);
}

long factorial(int n) {
	long result = 1;

	while (n) {
		result *= n;
		n--;
	}

	return result;
}
