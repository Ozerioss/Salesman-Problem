

#include<limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<limits.h>
#include<string.h>
#define pi 3.14159265359

#define R 6371

#define MAX_STR_LEN 1024
#define NBR_VILLES 72

struct ville{
    int index;
    char* nom;
    float latitude;
    float longitude;
};

struct ville villes[NBR_VILLES];

/* PROTOTYPE OF FUNCTIONS */
int readCitiesFile();
void printCitiesList();


//Méthodes pour faciliter le calcul des distances à partir des latitudes / longitudes
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

// Lecture du fichier et sauvegarde dans la liste chainée
int readCitiesFile()
{
    /* FileStream for the Library File */
    FILE* csvFile = NULL;
    csvFile = fopen("Cites.csv", "r");

    /* allocation of the buffer for every line in the File */
    char *buf = malloc(MAX_STR_LEN);
    //char *buf = malloc(sizeof(struct ville));
    char *tmp;

    /* if the space could not be allocaed, return an error */
    if (buf == NULL) {
        printf ("No memory\n");
        return 1;
    }

    if (( csvFile ) == NULL ) //Reading a file
    {
        printf( "File could not be opened.\n" );
    }

    int i = 0;
    while (fgets(buf, 255, csvFile) != NULL)
    {
        if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n'))
            buf[strlen (buf) - 1] = '\0';

        tmp = strtok(buf, ",");
        //villes[i].nom = tmp;
        villes[i].nom = strdup(tmp);
       //printf("%s", tmp);

        tmp = strtok(NULL, ",");
        villes[i].latitude = atof(tmp);

        tmp = strtok(NULL, ",");
        villes[i].longitude = atof(tmp);

        villes[i].index = i;
        i++;
    }
    //free(buf);
    fclose(csvFile);
    return 0;
}

void printCitiesList()
{

    int i;

    for (i = 1; i <= 71; i++)
    {
        if (villes[i].nom != NULL)
        printf("index i= %i %s -- %f -- %f\n", villes[i].index, villes[i].nom, villes[i].latitude, villes[i].longitude);
        else
            break;
    }

}


int main(int argc, char **argv)
{
    int isOK = 0;

    isOK = readCitiesFile();

    printCitiesList();
    printf("test\n");
    //printf("ville : %s", );

    system("pause");
    return 0;
}



