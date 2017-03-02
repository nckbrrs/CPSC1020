#define NAME_LEN 16

#include <string.h>
#include <stdio.h>

/* A meaningless structure to put on the list */

class e_t
{
	public:
		// constructor
    	e_t(char txt[], int len) {
       	strcpy(ename, txt);
       	ecount = len;
       	fprintf(stderr, "creating   e_t %s  at %p \n", this->ename, this);
    	}

		// destructor
   	~e_t(void) {
			fprintf(stderr, "destroying e_t %s  at %p \n", this->ename, this); 
		}

   	void eprint() {
      	fprintf(stderr, "%-12s %6d \n", ename, ecount);
   	}

	private:
   	char ename[NAME_LEN];    // entity name
   	int  ecount;             // number of entities
};

