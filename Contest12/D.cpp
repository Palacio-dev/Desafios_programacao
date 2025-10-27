#include <bits/stdc++.h>
using namespace std;    

const double EPS = 1e-9;
const double PI = acos(-1.0);

struct point {
    double x, y; 
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}

    bool operator < (point other) const {
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        else if (fabs(y - other.y) > EPS)
            return y < other.y;
        return false;
    }

    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
};

struct line {
    double a, b, c;
};
//Converte dois pontos para a equação da reta ax+by+c=0
void pointsToLine(point p1, point p2, line &l) {
    // Reta vertical
    if (fabs(p1.x - p2.x) < EPS){
        l.a = 1.0; l.b = 0.0; l.c = -p1.x;
    } 
    else {
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0; 
        l.c = -(double)(l.a * p1.x) - p1.y;
    }
}

//Verifica se duas retas são paralelas
bool areParallel(line l1, line l2) {
    // Compara os coeficientes a e b
    return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

//Verifica se duas retas são equivalentes (mesma reta)
bool areSame(line l1, line l2) {
    // Verifica se são paralelas E se o coeficiente c é igual
    return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS);
}

bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false;

    // Resolve o sistema linear 2x2
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);

    // Evita divisão por zero se a reta 1 for vertical (b=0)
    if (fabs(l1.b) > EPS)
        p.y = -(l1.a * p.x + l1.c);
    else
        p.y = -(l2.a * p.x + l2.c);

    return true;
}

int main(){
    int n;
    cin >> n;
    cout << fixed << setprecision(2);
    point p1, p2, p3,p4, p_intersection;
    line l1, l2;
    cout <<  "INTERSECTING LINES OUTPUT" << endl;
    while (n--){
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
        pointsToLine(p1, p2, l1);
        pointsToLine(p3, p4, l2);
        if (areIntersect(l1, l2, p_intersection)){
            cout << "POINT " << p_intersection.x << " " << p_intersection.y << endl;
        }
        else if (areSame(l1, l2)){
            cout << "LINE" << endl;
        }
        else{
            cout << "NONE" << endl;
        }
    }
    cout << "END OF OUTPUT" << endl;
}


