//Program Name
//Lawrence Su 3645884 University of California Santa Barbara ECE Department
//github.com/lawrence-su123
//CS16 Spring 2019
//Date:
// Program Function
// How to run the program: g++ -o Project1 Project1.cpp File.txt File.txt
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
struct Apartment //apartment node
{
	int id;
       	int rent;
       	string location;
	string  bedrooms;
       	string laundry;
	Apartment* prev;
	Apartment* next;


};

struct Student //student list node
{
	int id;
	string name;
	int rent;
	string bedrooms;
	string location;
	string laundry;

};

class ApartmentList //apartment list
{
	public:
	ApartmentList();
	~ApartmentList();

	Apartment* header;
	Apartment*trailer;
//apartment function constructor
	void insert(const Apartment& newapartment);
	void add(Apartment* v, int id ,int rent, string location, string br, string lau);
       	void remove(Apartment* v);
	bool isEmpty();
	int size;
		
};

//inserting into linked list
void insertlist() {
}

ApartmentList::ApartmentList() {
	header = new Apartment;
	trailer = new Apartment;
	size = 0;
	header->next = trailer;
	header->prev = 0;
	trailer->prev = header;
	trailer->next = 0;
}


bool ApartmentList::isEmpty() //checks if list in empty
	{ return (header->next == trailer); }


ApartmentList::~ApartmentList() {
	while (!isEmpty()){
		delete header;
		delete trailer;
	}
}
//add data into apartment node, and inserts the node in the list
void ApartmentList::add(Apartment* v, const int id, const int rent, const string location, const string br, const string lau) {
	Apartment* u = new Apartment; 
	u->id = id;
	u->rent = rent;
	u->location = location;
	u->bedrooms = br;
	u->laundry = lau;
	u->next = v;
	u->prev = v->prev;
	v->prev->next = u;
	v->prev = u;
	size ++;
}
//remove node from list
void ApartmentList::remove(Apartment* v) {
	Apartment* u = v->prev;
	Apartment* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
}

//student queue node
class SNode {
	public:
 		Student student;
		SNode* next;

	friend class WaitingStudentQueue;
};
//constructor for queue as a linked list
class WaitingStudentQueue {
	public:
		WaitingStudentQueue();
		bool isEmpty() const;
		void enqueue(const Student s);
		SNode* dequeue();
		SNode *front, *rear;
};

WaitingStudentQueue::WaitingStudentQueue() {
	front = 0;
	rear= 0;
}

//add to end of queue, enqueue
void WaitingStudentQueue::enqueue(const Student s) {
	SNode* v = new SNode();
	v->student = s;
	v->next = 0;

	if(rear == 0) {
		front = rear = v;
	}
	else {
		rear->next = v;
		rear = v;
	}
}
//remove from front of queue, dequeue
SNode* WaitingStudentQueue::dequeue() {
	SNode* old = front;
	front = old->next;
	return old;

}




int main(int argc, char *argv[])
{
	ifstream ifs;
	ifs.open(argv[1]);
	string line;

	Student s;
	ApartmentList alist;
	WaitingStudentQueue squeue;

	if (argc!=3) //checking if number of input files is correct
	{
		cerr << "Usage: "<< argv[0] << " Input apartment file followed by the student file" <<endl;
		exit(-1);
	}
	

	if (ifs.fail())
	{
		cerr<< "Unable to open the file :("<<endl;
		exit(-1);
	}




                while (getline( ifs, line)) //while files is still being read
                {
                        istringstream ss(line);

                        int id, rent;
                        string bedrooms, location, laundry;

                        ss >> id >> location >> bedrooms >> laundry >> rent;//assign variables to these values

			alist.add(alist.header->next, id, rent, location, bedrooms, laundry);//add assigned variables to linked list

                }
        
        ifs.close();

	ifs.open(argv[2]);//open second file

	if (ifs.fail())
	{
		cerr<< "Unable to open the file :("<<endl;
		exit(-1);
	}
	
	while (getline(ifs,line))
	{
		istringstream ss(line);

		int sid, srent;
		std::string sname, slocation, slaundry, sbedrooms;	

		ss >> sid >> sname >>  slocation >> sbedrooms >> slaundry >> srent;//assigns strings and ints to variables
		s.id = sid;
		s.rent = srent;
		s.name = sname;
		s.location = slocation;
		s.laundry = slaundry;
		s.bedrooms = sbedrooms;
		squeue.enqueue(s);
		//enqueue the variables

	}
	ifs.close();

	SNode* deq;


	Apartment* p; 
	Apartment* r;
	cout << alist.size  << endl;

	
	//iterate through student queue 
	for (auto q=squeue.front->next; q->next!= 0; q = q->next){
		bool assigned = 0;
		//iterate through apartment list
		for(auto p = alist.trailer->prev; p->prev!=0; p=p->prev){
			if(((p->location == q->student.location) || (q->student.location == "Any"))&&((p->bedrooms == q->student.bedrooms) || (q->student.bedrooms == "Any"))&&(p->rent <= q->student.rent)&&((q->student.laundry == p->laundry) || (q->student.laundry == "Any"))) //check conditions
			{
				cout << "The apartment " << p->id << " is assigned to " << q->student.name << " (" << q->student.id << ")." << endl;

				alist.remove(p);//remove apartment from list if taken
				assigned = 1;
				break;
			}
	
		}
		
		if(assigned==0) 
			cout << "There are no apartments satisfying " << q->student.name << " (" << q->student.id << ")'s requirements." << endl;
	}
	
	//iterate through apartmnet list for unassigned apartments  
	for ( Apartment* cursor = alist.trailer->prev; cursor->prev != 0; cursor= cursor->prev){
		cout<<"The apartment "<< cursor->id << " is unassigned."<<endl;
	}




	exit(0);
}

