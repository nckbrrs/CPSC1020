/*
	Nicholas Barrs	
	nbarrs
	CPSC 1021-003
	12 March 2015
	lab 8
	money.cpp - code for functions in money.h
*/

#include <cstdlib>
#include <iostream>
#include "money.h"
using namespace std;

//constructors/destructors
money_t::money_t () {
	dollars = 0;
	cents = 0;
}

money_t::money_t (double amt) {
	if (amt <= 0.0) {
		dollars = 0;
		cents = 0;
	}
	
	else {
		dollars = ((int)amt);
		cents = ((amt * 100) - (dollars * 100));
	}
}


money_t::money_t (int dollars, int cents) {
	if (dollars < 0)
		dollars = 0;

	else
		this->dollars = dollars;

	if (cents < 0)
		cents = 0;
	else
		this->cents = cents;
}

money_t::~money_t() {
	cout << "destructor invoked.\n";
}

//getters
int money_t::get_dollars() {
	return dollars;
}

int money_t::get_cents() {
	return cents;
}

//setters
void money_t::set_dollars(int amount) {
	if (amount < 0)
		dollars = 0;
	else
		dollars = amount;
}

void money_t::set_cents(int amount) {
	if (amount < 0)
		cents = 0;
	else
		cents = amount;
}

void money_t::set(int dollar_amt, int cent_amt) {
	if (dollar_amt < 0)
		dollars = 0;
	else
		dollars = dollar_amt;

	if (cent_amt < 0)
		cents = 0;
	else
		cents = cent_amt;

}

//other functions
int money_t::value_in_cents() {
	return ((dollars * 100) + cents);
}

double money_t::compute_value() {
	return (dollars + (cents / 100.00));
}

