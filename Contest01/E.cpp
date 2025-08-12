#include <iostream>
#include <string>
using namespace std;

int main(){
    int t; 
    cin >> t;
    while (t != 0){
        int n;
        string cartas;
        cin >> n >> cartas;
        bool aliceTem1 = false;
        bool aliceTemN = false;
        bool bobTem1 = false;
        bool bobTemN = false;
        if (cartas[0] == 'A'){
            aliceTem1 = true;
        }
        else{
            bobTem1 = true;
        }
        if (cartas[size(cartas) -1] == 'A'){
            aliceTemN = true;
        }
        else{
            bobTemN = true;
        }

        
        if (aliceTem1 and bobTemN) {
            cout << "Alice\n";
        }
        else if (bobTem1 and aliceTemN) {
            cout << "Bob\n";
        }
        else if (aliceTemN) {
            cout << "Alice\n";
        }
        else {
            cout << "Bob\n";
        }
        t--;
    }
}