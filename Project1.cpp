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
	string  bedrooms;
       	string laundry;
	Apartment* prev;
	Apartment* next;


};

struct Student
{
	int id;
	string name;
	int rent;
	string bedrooms;
	string location;
	string laundry;

};

class ApartmentList
{
	public:
	ApartmentList();
	~ApartmentList();

	Apartment* header;
	Apartment*trailer;

	void insert(const Apartment& newapartment);
	void add(Apartment* v, int id ,int rent, string location, int br, string lau);
       	void remove(Apartment* v);
	bool isEmpty();
	int size;
		
};

void insertlist() {
}

ApartmentList::ApartmentList() {
	header = new Apartment;
	trailer = new Apartment;
	size = 0;
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
	size ++;
}

void ApartmentList::remove(Apartment* v) {
	Apartment* u = v->prev;
	Apartment* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
}

class SNode {
	public:
 		Student student;
		SNode* next;

	friend class WaitingStudentQueue;
};

class WaitingStudentQueue {
	public:
		WaitingStudentQueue();
		bool isEmpty() const;
		void enqueue(Student s);
		SNode* dequeue();
		SNode *front, *rear;
};

WaitingStudentQueue::WaitingStudentQueue() {
	front = NULL;
	rear= NULL;
}


void WaitingStudentQueue::enqueue(const Student s) {
	SNode* v = new SNode();
	v->student = s;
	v->next = NULL;

	if(rear == NULL) {
		front = rear = v;
	}
	else {
		rear->next = v;
		rear = v;
	}
}

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

                }
        
        ifs.close();

	ifs.open(argv[2]);

	if (ifs.fail())
	{
		cerr<< "Unable to open the file :("<<endl;
		exit(-1);
	}
	
	while (getline(ifs,line))
	{
		istringstream ss(line);

		int sid, srent;
		string sname, slocation, slaundry, sbedrooms;	

		ss >> sid >> sname >>  slocation >> sbedrooms >> slaundry >> srent;

		s.id = sid;
		s.rent = srent;
		s.name = sname;
		s.location = slocation;
		s.laundry = slaundry;
		s.bedrooms = sbedrooms;
		squeue.enqueue(s);

	}

	SNode* deq;


	Apartment* p = alist.trailer->prev;
	Apartment* r;
	cout << alist.size  << " " << p->id << endl;
	
	for (SNode* q=squeue.front->next; q!= NULL; q = q->next){
		bool b = 0;
		p = alist.trailer;
		for(int i=0; i<alist.size&&(p->prev!=NULL)&&(b!=1); i++){
			if((p->location == q->student.location || q->student.location == "Any")&&(p->bedrooms == q->student.bedrooms || q->student.bedrooms == "Any")&&(p->rent <= q->student.rent)&&(q->student.laundry == p->laundry || p->laundry == "Any"))
			{
				cout << "The apartment " << p->id << " is assigned to " << q->student.name << " (" << q->student.id << ")." << endl;

				if(p->prev != NULL)
				{

				}


				b =1;
			}
			if (b == 1){
				cout << p->id << endl;
				r = p;
			}
			p = p->prev;

		}
		if (b==1){
			alist.remove(r);
		}
		if (b == 0) {
			cout << "There are no apartments satisfying " << q->student.name << " (" << q->student.id << ")'s requirements." << endl;
		}
	}
	Apartment * a = new Apartment;
	  
	for ( Apartment* cursor = alist.trailer; cursor->prev != NULL; cursor= cursor->prev){
		cout<<"The apartment "<< cursor->id << " is unassigned."<<endl;
	}
return 0;



}
