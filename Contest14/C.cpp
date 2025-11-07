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


/**
 * @brief Verifica se um ponto está dentro, na borda ou fora de um círculo.
 * Transcrição da Pág. 3 [cite: 89-91].
 * @return 0 (inside), 1 (border), 2 (outside)
 */
int insideCircle(point p, point  c, int r) { // Versão com inteiros
    int dx = p.x - c.x, dy = p.y - c.y;
    int Euc = dx * dx + dy * dy, rSq = r * r;
    return Euc < rSq ? 0 : (Euc == rSq ? 1 : 2); // 0=inside / 1=border / 2=outside
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

/*
==================================================
CIRCUNFERÊNCIA INSCRITA (Triângulos, Pág. 14-15)
==================================================
*/

/**
 * @brief Calcula o RAIO da circunferência inscrita (InCircle).
 * Versão com os comprimentos dos lados. [cite: 414, 426-427]
 * Fórmula: r = A / s (onde A é área, s é semi-perímetro)
 */
double rInscribedCircle(double ab, double bc, double ca) {
    // Usa as funções auxiliares que definimos acima
    double area = triangle_area(ab, bc, ca);
    double perimeter = triangle_perimeter(ab, bc, ca);
    
    // Evita divisão por zero se a área for 0 (pontos colineares)
    if (fabs(perimeter) < EPS) return 0.0;
    return area / (0.5 * perimeter);
}

/**
 * @brief Calcula o RAIO da circunferência inscrita (InCircle).
 * Versão com os pontos dos vértices. [cite: 422-424, 428-429]
 * Usa a função 'dist' da sua biblioteca 'geometria.h'.
 */
double rInscribedCircle(point a, point b, point c) {
    return rInscribedCircle(dist(a, b), dist(b, c), dist(c, a));
}


/**
 * @brief Calcula o CENTRO da circunferência inscrita.
 * Transcrição da Pág. 15 , agora funcional
 * usando as funções da sua biblioteca 'geometria.h'.
 */
int inCircle(point p1, point p2, point p3, point &ctr, double &r) {
    r = rInscribedCircle(p1, p2, p3);
    if (fabs(r) < EPS) return 0; // não há centro (pontos colineares)

    line l1, l2;

    // Calcula a bissetriz do ângulo p1
    double ratio = dist(p1, p2) / dist(p1, p3);
    point p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
    pointsToLine(p1, p, l1); // [cite: 469]

    // Calcula a bissetriz do ângulo p2
    ratio = dist(p2, p1) / dist(p2, p3);
    p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
    pointsToLine(p2, p, l2); // [cite: 472-475]

    // Pega a interseção delas
    areIntersect(l1, l2, ctr); // [cite: 476-477]
    
    return 1;
}


/**
 * NOTA DE EXPERT: O slide na Pág. 20 [cite: 611-615] repete o código de
 * 'rInscribedCircle' por engano.
 * O código abaixo implementa a fórmula correta para o RAIO 
 * da circunferência circunscrita (CircumCircle) da Pág. 20:
 * R = abc / 4A [cite: 610]
 */
double rCircumscribedCircle(double ab, double bc, double ca) {
    double area = triangle_area(ab, bc, ca);
    // Evita divisão por zero
    if (fabs(area) < EPS) return 0.0;
    return (ab * bc * ca) / (4.0 * area);
}



double rCircumscribedCircle(point a, point b, point c) {
    // Usa 'dist' da sua biblioteca
    return rCircumscribedCircle(dist(a, b), dist(b, c), dist(c, a));
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


/**
 * @brief [Page 12] Interseção de Linha-Segmento.
 * * Encontra o ponto 's' onde a linha infinita (A,B)
 * intercepta o segmento de reta (p,q).
 * * (Depende de 'line', 'pointsToLine' e 'areIntersect' do seu template)
 */
point lineIntersectSeg(point p, point q, point A, point B) { 
    point s; 
    line l1, l2; 
    // Linha 1 (representando o segmento p-q)
    pointsToLine(p, q, l1); 
    // Linha 2 (a linha de corte A-B)
    pointsToLine(A, B, l2); 
    // Encontra a interseção 's'
    areIntersect(l1, l2, s); 
    return s; 
}


/**
 * @brief [Page 12] Corta um polígono convexo.
 *
 * Corta o polígono Q pela linha (a, b).
 * Retorna o novo polígono P que está à esquerda da linha (a, b).
 * Assume que o último ponto de Q é igual ao primeiro.
 */
vector<point> cutPolygon(point a, point b, const vector<point> &Q) { 
    vector<point> P; 
    // Itera sobre todas as arestas (Q[i], Q[i+1])
    for (int i = 0; i < (int)Q.size() - 1; i++) { 
        // Posição de Q[i] e Q[i+1] em relação à linha (a,b)
        // (cross > 0 é 'left')
        double left1 = cross(toVec(a, b), toVec(a, Q[i])); 
        double left2 = cross(toVec(a, b), toVec(a, Q[i + 1])); 
        // Se Q[i] está à esquerda (ou sobre a linha), inclua em P.
        if (left1 > -EPS) {
            P.push_back(Q[i]); 
        }
        // Se a aresta (Q[i], Q[i+1]) cruza a linha (a,b)
        if (left1 * left2 < -EPS) { 
            // Adiciona o ponto de interseção
            P.push_back(lineIntersectSeg(Q[i], Q[i + 1], a, b)); 
        }
    }
    // Garante que o polígono resultante P também seja fechado
    if (!P.empty() && !(P.back() == P.front())) { 
        P.push_back(P.front()); 
    }
    return P; 
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
    if (n <= 3) { 
        if (n > 0 && !(P[0] == P[n - 1])) { 
            P.push_back(P[0]); 
        }
        return P; 
    }
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

int main(){
    int n;
    point p;
    while ((cin >> n) and n!= 0){
        vector<point> points;
        for (int i = 0; i < n; i++){
            cin >> p.x >> p.y;
            points.push_back(p);
        }
        if (n > 0) points.push_back(points[0]);
        cin >> p.x >> p.y;
        if (inPolygon(p, points)) cout << "T\n";
        else cout << "F\n";
    }
}