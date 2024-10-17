#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//infinite distance between 2 cities
#define INFINITY 9999

//structure of a travel point, loaded from the file
typedef struct {
    char locationA[30];
    char locationB[30];
    int distance;
} travelPoint;

//function declarations
void loadCities();
void createCityKey();
void populateAdjacencyMatrix();
int dijkstra(int cost[][21], int source, int target);

//list of all the possible travel points
travelPoint cities[40] = {0};
//list of all city names (multi dimensional array since the names are also arrays)
char cityKey[21][30] = {0};
//the adjacency matrix
int adjacencyMatrix[21][21];

int main()
{
    //load the cities from file
    loadCities();

    //check to make sure that the cities were loaded (would fail in the event of the file not being there.)
    if(cities != NULL)
    {
        //create a key of all the cities (this helps with tying a city to an int value, and with checking if the city is spelled correctly)
        createCityKey();
        //create and populate the adjacency matrix
        populateAdjacencyMatrix();

        bool running = true;
        //placeholders for the start and end destinations
        char startCity[30] = {0}, endCity[30] = {0};
        int startIndex, endIndex;
        while(running)
        {
            //get the input for the starting city
            while(strlen(startCity) == 0)
            {
                printf("Enter a start location.\n");
                scanf("%s", startCity);
                bool found = false;
                int i;
                for(i = 0; i < 21; i++)
                {
                    if(strcmp(startCity, cityKey[i]) == 0)
                    {
                        //once we have found a match, this is a valid city, so lets declare it found and break from the loop
                        found = true;
                        startIndex = i;
                        break;
                    }
                }
                if(!found)
                {
                    //if we've reached this point, and its not declared found, keep looping.
                    printf("That is not a valid city. Please try again.\n");
                    startCity[0] = '\0';
                }
            }
            //get the input for the ending city
            while(strlen(endCity) == 0)
            {
                printf("Enter a destination.\n");
                scanf("%s", endCity);
                bool found = false;
                int i;
                for(i = 0; i < 21; i++)
                {
                    if(strcmp(endCity, cityKey[i]) == 0)
                    {
                        //once we have found a match, this is a valid city, so lets declare it found and break from the loop
                        found = true;
                        endIndex = i;
                        break;
                    }
                }
                if(!found)
                {
                    printf("That is not a valid city. Please try again.\n");
                    endCity[0] = '\0';
                }
                if(found && strcmp(startCity, endCity) == 0)
                {
                    //if we've reached this point, and its not declared found, keep looping.
                    printf("The start and end location cannot be the same city.\n");
                    endCity[0] = '\0';
                }
            }

            //run the algorithm and display the data to the user.
            int distance = dijkstra(adjacencyMatrix, startIndex, endIndex);
            printf("Total distance: %i\n\n", distance);

            //prompt user if they would like to go again
            bool promptingForRetry = true;
            char answer[4];
            while(promptingForRetry) {
                printf("Would you like to try another destination?\n");
                printf("Enter Yes or No\n");
                scanf("%s", answer);
                if(strcmp(answer, "Yes") == 0)
                {
                    //if they do wish to go again, reset the start and end city
                    promptingForRetry = false;
                    startCity[0] = '\0';
                    endCity[0] = '\0';
                }
                else if(strcmp(answer, "No") == 0)
                {
                    //if they do not wish to go again, end the loops
                    running = false;
                    promptingForRetry = false;
                }
                else
                {
                    //an answer other than Yes or No was answered, loop again.
                    printf("Invalid response. Please try again.\n");
                }
            }
        }
    }
    else
    {
        //city data failed to load, the file might not be there
        printf("Failed to load city data. Is the file in the right location?");
    }

    return 0;
}

//this function loads the cities from file
void loadCities()
{
    //open the file
    FILE *file = fopen("ukcities.txt", "r");
    if(!file) return NULL;

    char buffer[1024];
    int counter = 0;
    //loop through the file
    while(fgets(buffer, sizeof(buffer), file) != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0';

        //split the tokens by tabs
        char *token;
        token = strtok(buffer, "\t");
        //incremental position so we know which piece of data we are reading
        int position = 0;
        while(token != NULL)
        {
            //position 0 is location a
            if(position == 0)
            {
                strncpy(cities[counter].locationA, token, sizeof(cities[counter].locationA) - 1);
                cities[counter].locationA[29] = '\0'; //ensure the last character is an end of string just in case
            }
            //position 1 is location b
            else if(position == 1)
            {
                strncpy(cities[counter].locationB, token, sizeof(cities[counter].locationB) - 1);
                cities[counter].locationB[29] = '\0'; //ensure the last character is an end of string just in case
            }
            //position 2 is distance
            else
            {
                cities[counter].distance = atoi(token);
            }
            token = strtok(NULL, "\t");\
            position++;
        }
        counter++;
    }

    //be sure to close the file
    fclose(file);
}

