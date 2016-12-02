#include <stdio.h>
#include <stdlib.h>
//#include "Header.h"
#include<limits.h>

typedef struct element* element;

struct element
{
    char ville;
    int latitude;
    int longitude;
    element* next;
};

// Création de nvxElement
element* insertion(element *liste, char ville, int latitude, int longitute)
{
    element *nvxElement = malloc(sizeof( *nvxElement));
    if (nvxElement == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nvxElement->ville =ville;
    nvxElement->latitude=latitude;
    nvxElement->longitude=longitute;
    nvxElement->next = liste;
    return nvxElement;
}
//Afficher une liste
void afficherListe(element *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    element *actuel = liste;
    while (actuel != NULL)
    {
        printf(" %c,%c,%d -> ", actuel->ville,actuel->latitude,actuel->longitude);
        actuel = actuel->next;
    }
    printf("NULL\n");
}
int main()
{
    FILE* fichier = NULL;
    int caractereActuel = 0;
    fichier = fopen("cites.csv", "r");
    element* listee=NULL;
    if (fichier != NULL)
    {
        char laLigne[100];
        while(fgets(laLigne,sizeof(laLigne),fichier) !=NULL)
        {
            char* premier= strtok(laLigne," ; ");
            char* deuxieme=strtok(NULL," ; ");
            char* troisieme=strtok(NULL," ; ");
            int valeur=atoi(deuxieme);
            int valeurbis=atoi(troisieme); // transforme le char en int
            char ville=*premier;
            listee = insertion(listee,ville,valeur, valeurbis);
            afficherListe(listee);
        }
    }
    fclose(fichier);
    return 0;
}
