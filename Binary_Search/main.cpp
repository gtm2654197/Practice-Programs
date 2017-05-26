#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int>&, int, int, int);

int main()
{
    vector<int> Test;
    for(int i = 0; i < 1000000; i++)
    {
        Test.push_back(i);
    }
    cout << binarySearch(Test,0,Test.size(),0) << endl << endl;
    return 0;
}

int binarySearch(vector<int>& dataSet, int start, int stop, int key)
{
    cout << "start: " << start << " stop: " << stop << " key: " << key << endl;
    int i = (stop+start)>>1;
    if(dataSet[i] == key) return i;
    if((stop-start)<=1) return -1;
    if(dataSet[i]>key) return binarySearch(dataSet,start,i,key);
    if(dataSet[i]<key) return binarySearch(dataSet,i,stop,key);
}
