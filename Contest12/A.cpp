#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct point {
    double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {} 

    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
};

int main(){
    cout << fixed << setprecision(3);
    point p1, p2, p3, p4;
    point p_comum, p_extremo1, p_extremo2, p_final;
    while (cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y){
        if (p1 == p3){
            p_comum = p1;
            p_extremo1 = p2; 
            p_extremo2 = p4; 
        } 
        else if (p1 == p4){
            p_comum = p1;
            p_extremo1 = p2;
            p_extremo2 = p3;
        } 
        else if (p2 == p3){ 
            p_comum = p2;
            p_extremo1 = p1;
            p_extremo2 = p4;
        } 
        else if (p2 == p4){ 
            p_comum = p2;
            p_extremo1 = p1;
            p_extremo2 = p3;
        }
        p_final.x = p_extremo1.x + p_extremo2.x - p_comum.x;
        p_final.y = p_extremo1.y + p_extremo2.y - p_comum.y;
        cout << p_final.x << " " << p_final.y << endl;
    }
}