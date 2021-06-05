#include "chaine_caractere.h"

char Minuscule(char* lettre)
{
    char resultat = *lettre;
    if ((*lettre >= 65) && (*lettre <= 90)) resultat = *lettre + 32;
    return resultat;
}

char Majuscule(char* lettre)
{
    char resultat = *lettre;
    if (lettre == Minuscule(lettre)) resultat = *lettre - 32;
    return resultat;
}

int taillemot(char* mot)
{
    int i = 0;
    while (mot[i] != '\0')
    {
        i++;
    }
    return i;
}

char* copie(char* source, int i)
{
    int taille = taillemot(source) - i + 1;
    char* destination = malloc(taille*sizeof(char));
    for (int j=0;j<taille;j++)
    {
        destination[j] = source[i+j];
    }
    return destination;    
}