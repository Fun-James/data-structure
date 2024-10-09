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
		head=new Node<T>;//哨兵节点不储存内容
		head->prev=head;
		head->next=head;
		count=0;
	}
	void insert(T d)
	{
		Node<T>* newnode=new Node<T>;
		newnode->data=d;

		newnode->next=head;
		newnode->prev=head->prev;//head->prev就是tail
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
			Node<T>* nextNode=curr->next;//保留下一个节点
     	   if (index % 2 == 1) // 奇数索引放到a
			{
           		//切断节点与链表的联系
				curr->prev->next=curr->next;
				curr->next->prev=curr->prev;

				//处理该节点，将该节点直接放入链表a中
				curr->prev=a.head->prev;
				curr->next=a.head;
				//原来的尾部的下一个是curr
				a.head->prev->next=curr;
				//新尾部是curr
				a.head->prev=curr;

       		} 
			else // 偶数索引放到b
			{
         		//切断节点与链表的联系
				curr->prev->next=curr->next;
				curr->next->prev=curr->prev;

				//将该节点直接放入链表b中
				curr->prev=b.head->prev;
				curr->next=b.head;
				
				b.head->prev->next=curr;
				b.head->prev=curr;  
       	 	}
        	curr = nextNode;
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