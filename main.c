#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<limits.h>
#include<string.h>
#define pi 3.14159265359

#define R 6371


// Method to calculate the distance between two points defined by latitude and longitude
// This is also known as the haversine function

double degToRad(double degree)  // Method to convert to Radian from Degree
{
    return degree * (pi/180);
}

double calculer_distance(double lat1,double lon1,double lat2,double lon2)  // On extrait du csv les points latX, lonX
{
    //static const int R = 6371;  // Radius of the earth
    double deltaLat = degToRad(lat2-lat1); // degToRad is a method that converts the delta of latitudes/longitudes ( which is in degree )
    double deltaLon = degToRad(lon2-lon1);
    double a = sin(deltaLat/2) * sin(deltaLat/2) + cos(degToRad(lat1)) * cos(degToRad(lat2)) * sin(deltaLon/2) * sin(deltaLon/2); // sin^2(dLat) +sin^2(dLon) * cos(lat1*pi/180) * cos(lat2*pi/180)
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = R * c;  // d distance in km
    return d;

}


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

               }

    }
    double x = calculer_distance(48.86669293, 2.333335326, 43.61039878, 3.869985716);  // Exemple Paris / Montpellier
    printf("La distance est %f", x);

    fclose(fichier);


    return 0;
}


