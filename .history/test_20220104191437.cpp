#include <iostream>

using namespace std;

int main()
{
    int a = 0;
    int b = 0;
    for (a=0; a < 100; a++)
    {
        b = a >> 1;
        cout << b << endl;
    }
    return 0;
}