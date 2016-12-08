
#include<limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<limits.h>
#include<string.h>
#define pi 3.14159265359

#define R 6371

typedef struct element element;
typedef struct element*liste;

struct element
{
    char* ville;
    float latitude;
    float longitude;
    element* next;
};

typedef struct matrice_distance matrice_distance;

struct matrice_distance
{
    int nbVille;
    double **tab;
};
double degToRad(double degree)  // Method to convert to Radian from Degree
{
    return degree * (pi/180);
}

double calculer_distance(float lat1,float lon1,float lat2,float lon2)  // On extrait du csv les points latX, lonX
{
    //static const int R = 6371;  // Radius of the earth



    double deltaLat = degToRad(lat2-lat1); // degToRad is a method that converts the delta of latitudes/longitudes ( which is in degree )
    double deltaLon = degToRad(lon2-lon1);
    double a = sin(deltaLat/2) * sin(deltaLat/2) + cos(degToRad(lat1)) * cos(degToRad(lat2)) * sin(deltaLon/2) * sin(deltaLon/2); // sin^2(dLat) +sin^2(dLon) * cos(lat1*pi/180) * cos(lat2*pi/180)
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = R * c; // d distance in km
    return d;


}

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
/*void afficherListe(element *liste)
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
}*/


void MatriceVille(matrice_distance* matrice)
{
    int i = 0, j = 0;
    printf("\n");
    printf("\t");

    for(i=0;i<matrice->nbVille;i++)
    printf("%d\t",i);
    printf("\n");


    for (i = 0; i <matrice->nbVille; i++)
    {
        printf("%d\t",i);
        for (j = 0; j < matrice->nbVille; j++)
        {

            int actuel,actuelbis;
            double dist = matrice->tab[actuel][actuelbis];
            double distance=dist(matrice,i,j);
            if(distance==0) printf("INFINI\t");
            else printf("%.2f\t", distance);
        }
        printf("\n");
    }
}

void ParcourirListe(element*liste)
{
    element *actuel =liste;
    float latitude;
    float longitude;

    while (actuel !=NULL)
    {
        element *actuelbis =actuel->next;


        while (actuelbis !=NULL)
       {


        double distance = calculer_distance(actuel->latitude,actuel->longitude,actuelbis->latitude,actuelbis->longitude);

        if (distance<=100)
        {

            distance=-1;
        }


        actuelbis=actuelbis->next;

    }

     actuel=actuel->next;
}

   printf("NULL\n");

}


int main()
{
    FILE* fichier = NULL;
    int caractereActuel = 0;
    fichier = fopen("test.csv", "r+");
    element* listee=NULL;
    liste villes;

    float latitude;
    float longitude;

    if (fichier != NULL)

    {

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
            //afficherListe(listee);

        }
       // ATTENTION LA LISTE EST A L'ENVERS !!

    printf("\n\n\n\n\n");
   //ParcourirListe(listee);
   matrice_distance* Matriix=(villes,NBCITY);
   ParcourirListe(Matriix);

}



    fclose(fichier);
    return 0;
}
