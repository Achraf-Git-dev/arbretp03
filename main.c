#include "arbre.h"

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        arbre_t* arbre = NULL;
        arbre = ConstructionArbre(argv[1]);
        AfficherDictionnaire(arbre);
    }
}