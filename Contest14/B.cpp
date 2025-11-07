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
    return cross(toVec(p, q), toVec(p, r)) >= 0;
}

//Verifica se os pontos 'p', 'q' e 'r' são colineares
bool collinear(point p, point q, point r) {
    // Se cross == 0 (com tolerância EPS), são colineares
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

point pivot;

bool isConvex(const vector<point> &P) {
    int sz = (int)P.size();
    // Um ponto, linha ou polígono degenerado não é convexo.
    if (sz < 3) return false;
    // Pega a direção da primeira curva (P0, P1, P2)
    bool isLeft = ccw(P[0], P[1], P[2]);
    // Compara com as outras
    for (int i = 1; i < sz; i++) {
        // Verifica a curva em P[i]
        // (P[i], P[(i+1)%sz], P[(i+2)%sz])
        if (ccw(P[i], P[(i + 1) % sz], P[(i + 2) % sz]) != isLeft) {
            return false; // (polígono é côncavo)
        }
    }
    return true; // (polígono é convexo)
}


/**
 * @brief [Page 8] Algoritmo "Winding Number".
 * * Retorna true se o ponto 'pt' está dentro de um 
 * polígono 'P' (côncavo ou convexo).
 * Computa a soma dos ângulos formados pelas arestas
 * com o ponto 'pt'.
 * Assume que o primeiro vértice é igual ao último.
 */
bool inPolygon(point pt, const vector<point> &P) {
    if ((int)P.size() == 0) return false; 
    
    double sum = 0; 
    
    // Itera sobre todas as arestas (P[i], P[i+1])
    for (int i = 0; i < (int)P.size() - 1; i++) { 
        if (ccw(pt, P[i], P[i + 1])) { 
            // left turn/ccw
            // sinal positivo
            sum += angle(P[i], pt, P[i + 1]); 
        } else {
            // right turn/cw
            // sinal negativo
            sum -= angle(P[i], pt, P[i + 1]); 
        }
    }
    // Se a soma for 2*PI (ou -2*PI), está dentro.
    // Comparamos usando fabs e EPS.
    return fabs(fabs(sum) - 2 * M_PI) < EPS; 
}

bool angleCmp(point a, point b) { 
    // Caso especial: se forem colineares com o pivô
    if (collinear(pivot, a, b)) { 
        // Desempata pela distância (mais próximo primeiro)
        return dist(pivot, a) < dist(pivot, b); 
    }
    // Compara os ângulos usando atan2
    // Calcula vetores do pivô para 'a' e 'b'
    double d1x = a.x - pivot.x; 
    double d1y = a.y - pivot.y; 
    double d2x = b.x - pivot.x; 
    double d2y = b.y - pivot.y; 
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0; 
}

vector<point> CH(vector<point> P) { 
    int i, j, n = (int)P.size(); 
    if (n == 1){
        P.push_back(P[0]);
        return P;
    }
    // if (n <= 3) { 
    //     if (n > 0 && !(P[0] == P[n - 1])) { 
    //         P.push_back(P[0]); 
    //     }
    //     return P; 
    // }
    // 1. Encontrar P0: ponto mais baixo e mais à direita.
    int P0 = 0; 
    for (i = 1; i < n; i++) { 
        if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x)) { 
            P0 = i; 
        }
    }
    // Coloca P0 na primeira posição
    point temp = P[0]; P[0] = P[P0]; P[P0] = temp; 
    // 2. Ordenar os pontos (P[1]...P[n-1]) pelo ângulo com P0.
    pivot = P[0]; // Define o pivô global para 'angleCmp'
    sort(++P.begin(), P.end(), angleCmp); 
    // 3. Testes CCW (algoritmo de Graham)
    vector<point> S; 
    // Inicia a pilha S (conforme slide)
    S.push_back(P[n - 1]); S.push_back(P[0]); S.push_back(P[1]); 
    i = 2; // Começa a verificar do terceiro ponto (índice 2)
    while (i < n) { 
        j = (int)S.size() - 1; 
        // Se for uma curva à esquerda, aceita o ponto.
        if (ccw(S[j - 1], S[j], P[i])) { 
            S.push_back(P[i++]); 
        } 
        // Se for curva à direita, remove o topo da pilha.
        else {
            S.pop_back(); 
        }
    }
    return S; 
}

bool check(point p1, point p2, const vector<point>& all_points) {
    vector<point> remaining_points;
    for (const auto& p : all_points) {
        if (!collinear(p1, p2, p)) {
            return false;
        }
    }
    return true;
    /*if (remaining_points.size() <= 2) {
        return true;
    }
    for (size_t i = 2; i < remaining_points.size(); i++) {
        if (!collinear(remaining_points[0], remaining_points[1], remaining_points[i])) {
            return false; 
        }
    }
    return true; */
}

int main(){
    int t, n; cin >> t;
    vector<point> ConvexH;
    point p;
    char c;
    while (t--){
        cin >> n;
        set<point> points;
        for (int i = 0; i < n; i++){
            cin >> p.x >> p.y >> c;
            if (c == 'Y'){
                points.insert(p);
            }
        }
        ConvexH = (vector<point>(points.begin(), points.end()));
        cout << ConvexH.size() -1  << "\n";
        // for (int i = 0; i < ConvexH.size();i++){
        //     cout << ConvexH[i].x << " " << ConvexH[i].y << endl;
        // }
        // return 0;
        int P0 = 0; 
        for (int i = 1; i < n; i++) { 
            if (ConvexH[i].y < ConvexH[P0].y || (ConvexH[i].y == ConvexH[P0].y && ConvexH[i].x > ConvexH[P0].x)) { 
                P0 = i; 
            }
        }
        // Coloca P0 na primeira posição
        point temp = ConvexH[0]; ConvexH[0] = ConvexH[P0]; ConvexH[P0] = temp; 
        // 2. Ordenar os pontos (ConvexH[1]...ConvexH[n-1]) pelo ângulo com P0.
        pivot = ConvexH[0]; // Define o pivô global para 'angleCmp'
        sort(++ConvexH.begin(), ConvexH.end(), angleCmp); 
        for (int i = 0; i < ConvexH.size() -1;i++){
            cout << ConvexH[i].x << " " << ConvexH[i].y << "\n";
        }
    }
} 