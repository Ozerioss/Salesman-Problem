#include <stdio.h>
#include <stdlib.h>
//#include "Header.h"
#include<limits.h>
#include<string.h>

typedef struct element element;

struct element
{
    char ville;
    char latitude;
    char longitude;
    element* next;
};

// Création de nvxElement
element* insertion(element *liste, char ville, int latitude, int longitude)
{
    element *nvxElement = malloc(sizeof( *nvxElement));

    if (nvxElement == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nvxElement->ville=ville;
    nvxElement->latitude=latitude;
    nvxElement->longitude=longitude;
    nvxElement->next = liste;

    return nvxElement;
}

//Afficher
void afficherListe(element *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    element *actuel = liste;
    while (actuel != NULL)
    {
        printf("%c,%d,%d -> ", actuel->ville,actuel->latitude,actuel->longitude);
        actuel = actuel->next;
    }

    printf("NULL\n");
}
int main()
{
    FILE* fichier = NULL;
    int caractereActuel = 0;
    fichier = fopen("Cites.csv", "r+");
    element* listee=NULL;
    char ville[30];
    float latitude;
    float longitude;
    if (fichier != NULL)

    {
        while (fscanf(fichier,"%30[^,],%f,%f", ville, &latitude,&longitude)!=EOF)
               {
                   printf("%s, %f, %f", ville, latitude,longitude);
                  /* listee = insertion(listee,ville,latitude, longitude);
                   afficherListe(listee);*/




               }

       /* char laLigne[100];
        while(fgets(laLigne,sizeof(laLigne),fichier) !=NULL)
        {
            char* premier= strtok(laLigne, ",");
            // utiliser la méthode strcpy pour avoir une string
            char* deuxieme=strtok(NULL,",");
            char* troisieme=strtok(NULL," ");
            int valeur=atoi(deuxieme);
            int valeurbis=atoi(troisieme);
            int latitude=deuxieme;
            int longitude=troisieme;
            char ville=*premier;
            listee = insertion(listee,ville,valeur, valeurbis);
            afficherListe(listee);

        }*/


    }
    fclose(fichier);
    return 0;
}
