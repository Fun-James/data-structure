#include <iostream>
#include <cmath>
using namespace std;

enum Color { RED, BLACK };

class RedBlackTree {
private:
    struct Node {
        int key;
        Color color;
        Node* left, * right, * parent;

        Node(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    // 辅助函数
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
        x->right = y;
        y->parent = x;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    void fixInsert(Node* k) {
        Node* u;//uncle节点
        while (k->parent != nullptr && k->parent->color == RED) //需要回溯
        {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u != nullptr && u->color == RED) //不转变色，根红子黑
                {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {//旋转变色，根黑子红
                    if (k == k->parent->left) {//RL
                        k = k->parent;
                        rightRotate(k);
                    }
                    //RR
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;
                if (u != nullptr && u->color == RED) //不转变色，根红子黑
                {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else {//旋转变色，根红子黑
                    if (k == k->parent->right) {//LR
                        k = k->parent;
                        leftRotate(k);
                    }
                    //LL
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->color = BLACK;//保证根节点是黑色的
    }

    void fixDelete(Node* x) {
        while (x != root && x != nullptr && x->color == BLACK) {
            if (x == x->parent->left) { // x 是左孩子
                Node* u = x->parent->right; 
                if (u != nullptr && u->color == RED) {
                    //1：兄弟节点 w 是红色
                    u->color = BLACK;          // 将兄弟节点变黑
                    x->parent->color = RED;    // 父节点变红
                    leftRotate(x->parent);     // 对父节点进行左旋LL
                    u = x->parent->right;      // 更新兄弟节点
                }
                if ((u->left == nullptr || u->left->color == BLACK) &&
                    (u->right == nullptr || u->right->color == BLACK)) {
                    // 2：兄弟节点 w 的两个孩子都是黑色
                    if (u != nullptr)
                        u->color = RED;        // 将兄弟节点变红
                    x = x->parent;            // 双黑上移，继续检查父节点
                }
                else {
                    if (u->right == nullptr || u->right->color == BLACK) {
                        // 3：兄弟节点 w 的右孩子是黑色，左孩子是红色
                        if (u->left != nullptr)
                            u->left->color = BLACK; // 将左孩子变黑
                        if (u != nullptr)
                            u->color = RED;        // 将兄弟节点变红
                        rightRotate(u);           // 对兄弟节点 w 右旋
                        u = x->parent->right;     // 更新兄弟节点
                    }
                    // 4：兄弟节点 w 的右孩子是红色
                    if (u != nullptr)
                        u->color = x->parent->color; // 兄弟节点继承父节点颜色
                    x->parent->color = BLACK;       // 父节点变黑
                    if (u->right != nullptr)
                        u->right->color = BLACK;   // 将兄弟节点的右孩子变黑
                    leftRotate(x->parent);        // 对父节点进行左旋
                    x = root;                     // 修正完成，跳出循环
                }
            }
            else { // x 是右孩子（对称情况）
                Node* w = x->parent->left;        // w 是 x 的兄弟节点
                if (w != nullptr && w->color == RED) {
                    // 1：兄弟节点 w 是红色
                    w->color = BLACK;            // 将兄弟节点变黑
                    x->parent->color = RED;      // 父节点变红
                    rightRotate(x->parent);      // 对父节点进行右旋
                    w = x->parent->left;         // 更新兄弟节点
                }
                if ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK)) {
                    // 2：兄弟节点 w 的两个孩子都是黑色
                    if (w != nullptr)
                        w->color = RED;          // 将兄弟节点变红
                    x = x->parent;              // 双黑上移，继续检查父节点
                }
                else {
                    if (w->left == nullptr || w->left->color == BLACK) {
                        // 3：兄弟节点 sssssw 的左孩子是黑色，右孩子是红色
                        if (w->right != nullptr)
                            w->right->color = BLACK; // 将右孩子变黑
                        if (w != nullptr)
                            w->color = RED;         // 将兄弟节点变红
                        leftRotate(w);             // 对兄弟节点 w 左旋
                        w = x->parent->left;       // 更新兄弟节点
                    }
                    // 4：兄弟节点 w 的左孩子是红色
                    if (w != nullptr)
                        w->color = x->parent->color; // 兄弟节点继承父节点颜色
                    x->parent->color = BLACK;       // 父节点变黑
                    if (w->left != nullptr)
                        w->left->color = BLACK;     // 将兄弟节点的左孩子变黑
                    rightRotate(x->parent);        // 对父节点进行右旋
                    x = root;                      // 修正完成，跳出循环
                }
            }
        }
        if (x != nullptr)
            x->color = BLACK;                      // 确保最终 x 是黑色
    }
    


    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

    void printHelper(Node* node, int level) {
        if (node == nullptr) return;

        // 先打印右子树
        printHelper(node->right, level + 1);

        // 打印当前节点
        for (int i = 0; i < level; i++) {
            cout << "    ";  // 4个空格表示一个层级
        }
        cout << node->key;
        if (node->color == BLACK)
        {
            cout << "B";
        }
        else
        {
            cout << "R";
        }
        cout << endl;

        // 最后打印左子树
        printHelper(node->left, level + 1);
    }


public:
    RedBlackTree() : root(nullptr) {}

    // 查找函数 - O(logn)
    bool find(int key) {
        Node* current = root;
        while (current != nullptr) {
            if (key == current->key)
                return true;
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return false;
    }

    // 插入函数 - O(logn) 
    void insert(int key) {
        Node* node = new Node(key);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (node->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        node->parent = y;//先插进去
        if (y == nullptr)
            root = node;
        else if (node->key < y->key)
            y->left = node;
        else
            y->right = node;

        fixInsert(node);//插入完成之后需要检查与修正
    }

    void deleteNode(int key) {
        Node* z = root;
        // 查找待删除的节点 z
        while (z != nullptr) {
            if (z->key == key)
                break;
            else if (key < z->key)
                z = z->left;
            else
                z = z->right;
        }

        if (z == nullptr) // 如果未找到对应的节点，直接返回
            return;

        Node* y = z;                // y 是要被删除或移动的节点
        Node* x;                    // x 是用于替换的节点
        Color yOriginalColor = y->color; // 保存 y 的原始颜色

        if (z->left == nullptr) {
            // 如果 z 没有左子节点，用其右子节点替代 z
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            // 如果 z 没有右子节点，用其左子节点替代 z
            x = z->left;
            transplant(z, z->left);
        }
        else {
            // 如果 z 有两个子节点，找到 z 的后继节点 y
            y = z->right;
            while (y->left != nullptr)
                y = y->left; // 一直往左找到最小节点

            yOriginalColor = y->color; // 记录后继节点的颜色
            x = y->right;              // y 的右子节点

            if (y->parent == z) { // 后继节点 y 就是 z 的右子节点
                if (x != nullptr)
                    x->parent = y;
            }
            else {
                // 如果 y 不是 z 的右子节点，先用 y 的右子节点替换 y
                transplant(y, y->right);
                y->right = z->right;    // 重新连接 y 和 z 的右子树
                if (y->right != nullptr)
                    y->right->parent = y;
            }

            // 用 y 替换 z 的位置
            transplant(z, y);
            y->left = z->left;         // 重新连接 y 和 z 的左子树
            if (y->left != nullptr)
                y->left->parent = y;
            y->color = z->color;       // 保持 y 的颜色与 z 的颜色一致
        }

        delete z; // 删除节点 z

        // hong色节点直接删除，黑色节点会影响红黑树的性质，需要调整
        if (yOriginalColor == BLACK)
            fixDelete(x);
    }


    // 升序遍历函数 - O(n)
    void ascend() {
        inorderTraversal(root);
        cout << endl;
    }

    void printTree() {
        printHelper(root, 0);
        cout << endl;
    }

};

int main()
{
    RedBlackTree tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(9);
    tree.insert(0);
    /*tree.deleteNode(22);*/
    tree.ascend();

    tree.printTree();


    return 0;
}