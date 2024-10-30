#include <iostream>
using namespace std;

// 定义三元组结构
template <typename T>
struct Triple
{
    int row;
    int col;
    T value;
};

template <typename T>
class SparseMatrix
{
private:
    Triple<T> *elements; // 动态数组存储三元组
    int rows, cols;
    int count; // 当前存储的三元组数量
public:
    // 构造函数
    SparseMatrix(int r, int c, int n)
    {
        rows = r;
        cols = c;
        count = n;
        elements = new Triple<T>[n];
    }

    // 析构函数
    ~SparseMatrix()
    {
        delete[] elements; // 释放动态数组
    }

    // 输出稀疏矩阵的三元组形式
    void print() const
    {
        for (int i = 0; i < count; ++i)
        {
            cout << "(" << elements[i].row << ", " << elements[i].col << ", " << elements[i].value << ")" << endl;
        }
    }

    void set()
    {
        for (int i = 0; i < count; i++)
        {
            cin >> elements[i].row >> elements[i].col >> elements[i].value;
        }
    }

    // 重载乘法运算符，实现稀疏矩阵乘法
    friend SparseMatrix<T> operator*(const SparseMatrix<T> &a, const SparseMatrix<T> &b)
    {
        if (a.cols != b.rows)
        {
            throw invalid_argument("Matrix dimensions do not match for multiplication.");
        }

        // 动态分配结果矩阵的元素数组，最大可能数量是 a.count * b.count
        Triple<T> *resultElements = new Triple<T>[a.count * b.count];
        int resultCount = 0;

        // 对于 A 矩阵中的每一个非零元素
        for (int i = 0; i < a.count; i++)
        {
            Triple<T> elemA = a.elements[i];

            // 遍历 B 矩阵中的每一个非零元素
            for (int j = 0; j < b.count; j++)
            {
                Triple<T> elemB = b.elements[j];

                // A 的列 == B 的行，则可以相乘
                if (elemA.col == elemB.row)
                {
                    bool found = false;
                    // 乘积结果的行是 elemA.row，列是 elemB.col
                    for (int k = 0; k < resultCount; ++k)
                    {
                        if (resultElements[k].row == elemA.row && resultElements[k].col == elemB.col)
                        {
                            resultElements[k].value += elemA.value * elemB.value;
                            found = true;
                            break;
                        }
                    }
                    // 如果未找到匹配项，创建新的三元组
                    if (!found)
                    {
                        resultElements[resultCount].row = elemA.row;
                        resultElements[resultCount].col = elemB.col;
                        resultElements[resultCount].value = elemA.value * elemB.value;
                        resultCount++;
                    }
                }
            }
        }
        // 创建结果矩阵对象并返回
        SparseMatrix<T> result(a.rows, b.cols, resultCount);
        for (int i = 0; i < resultCount; i++)
        {
            result.elements[i] = resultElements[i];
        }
        return result;
    }
};

int main()
{
    SparseMatrix<int> A(6, 5, 4);
    A.set();
    SparseMatrix<int> B(5, 6, 3);
    B.set();

    // 进行矩阵乘法

    SparseMatrix<int> C = A * B;
    // 输出结果矩阵 C
    C.print();

    return 0;
}
