#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include<limits.h>
#include<string.h>
#define BUF_SIZE 2048



// Création de nvxElement
element* insertion(element *liste, char* ville, float latitude, float longitude)
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

        printf("%s,%f,%f -> ", actuel->ville,actuel->latitude,actuel->longitude);
        actuel = actuel->next;
    }

    printf("NULL\n");
}



int main()
{
    FILE* fichier = NULL;
    int caractereActuel = 0;
    fichier = fopen("test.csv", "r+");
    element* listee=NULL;

    float latitude;
    float longitude;

    if (fichier != NULL)

    {
       /*AFFICHAGE SANS PARSER
       while (fscanf(fichier,"%30[^,],%f,%f", ville, &latitude,&longitude)!=EOF)

               {
                   printf("%s, %f, %f",ville, latitude,longitude);



               }*/

        char laLigne[50];
        while(fgets(laLigne,sizeof(laLigne),fichier) !=NULL)
        {
            char* a= strtok(laLigne, ",");
            char* ville=malloc(1+strlen(a));
            // utiliser la méthode strcpy pour avoir une string
            char* b=strtok(NULL,",");
            char* c=strtok(NULL," ");
            double valeur= atof(b);
            double valeurbis=atof(c);
            float latitude=valeur;
            float longitude=valeurbis;
            strcpy(ville,a);
            listee = insertion(listee,ville,valeur, valeurbis);
            afficherListe(listee);

        }


    }
    fclose(fichier);
    return 0;
}
