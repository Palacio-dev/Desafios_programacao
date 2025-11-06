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

//Calcula a distância Euclidiana entre dois pontos
double dist(point p1, point p2) {
    // hypot(dx, dy) retorna sqrt(dx*dx + dy*dy)
    return hypot(abs(p1.x - p2.x), abs(p1.y - p2.y));
}

//Converte graus para radianos
double DEG_to_RAD(double d) {
    return d * PI / 180.0;
}

//Rotaciona um ponto 'p' em 'theta' graus no sentido anti-horário
//em relação à origem (0,0)
point rotate(point p, double theta) {
    double rad = DEG_to_RAD(theta);
    return point(p.x * cos(rad) - p.y * sin(rad),
                 p.x * sin(rad) + p.y * cos(rad));
}

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

/**
 * Encontra o ponto de interseção de duas retas não-paralelas
 * Retorna true se houver interseção, false se forem paralelas
 * O ponto de interseção 'p' é passado por referência
 */
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

// Perímetro de um triângulo (implícito na Pág. 13/14)
double triangle_perimeter(double ab, double bc, double ca) {
    return ab + bc + ca;
}

/**
 * @brief Área de um triângulo (Fórmula de Heron) [cite: 405]
 * dados os comprimentos dos lados a, b, c.
 * O semiperímetro 's' é definido em[cite: 404].
 */
double triangle_area(double ab, double bc, double ca) {
    double s = 0.5 * triangle_perimeter(ab, bc, ca);
    return sqrt(s * (s - ab) * (s - bc) * (s - ca));
}

int main(){
    int n; cin >> n;
    vector<line> lines;
    line l;
    point a, b;
    point c, d, e;
    double max_perimetro = 0.0;
    bool achou_triangulo = false;
    for (int i = 0; i <  n; i++){
        cin >> a.x >> a.y >> b.x >> b.y;
        pointsToLine(a, b, l);
        lines.push_back(l);
    }
    for (int i = 0; i < lines.size(); i++){
        for (int j = i + 1; j < lines.size(); j++){
            for (int k = j + 1; k < lines.size();k++){
                if (areIntersect(lines[i], lines[j], c) and areIntersect(lines[i], lines[k], d) and 
                areIntersect(lines[j], lines[k], e)){
                    double dist1 = dist(c, d);
                    double dist2 = dist(c, e);
                    double dist3 = dist(d, e);
                    if ((dist1 + dist2 > dist3 + EPS) and (dist1 + dist3 > dist2 + EPS) and (dist2 + dist3 > dist1 + EPS)){
                        double perimetro = triangle_perimeter(dist1, dist2, dist3);
                        max_perimetro = max(max_perimetro, perimetro);
                        achou_triangulo = true;
                    }
                }
            }
        }
    }
    cout << fixed << setprecision(10);
    if (achou_triangulo) cout << max_perimetro << endl;
    else cout << "no triangle" << endl;
}