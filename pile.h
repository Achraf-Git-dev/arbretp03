#ifndef PILE__H
#define PILE__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arbre.h"

typedef struct pile
{
    arbre_t* value;
    struct pile* next;
} pile_t;

pile_t* InitialiserPile();
pile_t* CreerPile(arbre_t* val);
void AfficherPile(pile_t* tete);
void Empiler(pile_t** tete, arbre_t* val);
void Depiler(pile_t** tete);
bool estVide(pile_t* tete);
void AfficherPile(pile_t* tete);
void AfficherPileInverse(pile_t* tete);

#endif