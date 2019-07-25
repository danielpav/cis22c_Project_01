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
#include <sstream>

//#include "linkedlist.h"
using namespace std;


// creating structure for the linked list, it can be imprted from a .h file later
struct Apartment
{
	int id;
       	int rent;
       	string location;
	int bedrooms;
       	string laundry;
	Apartment* prev;
	Apartment* next;


};

struct Student
{
	int id;
	int rent;
	int bedrooms;
	string location;
	int laundry;

};

struct ApartmentList
{
	ApartmentList();
	~ApartmentList();

	Apartment* header;
	Apartment*trailer;

	void insert(const Apartment& newapartment);
	void add(Apartment* v, int id, int rent, string location, int br, string lau);
       	void remove(Apartment* v);
	void removeFront();
	bool isEmpty();
		
};

void insertlist() {
}

ApartmentList::ApartmentList() {
	header = new Apartment;
	trailer = new Apartment;
	header->next = trailer;
	trailer->prev = header;
}


bool ApartmentList::isEmpty() 
	{ return (header->next == trailer); }


ApartmentList::~ApartmentList() {
	while (!isEmpty()){
		delete header;
		delete trailer;
	}
}

void ApartmentList::add(Apartment* v, const int id, const int rent, const string location, const int br, const string lau) {
	Apartment* u = new Apartment; 
	u->id = id;
	u->rent = rent;
	u->location = location;
	u->bedrooms = br;
	u->laundry = lau;
	u->next = v;
	u->prev = v->prev;
	v->prev->next = v->prev = u;
}

void ApartmentList::remove(Apartment* v) {
	Apartment* u = v->prev;
	Apartment* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
}

struct CNode {
	Student student;
	CNode* next;
};

struct CircleList {
	CircleList();
	~CircleList();
	bool empty() const;
	void add(const Student& s);
	void remove();
	
	CNode* cursor;
};

CircleList::CircleList()
	: cursor(NULL) {}
CircleList::~CircleList()
	{ while (!empty()) remove(); }

bool CircleList::empty() const
	{ return cursor == NULL; }

void CircleList::add(const Student& s){
	CNode* v = new CNode;
	v->student = s;
	if (cursor == NULL) {
		v->next = v;
		cursor = v;
	}
	else {
		v->next = cursor->next;
		cursor->next = v;
	}
}

void CircleList::remove() {
	CNode* old = cursor->next;
	if (old == cursor)
		cursor = NULL;
	else
		cursor->next = old->next;
	delete old;
}

class WaitingStudentQueue {
		WaitingStudentQueue();
		bool isEmpty() const;
		const Student& front();
		void enqueue(const Student& s);
		void dequeue();
};


int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1]);
	string line;

	ApartmentList alist;

	if (argc!=3)
	{
		cerr << "Usage: "<< argv[0] << " Input apartment file followed by the student file" <<endl;
		exit(-1);
	}
	

	if (ifs.fail())
	{
		cerr<< "Unable to open the file :("<<endl;
		exit(-1);
	}




                while (getline( ifs, line))
                {
                        istringstream ss(line);

                        int id, rent, bedrooms;
                        string location, laundry;

                        ss >> id >> location >> bedrooms >> laundry >> rent;

			alist.add(alist.header->next, id, rent, location, bedrooms, laundry);

			cout << alist.trailer->prev << "\n";

			cout << alist.trailer->prev->id << "\n";
                        
                }
        
        ifs.close();

	cout << alist.trailer;
		
	ifs.open(argv[2]);
	

	if (ifs.fail())
	{
		cerr<< "Unable to open the file :("<<endl;
		exit(-1);
	}
	
	while (getline(ifs,line))
	{
		line;	
	}
}
