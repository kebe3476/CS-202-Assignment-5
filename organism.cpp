/*
CS 202 Assignment 5

Name: Keith Beauvais, 5005338658, CS 202 Assignment 5
*/
#include "organism.h"

organism::organism(double initSize, double initRate)
{
	size = initSize;
	growthRate = initRate;
}
/* simulateWeek - increments the size by growthRate

	return value - Void function does not return a value.
	*/
void organism::simulateWeek()
{
	alterSize(growthRate);
}
/* assignRate - assigns growthRate with the value passed in

	double newRate - passes in a rate that is new

	return value - Void function does not return a value.
	*/
void organism::assignRate(double newRate)
{
	growthRate = newRate;
}
/* alterSize - increases the size by amount if the size is equal to or less than
0 the death function is called.

	double amount - new alter size amount (plant or fish)

	return value - Void function does not return a value.
	*/
void organism::alterSize(double amount)
{
	size += amount;
	if(size <= 0){
		death();
		return;
	}
}
/* death - sets growthRate and size to 0

	return value - Void function does not return a value.
	*/
void organism::death()
{
	growthRate = 0;
	size = 0;
}
/* getSize - returns size

	return value - Void function does not return a value.
	*/
double organism::getSize() const
{
	return size;
}
/* getRate - returns growthRate

	return value - Void function does not return a value.
	*/
double organism::getRate() const
{
	return growthRate;
}
/* isAlive - returns true if size is larger than 0 and returns false otherwise

	return value - bool returns true is size is greater than 0 and false otherwise.

	*/
bool organism::isAlive() const
{
	if(size > 0){
		return true;
	}
	return false;
}

organism::~organism()
{
	growthRate = 0;
	size = 0;
}
