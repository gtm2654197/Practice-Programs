/*  The fast inverse square root function was
 *  first commonly seen in Quake 3 arena as
 *  a way to dramatically improve the performance
 *  of the game by approximating the inverse
 *  magnitude of a vector used to find a unit vector.
 *  The actual algorithm's author goes back much
 *  earlier, but is unclear.
 *
 *  Here I will test the fast inverse square root
 *  versus the sqrt function in math.h as well
 *  as a taking the reciprocal of a fast
 *  approximating square root function
 */
#include <iostream>
#include <math.h>
#include <ctime>

float Fast_InvSqrt(float);
float Fast_Sqrt(float);

using namespace std;

int main()
{
    float start = 1;
    float stop = 10001;
    long double iterations = 10000000000;
    long double i = 0;
    int beg = time(0);
    while(i<iterations)
    {
        while(start<stop)
        {
            1/sqrt(start);
            start+=.001;
        }
        i++;
    }
    int end = time(0);
    cout << "Time to recipricol sqrt using math.h for " << iterations << " iterations of " << (stop-1)*1000 << " elements: " << end-beg << " seconds" << endl;
    start = 1;
    i = 0;
    beg = time(0);
    while(i<iterations)
    {
        while(start<stop)
        {
            Fast_InvSqrt(start);
            start+=.001;
        }
        i++;
    }
    end = time(0);
    cout << "Time to Fast InvSqrt for " << iterations << " iterations of " << (stop-1)*1000 << " elements: " << end-beg << " seconds" << endl;
    start = 1;
    i = 0;
    beg = time(0);
    while(i<iterations)
    {
        while(start<stop)
        {
            1/Fast_Sqrt(start);
            start+=.001;
        }
        i++;
    }
    end = time(0);
    cout << "Time to Fast Sqrt for " << iterations << " iterations of " << (stop-1)*1000 << " elements: " << end-beg << " seconds" << endl;

    cout << endl << endl;
    return 0;
}

float Fast_InvSqrt(float input)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = input * 0.5f;
    y = input;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );
    y = * (float * ) &i;
    y = y * ( threehalfs - (x2 * y * y));       //1st Iteration
    y  = y * ( threehalfs - ( x2 * y * y ) );   //2nd Iteration (can be removed for more speed, less precision)
    return y;
}

float Fast_Sqrt(float x)
 {
    const float xhalf = 0.5f*x;

      union // get bits for floating value
      {
        float x;
        int i;
      } u;
      u.x = x;
      u.i = 0x5f3759df  - (u.i >> 1);  // gives initial guess y0
      return x*u.x*(1.5f - xhalf*u.x*u.x);
 }
