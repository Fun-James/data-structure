#include<iostream>
#include<climits>

using namespace std;
template<typename K,typename V>
class Node {
public:	
	Node* next;
	K key;
	V value;
	Node(K k, V v)
	{
		next = nullptr;
		key = k;
		value = v;
	}
};
template<typename K,typename V>
class List{
public:
	Node<K,V>* head;//作为哨兵节点
	Node<K,V>* tail;
	List()
	{
		head=new Node<K,V>(INT_MAX,"null");
		tail=new Node<K,V>(INT_MAX,"null");
		head->next=tail;
	}
};
template<typename K,typename V>
class hashChainsWithTail {
	List<K,V>* ls;
	int divisor;
public:
	hashChainsWithTail(int divisor)
	{
		this->divisor=divisor;
		ls=new List<K,V>[divisor];
	}
	int hash(K key)
	{
		return key%divisor;
	}
	void insert(K key, V value)
{
    int pos = hash(key);
    Node<K,V>* newnode = new Node<K,V>(key, value);
    
    // 找到正确的插入位置
    Node<K,V>* prev = ls[pos].head;
    Node<K,V>* curr = prev->next;
    
    // 遍历找到合适的插入位置（保持有序）
    while(curr != ls[pos].tail && curr->key <= key)
    {
        prev = curr;
        curr = curr->next;
    }
    
    // 插入新节点，保持与tail的连接
    newnode->next = curr;  // curr可能是tail或中间节点
    prev->next = newnode;
}
	void remove(K key)
{
    int pos = hash(key);
    Node<K,V>* prev = ls[pos].head;
    Node<K,V>* curr = prev->next;

    while (curr != ls[pos].tail)
    {
        if (curr->key == key)
        {
            prev->next = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}
	 void print() {
        for (int i = 0; i < divisor; ++i) {
            Node<K, V>* curr = ls[i].head->next;
            cout << "Chain " << i << ": ";
            while (curr != ls[i].tail) {
                cout << "(" << curr->key << ", " << curr->value << ") -> ";
                curr = curr->next;
            }
            cout << "NULL" << endl;
        }
    }

};

int main() {
    hashChainsWithTail<int, string> hashTable(10);

    // 插入一些键值对
    hashTable.insert(1, "one");
    hashTable.insert(2, "two");
    hashTable.insert(11, "eleven");
    hashTable.insert(12, "twelve");

    // 打印哈希表
    cout << "Hash table after insertions:" << endl;
    hashTable.print();

    // 删除一个键值对
    hashTable.remove(1);

    // 打印哈希表
    cout << "Hash table after deletion:" << endl;
    hashTable.print();

    return 0;
}