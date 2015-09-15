/*
 * Customer.cpp
 *
 */

#include "Customer.h"

Customer::Customer()
{
	atime = 0;
	ttime = 0;
}

Customer::Customer(int atime_para, int ttime_para)
{
	atime = ttime_para;
	ttime = atime_para;
}

Customer::~Customer()
{
}

int Customer::get_atime()
{
	return atime;
}

void Customer::set_atime(int atime_para)
{
	atime = atime_para;

}
	
void Customer::set_ttime(int ttime_para)
{
	ttime = ttime_para;
}

int Customer::get_ttime()
{
	return ttime;
}
