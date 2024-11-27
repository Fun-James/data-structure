#include <iostream>
#include <string>
#include <exception>
using namespace std;

class OutOfBounds : public exception {
public:
    const char* what() const noexcept override {
        return "Stack out of bounds";
    }
};

int MAX=20;
template<typename T>
class stack{
    T* st;
    int top;
    int maxsize;
public:
    stack()
    {
        maxsize=MAX;
        st=new T[maxsize];
        top=-1;
    }
    void push(T ch)
    {
        if(top>maxsize-1)
        {
            cout<<"FULL";
            return;
        }
        st[++top]=ch;
    }
    T pop()
    {
        if(top==-1)
        {
            throw OutOfBounds();
        }
        return st[top--];
    }
    bool IsEmpty()
    {
        if(top==-1)
        {
            return true;
        }
        return false;
    }
    T Top()
    {
        return st[top];
    }
};

template<typename T>
class treeNode{
public:
    T data;
    treeNode* rightchild;
    treeNode* leftchild;
    treeNode(T val){
        data=val;
        rightchild=nullptr;
        leftchild=nullptr;
    }
};

bool isOperator(char c)
{
    if(c=='+'||c=='-'||c=='*'||c=='/')
    {
        return true;
    }
    return false;
}

bool isLe(char c)
{
    if(c>='a'&&c<='z')
    {
        return true;
    }
    return false;
}

template<typename T>
class BinaryTree {
public:
    treeNode<T>* root;

    BinaryTree() {
        root = nullptr;
    }

    treeNode<T>* constructTree(string str) {
        stack<treeNode<T>*> nodeStack;
        for(int i=0;i<str.length();i++)
        {
            treeNode<T>* newnode=new treeNode<T>(str[i]);
            if(isLe(str[i]))
            {
                nodeStack.push(newnode);
            }
            else if(isOperator(str[i]))
            {
                newnode->leftchild=nodeStack.pop();
                newnode->rightchild=nodeStack.pop();
                nodeStack.push(newnode);
            }
        }
        return nodeStack.pop();
    }

    void visit(treeNode<T>* t) {
        int depth=getDepth(root,t);
        for(int i=0;i<depth;i++)
        cout<<"  ";
        cout<<t->data<<endl;
    }
    
    int getDepth(treeNode<T>* node,treeNode<T> *target,int depth=0)
    {
        if(node==nullptr)//没有找到target
        {
            return -1;
        }
        if(node==target)
        {
            return depth;
        }
        int leftDepth=getDepth(node->leftchild,target,depth+1);
        if(leftDepth!=-1)
        {
            return leftDepth;
        }
        return getDepth(node->rightchild,target,depth+1);
    }

    void inOrder(treeNode<T>* t) {
        if(t!=nullptr)
        {
            inOrder(t->leftchild);
            visit(t);
            inOrder(t->rightchild);
        }
    }
};

int getPriority(char ch)
{
    if(ch=='+'||ch=='-')
    {
        return 1;
    }
    if(ch=='*'||ch=='/')
    {
        return 2;
    }
    return 0;
}

string middleToBack(const string s)
{
    string after="";
    stack<char> charStack;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]>='a'&& s[i]<='z')
        {
            after+=s[i];
        }
        else
        {
            if(s[i]=='(')
            {
                charStack.push(s[i]);
            }
            else if(s[i]==')')
            {
                while(charStack.Top()!='(')
                {
                    after+=charStack.pop();
                }
                charStack.pop();//把左括号直接去掉
            }
            else
            {
                if(getPriority(s[i])>getPriority(charStack.Top()))
                {
                    charStack.push(s[i]);
                }
                else
                {
                    after+=s[i];
                }
            }
        }
    }
    while(!charStack.IsEmpty())
    {
       after+=charStack.pop();
    }
    return after;
}

int main()
{
    string str,str1;
    cin>>str;
    //中缀表达式转换后缀表达式
    str1=middleToBack(str);
    BinaryTree<char> tree;
    tree.root = tree.constructTree(str1);
    tree.inOrder(tree.root);

    return 0;
}