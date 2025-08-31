#include <bits/stdc++.h>
#define MAXDIGITS 500
#define MINUS -1
#define PLUS 1
using namespace std;
typedef unsigned long long ll;

typedef struct {
    char digits[MAXDIGITS];
    int signbit;
    int last_digit;
} bignum;

void add_bignum(bignum *a, bignum *b, bignum *c);
void subtract_bignum(bignum *a, bignum *b, bignum *c);

void ll_to_bignum(ll s, bignum *n){
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

int compare_bignum(bignum *a, bignum *b){
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

void initialize_bignum(bignum * n){
    n->signbit = PLUS;
    for (int i = 0; i < MAXDIGITS;i++){
        n->digits[i] = (char) 0;
    }
    n->last_digit = 0;
}

void zero_justify(bignum *n){
    while ((n->last_digit > 0) and (n->digits[n->last_digit] == 0))
        n->last_digit--;
    if ((n->last_digit == 0) and (n->digits[0] == 0)) n->signbit = PLUS;
}

void add_bignum(bignum *a, bignum *b, bignum *c){
    int i, carry;
    initialize_bignum(c);
    if (a->signbit == b->signbit) c->signbit = a->signbit;
    else{
        if (a->signbit == MINUS){
            a->signbit = PLUS;
            subtract_bignum(b,c,a);
            a->signbit = MINUS;
        }
        else{
            b->signbit = PLUS;
            subtract_bignum(a,b,c);
            b->signbit = MINUS;
        }
    }
    c->last_digit = max(a->last_digit, b->last_digit) +1;
    carry = 0;
    for (i = 0; i <= (c->last_digit); i++){
        c->digits[i] = (char) (carry + a->digits[i] + b->digits[i]) % 10;
        carry = (carry + a->digits[i] + b->digits[i]) /10;
    }
    zero_justify(c);
}

void subtract_bignum(bignum *a, bignum *b, bignum *c){
    initialize_bignum(c);
    if ((a->signbit == MINUS) or (b->signbit == MINUS)){
        b->signbit = -1 * b->signbit;
        add_bignum(a,b,c);
        b->signbit = -1 * b->signbit;
        return;
    }
    if (compare_bignum(a,b) == PLUS){
        subtract_bignum(b,a,c);
        c->signbit = MINUS;
        return;
    }

    c->last_digit = max(a->last_digit, b->last_digit);
    int borrow = 0;
    int v = 0;
    for (int i = 0; i  <= (c->last_digit); i++){
        v = (a->digits[i] - borrow - b->digits[i]);
        if (a->digits[i] > 0) borrow = 0;
        if (v < 0){
            v = v + 10;
            borrow = 1;
        }
        c->digits[i] = (char) v;
    }
    zero_justify(c);
}

void digit_shift(bignum *n, int d){
    int i;
    if ((n->last_digit == 0) and (n->digits[0] == 0)) return;
    for (i = n->last_digit; i >= 0; i--){
        n->digits[i+d] = n->digits[i];
    }
    for (i = 0; i < d;i++) n->digits[i] = 0;

    n->last_digit = n->last_digit + d;
}

void multiply_bignum(bignum *a, bignum *b, bignum *c){
    bignum row, tmp;
    initialize_bignum(&row); initialize_bignum(&tmp); initialize_bignum(c);
    int i, j;
    row = *a;
    for (i = 0; i <= b->last_digit;i++){
        for (j = 1; j <= b->digits[i];j++){
            add_bignum(c, &row, &tmp);
            *c = tmp;
        }
        digit_shift(&row, 1);
    }
    c->signbit = a->signbit * b->signbit;
    zero_justify(c);
}

void copy_bignum(bignum *src, bignum *dest) {
    dest->signbit = src->signbit;
    dest->last_digit = src->last_digit;
    for (int i = 0; i <= src->last_digit; i++) {
        dest->digits[i] = src->digits[i];
    }
}

void divide_bignum(bignum *a, bignum *b, bignum *c){
    bignum row, tmp;
    initialize_bignum(&tmp); initialize_bignum(&row);
    int asing, bsing;
    int i;
    c->last_digit = a->last_digit;
    c->signbit = a->signbit * b->signbit;
    asing = a->signbit; a->signbit = PLUS;
    bsing = b->signbit; b->signbit = PLUS;
    for (i = a->last_digit; i >=0; i--){
        digit_shift(&row,1);
        row.digits[0] = a->digits[i];
        c->digits[i] = 0;
        while (compare_bignum(&row,b) != PLUS){
            c->digits[i]++;
            subtract_bignum(&row,b, &tmp);
            row = tmp;
        }
    }
    zero_justify(c);
    a->signbit = asing;
    b->signbit = bsing;
}

void read_bignum(bignum *n, string & line){
    n->signbit = PLUS;
    for (int i = line.size()-1; i >= 0; i--){
        n->digits[i] = line[line.size()-1 - i] - '0';
    }
    n->last_digit = line.size()-1;
}

void print_bignum(bignum *n){
    for (int i = n->last_digit; i >= 0; i--){
        cout << char (n->digits[i]+'0');
    }
    cout << endl;
}

void drop_last_digit(bignum *n, bignum *e){
    bignum ten;
    initialize_bignum(&ten);
    ll_to_bignum(10, &ten);
    divide_bignum(n, &ten,e);
}

void mod_bignum(bignum *a, bignum *b, bignum *c){
    bignum quotient, product;
    initialize_bignum(&quotient);
    initialize_bignum(&product);
    
    divide_bignum(a, b, &quotient);
    multiply_bignum(&quotient, b, &product);
    subtract_bignum(a, &product, c);
}

void calcula_gcd(bignum *a, bignum *b, bignum *result){
    bignum temp_a, temp_b, quotient, remainder;
    initialize_bignum(&temp_a); initialize_bignum(&temp_b);
    initialize_bignum(&quotient); initialize_bignum(&remainder); 
    copy_bignum(a, &temp_a); copy_bignum(b, &temp_b);
    while (temp_b.digits[0] != 0) {
        mod_bignum(&temp_a, &temp_b, &remainder); //pega o resto da divisão
        zero_justify(&temp_b);
        copy_bignum(&temp_b, &temp_a);            //temp_a = temp_b
        zero_justify(&temp_a);
        copy_bignum(&remainder, &temp_b);         //temp_b = remainder
    }
    copy_bignum(&temp_a, result);
    result->signbit = PLUS;
}

int main(){
    string line1, line2;
    bignum a,b, result;
    initialize_bignum(&a); initialize_bignum(&b); initialize_bignum(&result);
    cin >> line1 >> line2;
    read_bignum(&a, line1); read_bignum(&b, line2);
    if (compare_bignum(&a, &b) == 0) print_bignum(&a);
    else cout << 1 << endl;
    // calcula_gcd(&a, &b, &result);
    // print_bignum(&result);
}