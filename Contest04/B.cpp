#include <bits/stdc++.h>
#define MAXDIGITS 220
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
    c->last_digit = max(a->last_digit, b->last_digit) + 1;
    carry = 0;
    for (i = 0; i <= (c->last_digit); i++){
        c->digits[i] = (char) (carry + a->digits[i] + b->digits[i]) % 10;
        carry = (carry + a->digits[i] + b->digits[i]) /10;
    }
    zero_justify(c);
}

void subtract_bignum(bignum *a, bignum *b, bignum *c){
    initialize_bignum(c);
    if (a->signbit == MINUS or b->signbit == MINUS){
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
    int v;
    c->last_digit = max(a->last_digit, b->last_digit);
    int borrow = 0;
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
    bignum row;
    bignum tmp;
    initialize_bignum(&row);
    initialize_bignum(&tmp);
    initialize_bignum(c);
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

void divide_bignum(bignum *a, bignum *b, bignum *c){
    bignum row, tmp;
    initialize_bignum(&tmp); initialize_bignum(&row); initialize_bignum(c);
    c->last_digit = a->last_digit;
    c->signbit = a->signbit * b->signbit;
    int asing = a->signbit; a->signbit = PLUS;
    int bsing = b->signbit; b->signbit = PLUS;
    for (int i = a->last_digit; i >=0; i--){
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

bool eh_bignum_zero(bignum *n){
    return (n->digits[0] == 0) and (n->last_digit == 0);
}

void copy_bignum(bignum *src, bignum *dest) {
    dest->signbit = src->signbit;
    dest->last_digit = src->last_digit;
    for (int i = 0; i <= src->last_digit; i++) {
        dest->digits[i] = src->digits[i];
    }
}

void power(bignum *base, bignum *exp, bignum * result, bignum *um, bignum *dois){
    bignum aux1, aux2, aux3, aux4, aux5;
    initialize_bignum(&aux1); initialize_bignum(&aux2);initialize_bignum(&aux3); initialize_bignum(&aux4);initialize_bignum(&aux5);
    copy_bignum(um, &aux1);
    copy_bignum(base, &aux2);
    copy_bignum(base, &aux4);
    while (!eh_bignum_zero(exp)){
        if ((exp->digits[0] != 0) and (exp->digits[0] != 2) and (exp->digits[0] != 4) and (exp->digits[0] != 6) and (exp->digits[0] != 8)){
            multiply_bignum(&aux1, &aux2, &aux5);
            copy_bignum(&aux5, &aux1);
            copy_bignum(&aux5, result);
            // initialize_bignum(&aux5);
        }
        // initialize_bignum(&aux2);
        multiply_bignum(&aux4, &aux4, &aux2);
        // initialize_bignum(&aux4);
        copy_bignum(&aux2, &aux4);
        divide_bignum(exp, dois, &aux3);
        // initialize_bignum(exp);
        copy_bignum(&aux3, exp);
    }
}

int main(){
    bignum t,a,b, numerador, denomidador, um,dois, result, power1, power2;
    ll num1, num2, num3;
    initialize_bignum(&um); initialize_bignum(&numerador); initialize_bignum(&denomidador); initialize_bignum(&result);
    initialize_bignum(&power1); initialize_bignum(&power2); initialize_bignum(&dois);
    ll_to_bignum(1,&um); ll_to_bignum(2,&dois);
    while (cin >> num1 >> num2 >> num3){
        initialize_bignum(&t); initialize_bignum(&a); initialize_bignum(&b);
        initialize_bignum(&numerador); initialize_bignum(&denomidador); initialize_bignum(&result);
        ll_to_bignum(num1, &t); ll_to_bignum(num2, &a); ll_to_bignum(num3, &b);
        cout << '(' << num1 << '^' << num2 << "-1)"
         << '/'
         << '(' << num1 << '^' << num3 << "-1) ";
        power(&t, &a, &power1, &um, &dois);
        subtract_bignum(&power1, &um, &numerador);
        power(&t, &b, &power2, &um, &dois);
        subtract_bignum(&power2, &um, &denomidador);
        divide_bignum(&numerador, &denomidador, &result);
        if (result.last_digit < 100) print_bignum(&result);
        else cout << "is not an integer with less than 100 digits." << endl;
    }
}