#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"polynomes.h"

int main()
{
    Polynomial* polynomials = NULL;

    int choice;
    char filename[100];

    do {
        printf("\n\n\t\t&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
        printf("\t\t&&&&                 PROGRAMME DE MANIPULATION DES POLYNOMES                  &&&&\n");
        printf("\t\t&&&&                       UE: INFO 132 EC2                                   &&&&\n");
        printf("\t\t&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n\n\n");
        printf("\t\t\t1. Charger la liste des polynomes depuis un fichier\n");
        printf("\t\t\t2. Creer un polynome\n");
        printf("\t\t\t3. Afficher la liste des polynomes contenu dans le fichier\n");
        printf("\t\t\t4. Additionner deux polynomes\n");
        printf("\t\t\t5. Soustraire deux polynomes\n");
        printf("\t\t\t6. Multiplier deux polynomes\n");
        printf("\t\t\t7. Diviser deux polynomes\n");
        printf("\t\t\t8. Calculer la derivee d'un polynome\n");
        printf("\t\t\t9. Calculer la primitive d'un polynome\n");
        printf("\t\t\t10. evaluer un polynome pour une valeur donnee\n");
        printf("\t\t\t11. Obtenir le degre d'un polynome\n");
        printf("\t\t\t0. Quitter le programme \n\n");
        printf("\t\tFaites un choix parmis ceux-ci dessus: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Entrez le nom du fichier : ");
                scanf("%s", filename);
                loadPolynomialsFromFile(&polynomials, filename);
                break;
            case 2:
                {
                    int numTerms;
                    printf("Combien de termes contiendra  le polynome ? ");
                    scanf("%d", &numTerms);

                    Polynomial* polynomial = createPolynomial();

                    for (int i = 0; i < numTerms; i++) {
                        float coefficient; int exponent;
                        printf("Entrez le coefficient et l'exposant du terme %d : ", i + 1);
                        scanf("%f %d", &coefficient, &exponent);
                        addTerm(polynomial, coefficient, exponent);
                    }

                    addPolynomialToList(&polynomials, polynomial);
                    savePolynomialsToFile(polynomial);
                    printf("Polynome ajoute à la liste.\n");
                }
                break;
            case 3:
                printPolynomials(polynomials);
                break;
            case 4:
                {
                int index1, index2;
                printf("Entrez l'indice du premier polynome : ");
                scanf("%d", &index1);
                printf("Entrez l'indice du deuxième polynome : ");
                scanf("%d", &index2);

                Polynomial* polynomial1 = polynomials;
                Polynomial* polynomial2 = polynomials;
                int count = 1;

                // Trouver le premier polynome
                while (polynomial1 != NULL && count < index1) {
                    polynomial1 = polynomial1->next;
                    count++;
                }

        count = 1;

        // Trouver le deuxième polynome
        while (polynomial2 != NULL && count < index2) {
            polynomial2 = polynomial2->next;
            count++;
        }

        if (polynomial1 == NULL || polynomial2 == NULL) {
            printf("Polynome(s) introuvable(s).\n");
        } else {
            printf("La somme des polynomes %d et %d est: ",index1,index2);
            Polynomial* sum = addPolynomials(polynomial1, polynomial2);
            addPolynomialToList(&polynomials, sum);
            savePolynomialsToFile(sum);
        }
    
    }
    break;
           case 5:
    {
        int index1, index2;
        printf("Entrez l'indice du premier polynome : ");
        scanf("%d", &index1);
        printf("Entrez l'indice du deuxième polynome : ");
        scanf("%d", &index2);

        Polynomial* polynomial1 = polynomials;
        Polynomial* polynomial2 = polynomials;
        int count = 1;

        // Trouver le premier polynome
        while (polynomial1 != NULL && count < index1) {
            polynomial1 = polynomial1->next;
            count++;
        }

        count = 1;

        // Trouver le deuxième polynome
        while (polynomial2 != NULL && count < index2) {
            polynomial2 = polynomial2->next;
            count++;
        }

        if (polynomial1 == NULL || polynomial2 == NULL) {
            printf("Polynome(s) introuvable(s).\n");
        } else {
            printf("La soustraction des polynomes %d et %d est : ",index1,index2);
            Polynomial* difference = subtractPolynomials(polynomial1, polynomial2);
            addPolynomialToList(&polynomials, difference);
            //printPolynomials(difference);
            savePolynomialsToFile(difference);
        }
    }
    break;
             case 6:
    {
        int index1, index2;
        printf("Entrez l'indice du premier polynome : ");
        scanf("%d", &index1);
        printf("Entrez l'indice du deuxième polynome : ");
        scanf("%d", &index2);

        Polynomial* polynomial1 = polynomials;
        Polynomial* polynomial2 = polynomials;
        int count = 1;

        // Trouver le premier polynome
        while (polynomial1 != NULL && count < index1) {
            polynomial1 = polynomial1->next;
            count++;
        }

        count = 1;

        // Trouver le deuxième polynome
        while (polynomial2 != NULL && count < index2) {
            polynomial2 = polynomial2->next;
            count++;
        }

        if (polynomial1 == NULL || polynomial2 == NULL) {
            printf("Polynome(s) introuvable(s).\n");
        } else {
            printf("Le produit des polynomes %d et %d est: ",index1,index2);
            Polynomial* product = multiplyPolynomials(polynomial1, polynomial2);
            addPolynomialToList(&polynomials, product);
            //printPolynomials(product);
            savePolynomialsToFile(product);
        }
    }
    break;
   /*       case 7:
    {
        int index1, index2;
        printf("Entrez l'indice du dividende : ");
        scanf("%d", &index1);
        printf("Entrez l'indice du diviseur : ");
        scanf("%d", &index2);

        Polynomial* dividend = polynomials;
        Polynomial* divisor = polynomials;
        int count = 1;

        // Trouver le dividende
        while (dividend != NULL && count < index1) {
            dividend = dividend->next;
            count++;
        }

        count = 1;

        // Trouver le diviseur
        while (divisor != NULL && count < index2) {
            divisor = divisor->next;
            count++;
        }

        if (dividend == NULL || divisor == NULL) {
            printf("Polynome(s) introuvable(s).\n");
        } else {
            Polynomial* remainder;
            Polynomial* quotient = dividePolynomials(dividend, divisor, &remainder);

            if (quotient != NULL) {
                addPolynomialToList(&polynomials, quotient);
                addPolynomialToList(&polynomials, remainder);

                printPolynomials(remainder);
            }
        }
    }
    break;*/
         case 8:
    {
        int index;
        printf("Entrez l'indice du polynome : ");
        scanf("%d", &index);

        Polynomial* polynomial = polynomials;
        int count = 1;

        // Trouver le polynome
        while (polynomial != NULL && count < index) {
            polynomial = polynomial->next;
            count++;
        }

        if (polynomial == NULL) {
            printf("Polynome introuvable.\n");
        } else {
            printf("La derivee du polynome %d est: ",index);
            Polynomial* derivative = derivativePolynomial(polynomial);
            addPolynomialToList(&polynomials, derivative);
            printPolynomials(derivative);
            savePolynomialsToFile(derivative);
        }
    }
    break;
        case 9:
    {
        int index;
        printf("Entrez l'indice du polynome : ");
        scanf("%d", &index);

        Polynomial* polynomial = polynomials;
        int count = 1;

        // Trouver le polynome
        while (polynomial != NULL && count < index) {
            polynomial = polynomial->next;
            count++;
        }

        if (polynomial == NULL) {
            printf("Polynome introuvable.\n");
        } else {
            printf("La primitive du polynome %d est: ",index);
            Polynomial* integral = integralPolynomial(polynomial);
            addPolynomialToList(&polynomials, integral);
            savePolynomialsToFile(integral);
        }
    }
    break;
           case 10:
    {
        int index, value;
        printf("Entrez l'indice du polynome : ");
        scanf("%d", &index);
        printf("Entrez la valeur à evaluer : ");
        scanf("%d", &value);

        Polynomial* polynomial = polynomials;
        int count = 1;

        // Trouver le polynome
        while (polynomial != NULL && count < index) {
            polynomial = polynomial->next;
            count++;
        }

        if (polynomial == NULL) {
            printf("Polynome introuvable.\n");
        } else {
            int evaluation = evaluatePolynomial(polynomial, value);
           printf("P(%d) = %d",value, evaluation);
        }
    }
    break;
            case 11:
    {
        int index;
        printf("Entrez l'indice du polynome : ");
        scanf("%d", &index);

        Polynomial* polynomial = polynomials;
        int count = 1;

        // Trouver le polynome
        while (polynomial != NULL && count < index) {
            polynomial = polynomial->next;
            count++;
        }

        if (polynomial == NULL) {
            printf("Polynome introuvable.\n");
        } else {
            int degree = getPolynomialDegree(polynomial);
            printf("le degre du polynome est %d",degree);
        }
    }
    break;

            case 0:
                printf("\n\t\tAU REVOIR ET A LA PROCHAINE !\n");
                break;
                
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }

        printf("\n");
    } while (choice != 0 && 1<=choice<=11);
 /*
 les polynomes sont enregistres dans le fichier comme suit:
 <nombre de polynome cree>
 <nombre de terme du polynome>
 <coef du monome i > <exposant du monome i>
 */

    return 0;
    
}


