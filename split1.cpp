#include <iostream>
using namespace std;
template<typename T>
class Node {
public:
	T data;
	Node* next;
	Node* prev;
	Node()
	{
		data = 0;
		next = nullptr;
		prev=nullptr;
	}
};
template<typename T>
class extendedChain{
public:
	Node<T>* head;
	int count;
	extendedChain()
	{
		head=new Node<T>;
		head->prev=head;
		head->next=head;
		count=0;
	}
	void insert(T d)
	{
		Node<T>* newnode=new Node<T>;
		newnode->data=d;

		newnode->next=head;
		newnode->prev=head->prev;
		head->prev->next=newnode;
		head->prev=newnode;

		count++;
	}
	void display()
	{
		Node<T>* curr=head->next;
		while(curr!=head)
		{
			cout<<curr->data<<" ";
			curr=curr->next;
		}
		cout<<endl;
	}
	friend void split(const extendedChain& c,extendedChain& a, extendedChain& b) 
	{
    	Node<T>* curr = c.head->next;
   	 	int index = 0;
    	for(int i=0;i<c.count;i++)
		{
     	   if (index % 2 == 1)
			{
           		a.insert(curr->data);  // 奇数放到a
       		} 
			else 
			{
         		b.insert(curr->data);  // 偶数放到b
       	 	}
        	curr = curr->next;
        	index++;
		}
    }
};

int main()
{
	int n;
	cin>>n;
	extendedChain<int> c;
	extendedChain<int> a;
	extendedChain<int> b;
	for(int i=0;i<n;i++)
	{
		int temp;
		cin>>temp;
		c.insert(temp);
	}
	split(c,a,b);
	a.display();
	b.display();

	return 0;
}