
#include<limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<limits.h>
#include<string.h>
#define pi 3.14159265359

#define R 6371

typedef struct element element;
typedef struct element* liste;

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
    int limite;
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
    nvxElement->ville=ville;
    nvxElement->latitude=latitude;
    nvxElement->longitude=longitude;
    nvxElement->next = NULL;

    if (liste == NULL) return nvxElement;
    else
    {
        element* tmp =liste;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = nvxElement;
        return liste;
    }
}

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

liste InverseTab(liste tab[], int debut, int fin)
{
    liste temp;
    while (debut < fin)
    {
        temp = tab[debut-1];
        tab[debut-1] = tab[fin];
        tab[fin] = temp;
        debut++;
        fin--;
    }

    return tab;
}

liste EchangeVille(liste chemin, int i, int k)
{
    int t=0;
    liste tmp=chemin;
    element* tab[k-i+1];
    int compteur=0;
    while (tmp !=NULL)
    {
        if (compteur>=i && compteur <=k)
        {
            tab[t]=tmp;
            t++;
        }

         tmp=tmp->next;
         compteur ++;
    }


     int j;
     printf("\n");

     tab[k-i+1]=InverseTab(tab,0,t);
     /*for(j = 0; j < t; j++)
     {

       // printf(" %s %f \n", tab[j]->ville, tab[j]->latitude);
     }*/

    liste nvRoute=NULL;
    for(j=0;j<t;j++)
    {
        nvRoute=insertion(nvRoute,tab[j]->ville,tab[j]->latitude,tab[j]->longitude);
    }


    tmp = chemin;
    compteur=0;

    for(j=0; j<i-1; j++)
    {
        tmp=tmp->next;
    }

    liste ville1=tmp;
    int b;
    for(b=j;b<k;b++)
    {
        tmp=tmp->next;
    }
    liste ville2=tmp->next;
    ville1->next=nvRoute;

    while(ville1->next!=NULL)
    {
        ville1=ville1->next;
    }

    ville1->next=ville2;
    return chemin;

}

int CalculTotalDistance(liste chemin)
{
  int totaleDistance=0;

  while (chemin->next!=NULL)
  {

  totaleDistance=calculer_distance(chemin->latitude,chemin->longitude,chemin->next->latitude,chemin->next->longitude);
  chemin=chemin->next;

  }
   return totaleDistance;
}

liste LinKernighan(liste route)
{
int limit =8;
   int meilleuDistance = CalculTotalDistance(route);
   int nvDistance;
   liste nvRoute=NULL;
   int i,k;
   for(i=1; i<limit-1; i++)
   {
       for(k=1; k<limit-1; k++)
       {
           nvRoute=EchangeVille(route, i, k);
           nvDistance=CalculTotalDistance(nvRoute);
           if(nvDistance > meilleuDistance)
           {
               route=nvRoute;
           }
       }
   }

   return route;


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
            //

        }

    printf("Choix de l'exercice ? \n\n 1) Methode exacte\n 2) LinKernighan\n 3) Recherche locale\n 4) Dijkstra \n");
    printf(" \n ");
       int exercice;
    scanf("%d",&exercice);

      switch (exercice)
        {
         case 1:
            break;

        case 2 :
            afficherListe(listee);
            LinKernighan(listee);
            break;

        case 3 :
            break;
        default :
            printf("Erreur");
        }

}



    fclose(fichier);
    return 0;
}
