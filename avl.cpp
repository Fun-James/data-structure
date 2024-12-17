#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

template<class T>
class treeNode {
public:
    T data;
    treeNode* leftChild;
    treeNode* rightChild;
    int balance;
    treeNode(T d) {
        data = d;
        leftChild = rightChild = nullptr;
        balance = 0;
    }
};

template<class T>
class avlTree {
public:
    treeNode<T>* root;
    avlTree() {
        root = nullptr;
    }

    int height(treeNode<T>* node)//log(n)
    {
        if (node == nullptr) return 0;
        int leftHeight = height(node->leftChild);
        int rightHeight = height(node->rightChild);
        return max(leftHeight, rightHeight) + 1;
    }

    vector<treeNode<T>*> nearest() {
    vector<treeNode<T>*> result;
    queue<pair<treeNode<T>*, int>> qu; // 节点和其深度

    qu.push({root, 0});
    int minDepth = -1;

    while (!qu.empty()) {
        auto [curr, depth] = qu.front();
        qu.pop();
        // 如果是叶节点
        if (!curr->leftChild && !curr->rightChild) {
            // 如果是第一个叶节点
            if (minDepth == -1) {
                minDepth = depth;
                result.push_back(curr);
            }
            // 如果是同深度的其他叶节点
            else if (depth == minDepth) {
                result.push_back(curr);
            }
            // 如果遇到更深的叶节点，直接退出
            else if (depth > minDepth) {
                break;
            }
        }

        // 继续遍历
        if (curr->leftChild) {
            qu.push({curr->leftChild, depth + 1});
        }
        if (curr->rightChild) {
            qu.push({curr->rightChild, depth + 1});
        }
        
    }

    return result;
}

    int getBalance(treeNode<T>* node) {
        if (node == nullptr) return 0;
        return height(node->leftChild) - height(node->rightChild);
    }

    treeNode<T>* rightRotate(treeNode<T>* y) {//LL型
        treeNode<T>* x = y->leftChild;
        treeNode<T>* T2 = x->rightChild;

        x->rightChild = y;
        y->leftChild = T2;

        y->balance = getBalance(y);
        x->balance = getBalance(x);

        return x;
    }

    treeNode<T>* leftRotate(treeNode<T>* x) {//RR型
        treeNode<T>* y = x->rightChild;
        treeNode<T>* T2 = y->leftChild;

        y->leftChild = x;
        x->rightChild = T2;

        x->balance = getBalance(x);
        y->balance = getBalance(y);

        return y;
    }

    treeNode<T>* insertNode(treeNode<T>* node, T key) {
        if (node == nullptr)
            return new treeNode<T>(key);

        if (key < node->data)
            node->leftChild = insertNode(node->leftChild, key);
        else if (key > node->data)
            node->rightChild = insertNode(node->rightChild, key);
        else
            return node; // 不允许插入重复值

        node->balance = getBalance(node);

        // LL情况
        if (node->balance > 1 && key < node->leftChild->data)
            return rightRotate(node);

        // RR情况
        if (node->balance < -1 && key > node->rightChild->data)
            return leftRotate(node);

        // LR情况
        if (node->balance > 1 && key > node->leftChild->data) {
            node->leftChild = leftRotate(node->leftChild);
            return rightRotate(node);
        }

        // RL情况
        if (node->balance < -1 && key < node->rightChild->data) {
            node->rightChild = rightRotate(node->rightChild);
            return leftRotate(node);
        }

        return node;
    }

    avlTree<T>& insert(T x) {
        root = insertNode(root, x);
        return *this;
    }

    void print(treeNode<T>* node, int space = 0, int height = 10) {
        if (node == nullptr) return;
        space += height;
        print(node->rightChild, space);
        cout << endl;
        for (int i = height; i < space; i++) cout << ' ';
        cout << node->data << "\n";
        print(node->leftChild, space);
    }

    void print() {
        print(root);
        cout << "--------------------------------------------------------" << endl;
    }
};

int main()
{
    avlTree<int> tree;
    tree.insert(55);
    tree.insert(31);
    tree.insert(11);
    tree.insert(37);
    tree.insert(46);
    tree.insert(73);
    tree.insert(63);
    tree.insert(2);
    tree.insert(7);
    tree.print();
    cout<<tree.height(tree.root)<<endl;  
    vector<treeNode<int>*> a=tree.nearest();
    while(!a.empty())
    {
        cout<<a.back()->data<<" ";
        a.pop_back();
    }
    
}