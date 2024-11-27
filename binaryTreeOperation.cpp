#include <iostream>
#include <string>
#include <queue>
using namespace std;
template <class T>
class treeNode
{
public:
    T element;
    treeNode<T>* leftChild;
    treeNode<T>* rightChild;
    treeNode(T data)
    {
        element = data;
        leftChild = rightChild = nullptr;
    }
};

template <class T>
class binaryTree
{
public:
    treeNode<T>* root;
    binaryTree()
    {
        root = nullptr;
    }
    void create()
    {
        root = createTree();
    }
    treeNode<T>* createTree()
    {
        T data;
        cin >> data;
        if (data == '#') // 空节点
        {
            return nullptr;
        }
        treeNode<T>* newnode = new treeNode<T>(data);
        newnode->leftChild = createTree();
        newnode->rightChild = createTree();
        return newnode;
    }
    int countNode(treeNode<T>* t)
    {
        if (t == nullptr)
        {
            return 0;
        }
        return 1 + countNode(t->leftChild) + countNode(t->rightChild);
    }
    void switchTree(treeNode<T>* t)
    {
        if (t == nullptr)
        {
            return;
        }
        treeNode<T>* temp = t->leftChild;
        t->leftChild = t->rightChild;
        t->rightChild = temp;
        switchTree(t->leftChild);
        switchTree(t->rightChild);
    }
    void visit(treeNode<T>* t)
    {
        cout << t->element << " ";
        return;
    }

    void levelOrder(treeNode<T>* t)
    {
        queue<treeNode<T>*> q;
        while (t)
        {
            visit(t);
            if (t->leftChild != nullptr)
            {
                q.push(t->leftChild);
            }
            if (t->rightChild != nullptr)
            {
                q.push(t->rightChild);
            }

            if (!q.empty())
            {
                t = q.front(); // 队列为空的时候，q.front()传递的并不是nullptr，while（t）仍然不会终止
            }
            else
            {
                t = nullptr;
                break;
            }
            q.pop();
        }
        cout << endl;
    }
    int width(treeNode<T>* t)
    {
        if (t == nullptr)
        {
            return 0;
        }
        queue<treeNode<T>*> q;
        q.push(t);
        int max = 0;
        while (!q.empty())
        {
            int levelsize = q.size();
            if (levelsize > max)
            {
                max = levelsize;
            }
            for (int i = 0; i < levelsize; i++)
            {
                treeNode<T>* node = q.front();
                q.pop();
                if (node->leftChild != nullptr)
                {
                    q.push(node->leftChild);
                }
                if (node->rightChild != nullptr)
                {
                    q.push(node->rightChild);
                }
            }
        }
    }
};

int main()
{
    binaryTree<char> tree;
    tree.create();
    cout << tree.countNode(tree.root) << endl;
    tree.switchTree(tree.root);
    tree.levelOrder(tree.root);
    cout << tree.width(tree.root);
    return 0;
}