#include <iostream>
using namespace std;

class dataNode
{
public:
    int col;
    int value;
    dataNode *next;
    dataNode(int c, int d) : col(c), value(d) { next = nullptr; }
    dataNode(int c) : col(c), value(0) { next = nullptr; }
};

class rowNode
{
public:
    int row;
    rowNode *down;
    dataNode *first;
    dataNode *tail;
    rowNode(int r) : row(r)
    {
        first = nullptr;
        down = nullptr;
        tail = nullptr;
    }
    void addData(int c, int v)
    {
        if (first == nullptr)
        {
            first = new dataNode(c, v);
            tail = first;
            return;
        }
        dataNode *newnode = new dataNode(c, v);
        tail->next = newnode;
        tail = newnode;
    }
};

class rowList
{
public:
    rowNode *head;
    rowNode *tail;
    rowList() { head = tail = nullptr; }
    void insert(int r, int c, int v)
    {
        if (head == nullptr)
        {
            head = new rowNode(r);
            head->addData(c, v);
            tail = head;
            return;
        }
        bool findr = false;
        rowNode *curr = head;
        while (curr != nullptr)
        {
            if (curr->row == r)
            {
                findr = true;
                break;
            }
            curr = curr->down;
        }
        if (findr) // 找到了，直接插入
        {
            curr->addData(c, v);
            return;
        }
        else // 没找到，设置新的行
        {
            rowNode *newnode = new rowNode(r);
            newnode->addData(c, v);

            if (r < head->row)
            {
                newnode->down = head;
                head = newnode;
                return;
            }

            if (r > tail->row)
            {
                tail->down = newnode;
                tail = newnode;
                return;
            }
            rowNode *curr = head;
            while (curr->down != nullptr)
            {
                if ((curr->row <= r) && (curr->down->row > r))
                {
                    newnode->down = curr->down;
                    curr->down = newnode;
                    return;
                }
                curr = curr->down;
            }
        }
    }
    void reset(int i, int j, int value)
    {
        rowNode *currR = head;
        while (currR->row != i)
        {
            currR = currR->down;
        }
        dataNode *currC = currR->first;
        while (currC->col != j)
        {
            currC = currC->next;
        }
        currC->value = value;
    }
    int get(int i, int j)
    {
        bool findr = false;
        rowNode *currR = head;
        while (currR != nullptr)
        {
            if (currR->row == i)
            {
                findr = true;
                break;
            }
            currR = currR->down;
        }
        if (findr)
        {
            bool findc = false;
            dataNode *currC = currR->first;
            while (currC != nullptr)
            {
                if (currC->col == j)
                {
                    findc = true;
                    break;
                }
                currC = currC->next;
            }
            if (findc)
            {
                return currC->value;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
};

class linkedMatrix
{
    rowList *rowlist;
    int rows;
    int cols;

public:
    linkedMatrix() { rowlist = nullptr; }
    void set(int i, int j, int value);
    int get(int i, int j) { return rowlist->get(i, j); }
    linkedMatrix &operator+(linkedMatrix &a);
    linkedMatrix &operator-(linkedMatrix &a);
    linkedMatrix &operator*(linkedMatrix &a);
    istream &operator>>(istream &in);
    void print();
};

void linkedMatrix::print()
{
    if (rowlist == nullptr)
    {
        cout << "Empty matrix" << endl;
        return;
    }

    rowNode *currR = rowlist->head;
    while (currR != nullptr)
    {
        dataNode *currC = currR->first;
        while (currC != nullptr)
        {
            if (currC->value == 0)
            {
                currC = currC->next;
                continue;
            }
            cout << "(" << currR->row << "," << currC->col << "," << currC->value << ")" << endl;
            currC = currC->next;
        }
        currR = currR->down;
    }
    cout << endl;
}

void linkedMatrix::set(int i, int j, int value)
{
    if (rowlist == nullptr)
    {
        rowlist = new rowList;
        rowlist->insert(i, j, value);
        return;
    }
    if (get(i, j) != 0) // 如果i,j存在，覆盖
    {
        rowlist->reset(i, j, value);
    }
    else // i,j不存在，插入
    {
        rowlist->insert(i, j, value);
    }
}

linkedMatrix &linkedMatrix ::operator+(linkedMatrix &a)
{
    rowNode *currR = a.rowlist->head;
    while (currR != nullptr)
    {
        dataNode *currC = currR->first;
        while (currC != nullptr)
        {
            set(currR->row, currC->col, currC->value + this->get(currR->row, currC->col));
            currC = currC->next;
        }
        currR = currR->down;
    }

    return *this;
}

linkedMatrix &linkedMatrix ::operator-(linkedMatrix &a)
{
    rowNode *currR = a.rowlist->head;
    while (currR != nullptr)
    {
        dataNode *currC = currR->first;
        while (currC != nullptr)
        {
            set(currR->row, currC->col, this->get(currR->row, currC->col) - currC->value);
            currC = currC->next;
        }
        currR = currR->down;
    }

    return *this;
}

linkedMatrix &linkedMatrix::operator*(linkedMatrix &b)
{
    // 创建新的 rowList
    rowList *newRowList = new rowList();

    // 遍历左矩阵的每一行
    rowNode *currR_A = this->rowlist->head;
    while (currR_A != nullptr)
    {
        int row_A = currR_A->row;
        dataNode *currC_A = currR_A->first;

        // 遍历当前行的每一列
        while (currC_A != nullptr)
        {
            int col_A = currC_A->col;
            int val_A = currC_A->value;

            // 在矩阵 b 中找到行 col_A（即匹配的列）
            rowNode *currR_B = b.rowlist->head;
            while (currR_B != nullptr)
            {
                if (currR_B->row == col_A)
                {
                    dataNode *currC_B = currR_B->first;

                    // 遍历 b 矩阵的 col_A 行的每一列
                    while (currC_B != nullptr)
                    {
                        int col_B = currC_B->col;
                        int val_B = currC_B->value;

                        // 计算乘积并累加到 newRowList 中

                        // 检查 newRowList 中是否已经存在位置 (row_A, col_B)
                        rowNode *currR_Result = newRowList->head;
                        rowNode *prevR_Result = nullptr;
                        while (currR_Result != nullptr && currR_Result->row < row_A)
                        {
                            prevR_Result = currR_Result;
                            currR_Result = currR_Result->down;
                        }
                        if (currR_Result == nullptr || currR_Result->row > row_A)
                        {
                            // 创建新的行节点
                            rowNode *newRow = new rowNode(row_A);
                            newRow->down = currR_Result;
                            if (prevR_Result == nullptr)
                            {
                                newRowList->head = newRow;
                            }
                            else
                            {
                                prevR_Result->down = newRow;
                            }
                            currR_Result = newRow;
                        }

                        dataNode *currC_Result = currR_Result->first;
                        dataNode *prevC_Result = nullptr;
                        while (currC_Result != nullptr && currC_Result->col < col_B)
                        {
                            prevC_Result = currC_Result;
                            currC_Result = currC_Result->next;
                        }
                        if (currC_Result == nullptr || currC_Result->col > col_B)
                        {
                            // 创建新的列节点
                            dataNode *newData = new dataNode(col_B, val_A * val_B);
                            newData->next = currC_Result;
                            if (prevC_Result == nullptr)
                            {
                                currR_Result->first = newData;
                            }
                            else
                            {
                                prevC_Result->next = newData;
                            }
                        }
                        else
                        {
                            // 更新已有的值
                            currC_Result->value += val_A * val_B;
                        }

                        currC_B = currC_B->next;
                    }
                    break;
                }
                currR_B = currR_B->down;
            }

            currC_A = currC_A->next;
        }
        currR_A = currR_A->down;
    }

    // 释放原有的 rowList
    // 注意：需要实现一个函数来释放 this->rowlist 的内存
    // 此处假设存在一个名为 freeRowList 的函数
    // freeRowList(this->rowlist);

    // 替换为新的 rowList
    this->rowlist = newRowList;

    return *this;
}

istream &linkedMatrix::operator>>(istream &in)
{
    int numberOfTerms;
    in >> rows >> cols >> numberOfTerms;
    int prevRow = -1, prevCol = -1;
    for (int i = 0; i < numberOfTerms; i++)
    {
        int r, c, value;
        in >> r >> c >> value;
        // 验证合法性
        if (r > rows || c > cols)
        {
            cout << "输入超出矩阵维度" << endl;
            continue;
        }
        if (r < prevRow)
        {
            cout << "行号顺序错误，输入非法" << endl;
            continue;
        }
        if (r == prevRow && c <= prevCol)
        {
            cout << "同一行内列号顺序错误，输入非法" << endl;
            continue;
        }
        prevRow = r;
        prevCol = c;
        set(r, c, value);
    }
    return in;
}
int main()
{
    // linkedMatrix mat0;
    // mat0.set(1, 1, 108);
    // mat0.set(100, 100, 20);
    // mat0.set(23, 56, 10);
    // linkedMatrix mat1;
    // mat1.set(1, 2, 23);
    // mat1.set(100, 100, 20);

    // cout << mat1.get(1, 2) << " " << mat1.get(1, 3) << endl;
    // (mat0 - mat1).print();

    linkedMatrix mat0;
    linkedMatrix mat1;
    mat0.set(1, 2, 23);
    mat0.set(2, 5, 7);
    mat0.set(5 ,3 ,11);
    mat0.set(6 ,5, 12);

    mat1.set(2, 2, 4);
    mat1.set(3, 6 ,8);
    mat1.set(5, 5, 9);
    (mat0*mat1).print();
    return 0;
}