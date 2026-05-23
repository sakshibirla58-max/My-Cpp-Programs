#include<iostream>
using namespace std;
int main() {
    int a, b, c;
    cout << " Enter three numbers ";
    cin >> a >> b >> c;
    if ( a > b && a > c)
    cout << " A is Largest " ;
    else if ( b > a && b > c)
    cout << " B is Largest " ;
    else 
    cout << " C is largest " ;
    
    return 0;
}
