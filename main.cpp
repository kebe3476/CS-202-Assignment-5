/*
CS 202 Assignment 5

Name: Keith Beauvais, 5005338658, CS 202 Assignment 5
*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "herbivore.h"
#include "plant.h"
#include "organism.h"
#include "randNum.h"

using namespace std;

const int ROWS = 5;
const int COLS = 5;

void buildPondSimulator(ifstream&, organism***);
void simulateAWeek(organism***, randNum&);
void outputOrganism(organism*);
void clearSimulation(organism***);
double stringConvertDouble(string s);
int stringConvertInt(string s);

int main()
{
    organism *** pond;
    ifstream infile;
    string filename;
    randNum rN("RandomNums.txt");
    int weeks;

    //allocate the pond structure

    //allocate the amount of rows
    pond = new organism**[ROWS];

    //allocate the columns for each row
    for (int i = 0; i < ROWS; i++)
        pond[i] = new organism*[COLS];

    //This would be an empty pond initial so each cell is set to empty
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            pond[i][j] = NULL;

    //ask for pond file and re-prompt if not found
    do
    {
        cout << "Enter pond data file: ";
        cin >> filename;

        infile.open(filename.c_str());
    }
    while (!infile.is_open());

    //Time to build the simulation, reads the contents from the CSV file
    //and inserts objects into pond array

    buildPondSimulator(infile, pond);

    //Asks the user for the amount of weeks they wish to simulate
    //re-prompts if invalid input read
    cout << "Enter amount of weeks for the simulation: ";
    cin >> weeks;

    while (cin.fail() || weeks <= 0)
    {
        if (cin.fail())
        {
            cin.fail();
            cin.ignore(100, '\n');
        }
        cout << "Enter amount of weeks for the simulation: ";
        cin >> weeks;
    }

    //Simulates the amount of weeks, calls simulateAWeek function
    //weeks amount of times
    for (int i = 0; i < weeks; i++)
    {
        cout << "WEEK " << i + 1 << " RESULTS" << endl;
        simulateAWeek(pond, rN);
        cout << endl << endl;
    }

    cout << "Ending simulation" << endl;

    //destroy the simulation
    clearSimulation(pond);

    return 0;
}
/* buildPondSimulator -  this function takes in an already opened filestream
that reads from a CSV file and empty 2D array of organism objects. inserted an
herbivore or plant object into pond[r][c]. Every line in the CSV file will contain:
ORGANISM_TYPE,SIZE,GROWTH_RATE,X_COORDINATE,Y_COORDINATE
parsed the lines and convert each element into its correct type (SIZE and
GROWTH_RATE converted in double and X_COORDINATE and Y_COORDINATE converted into
int, and ORGANISM_TYPE will remain a string), assigned pond[X_COORDINATE][Y_COORDINATE]
withnew herbivore(size, rate, size * 0.1) or new plant(size, rate)based
on whether ORGANISM_TYPE contains "FISH" or "PLANT" respectively.

	ifstream& infile - infiles the PondData.csv

  organism *** pond - 2D pointer array of organism type

	return value - Void function does not return a value.
	*/
void buildPondSimulator(ifstream& infile, organism *** pond)
{

  string line, type, subString, type2, type3, type4, type5;
  int x_coord, y_coord, index;
  double size, gRate;
  stringstream s;

  getline(infile,line);
  int count = 0;
  while(!infile.eof()){
      stringstream s(line);
      getline(s,type,',');  //parsing through line
      getline(s,type2,','); //parsing through line
      getline(s,type3,','); //parsing through line
      getline(s,type4,','); //parsing through line
      getline(s,type5,','); //parsing through line
      size = stringConvertDouble(type2); //converts string to double
      gRate = stringConvertDouble(type3); //converts string to double
      x_coord = stringConvertInt(type4); //converts string to int
      y_coord = stringConvertInt(type5); //converts string to int

      if(type == "PLANT"){
        pond[x_coord][y_coord] = new plant(size, gRate);//passing in size and gRate to plant

      }
      if(type == "FISH"){
        pond[x_coord][y_coord] = new herbivore(size, gRate, (size*.1));//passing in size and gRate to herbivore

      }
      getline(infile,line);
    }
  }
  /* simulateAWeek -  this function simulates one week of the pond simulator,
  will simulate 100 activities and each activity does the following:
  -Get a random x1, y1, x2, and y2 indices to investigate two potential organisms
   in the pond array
   -two pointers organism * o1, * o2 and set them with the content in pond[x1][y1] and
   pond[x2][y2] respectively
   -Check the contents in o1 and o2 for whether they are NULL or if they point to an herbivore
   and/or plant object
   Cases:
   -If they are both NULL then this is a failed activity, thus nothing happens
   -If they both point to plant objects, then this would be a failed activity, thus nothing happens
   -If one of the pointers is NULL and the other is a plant then nothing happens
   -If one of the pointers is NULL and the other points to an herbivore, assign
   NULL to where the herbivore object used to be be and assign the herbivore obect
   to where the NULL used to be
  -If they both point to herbivore objects then you need to swap their positions
  in the pond array
  -If one of the pointers points to an herbivore object and the other points to a
  plant object, then the herbivore object’s nibble function is called and
  pass in the plant object as the parameter, then swapped positions.

  Once all 100 activities are simulated, called simulateWeek() function for
  each element. Check each object if it is still alive, if no longer alive then
  deallocated the object pond[r][c] and then set pond[r][c] to NULL


  	randNum& rN - random number passed in from .txt file % 5

    organism *** pond - 2D pointer array of organism type

  	return value - Void function does not return a value.
  */
