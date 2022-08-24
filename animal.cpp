/*
CS 202 Assignment 5

Name: Keith Beauvais, 5005338658, CS 202 Assignment 5
*/
#include "animal.h"
#include "cmath"

animal::animal(double initSize, double initRate, double initNeed) : organism(initSize, initRate)
{
	needThisWeek = initNeed;
	eatenThisWeek = 0;
}
/* assignNeed - reassigns needsThisWeek to the value passed in

	newNeed- double value that sets needThisWeek to the newNeed

	return value - Void function does not return a value.
	*/
void animal::assignNeed(double newNeed)
{
	needThisWeek = newNeed;
}
/* eat - increments eatenThisWeek by amount

	amount- increases eatenThisWeek by amount

	return value - Void function does not return a value.
	*/
void animal::eat(double amount)
{
	eatenThisWeek += amount;
	//std::cout << eatenThisWeek << std::endl;
}
/* simulateWeek - the function does the following:
-Changes the sign on growthRate based on whether the value returned by stillNeed();
sets the sign to negative if stillNeed() returns a positive number and sets the
sign to positive if stillNeed() returns 0.
-Then the function calls organism’s simulateWeek() function, sets eatenThisWeek
to 0, checks if stillAlive() if no longer alive then call death() function

	return value - Void function does not return a value.
	*/
void animal::simulateWeek()
{
	double temp;
	//std::cout<<getRate()<<std::endl;

	if(stillNeed() > 0){
		temp = getRate();
		if(temp > 0){
			assignRate((-temp));//negative abs value so it will always be negative
		}

	}
	else if(stillNeed() == 0){
		temp = getRate();
		assignRate(abs(temp));// abs value so that it will always be positive
	}

	organism::simulateWeek();

	if(isAlive() == false){
		death();
	}
	eatenThisWeek = 0;
}
/* stillNeed - returns 0 if eatenThisWeek is greater than or equal to needThisWeek,
and returns the difference between needThisWeek and eatenThisWeek otherwise

	return value - returns a 0 or the difference between needThisWeek and eatenThisWeek.
	*/
double animal::stillNeed() const
{

	double difference;

	if(eatenThisWeek >= needThisWeek){
		return 0;
	}
	else{
	difference = (needThisWeek - eatenThisWeek);

	}
	//std::cout <<difference<<std::endl;
	return difference;
}
/* totalNeed-returns needThisWeek

	return value - returns double needThisWeek.
	*/
double animal::totalNeed() const
{
	return needThisWeek;
}

animal::~animal()
{
	needThisWeek=0;
	eatenThisWeek =0;
}
