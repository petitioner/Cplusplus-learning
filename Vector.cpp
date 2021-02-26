#include<cstdio>
#include<iostream>
using namespace std;

class Vector
{
	public:
	int head;
	int tail;

	int *data;
	int max_size;
	static const int INIT_SIZE = 5;/* wrong if no static */
	static const int INCREMENT = 10;/*increment to expand*/

	Vector()
	{
		data = new int[INIT_SIZE];
		head = 0;
		tail = 0;
		max_size = INIT_SIZE;
	}
	Vector(const Vector &v)
	{
		head = v.head;
		tail = v.tail;
		data = new int[max_size];/*!!*/
		for(int i=0;i<max_size;i++)
			data[i] = v.data[i];
	}

	virtual int size()=0;
	virtual bool insert(int n)=0;
	virtual bool remove()=0;
	virtual bool resize()=0;
	virtual void disp()=0;

	virtual ~Vector()
	{
		delete[] data;
	}
};
class Queue:public Vector
{
	public:
		
	Queue()
	{
		data = new int[INIT_SIZE];
		head = 0;
		tail = 0;
		max_size = INIT_SIZE;
	}
	int size(){ return (tail+max_size - head)%max_size; }
	bool insert(int n)
	{
		if((tail+1)%max_size==head)
		{
			/* throw resize? */
			cout<<"No Room!"<<endl;
			return false;
		}

		data[tail]=n;
		tail = (tail+1)%max_size;
		return true;
	}
	bool remove()
	{
		if(head == tail)
			return true;/* do nothing if empty */
		head = (head+1)%max_size;
	}
	void disp()
	{
		cout<<"Queue from tail to head:"<<endl;
		for(int i=head;i%max_size!=tail;i++)
			cout<<data[i]<<'\t';
		cout<<endl;
	}

	/* 1th,count size;2nd,new size;
	   3rd,copy;4th,delete        */
	bool resize()
	{
		return false;
	}

};
class Stack:public Vector
{
	public:
	/* operator on the tail side */
	Stack():Vector()
	{
	}
	Stack(const Stack &s):Vector(s)
	{
	}

	int size(){return (tail - head);}
	bool insert(int n)
	{
		/* must leave one room?*/
		if(tail - head >= max_size)
		{
			/* throw resize? */
			cout<<"No Room!"<<endl;
			return false;
		}

		data[tail]=n;
		tail++;
		return true;
	}
	bool remove()
	{
		if(head == tail)
			return true;/* do nothing if empty */
		tail--;
		return true;
	}
	bool resize()
	{
		return false;
	}
	void disp()
	{
		cout<<"Stack from head to tail:"<<endl;
		for(int i=head;i<tail;i++)
			cout<<data[i]<<'\t';
		cout<<endl;
	}
};


int main(int argc, char *argv[])
{

	Queue q;
	cout<<q.size()<<endl;
	cout<<q.head<<endl;
	cout<<q.tail<<endl;
	cout<<q.max_size<<endl;
	q.insert(1);cout<<q.head<<" -> "<<q.tail<<endl;
	q.insert(2);cout<<q.head<<" -> "<<q.tail<<endl;
	q.insert(3);cout<<q.head<<" -> "<<q.tail<<endl;
	q.insert(4);cout<<q.head<<" -> "<<q.tail<<endl;
	q.insert(5);cout<<q.head<<" -> "<<q.tail<<endl;q.disp();
	q.remove();cout<<q.head<<" -> "<<q.tail<<endl;q.disp();
	q.remove();cout<<q.head<<" -> "<<q.tail<<endl;q.disp();
	q.remove();cout<<q.head<<" -> "<<q.tail<<endl;q.disp();
	q.remove();cout<<q.head<<" -> "<<q.tail<<endl;q.disp();
	q.remove();cout<<q.head<<" -> "<<q.tail<<endl;q.disp();

	Stack s;
	cout<<s.size()<<endl;
	cout<<s.head<<endl;
	cout<<s.tail<<endl;
	cout<<s.max_size<<endl;
	s.insert(1);cout<<s.head<<" -> "<<s.tail<<endl;
	s.insert(2);cout<<s.head<<" -> "<<s.tail<<endl;
	s.insert(3);cout<<s.head<<" -> "<<s.tail<<endl;
	s.insert(4);cout<<s.head<<" -> "<<s.tail<<endl;
	s.insert(5);cout<<s.head<<" -> "<<s.tail<<endl;s.disp();
	s.insert(6);cout<<s.head<<" -> "<<s.tail<<endl;s.disp();
	s.remove();cout<<s.head<<" -> "<<s.tail<<endl;s.disp();
	s.remove();cout<<s.head<<" -> "<<s.tail<<endl;s.disp();
	s.remove();cout<<s.head<<" -> "<<s.tail<<endl;s.disp();
	s.remove();cout<<s.head<<" -> "<<s.tail<<endl;s.disp();
	s.remove();cout<<s.head<<" -> "<<s.tail<<endl;s.disp();
	
	return 0;
}
