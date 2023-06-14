#include <iostream>
#include "forward.cpp"
#include "backward.cpp"
using std::cin;
using std::cout;
int main()
{
    int choice;
    cout << "1. Forward " << endl;
    cout << "2. Backward" << endl;
    cin >> choice;
    if (choice == 1)
    {
        forward();
    }
    else if (choice == 2)
    {
        backward();
    }
    else
    {
        cout << "Try again";
    }
    return 0;
}