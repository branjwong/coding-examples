/*
 * Customer.cpp
 *
 *  Created on: Mar 5, 2010
 *      Author: Brandon J Wong
 */

#include "Customer.h"

Customer::Customer(void){
	name = "noname";
	initial = 'x';
	account = 0;
}

Customer::~Customer(void){

}

Customer::Customer(string x, char y) {
	name = x;
	initial = y;
	account = 0;
}

Customer::Customer(string x, char y, int z) {
	name = x;
	initial = y;
	account = z;
}

string Customer::get_name(){
	return name;
}

char Customer::get_initial(){
	return initial;
}

int Customer::get_account(){
	return account;
}

void Customer::setBalance(int z){
	account = z;
}

bool Customer::operator<(const Customer& c) const{
	return (name+initial) < (c.name+c.initial);
}

bool Customer::operator>(const Customer& c) const{
	return (name+initial) > (c.name+c.initial);
}

bool Customer::operator<=(const Customer& c) const{
	return (name+initial) <= (c.name+c.initial);
}
bool Customer::operator>=(const Customer& c) const{
	return (name+initial) >= (c.name+c.initial);
}
bool Customer::operator==(const Customer& c) const{
	return (name+initial) == (c.name+c.initial);
}
bool Customer::operator!=(const Customer& c) const{
	return (name+initial) != (c.name+c.initial);
}


ostream& operator<<(ostream & os,  Customer & c) {
	os << c.name << ", " << c.initial << ". (" << c.account << ")";
}
