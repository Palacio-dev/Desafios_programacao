#include <bits/stdc++.h>
#define MAXDIGITS 600
#define MINUS -1
#define PLUS 1
using namespace std;
typedef unsigned long long ll;

typedef struct {
    char digits[MAXDIGITS];
    int signbit;
    int last_digit;
} big_num;

void ll_to_big_num(ll s, big_num *n){
    int i;
    ll t;
    if (s >= 0) n->signbit = PLUS;
    else n->signbit = MINUS;
    for (i = 0; i < MAXDIGITS; i ++) n->digits[i] = (char) 0;
    n->last_digit = -1;
    t = (s >= 0) ? s : -s;
    while (t > 0){
        n->last_digit++;
        n->digits[n->last_digit] = (char) (t % 10);
        t = t/10;
    }
    if (s == 0) n->last_digit = 0;
}

int compare_big_num(big_num *a, big_num *b){
    int i;
    if ((a->signbit == MINUS) and (b->signbit == PLUS)) return (PLUS);
    if ((a->signbit == PLUS) and (b->signbit == MINUS)) return (MINUS);

    if (a->last_digit > b->last_digit) return (MINUS * a->signbit);
    if (b->last_digit > a->last_digit) return (PLUS * a->signbit);

    for (int i = a->last_digit; i >= 0;i--){
        if (a->digits[i] > b->digits[i]) return (MINUS * a->signbit);
        if (b->digits[i] > a->digits[i]) return (PLUS * a->signbit);
    }
    return 0;
}

void le_big_num_b(string & l, int pos, big_num * b){
    for (int j = pos; j < l.size();j++){
        b->digits[l.size()-1-j] = l[j] - '0';
    }
    b->last_digit = l.size() - pos;
}

void zero_justify(big_num *n){
    while ((n->last_digit > 0) and (n->digits[n->last_digit] == 0))
        n->last_digit--;
    if ((n->last_digit == 0) and (n->digits[0] == 0)) n->signbit = PLUS;
}

void add_big_num(big_num *a, big_num *b, big_num *c){
    int i, carry;
    c->last_digit = max(a->last_digit, b->last_digit) +1;
    carry = 0;
    for (i = 0; i <= (c->last_digit); i++){
        c->digits[i] = (char) (carry + a->digits[i] + b->digits[i]) % 10;
        carry = (carry + a->digits[i] + b->digits[i]) /10;
    }
    zero_justify(c);
}

void initialize_big_num(big_num * n){
    n->signbit = PLUS;
    for (int i = 0; i < MAXDIGITS;i++){
        n->digits[i] = (char) 0;
    }
    n->last_digit = 0;
}

void digit_shift(big_num *n, int d){
    int i;

    if ((n->last_digit == 0) and (n->digits[0] == 0)) return;
    for (i = n->last_digit; i >= 0; i--){
        n->digits[i+d] = n->digits[i];
    }
    for (i = 0; i < d;i++) n->digits[i] = 0;

    n->last_digit = n->last_digit + d;
}

void multiply_big_num(big_num *a, big_num *b, big_num *c){
    big_num row;
    big_num tmp;
    initialize_big_num(&row);
    initialize_big_num(&tmp);
    int i, j;
    row = *a;
    for (i = 0; i <= b->last_digit;i++){
        for (j = 1; j <= b->digits[i];j++){
            add_big_num(c, &row, &tmp);
            *c = tmp;
        }
        digit_shift(&row, 1);
    }
    c->signbit = a->signbit * b->signbit;
    zero_justify(c);
}

int main(){
    vector <string> lines;
    string line;
    ll max = INT_MAX;
    big_num max_int;
    initialize_big_num(&max_int);
    ll_to_big_num(max, &max_int);
    while (getline(cin,line)){
        lines.push_back(line);
    }
    for (string& l : lines){
        big_num a;
        big_num b;
        big_num c;
        initialize_big_num(&a);
        initialize_big_num(&b);
        initialize_big_num(&c);
        char operador;
        int comp = 0;
        int comp2 = 0;
        int comp3 = 0;
        for (int i = 0; i < l.size();i++){
            if (l[i] == ' '){
                a.last_digit = i-1;
                for (int j = 0; j < i; j++){
                    a.digits[i-j-1] = l[j] - '0';
                }
                operador = l[i+1];
                le_big_num_b(l, i+3, &b);
                break;
            }
        }
        zero_justify(&a);
        zero_justify(&b);
        comp = compare_big_num(&max_int, &a);
        comp2 = compare_big_num(&max_int, &b);
        if (operador == '+') add_big_num(&a,&b, &c);
        else multiply_big_num(&a, &b, &c);
        zero_justify(&c);
        comp3 = compare_big_num(&max_int, &c);
        cout << l << endl;
        if (comp == 1) cout << "first number too big" << endl;
        if (comp2 == 1) cout << "second number too big" << endl;
        if (comp3 == 1) cout << "result too big" << endl;
    }
}