//this function creates a key of all the cities
void createCityKey()
{
    int counter = 0;
    int x, y;
    for(x = 0; x < 40; x++)
    {
        bool found = false;
        //first lets check locationA
        for(y = 0; y < counter + 1; y++)
        {
            //check if the string is empty and this city was not already found
            if(strlen(cityKey[y]) == 0 && !found)
            {
                //if this is the case, its an unarchived city
                strncpy(cityKey[counter], cities[x].locationA, sizeof(cities[0].locationA));
                counter++;
                found = false;
                break;
            }
            else
            {
                //the current city key is not empty, so lets compare this key to the location
                if(strcmp(cities[x].locationA, cityKey[y]) == 0 && strlen(cityKey[y]) != 0 && !found)
                {
                    found = true;
                }
            }
        }
        //now we check locationB
        for(y = 0; y < counter + 1; y++)
        {
            //check if the string is empty and this city was not already found
            if(strlen(cityKey[y]) == 0 && !found)
            {
                //if this is the case, its an unarchived city
                strncpy(cityKey[counter], cities[x].locationB, sizeof(cities[0].locationB));
                counter++;
                found = false;
                break;
            }
            else
            {
                //the current city key is not empty, so lets compare this key to the location
                if(strcmp(cities[x].locationB, cityKey[y]) == 0 && strlen(cityKey[y]) != 0 && !found)
                {
                    found = true;
                }
            }
        }
    }
}

//populates the adjacency matrix with the city data with the key being the value of cityKey
void populateAdjacencyMatrix()
{
    //first lets set all distances to infinity
    int x, y, i, j;
    for(x = 0; x < 21; x++)
    {
        for(y = 0; y < 21; y++)
        {
            adjacencyMatrix[x][y] = INFINITY;
        }
    }
    //now lets loop through all the amounts
    for(i = 0; i < 40; i++)
    {
        //placeholders for the index, set to -1 so we can check if they have been found to break the loop
        int index1 = -1, index2 = -1;
        for(j = 0; j < 21; j++)
        {
            //compare location a to the city key
            if(strcmp(cities[i].locationA, cityKey[j]) == 0 && index1 < 0)
            {
                index1 = j;
            }
            //compare location b to the city key
            if(strcmp(cities[i].locationB, cityKey[j]) == 0 && index2 < 0)
            {
                index2 = j;
            }
            //if both indexes were found, break from the loop
            if(index1 >= 0 && index2 >= 0)
            {
                break;
            }
        }
        //set the values in the adjacency matrix
        adjacencyMatrix[index1][index2] = cities[i].distance;
        adjacencyMatrix[index2][index1] = cities[i].distance;
    }
}

//dijkstra algorithm for finding the shortest path
int dijkstra(int cost[][21], int source, int target)
{
    int dist[21], prev[21], selected[21] = {0}, i, m, min, start, d, j;
    char path[21];
    //initialize dist and prev
    for(i = 0; i < 21; i++)
    {
        dist[i] = INFINITY;
        prev[i] = -1;
    }
    start = source;
    selected[start] = 1;
    dist[start] = 0;
    while(selected[target] == 0)
    {
        min = INFINITY;
        m = 0;
        for(i = 0; i < 21; i++)
        {
            d = dist[start] +cost[start][i];
            if(d < dist[i] && selected[i] == 0)
            {
                dist[i] = d;
                prev[i] = start;
            }
            if(min > dist[i] && selected[i] == 0)
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    start = target;
    j = 0;
    while(start != -1)
    {
        path[j++] = start + 65;
        start = prev[start];
    }
    //while(j < 21) {
    path[j]='\0';
        //j++;
    //}
    strrev(path);
    //now lets print the path
    printf("\n\n");
    printf("Shortest route.\n");
    for(i = 0; i < 21; i++) {
        if(path[i] == NULL) {
            break;
        }

        if(i > 0) printf(" -> ");
        int key = path[i] - 65;
        printf("%s", cityKey[key]);
    }
    printf("\n");

    //return the total distance
    return dist[target];
}
