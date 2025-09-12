#include <bits/stdc++.h>
#include <cmath>
using namespace std;
typedef long long ll;
typedef vector<int> vi ;
typedef map<int,int> mii;

ll _sieve_size;
bitset <10000010> bs ; // 10^7 should be enough for most cases
vi primes ; 

void sieve (ll upperbound){ // c reate l i s t o f primes i n [ 0 . . upperbound ]
    _sieve_size = upperbound + 1; // add 1 to inc lude upperbound
    bs.set() ; // se t a l l b i t s to 1
    bs[0] = bs[1] = 0 ; 
    for (ll i = 2 ;i <=_sieve_size ;i++) if (bs[i]){
        for (ll j = i * i ; j <= _sieve_size ; j += i ) bs[j] = 0 ;
        primes.push_back (( int ) i) ;
    } 
} 

bool isPrime (ll N) { 
    if (N <= _sieve_size) return bs [N] ;
    for (int i = 0 ; i < ( int )primes.size();i ++)
        if (N % primes[i] == 0) return false ;
    return true ; 
} 

vi primeFactors (ll N) { 
    vi factors; 
    ll PF_idx = 0, PF = primes[PF_idx]; 
    while (N != 1 and (PF * PF <= N)){ // s top a t s q r t (N) , but N can get smal le r
        while (N % PF == 0) { N /= PF ; factors.push_back (PF) ; } // remove t h i s PF
        PF = primes [++PF_idx] ; // on ly cons ider primes !
    }
    if (N != 1) factors.push_back (N) ; // spec ia l case i f N i s a c t u a l l y a prime
    return factors ; // i f p f exceeds 32−b i t i n teger , you have to change v i
}

int gcd(int a , int b){return b == 0 ? a : gcd (b, a % b);}
int lcm (int a , int b){return a * (b / gcd (a , b));}

ll EulerPhi(ll N){
    ll PF_idx = 0 ,PF = primes[PF_idx], ans = N; // s t a r t from ans = N
    while (N != 1 and (PF * PF <= N) ) {
        if (N % PF == 0) ans -= ans/PF ; // on ly count unique f a c t o r
        while (N % PF == 0) N /= PF ;
        PF = primes [++ PF_idx ] ;
    }
    if (N != 1) ans -= ans / N; // l a s t f a c t o r
    return ans ;
}

int main(){
    sieve(10000000); 
    ll n, x;
    cin >> n;
    double raiz;
    while (n--){
        cin >> x;
        raiz = sqrt(x);
        ll raiz_inteira = (int)(raiz);
        if (raiz_inteira * raiz_inteira != x){
            cout << "NO" << endl;
            continue;
        }
        else{
            if (isPrime(raiz_inteira)) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }    
}

