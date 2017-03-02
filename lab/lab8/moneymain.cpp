#include <iostream>
#include <iomanip>
#include "money.h"

using namespace std;

int main() {
   money_t checking;
   money_t savings(575.85);
   money_t other(950, 55);
   int amt;

   /**
      LAB EXERCISE.  DECLARE A POINTER TO A money_t AND 
      USE new WITH ONE OF THE CONSTRUCTORS TO CREATE AN
      INSTANCE OF THE CLASS.
   **/
	money_t *my_money = new money_t(550.75);


   cout << fixed << showpoint << setprecision(2);

   cout << "checking amount:  "
        << checking.compute_value() 
        << endl << endl;

   cout << "Enter checking dollars (integer value): ";
   cin >> amt;
   checking.set_dollars(amt);

   cout << "Enter checking cents (integer value): ";
   cin >> amt;
   checking.set_cents(amt);

   cout << "\nchecking amount after read:  "
        << checking.compute_value() 
        << endl << endl;

   cout << "savings amount:  "
        << savings.get_dollars() 
        << " dollars and "
        << savings.get_cents()
        << " cents" << endl << endl;

   cout << "other amount in total cents:  "
        << other.value_in_cents() 
        << " cents" << endl << endl;

   cout << "Setting new amount in checking" << endl;
    
   checking.set(1200, 98);

   cout << "new checking amount:  "
        << "$"  <<  checking.compute_value() 
        << endl << endl;

   // PART OF EXERCISE
   cout << "printing my_money" << endl;
   cout << "$" 
        << my_money->compute_value() << endl;

   return 0;
}

