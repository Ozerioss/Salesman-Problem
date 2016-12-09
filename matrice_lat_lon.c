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

#define V 71

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

void permuter(int a, int b)
{
    int c = 0;
    c = a;
    a = b;
    b = c;
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
                *visited[i] = villes[i].index;  // mark it as visited
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




int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
int v;
    for ( v = 0; v < V; v++)
    {
      if (sptSet[v] == false && dist[v] <= min)
          min = dist[v], min_index = v;
    }
    return min_index;
}

// A utility function to print the constructed distance array
void printPath(int parent[], int j)
{
     // Base Case : If j is source
     if (parent[j]==-1)
         return;

     printPath(parent, parent[j]);

     printf("%d ", j);
}

// A utility function to print the constructed distance
// array

void print_MST(int dist[], int n)
{
     int src = 0;
     printf("Vertex\t  Distance Path");
     int i;
     for ( i = 1; i < V; i++)
     {
         printf("\n%d -> %d \t\t %d\t ", src, i, dist[i]);
      //   printPath(parent, i);
     }
}
// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation

void dijkstra(float graph[V][V], int src)
{
      int dist[V];     // The output array.  dist[i] will hold the shortest
                       // distance from src to i

      bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
                      // path tree or shortest distance from src to i is finalized

     // Parent array to store shortest path tree
         int parent[V];

      // Initialize all distances as INFINITE and stpSet[] as false
      int i;
      for ( i = 0; i < V; i++)
      {
             dist[i] = INT_MAX;
             sptSet[i] = false;
             parent[0] = -1;

      }

      // Distance of source vertex from itself is always 0
      dist[src] = 0;

      // Find shortest path for all vertices
      int count;
      for (count = 0; count < V-1; count++)
      {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        int v;
        for (v = 0; v < V; v++)

          // Update dist[v] only if is not in sptSet, there is an edge from
          // u to v, and total weight of path from src to  v through u is
          // smaller than current value of dist[v]
          if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                        && dist[u]+graph[u][v] < dist[v])
                                        {
             dist[v] = dist[u] + graph[u][v];
             parent[v]  = u;
          }
      }

      // print the constructed distance array
      print_MST(dist, V);
}


float **create_array(int size_row, int size_column)
{
    float **matrice = (float **)malloc(size_row*size_column*sizeof(float));
    int k = 0;
    for (int i=0;i<=size_row; i++)
    {
        for(int j=0;j<=size_column;j++)
        {
            if(i==j)
            {
                matrice[i][j] = 0;
            }
            else
            {
                matrice[i][j]=calculer_distance(villes[i].latitude, villes[i].longitude, villes[j].latitude, villes[j].longitude); //ville par ville
                matrice[j][i] = matrice[i][j]; // to get a symetric matrix
            }
        }
    }
    return matrice;
}

void destoryArray(float  **array)
{
    free(*array);
    free(array);
}
int main(int argc, char **argv)
{

    readCitiesFile();

    printCitiesList();

    int size_row = 71;
    int size_column = 71;

    //float **matrix = create_array(size_row, size_column); // We create our 72 by 72 matrix that will hold the values of the distance (in km) of all cities
    // for example matrix[47][0] is gonna be distance from Paris to Agen

    //dijkstra(matrix,72);



   // bruteForce(1,3);
    //float x = calculer_distance(48.86669293, 2.333335326, 43.61039878, 3.869985716);  // Exemple Paris / Montpellier

    system("pause");
    return 0;
}





