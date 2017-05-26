#include <iostream>

using namespace std;

int Fibonacci(int);

int main()
{
    int n = 20;
    for(int i = 0; i < n; i++)
    {
        cout << Fibonacci(i) << " ";
    }

    cout << endl << endl;
    return 0;
}


int Fibonacci(int n)
{
    if(n == 0 || n == 1)
    {
        return n;
    }
    else return(Fibonacci(n-1) + Fibonacci(n-2));
}
