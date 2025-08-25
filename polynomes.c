#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"polynomes.h"

Term* createTerm(float coefficient, int exponent) {
    Term* term = (Term*)malloc(sizeof(Term));
    term->coefficient = coefficient;
    term->exponent = exponent;
    term->next = NULL;
    return term;
}


void addTerm(Polynomial* polynomial, float coefficient, int exponent) {
    Term* term = createTerm(coefficient, exponent);
    if (polynomial->terms == NULL) {
        polynomial->terms = term;
    } else {
        Term* current = polynomial->terms;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = term;
    }
}

Polynomial* createPolynomial() {
    Polynomial* polynomial = (Polynomial*)malloc(sizeof(Polynomial));
    polynomial->terms = NULL;
    polynomial->next = NULL;
    return polynomial;
}

void addPolynomialToList(Polynomial** list, Polynomial* polynomial) {
    if (*list == NULL) {
        *list = polynomial;
    } else {
        Polynomial* current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = polynomial;
    }
}

void loadPolynomialsFromFile(Polynomial** list,  char filename[100]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int numPolynomials;
    fscanf(file, "%d\n", &numPolynomials);

    for (int i = 0; i < numPolynomials; i++) {
        Polynomial* polynomial = createPolynomial();

        int numTerms;
        fscanf(file, "%d\n", &numTerms);

        for (int j = 0; j < numTerms; j++) {
            float coefficient; int exponent;
            fscanf(file, "%f %d\n", &coefficient, &exponent);
            addTerm(polynomial, coefficient, exponent);
        }

        addPolynomialToList(list, polynomial);
    }
    printf("Liste des polynomes chargee depuis le fichier.\n");
    fclose(file);
}

void savePolynomialsToFile(Polynomial* list/*, const char* filename*/) {
    FILE* file = fopen("polynomes.txt", "a+");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    int numPolynomials = 0;
    Polynomial* current = list;
    while (current != NULL) {
        numPolynomials++;
        current = current->next;
    }

    fprintf(file, "%d\n", numPolynomials);

    current = list;
    while (current != NULL) {
        int numTerms = 0;
        Term* term = current->terms;
        while (term != NULL) {
            numTerms++;
            term = term->next;
        }

        fprintf(file, "%d\n", numTerms);

        term = current->terms;
        while (term != NULL) {
            fprintf(file, "%.2f %d\n", term->coefficient, term->exponent);
            term = term->next;
        }

        current = current->next;
    }

    fclose(file);
}

void printPolynomials(Polynomial* list) {
    Polynomial* current = list;
    int index = 1;  

    while (current != NULL) {
        printf("\n");
        printf("P(X)%d = ", index);

        Term* term = current->terms;
        while (term != NULL) {
            if(term->exponent==0){
            printf("%.2f",term->coefficient);
            }
            else if (term->coefficient==0)
            {
                printf("0");
            }
            else if (term->coefficient==1)
            {
                printf("X^%d",term->exponent);
            }
            else if (term->exponent==1)
            {
                printf("%.2fX",term->coefficient);
            }
            else 
            printf("%.2fX^%d", term->coefficient, term->exponent);
            if (term->next!=NULL)
            {
                printf(" + ");
            }
            
            term = term->next;
            
        }

        printf("\n");
        current = current->next;
        index++;
    }
}


Polynomial* addPolynomials(Polynomial* polynomial1, Polynomial* polynomial2) {
    Polynomial* result = createPolynomial();
    Term* term1 = polynomial1->terms;
    Term* term2 = polynomial2->terms; 
    while (term1 != NULL && term2 != NULL) {
        if (term1->exponent > term2->exponent) {
            addTerm(result, term1->coefficient, term1->exponent);
            term1 = term1->next;
        } else if (term2->exponent > term1->exponent) {
            addTerm(result, term2->coefficient, term2->exponent);
            term2 = term2->next;
        } else {
            int coefficientSum = term1->coefficient + term2->coefficient;
            addTerm(result, coefficientSum, term1->exponent);
            term1 = term1->next;
            term2 = term2->next;
        
        }
    }

    // Ajouter les termes restants du polynome 1
    while (term1 != NULL) {
        addTerm(result, term1->coefficient, term1->exponent);
        term1 = term1->next;
    }

    // Ajouter les termes restants du polynome 2
    while (term2 != NULL) {
        addTerm(result, term2->coefficient, term2->exponent);
        term2 = term2->next;
    }
    printPolynomials(result);
    return result;
}

