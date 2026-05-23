#include<iostream>
using namespace std;
int main() {
    int n, i;
    cout << " Enter a number " ;
    cin >> n;
    for ( i = 2; i < n; i++){
      if( n % i == 0){
      cout << " Not prime ";
      return 0;
       }
    }
      cout << " prime " ;
      return 0;
}
