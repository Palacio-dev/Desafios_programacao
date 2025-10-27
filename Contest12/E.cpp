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
    return hypot(p1.x - p2.x, p1.y - p2.y);
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

/**
 * Estrutura para representar um Vetor
 * (basicamente um alias para 'point', mas semanticamente diferente)
 */
struct vec {
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};

/**
 * Converte dois pontos 'a' e 'b' em um vetor (a -> b)
 */
vec toVec(point a, point b) {
    return vec(b.x - a.x, b.y - a.y);
}

//Escala um vetor 'v' por um fator 's'
vec scale(vec v, double s) {
    return vec(v.x * s, v.y * s);
}

//Translada um ponto 'p' de acordo com um vetor 'v'
point translate(point p, vec v) {
    return point(p.x + v.x, p.y + v.y);
}

//Produto escalar (dot product) de dois vetores
double dot(vec a, vec b) {
    return (a.x * b.x + a.y * b.y);
}

//Quadrado da norma (magnitude) de um vetor
double norm_sq(vec v) {
    return v.x * v.x + v.y * v.y;
}

/**
 * Calcula a distância de um ponto 'p' até uma reta definida por 'a' e 'b'
 * O ponto 'c' (ponto na reta mais próximo de 'p') é armazenado por referência
 */
double distToLine(point p, point a, point b, point &c) {
    // c = a + u * ab
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(p, c);
}


/**
 * Calcula a distância de um ponto 'p' até um segmento de reta [a, b]
 * O ponto 'c' (ponto no segmento mais próximo de 'p') é armazenado por referência
 */
double distToLineSegment(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);

    if (u < 0.0) { 
        c = point(a.x, a.y);
        return dist(p, a);
    }
    if (u > 1.0) { 
        c = point(b.x, b.y);
        return dist(p, b);
    }
    return distToLine(p, a, b, c);
}

//Calcula o ângulo <aob em radianos
double angle(point a, point o, point b) {
    vec oa = toVec(o, a);
    vec ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

//Produto vetorial 2D (resultado é um escalar)
double cross(vec a, vec b) {
    return a.x * b.y - a.y * b.x;
}

//Verifica se o ponto 'r' está à esquerda da linha orientada 'pq'
bool ccw(point p, point q, point r) {
    // Se cross > 0, r está à esquerda
    return cross(toVec(p, q), toVec(p, r)) > 0;
}

//Verifica se os pontos 'p', 'q' e 'r' são colineares
bool collinear(point p, point q, point r) {
    // Se cross == 0 (com tolerância EPS), são colineares
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}


int main(){
    int n; cin >> n;
    vector<point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    vector<line> unique_lines;
    line temp_line;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pointsToLine(points[i], points[j], temp_line);
            bool found = false;
            for (int k = 0; k < unique_lines.size(); k++) {
                if (areSame(unique_lines[k], temp_line)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                unique_lines.push_back(temp_line);
            }
        }
    }

    int intersection_count = 0;
    point p; 
    for (int i = 0; i < unique_lines.size(); i++) {
        for (int j = i + 1; j < unique_lines.size(); j++) {
            if (areIntersect(unique_lines[i], unique_lines[j], p)) {
                intersection_count++;
            }
        }
    }
    cout << intersection_count << endl;
}