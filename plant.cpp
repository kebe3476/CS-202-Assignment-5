/*
CS 202 Assignment 5

Name: Keith Beauvais, 5005338658, CS 202 Assignment 5
*/
#include "plant.h"
#include <iostream>
using namespace std;

plant::plant(double initSize, double initRate) : organism(initSize, initRate)
{

}
/* nibbledOn - decreases the size by amount, if the amount is larger than
the size, then set the size to 0 using death function.

	double amount - passes in amount from nibble in herbivore class

	return value - Void function does not return a value.
	*/
void plant::nibbledOn(double amount)
{
  if(amount > getSize()){
    death();
    return;
  }
  alterSize((-amount));
}

plant::~plant()
{
  cout <<"PLANT IS DEAD" << endl;
}