Polynomial* subtractPolynomials(Polynomial* polynomial1, Polynomial* polynomial2) {
    Polynomial* result = createPolynomial();

    Term* term1 = polynomial1->terms;
    Term* term2 = polynomial2->terms;

    while (term1 != NULL && term2 != NULL) {
        if (term1->exponent > term2->exponent) {
            addTerm(result, term1->coefficient, term1->exponent);
            term1 = term1->next;
        } else if (term2->exponent > term1->exponent) {
            addTerm(result, -term2->coefficient, term2->exponent);
            term2 = term2->next;
        } else {
            int coefficientDiff = term1->coefficient - term2->coefficient;
            addTerm(result, coefficientDiff, term1->exponent);
            term1 = term1->next;
            term2 = term2->next;
        }
    }

    // Ajouter les termes restants du polynome 1
    while (term1 != NULL) {
        addTerm(result, term1->coefficient, term1->exponent);
        term1 = term1->next;
    }

    // Ajouter les termes restants du polynome 2 (avec signe inverse)
    while (term2 != NULL) {
        addTerm(result, -term2->coefficient, term2->exponent);
        term2 = term2->next;
    }

    printPolynomials(result);
}
// Fonction pour multiplier deux polynomes
Polynomial* multiplyPolynomials(Polynomial* polynomial1, Polynomial* polynomial2) {
    Polynomial* result = createPolynomial();
    Term* term1 = polynomial1->terms;

    while (term1 != NULL) {
        Term* term2 = polynomial2->terms;

        while (term2 != NULL) {
            int coefficientProd = term1->coefficient * term2->coefficient;
            int exponentSum = term1->exponent + term2->exponent;

            addTerm(result, coefficientProd, exponentSum);

            term2 = term2->next;
        }

        term1 = term1->next;
    }

    printPolynomials(result);
    return result;
}

Polynomial* derivativePolynomial(Polynomial* polynomial) {
    Polynomial* derivative = createPolynomial();
    Term* term = polynomial->terms;

    while (term != NULL) {
        if (term->exponent > 0) {
            int derivativeCoefficient = term->coefficient * term->exponent;
            int derivativeExponent = term->exponent - 1;
            addTerm(derivative, derivativeCoefficient, derivativeExponent);
        }

        term = term->next;
    }
    return derivative;
}

Polynomial* integralPolynomial(Polynomial* polynomial) {
    Polynomial* integral = createPolynomial();
    Term* term = polynomial->terms;

    while (term != NULL) {
        float integralCoefficient = term->coefficient / (term->exponent + 1);
        int integralExponent = term->exponent + 1;
        addTerm(integral, integralCoefficient, integralExponent);

        term = term->next;
    }

    printPolynomials(integral);
    return integral;
}

float power(int x,int n)
{
    float pu=1;
    for(int i=1;i<=n;i++)
    {
        pu*=x;
    }
    return pu;
}

int evaluatePolynomial(Polynomial* polynomial, int value) {
    int result = 0;
    Term* term = polynomial->terms;

    while (term != NULL) {
        result += term->coefficient * power(value, term->exponent);
        term = term->next;
    }
    return result;
}

int getPolynomialDegree(Polynomial* polynomial) {
    int degree = 0;
    Term* term = polynomial->terms;

    while (term != NULL) {
        if (term->exponent > degree) {
            degree = term->exponent;
        }
        term = term->next;
    }
    return degree;
}
