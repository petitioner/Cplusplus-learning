#include<cstdio>
#include<iostream>
using namespace std;

typedef struct Node{
	int data;
	struct Node *prev;
	struct Node *next;
}Node,*link;

class List
{
	public:
	link head;/* Node *tail  */
	link tail;/* is different. */

	int length;

	List()
	{ 
		head = tail = new Node;
		length=0;
	}
	List(const List &li)
	{
		length = li.length;
	}

	virtual bool insert(int)=0;
	virtual bool remove()=0;
	void disp()
	{
		if(length==0)
		{
			cout<<"it is Empty!"<<endl;
			return;
		}
		for(link it=head->next;it!=0;it=it->next)
			cout<<it->data<<'\t';
		cout<<endl;
	}
	virtual ~List()
	{

	}
	
};
class Queue:public List
{
	public:

	Queue():List()
	{ 
	}

	bool insert(int n)
	{
		Node *p = new Node;//throw exception;
		p->data = n;
		p->prev=0;
		
		p->next=0;
		tail->next = p;
		tail = p;

		length++;
		cout<<"Queue::Length:"<<length<<endl;
		return true;
	}
	bool remove()
	{
		if(head == tail) return false;
		
		link first = head->next;
		head->next = first->next;
	
		if(tail == first) tail = head;

		delete first;

		length--;
		cout<<"Queue::Length:"<<length<<endl;
		return true;
	}

};



int main(int argc, char *argv[])
{
	Queue q;
	q.insert(1);q.disp();
	q.insert(2);q.disp();
	q.insert(3);q.disp();
	q.insert(4);q.disp();
	q.insert(5);q.disp();
	q.remove();q.disp();
	q.remove();q.disp();
	q.remove();q.disp();
	q.remove();q.disp();
	q.remove();q.disp();
	q.remove();q.disp();

	return 0;
}
