#ifndef ARBRE__H
#define ARBRE__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pile.h"
#include "chaine_caractere.h"

typedef struct arbre
{
    char contenu;
    struct arbre* lv;
    struct arbre* lh;
} arbre_t;

arbre_t* ConstructionArbre(char* notation);
arbre_t* AjouterNoeud(char a_ajouter);
void AfficherDictionnaire(arbre_t* arbre);
arbre_t** RechercheHorizontale(arbre_t* cellule, char lettre);
void RechercheDictionnaire(arbre_t* arbre, char* motif);
bool Existe(arbre_t* cellule, char lettre);
arbre_t* Inserer(arbre_t** racine, char* mot);
arbre_t* InsererMot(arbre_t** racine, char* mot);

#endif