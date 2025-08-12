#include <iostream>
#include <string>
using namespace std;

int main(){
    int t; 
    cin >> t;
    while (t > 0){
        int n;
        string cartas;
        cin >> n >> cartas;
        bool aliceTem1 = false;
        bool aliceTemN = false;
        bool bobTem1 = false;
        bool bobTemN = false;
        int quant_alice = 0;
        int quant_bob = 0;
        for (int i = 0; i < cartas.size(); i++){
            if (cartas[i] == 'A'){
                quant_alice += 1;
            }
            else{
                quant_bob += 1;
            }
        }
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
        if (aliceTem1 and aliceTemN){
            cout << "Alice" << endl;
        }
        else if (bobTem1 and bobTemN){
            cout << "Bob" << endl;
        }
        else if (aliceTem1 and bobTemN){
            if (quant_bob == 1){
                cout << "Alice" << endl;
            }
            else{
                cout << "Bob" << endl;
            }
        }
        else if ((aliceTemN and bobTem1) or (bobTem1 and aliceTemN)){
            if (cartas[size(cartas) - 2] == 'A'){
                cout << "Alice" << endl;
            }
            else{
                cout << "Bob" << endl;
            }
        }
    t--;    
    }
}