#ifndef POLYNOMES_H
#define POLYNOME_H

// Representons un terme du polynome par Term
typedef struct Term {
    float coefficient;
    int exponent;
    struct Term* next;
} Term;

// Un polynome sera donc un ensemble de termes d'ou la structure Polynomial pour representer un polynome
typedef struct Polynomial {
    Term* terms;
    struct Polynomial* next;
} Polynomial;
Term* createTerm(float coefficient, int exponent);  // Fonction pour creer un nouveau terme
void addTerm(Polynomial* polynomial, float coefficient, int exponent); // Fonction pour ajouter un terme à un polynome
Polynomial* createPolynomial(); // Fonction pour creer un nouveau polynome
void addPolynomialToList(Polynomial** list, Polynomial* polynomial);// Fonction pour ajouter un polynome à la liste de polynomes
void loadPolynomialsFromFile(Polynomial** list, char filename[100]);// Fonction pour charger la liste de polynomes depuis un fichier
void savePolynomialsToFile(Polynomial* list/*, const char* filename*/);
void printPolynomials(Polynomial* list);
Polynomial* addPolynomials(Polynomial* polynomial1, Polynomial* polynomial2);
Polynomial* subtractPolynomials(Polynomial* polynomial1, Polynomial* polynomial2);
Polynomial* multiplyPolynomials(Polynomial* polynomial1, Polynomial* polynomial2);
Polynomial* derivativePolynomial(Polynomial* polynomial);
Polynomial* integralPolynomial(Polynomial* polynomial);
int evaluatePolynomial(Polynomial* polynomial, int value);
int getPolynomialDegree(Polynomial* polynomial);

#endif