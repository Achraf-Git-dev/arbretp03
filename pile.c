#include "pile.h"

pile_t* InitialiserPile()
{
    pile_t* tete = malloc(sizeof(pile_t));
    tete->value = NULL;
    tete->next = NULL;
    return tete;
}

void Empiler(pile_t** tete, arbre_t* val)
{
    pile_t* nv = malloc(sizeof(pile_t));
    if ((tete != NULL) || (nv != NULL))
    {
        nv->value = val;
        nv->next = *tete;
        (*tete) = nv;
    }
}

void Depiler(pile_t** tete)
{
    pile_t* tmp = (*tete);

    if (tete != NULL)
    {
        (*tete) = (*tete)->next;
    }

    //free(tmp);
}

void AfficherPile(pile_t* tete)
{
    pile_t* tmp = tete;
    while (tmp->value != NULL)
    {
        printf("%c", tmp->value->contenu);
        tmp = tmp->next;
    }
    printf("\n");
}

void AfficherPileInverse(pile_t* tete)
{
    pile_t* nv = InitialiserPile();
    pile_t* tmp = tete;
    if (nv != NULL)
    {
        while (tmp->value != NULL)
        {
            Empiler(&nv, tmp->value);
            tmp = tmp->next;
        }
        AfficherPile(nv);
    }
}

bool estVide(pile_t* tete)
{
    return (tete == NULL);
}
