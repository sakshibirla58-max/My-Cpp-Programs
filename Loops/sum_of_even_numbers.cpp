#include<iostream>
using namespace std;
int main() {
    int n, sum =0;
    cout << " enter a number ";
    cin >> n ;
    for ( int i = 1; i <= n; i++){
    if(i % 2 == 0){
       cout << i << " ";
       sum += i;
    }
      } 
      cout <<" even sum = " << sum << endl;

    return 0;
}
