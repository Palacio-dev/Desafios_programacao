#include <bits/stdc++.h>
using namespace std;

int main(){
   long long a,b;
   cin >> a >> b;
   int res = (a + 1) % 10;
   if ((b-a) >= 9) res = 0;
   else if (a == b) res = 1;
   else{    
        for (long long  i = (a + 2); i <= b; i++){
            res = (res * (i % 10)) % 10;
        }
   }
   cout << res << endl;
}

