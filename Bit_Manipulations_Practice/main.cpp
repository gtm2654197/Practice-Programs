#include <iostream>

using namespace std;
int mult_by_pow2(int, int);  //result = num * 2^power;

int main()
{
    int x = 21, y = 10;
    int diff = (x|y)-(x&y);
    int mod, sum = 0;
    while(diff != 0)
    {
        mod = diff%2;
        if(mod==1){sum++;}
        diff = diff/2;
    }
    cout << sum;

    cout << endl << endl;
    return 0;
}

int mult_by_pow2(int number, int power)
{
    cout << number << " * 2^" << power << " = ";
    return number<<power;
}
