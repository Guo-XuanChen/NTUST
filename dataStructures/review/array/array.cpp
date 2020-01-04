/*
    File      : array.cpp
    Time      : 2019
    Author    : Guo-XuanChen
*/
#include <iostream>
#include <string>

using namespace std;

class Matrix {
    unsigned int n1, n2; // row, colume
    int** store = NULL;
    public:
    Matrix(){};
    Matrix(unsigned int n1, unsigned int n2);
    Matrix operator+(Matrix&);
    void operator+=(Matrix&);
    Matrix operator-(Matrix&);
    void operator-=(Matrix&);
    Matrix operator*(Matrix&);
    void operator*=(Matrix&);
    void Transpose();
    void print();
    friend istream& operator>>(istream&, Matrix&);
};

int main(int argc, char **argv)
{
    Matrix matrix1;
    cin >> matrix1;

    string cmd;

    while(cin >> cmd)
    {
        if(cmd == "+")
        {
            Matrix matrix; 
            cin >> matrix;
            try{
                matrix1 += matrix;
            }
            catch(const char *msg)
            {
                cout << msg << endl;
            }
        }
        else if(cmd == "-")
        {
            Matrix matrix;
            cin >> matrix;
            try {
                matrix1 -= matrix;
            }
            catch(const char *msg)
            {
                cout << msg << endl;
            }
        }
        else if(cmd == "*")
        {
            Matrix matrix;
            cin >> matrix;
            try {
                matrix1 *= matrix;
            }
            catch(const char *msg)
            {
                cout << msg << endl;
            }
        }
        else if(cmd == "T")
        {
            matrix1.Transpose();
        }
        else if(cmd == "print")
        {
            matrix1.print();
        }
    }

    return 0;
}

Matrix::Matrix(unsigned int n1, unsigned int n2)
{
    this->n1 = n1; this->n2 = n2;

    this->store = new int *[this->n1];
    for(unsigned int x = 0; x < this->n1; x++)
    {
        this->store[x] = new int[this->n2];
    }
}

void Matrix::print()
{
    for(unsigned int x = 0; x < this->n1; x++)
    {
        for(unsigned int y = 0; y < this->n2 - 1; y++)
        {
            cout << this->store[x][y] << " ";
        }
        cout << this->store[x][this->n2 - 1] << endl;
    }
}

/* 
    matrix3 = matrix1 + matirx2
    matrix1 = matrix1 + matrix2
*/
Matrix Matrix::operator+(Matrix& matrix)
{
    if(this->n1 != matrix.n1 || this->n2 != matrix.n2)
    {
        throw "Addition Error";
    }

    Matrix res(this->n1, this->n2);
    for(unsigned int x = 0; x < this->n1; x++)
    {
        for(unsigned int y = 0; y < this->n2; y++)
        {
            res.store[x][y] = this->store[x][y] + matrix.store[x][y];
        }
    }

    return res;
}

/*
    matrix1 += matrix2;
*/
void Matrix::operator+=(Matrix& matrix)
{
    if(this->n1 != matrix.n1 || this->n2 != matrix.n2)
    {
        throw "Addition Error";
    }

    for(unsigned int x = 0; x < this->n1; x++)
    {
        for(unsigned int y = 0; y < this->n2; y++)
        {
            this->store[x][y] += matrix.store[x][y];
        }
    }
}

/* 
    matrix3 = matrix1 - matirx2
    matrix1 = matrix1 - matrix2
*/
Matrix Matrix::operator-(Matrix& matrix)
{
    if(this->n1 != matrix.n1 || this->n2 != matrix.n2)
    {
        throw "Subtraction Error";
    }

    Matrix res(this->n1, this->n2);
    for(unsigned int x = 0; x < this->n1; x++)
    {
        for(unsigned int y = 0; y < this->n2; y++)
        {
            res.store[x][y] = this->store[x][y] - matrix.store[x][y];
        }
    }
    return res;
}

/*
    matrix1 -= matrix2
*/
void Matrix::operator-=(Matrix& matrix)
{
    if(this->n1 != matrix.n1 || this->n2 != matrix.n2)
    {
        throw "Subtraction Error";
    }

    for(unsigned int x = 0; x < this->n1; x++)
    {
        for(unsigned int y = 0; y < this->n2; y++)
        {
            this->store[x][y] -= matrix.store[x][y];
        }
    }
}

/*
    matrix3 = matrix1 * matrix2
    matrix1 = matrix1 * matrix2
*/

Matrix Matrix::operator*(Matrix& matrix)
{
    if(this->n2 != matrix.n1)
    {
        throw "Multiplication Error";
    }

    /*
        matrix1 = m x n
        matrix2 = n x p
        result = m x p
    */
    Matrix res(this->n1, matrix.n2);

    for(unsigned int x = 0; x < this->n1; x++)
    {
        for(unsigned int y = 0; y < matrix.n2; y++)
        {
            for(unsigned int z = 0; z < this->n2; z++)
            {
                /*
                    res0,0 = a0,0 * b0,0 + a0,1 * b1,0 + a0,2 * b2,0 ...
                    res0,1 = a0,0 * b0,1 + a0,1 * b1,1 + a0,2 * b2,1 ...
                    ...
                */
                res.store[x][y] += this->store[x][z] * matrix.store[z][y]; 
            }
        }
    }
    return res;
}

/*
    matrix1 *= matrix2
*/
void Matrix::operator*=(Matrix& matrix)
{
    if(this->n2 != matrix.n1)
    {
        throw "Multiplication Error";
    }

    Matrix res(this->n1, matrix.n2);
    for(unsigned int x = 0; x < this->n1; x++)
    {
        for(unsigned int y = 0; y < matrix.n2; y++)
        {
            for(unsigned int z = 0; z < this->n2; z++)
            {
                res.store[x][y] += this->store[x][z] * matrix.store[z][y];
            }
        }
    }
    
    delete [] this->store;
    this->store = res.store;
    this->n1 = res.n1;
    this->n2 = res.n2;
}

void Matrix::Transpose()
{
    unsigned int n1 = this->n2;
    unsigned int n2 = this->n1;

    Matrix res(n2, n1);

    for(unsigned int x = 0; x < n2; x++)
    {
        for(unsigned int y = 0; y < n1; y++)
        {
            res.store[x][y] = this->store[y][x]; 
        }
    }

    delete [] this->store;
    this->store = res.store;
    this->n1 = n1;
    this->n2 = n2;
}

istream& operator>>(istream& is, Matrix& matrix)
{
    is >> matrix.n1 >> matrix.n2;
    matrix.store = new int *[matrix.n1];

    // 2-way pointer array
    for(unsigned int x = 0; x < matrix.n1; x++)
    {
        matrix.store[x] = new int [matrix.n2];
    }

    for(unsigned int x = 0; x < matrix.n1; x++)
    {
        for(unsigned int y = 0; y < matrix.n2; y++)
        {  
            is >> matrix.store[x][y];
        }
    }
    return is;   
}