void simulateAWeek(organism *** pond, randNum& rN)
{
  int x1,x2,y1,y2, count = 0;
  organism *o1, *o2;

  for(int i = 0; i < 100; i++){
    bool o1Plant = false, o2Plant = false, o1Herb = false, o2Herb = false;
    x1 = ((rN.getNextRand())%5);
    y1 = ((rN.getNextRand())%5);
    x2 = ((rN.getNextRand())%5);
    y2 = ((rN.getNextRand())%5);

    o1 = pond[x1][y1];
    o2 = pond[x2][y2];

    //checking to see if o1 and o2 not NULL and checking if plant or herb
    if(o1 != NULL){
      o1Plant = dynamic_cast<plant*>(o1);
      o1Herb = dynamic_cast<herbivore*>(o1);
    }
    if(o2 != NULL){
      o2Plant = dynamic_cast<plant*>(o2);
      o2Herb = dynamic_cast<herbivore*>(o2);
    }
    //Cases for the simulation:
    //checking too see if o1 and o2 NULL:
    if((o1 == NULL && o2 == NULL)){
      continue;
    }
    //Both Plants
    if(o1Plant == true && o2Plant == true){
      continue;
    }
    //Plant and Null
    if((o1Plant == true || o2Plant == true) && (o1 == NULL || o2 == NULL)){
      continue;
    }
    //Herb and null
    if((o1Herb == true || o2Herb == true) && (o1 == NULL || o2 == NULL)){
      if(o1Herb == true && o2 == NULL){
        pond[x1][y1] = o2; //swappes whats in o1 with o2
        pond[x2][y2] = o1;//swappes whats in o2 with o1
        continue;
      }
      if(o1 == NULL && o2Herb == true){
        pond[x2][y2] = o1;//swappes whats in o2 with o1
        pond[x1][y1] = o2;//swappes whats in o1 with o2
        continue;
      }
    }
    //Both herbs
    if(o1Herb == true && o2Herb == true){
      pond[x2][y2] = o1;//swappes whats in o2 with o1
      pond[x1][y1] = o2;//swappes whats in o1 with o2
      continue;
    }
    //Herb and Plant
    if((o1Herb == true || o2Herb == true) && (o1Plant == true || o2Plant == true)){
      if(o1Herb == true && o2Plant == true){
        herbivore * h;
        plant * p;

        h = dynamic_cast<herbivore*>(o1); // pointing to herb object
        p = dynamic_cast<plant*>(o2); // pointing to plant object

        h -> nibble (*p);

        pond[x2][y2] = o1;//swappes whats in o2 with o1
        pond[x1][y1] = o2;//swappes whats in o1 with o2
        continue;

      }
      if(o1Plant == true && o2Herb == true){
        herbivore * h;
        plant * p;

        h = dynamic_cast<herbivore*>(o2); // pointing to herb object
        p = dynamic_cast<plant*>(o1); // pointing to plant object

        h -> nibble (*p);
        pond[x2][y2] = o1;//swappes whats in o2 with o1
        pond[x1][y1] = o2;//swappes whats in o1 with o2
        continue;
      }
    }
  }

  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      if(pond[i][j] != NULL){ // checks to see if pond[i][j] is NULL
        pond[i][j] -> simulateWeek(); //calls organisms simulateWeek
        if(pond[i][j] -> isAlive()==false){
          delete pond[i][j];
          pond[i][j] = NULL;
        }
        else{
          outputOrganism(pond[i][j]);
        }
      }
    }
  }
}
/* outputOrganism -  Outputsthestring"Fish with weight"or"Plant with weight"
   depending on whether org points to an herbivore or plant object and then output
   org->getSize()

	 organism * org - passes in org pointer of type organism

	 return value - Void function does not return a value.
	*/
void outputOrganism(organism * org)
{
  if(dynamic_cast<herbivore*>(org)){
    cout<<"Fish with weight " << org -> getSize()<<endl;
  }
  if(dynamic_cast<plant*>(org)){
    cout<<"Plant with weight " << org -> getSize()<<endl;
  }
}
/* clearSimulation -  deallocates all the objects in each pond[r][c] position
and then deallocates the pointers as well

	 organism *** pond - 2D pointer array of organism type

	 return value - Void function does not return a value.
	*/
void clearSimulation(organism *** pond)
{
  //for the elements in the 2D array
  for(int i = 0;i < ROWS; i++ ){
    for(int j = 0;j < COLS; j++){
      if(pond[i][j] != NULL){
          delete pond[i][j];
      }
    }
  }
  //for the rows in the 2D array
  for(int i = 0;i < ROWS; i++ ){
    if(pond[i] != NULL){
      delete pond[i];
    }
  }
  //for the entire array
  delete [] pond;
}
/* stringConvertDouble - This function converts strings into doubles.

string s - this string is passed in from the saveField function.

return value - returns a double from the string when called in saveField function.

*/
double stringConvertDouble(string s){
  stringstream ss;
  double value;

  ss << s;
  ss >> value;

  return value;
}
/* stringConvertInt - This function converts strings into int.

string s - this string is passed in from the saveField function.

return value - returns a double from the string when called in saveField function.

*/
int stringConvertInt(string s){
  stringstream ss;
  int value;

  ss << s;
  ss >> value;

  return value;
}
