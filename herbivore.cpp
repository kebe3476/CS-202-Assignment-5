/*
CS 202 Assignment 5

Name: Keith Beauvais, 5005338658, CS 202 Assignment 5
*/
#include "herbivore.h"
#include <iostream>
using namespace std;
//constant variables
const double herbivore::PORTION = 0.5;
const double herbivore::MAX_FRACTION = 0.1;

herbivore::herbivore(double initSize, double initRate, double initNeed) : animal(initSize, initRate, initNeed)
{

}
/* nibble - is a function that consumes a portion of a plant object.

-amount is set to PORTION multiplied by size of the meal object
-if the amount is larger than MAX_FRACTION multiplied by needThisWeek, then set amount to
MAX_FRACTION multiplied by needThisWeek
-if the amount is larger than the value returned by stillNeed(), then set amount
to stillNeed()
-Call eat and the meal object’s nibbledOn functions and pass the same amount
into both functions.

	plant& meal- meal of plant type (plant dereference pointer passed in).

	return value - Void function does not return a value.
*/
void herbivore::nibble(plant& meal)
{
  double amount, size, stillN;
  size = getSize();
  stillN = stillNeed();
  amount = PORTION * size;

  if(amount > (MAX_FRACTION*totalNeed())){
    amount = MAX_FRACTION*totalNeed();
  }
  if(amount > stillN){
    amount = stillN;
  }
  eat(amount);
  meal.nibbledOn(amount);
}

herbivore::~herbivore()
{
  cout<<"FISH DIED"<<endl;
}
