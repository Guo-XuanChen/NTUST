/*
    File      : main.cpp
    Time      : 2019/11/24 20:38:19
    Author    : Guo-XuanChen
*/
#include <iostream>
#include <string.h>

template<class T>
class Polynomial {
    public:
        Polynomial(int degree)
        {
            this->degree = degree;
            this->coef = new T[this->degree+1];
        }
        ~Polynomial()
        {
            delete [] this->coef;
            this->coef = NULL;
        }
        T Eval(const T& X); 
        template<class F>
        friend std::istream& operator>>(std::istream& is, Polynomial<F>& pol);
    private:
        T pow(const T&, int);
        T* coef;
        int degree;
};


int main(int argc, char **argv)
{
    char cmd[6];
    while(std::cin >> cmd)
    {
        if(strcmp(cmd, "int") == 0)
        {
            int X;
            int degree;
            std::cin >> degree;
            Polynomial<int> pol(degree);
            std::cin >> pol;
            std::cin >> X;
            int result = pol.Eval(X);
            std::cout << result << std::endl;
        }
        else if(strcmp(cmd, "float") == 0)
        {
            float X;
            int degree;
            std::cin >> degree;
            Polynomial<float> pol(degree);
            std::cin >> pol;
            std::cin >> X;
            float result = pol.Eval(X);
            std::cout.precision(6);
            std::cout << result << std::endl;
        }
        else if(strcmp(cmd, "double") == 0)
        {
            double X;
            int degree;
            std::cin >> degree;
            Polynomial<double> pol(degree);
            std::cin >> pol;
            std::cin >> X;
            double result = pol.Eval(X);
            std::cout.precision(10);
            std::cout << result << std::endl;
        }
    }
    return 0;
}

template<class F>
std::istream& operator>>(std::istream& is, Polynomial<F>& pol)
{
    for(int x = 0; x <= pol.degree; x++)
    {
       is >> pol.coef[x];
    }
    return is;
}

template<class T>
T Polynomial<T>::Eval(const T& X)
{
    T sum = 0;
    for(int x = 0; x <= this->degree; x++)
    {
        sum += this->coef[x] * this->pow(X, x);
    }
    return sum;
}

template<class T>
T Polynomial<T>::pow(const T& X, int x)
{
    return (x == 0) ? 1 : X * pow(X, x - 1);  
}