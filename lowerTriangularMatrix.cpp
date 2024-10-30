#include <iostream>
#include <iomanip>
using namespace std;

int N = 5;

template<typename T>
class upperTriangularMatrix {
private:
    int n;
    T* element;
public:
    upperTriangularMatrix(int inN)
    {
        n = inN;
        element = new T[(1 + n) * n / 2];
    }
    ~upperTriangularMatrix()
    {
        delete[]element;
    }
    void display();
    upperTriangularMatrix<T>& store(const T& x, int i, int j);
};

template <typename T>
class lowerTriangularMatrix {
private:
    int n;//维数
    T* element;
public:
    lowerTriangularMatrix(int inN)
    {
        n = inN;
        element = new T[(1 + n) * n / 2];
    }
    ~lowerTriangularMatrix()
    {
        delete[]element;
    }
    void set(int* d){element=d;}
    lowerTriangularMatrix<T>& store(const T& x, int i, int j);
    void display();
    T getVal(int i, int j) { return element[(i - 1) * i / 2 + j - 1]; }
    upperTriangularMatrix<T> transposition();
};

template<typename T>
upperTriangularMatrix<T>& upperTriangularMatrix<T>::store(const T& x, int i, int j)//i行j列
{
    if (i <= j)
    {
        if(i==1)
        {
            element[j-1]=x;
        }
        else
        {
            element[(N+(N-i+2))*(i-1)/2+j-i]=x;
        }
    }
    return *this;
}
template<typename T>
lowerTriangularMatrix<T>& lowerTriangularMatrix<T>::store(const T& x, int i, int j)//i行j列
{
    if (i >= j)
    {
        element[i * (i - 1) / 2 + j - 1] = x;
    }
    return *this;
}

template<typename T>
void lowerTriangularMatrix<T>::display()
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j <= 2 * i; j++)
        {
            cout << setw(3) << element[count++] << " ";
        }
        for (int k = 0; k < n - i - 1; k++)
        {
            cout << setw(3) << 0 << " ";
        }
        cout << endl;
    }
    cout<<endl;
}
template<typename T>
void upperTriangularMatrix<T>::display()
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < i; k++)
        {
            cout << setw(3) << 0 << " ";
        }
        for (int j = i; j < N; j++)
        {
            cout << setw(3) << element[count++] << " ";
        }

        cout << endl;
    }
}

template<typename T>
upperTriangularMatrix<T> lowerTriangularMatrix<T>::transposition()
{
    upperTriangularMatrix<T> umat(N);
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            umat.store(getVal(i,j), j, i);
        }
    }
    return umat;
}

int main()
{
    lowerTriangularMatrix<int> lmat(N);
    int* a=new int[N * (N + 1)];
    for (int i = 0; i < N * (N + 1) / 2; i++)
    {
        cin >> a[i];
    }
    lmat.set(a);

    lmat.display();

    lmat.transposition().display();


    return 0;
}