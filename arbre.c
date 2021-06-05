#include "arbre.h"

// Fonction qui prend en argument l'expression algebrique d'une arbre ou forêt pour construire un dictionnaire

arbre_t* ConstructionArbre(char* notation)
{
    arbre_t* arbre = NULL;
    pile_t* ptr_pile = InitialiserPile();
    arbre_t** prec = &arbre; // on declare un pointeur pour nous aider à parcourir l'arbre
    bool code = true; // un booleen pour nous aider à sarvoir quand il faut empiler lorsque qu'on a plusieurs * suivies
    int i = 0;

    while (notation[i] != '\0')
    {
        switch(notation[i])
        {
            case '*' :
                if (code) Empiler(&ptr_pile, *prec);
                prec = &((*prec)->lv);
                code = false;
                i++;
                break;
            case '+' :
                prec = &(ptr_pile->value->lh);
                Depiler(&ptr_pile);
                code = 0;
                i++;
                break;
            case ')' :
                Depiler(&ptr_pile);
                code = 0;
                i++;
                break;
            case '(' :
                code = 0;
                i++;
                break;
            default :
                *prec = Ajouter(prec, notation[i]);
                if ((notation[i+1] == '+') && (code == 0)) Empiler(&ptr_pile, *prec);
                i++;
                break;
        }
    }
    free(ptr_pile);
    return arbre;
}

arbre_t* AjouterNoeud(char a_ajouter)
{
    arbre_t* tmp = malloc(sizeof(arbre_t));
    if (tmp != NULL)
    {
        tmp->contenu = a_ajouter;
        tmp->lh = NULL;
        tmp->lv = NULL;
    }
    return tmp;
}

void AfficherDictionnaire(arbre_t* arbre)
{
    pile_t* ptr_pile = InitialiserPile();
    bool code = true;
    int verification = 0;
    arbre_t** prec = &arbre;

    while (code == true)
    {
        while (*prec != NULL)
        {
            Empiler(&ptr_pile, *prec);
            if (((*prec)->contenu >= 'A') && ((*prec)->contenu <= 'Z')) AfficherPileInverse(ptr_pile);
            prec = &((*prec)->lv);
        }
        prec = &(ptr_pile->value);
        while ((ptr_pile->value != NULL) && ((*prec)->lh == NULL))
        {
            Depiler(&ptr_pile);
            prec = &(ptr_pile->value);
        }
        if (ptr_pile->value == NULL) code = false;
        else
        {
            prec = &(ptr_pile->value->lh);
            Depiler(&ptr_pile);
        }
    }
}

arbre_t** RechercheHorizontale(arbre_t* cellule, char lettre)
{
    arbre_t* prec = cellule;
    arbre_t** cour = &cellule;
    if (prec != NULL)
    {
        while ((prec->lh != NULL) && (Minuscule(&(prec->lh->contenu)) <= lettre))
        {
            prec = prec->lh;
        }
        *cour = prec;
        /*if ((prec == NULL) || (Miniscule(prec->contenu) != lettre))
        {
            cour = &cellule;
            while ((*cour)->lh != prec)
            {
                cour = &((*cour)->lh);
            }
        }
        else cour = &prec;*/
    }
    else cour = NULL;
    return cour;
}

bool Existe(arbre_t* cellule, char lettre)
{
    int* position;
    arbre_t** prec = RechercheHorizontale(cellule, lettre);
    return ((*prec)->contenu == lettre);
}

arbre_t* Inserer(arbre_t** racine, char* mot)
{
    int i = 0;
    arbre_t** prec = NULL;
    arbre_t** cour = racine;
    arbre_t* tmp = NULL;
    int position;
    pile_t* pile = InitialiserPile();
    char* cp;
    bool oui;
    bool fini = false;
    while ((mot[i] != '\0') && (*cour != NULL) && (!fini))
    {
        prec = RechercheHorizontale(*cour, mot[i]);
        tmp = *prec;
        oui = Existe(*cour, mot[i]);
        if (oui)
        {
            Empiler(&pile, tmp);
            cour = &(pile->value->lv);
            i++;
        }
        else
        {
            if (*prec == *cour)
            {
                if ( Minuscule(&((*prec)->contenu)) > mot[i] )
                {
                    if (*cour == *racine)
                    {
                        *prec = Ajouter(cour, mot[i]);
                        (*prec)->lh = tmp;
                        *racine = *prec;
                        cour = &((*prec)->lv);
                        i++;
                    }
                    else
                    {
                        tmp = pile->value->lv;
                        *prec = Ajouter(cour, mot[i]);
                        pile->value->lv = *prec;
                        (*prec)->lh = tmp;
                        cour = &((*prec)->lv);
                        i++;
                    }
                }
                else
                {
                    cour = &(tmp->lh);
                }
            }
            else
            {
                if ((*prec)->lh != NULL)
                {
                    tmp = (*prec)->lh;
                    (*prec)->lh = Ajouter(cour, mot[i]);
                    (*prec)->lh->lh = tmp;
                    *cour = (*prec)->lh->lv;
                    i++;
                }
                else
                {
                    cour = &((*prec)->lh);
                }
            }
            fini = true;
        }
    }
    cp = copie(mot, i);
    *cour = InsererMot(cour, cp);
    free(pile);
    return *racine;
}

arbre_t* InsererMot(arbre_t** racine, char* mot)
{
    int i = 0;
    arbre_t** prec = racine;
    while (mot[i] != '\0')
    {
        if (mot[i+1] == '\0') *prec = Ajouter(racine, Majuscule(&(mot[i])));
        else *prec = Ajouter(racine, mot[i]);
        prec = &((*prec)->lv);
        i++;
    }
    return *racine;
}

void RechercheDictionnaire(arbre_t* arbre, char* motif)
{
    pile_t* ptr_pile = InitialiserPile();
    pile_t* parcour_pile;
    arbre_t* sauv;
    bool code = true;
    bool admis = true;
    char* cp = malloc(taillemot(motif)*sizeof(char));
    char* s;
    arbre_t** prec = NULL;
    arbre_t** cour = &arbre;
    arbre_t* tmp;
    bool debut = true;
    int i = 0;

    while ((motif[i] != '\0') && (admis == true))
    {
        prec = RechercheHorizontale(*cour, motif[i]);
        tmp = *prec;
        admis = Existe(*cour, motif[i]);
        if (admis)
        {
            cour = &(tmp->lv);
            if (debut)
            {
                sauv = tmp;
                debut = false;
            }
        }
        i++;
    }

    *prec = tmp;

    code = admis;
    
    while (code)
    {
        while (*prec != NULL)
        {
            tmp = *prec;
            Empiler(&ptr_pile, *prec);
            if ((tmp->contenu >= 'A') && (tmp->contenu <= 'Z'))
            {
                for (i=0;i<taillemot(motif)-1;i++){
                    printf("%c",motif[i]);
                }
                AfficherPileInverse(ptr_pile);
            }
            prec = &(tmp->lv);
        }
        prec = &(ptr_pile->value);
        while ((ptr_pile->value != NULL) && ((*prec)->lh == NULL))
        {
            Depiler(&ptr_pile);
            prec = &(ptr_pile->value);
        }
        if (ptr_pile->value == NULL) code = false;
        else
        {
            prec = &(ptr_pile->value->lh);
            Depiler(&ptr_pile);
            if (ptr_pile->value == NULL) code = false;
        }
    }
}
