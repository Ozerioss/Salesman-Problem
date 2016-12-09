


#include<limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<limits.h>
#include<string.h>
#include<stdbool.h>
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
float degToRad(float degree)  // Method to convert to Radian from Degree
{
    return degree * (pi/180);
}

float calculer_distance(float lat1,float lon1,float lat2,float lon2)  // On extrait du csv les points latX, lonX
{
    //static const int R = 6371;  // Radius of the earth



    float deltaLat = degToRad(lat2-lat1); // degToRad is a method that converts the delta of latitudes/longitudes ( which is in degree )
    float deltaLon = degToRad(lon2-lon1);
    float a = sin(deltaLat/2) * sin(deltaLat/2) + cos(degToRad(lat1)) * cos(degToRad(lat2)) * sin(deltaLon/2) * sin(deltaLon/2); // sin^2(dLat) +sin^2(dLon) * cos(lat1*pi/180) * cos(lat2*pi/180)
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    float d = R * c; // d distance in km
    return d;


}

void bruteForce(int a[], int i, int n)
{
    int currentCity = 47; // index de Paris qui est notre ville de départ
    float currentDist = 0;
    float globalDist = 0;

    int nextCity;   // ID
    int order[72];
    order[0] = villes[0].index;
    int maxGlobalDist = 100000;

    if(i == n)
    {
        for(int k=0; k<i+1; k++)
        {

            nextCity = a[k];
            order[k+1] = nextCity;
            currentDist = calculer_distance(villes[k].latitude, villes[k].longitude, villes[k+1].latitude, villes[k].longitude); // on calcule la distance
            globalDist += currentDist;
            currentCity = nextCity;
        }

        if(globalDist>maxGlobalDist)
        {
            maxGlobalDist = globalDist;
            for(int i =0; i<71; i++)
            {

                printf("ville  %s ->", villes[i].nom);
            }
            printf("Paris");
            maxGlobalDist += calculer_distance(villes[47].latitude, villes[47].longitude, villes[order[i]].latitude, villes[order[i]].longitude);
        }
    }
    else
    {
        for(int j=1;j<=n;j++)
        {
            permuter(a[i],a[j]);
            bruteForce(a, i+1, n); // parametre updatés
            permuter(a[i],a[j]);
        }
    }
}

void permuter(int a, int b)
{
    int c = 0;
    c = a;
    a = b;
    b = c;
}

bool checkVisited(int id, int tab[])
{
    bool isVisited;
    for(int i =0;i<72;i++)
    {
        if (tab[i] == id)
        {
            isVisited = true;
        }
    }
    return isVisited;
}

void getLongestPath(float currentDist)
{
    int* visited[72];
    //float currentDist;
    float globalDist;
    float maxDist;
    //struct ville *villes;
    for(int i = 0;i<72;i++)
    {
        if (!checkVisited(villes[i].index,visited[72]))
        {
                currentDist = calculer_distance(villes[i].latitude, villes[i].longitude, villes[i+1].latitude, villes[i+1].longitude); // calculate the distance
                visited[i] = villes[i].index;  // mark it as visited
                globalDist += currentDist;
                printf("%f", globalDist);
        }
        else
        {
            return;
        }

    }

    for(int j = 0 ; j <= 72 ; j++)
    {
        getLongestPath(currentDist + globalDist);
        printf("%f", globalDist);

    }
    printf("%f", globalDist);

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
        printf("index i=%i %s -- %f -- %f\n", villes[i].index, villes[i].nom, villes[i].latitude, villes[i].longitude);
        else
            break;
    }

}


int main(int argc, char **argv)
{

    readCitiesFile();

    printCitiesList();

   // bruteForce(1,3);
    //float x = calculer_distance(48.86669293, 2.333335326, 43.61039878, 3.869985716);  // Exemple Paris / Montpellier

    system("pause");
    return 0;
}





