#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

double mySqrt(double);
double BabylonianAlgorithm(double, double);

int main()
{    
    double start = 1;
    double stop = 50000001;
    int beg = time(0);
    while(start < stop)
    {
        mySqrt(start);
        start++;
    }
    int end = time(0);
    int totaltime1 = end-beg;
    start = 1;
    beg = time(0);
    while(start < stop)
    {
        sqrt(start);
        start++;
    }
    end = time(0);
    int totaltime2 = end-beg;
    cout << "Time to calculate " << stop-1 << "square roots using my function: " << totaltime1 << endl;
    cout << "Time to calculate " << stop-1 << "square roots using cmath function: " << totaltime2 << endl;





    return 0;
}

double mySqrt(double input)
{
    return BabylonianAlgorithm(input, input/2);
}
double BabylonianAlgorithm(double input, double guess)
{
    double previous_guess = guess;
    double r = input/guess;
    guess = (guess + r)/2;
    double margin_for_error = (guess - previous_guess);
    if(margin_for_error < 0) margin_for_error*=-1;
    if(margin_for_error < 0.001) return guess;
    return BabylonianAlgorithm(input, guess);
}
