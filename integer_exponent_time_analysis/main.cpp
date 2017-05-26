#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

double myPow(double, int);

int main()
{
    long double start = 1;
    long double stop = 1000000000;
    int beg = time(0);
    while(start < stop)
    {
        pow(start,2);
        start++;
    }
    int end = time(0);
    cout << "Built in: " << end - beg << " seconds" << endl;
    start = 1;
    beg = time(0);
    while(start < stop)
    {
        myPow(start,2);
        start++;
    }
    end = time(0);
    cout << "My function: " << end - beg << " seconds";

    cout << endl << endl;
    return 0;
}

double myPow(double num, int pow)
{
    if(pow == 0) return 1;
    double result = num;
    for(int i = 1; i < pow; i++)
    {
        result*=num;
    }
    return result;
}
