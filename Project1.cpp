//Program Name
//Lawrence Su 3645884 University of California Santa Barbara ECE Department
//github.com/lawrence-su123
//CS16 Spring 2019
//Date:
// Program Function
// How to run the program
// Bugs (Hopefully this line will be empty :) )
//



#include <iostream>
#include <cstdlib>
#include <fstream> //reading from /txt files
#include <string>
#include <cstring>

//#include "linkedlist.h"
using namespace std;


// creating structure for the linked list, it can be imprted from a .h file later
struct Apartment
{
	int id;
	int rent;
	char location;
	int bedrooms;
	bool laundry;


	Node *next;
	Node *prev;
};

struct student
{
	int id;
	int rent;

struct Apartment_list
{
	Node* head;
	Node*tail;
};

void insertlist() {
}


//void 



int main(int argc, char *argv[])
{
	ifstream ifs;
	string my_line;
	if (argc!=3)
	{
		cerr << "Usage: "<< argv[0] << " Input apartment file followed by the student file" <<endl;
		exit(-1);
	}
	ifs.open(argv[1]);
	

	if (ifs.fail())
	{
		cerr<< "Unable to open the file :("<<endl;
		exit(-1)
	}
	
	while (getline(ifs,my_line))
	{
		if (my_line != " ")
		{
			counter ++;
			for (int i =0; i<
		}
	}
	ifs.close();

		
	ifs.open(argv[2]);
	

	if (ifs.fail())
	{
		cerr<< "Unable to open the file :("<<endl;
		exit(-1)
	}
	
	while (getline(ifs,my_line))
	{
	
	}
	return 0
}
