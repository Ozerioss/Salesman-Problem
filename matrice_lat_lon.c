#include<limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<limits.h>
#include<string.h>
#define pi 3.14159265359

#define R 6371

#define MAX_STR_LEN 256
#define NBR_VILLES 72

struct ville{
    char *nom;
    float latitude;
    float longitude;
};

struct ville villes[NBR_VILLES];

/* PROTOTYPE OF FUNCTIONS */
int readCitiesFile();
void printCitiesList();

int main(int argc, char **argv)
{
    int isOK = 0;

    /*isOK = */readCitiesFile();

    printCitiesList();

    system("pause");
    return 0;
}

int readCitiesFile()
{
    /* FileStream for the Library File */
    FILE* csvFile = NULL;
    csvFile = fopen("Cites.csv", "r");

    /* allocation of the buffer for every line in the File */
    char *buf = malloc(MAX_STR_LEN);
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
        villes[i].nom = (tmp);

        tmp = strtok(NULL, ",");
        villes[i].latitude = atof(tmp);

        tmp = strtok(NULL, ",");
        villes[i].longitude = atof(tmp);

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
        if (villes[i].nom != 0)
        printf("index i= %i  %f, %f\n",i+1, villes[i].latitude, villes[i].longitude);
        else
            break;
    }

}
