#include<iostream>
using namespace std;
template <typename T>
class Node {
public:
	T data;
	Node* next;
	Node()
	{
		data = 0;
		next = nullptr;
	}
};
template<typename T>
class extendedChain {
public:
	Node<T>* head;
	Node<T>* tail;
	int number;
	extendedChain()
	{
		head = tail = nullptr;
		number = 0;
	}
	void insert(T d)
	{
		Node<T>* newnode = new Node<T>;
		newnode->data = d;
		//当链表为空时
		if (head == nullptr)
		{
			head = tail = newnode;
			number++;
			return;
		}
		//链表不为空
		tail->next = newnode;
		tail = newnode;
		number++;
		return;
	}
	void display()
	{
		Node<T>* curr = head;
		for (int i = 0; i < number; i++)
		{
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << endl;
	}
	friend extendedChain meld(extendedChain& a, extendedChain& b)
	{
		extendedChain c;
		int totalcount = a.number + b.number;
		Node<T>* currA = a.head;
		Node<T>* currB = b.head;
		for (int i = 0; i < totalcount;)
		{
			if (currA != nullptr)
			{
				c.insert(currA->data);
				currA = currA->next;
				i++;
			}
			if (currB != nullptr)
			{
				c.insert(currB->data);
				currB = currB->next;
				i++;
			}
		}
		return c;
	}
};
int main()
{
	int na, nb;
	cin >> na >> nb;
	extendedChain<int> a;
	for (int i = 0; i < na; i++)
	{
		int temp;
		cin >> temp;
		a.insert(temp);
	}
	extendedChain<int> b;
	for (int i = 0; i <nb ; i++)
	{
		int temp;
		cin >> temp;
		b.insert(temp);
	}
	meld(a, b).display();
	return 0;
}