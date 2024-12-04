#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>





/* 1. take out distance matrix from csv
     save place names in arr 
     2. search on graph operation which returns vertex 
     3. use Dijkstra's algorithm to find min distance
     4. should get path also
     
     in main:
     1. take source place
      check until they match from name file
     2. take destination place
      check until they match from name file
     3. use above functions
     4. print road
*/

// NAMES OF PLACES FUNCTION



void strlwrmatrix(char str[]){
	int i;
	for(i=0;str[i] != '\0'; i++){
		str[i] = tolower(str[i]);
	}
	return;
}


int isinfilematrix(char*str, const char* file, int *n){
	FILE* fptr = fopen(file, "r");
    if (!fptr) {
        printf("Error opening file.\n");
        return -1;
    }
    char buffer[100]; 
    int k = 0;

    while (fgets(buffer, sizeof(buffer), fptr)) {
    	strlwrmatrix(buffer);
        if(strcmp(str, buffer) == 0){
        	*n = k;
        	return 1;
        }
        k++; 
    }
    fclose(fptr);
    return 0;
    
}

void printwithsamematrix(char* a, const char* file) {
    FILE* fptr = fopen(file, "r");
    if (!fptr) {
        printf("Error opening file.\n");
        return;
    }

    // Convert `a` to lowercase and count character frequencies
    int count[256] = {0};  // Assuming ASCII character set
    for (int i = 0; a[i] != '\0'; i++) {
        count[tolower((unsigned char)a[i])]++;
    }

    char buffer[100]; 

    // Read each line from the file
    while (fgets(buffer, sizeof(buffer), fptr)) {
        // Convert the line to lowercase and count character frequencies
        int countbuf[256] = {0};  // Assuming ASCII character set
        for (int j = 0; buffer[j] != '\0'; j++) {
            countbuf[tolower((unsigned char)buffer[j])]++;
        }

        // Check if at least 3 characters have the same frequency in both `a` and the current line
        int match = 0;
        for (int k = 0; k < 256; k++) {
            if (count[k] > 0 && countbuf[k] > 0) {
                match++;
            }
        }
	
	if(strlen(a) <= 2){
		if(buffer[0] == a[0])
		printf("%s", buffer);	
	}
        // If 3 or more characters match in frequency, print the line
        else{ 
        if (match >= 3 && buffer[0] == a[0]) {
            printf("%s", buffer);
        }
        }
    }

    fclose(fptr);
}

void printFromPlaces(const char* file, int n){
	FILE* fptr = fopen(file, "r");
    if (!fptr) {
        printf("Error opening file.\n");
        return;
    }
    char buffer[100]; 
	int count = 0;
    // Read each line from the file
    while (fgets(buffer, sizeof(buffer), fptr)) {
    	if(count == n){
    		printf("%s ", buffer);
    		break;
    	}
    	count++;
    }
    return;
}



// MATRIX AND GRAPH FUNCTIONS

#define THRESHOLD_DISTANCE 1  // Only connect places within 1 km

// Radius of Earth in kilometers
#define R 6371.0

// Function to convert degrees to radians
double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// Function to calculate Haversine distance
double haversine(double lat1, double lon1, double lat2, double lon2) {
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}

// Function to read CSV and fill matrix
void calculateDistanceMatrix(const char* csvFilePath, double** matrix, int* n ,const char* txtFile) {
    FILE* file = fopen(csvFilePath, "r");
    if (!file) {
        printf("Could not open file %s\n", csvFilePath);
        return;
    }
	
	FILE *fptr;
      fptr = fopen(txtFile, "w"); 
      if (!fptr) {
        printf("Error opening file.\n");
        return;
    }
	
    char line[1000];
    double latitudes[6000], longitudes[6000]; // Assuming maximum 6000 places
    char names[6000][100];
    int row = 0;

    // Skip header line
    fgets(line, sizeof(line), file);

    // Read data from CSV
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%lf,%lf", names[row], &latitudes[row], &longitudes[row]);
        row++;
    }
    *n = row;
	/*
    // Calculate Haversine distance and fill matrix
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            matrix[i][j] = haversine(latitudes[i], longitudes[i], latitudes[j], longitudes[j]);
        }
    }
	
	
	*/
	srand(time(0));  // Seed for random number generation
	
	/*this will form square like chess
	int i, j;
	for(i = 1; i < 100; i = i + 10){
		for(j = i; j < i + 10; j++){
		if(j < i + 9)
		addvertexwithWT(&G, j, j + 1, 10);
		if(j + 10 <= 100)
		addvertexwithWT(&G, j, j + 10, 10);
	}
	}*/
	
	// Calculate Haversine distance and fill matrix with limited connections
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            double distance = haversine(latitudes[i], longitudes[i], latitudes[j], longitudes[j]);
            
            // Only connect if the distance is below the threshold or they are random close neighbors
            if (distance <= THRESHOLD_DISTANCE) {
                matrix[i][j] = distance;
                matrix[j][i] = distance;  // Since the graph is undirected
            } else {
                // 0.1% chance to add a random connection to simulate random direct roads
                if ((rand() % 100) < 0.1 && distance < 2) {
                    matrix[i][j] = distance;
                    matrix[j][i] = distance;
                } else {
                    matrix[i][j] = 0;  // No connection
                    matrix[j][i] = 0;
                }
            }
            
        }
    }
	
    fclose(file);
    
    int k=0;
    while(k<*n){
       fprintf(fptr, "%s\n", names[k]);
        k++;
    }
     fclose(fptr);
     
     return;
}

// Function to check if matrix is square
void checkIfMatrixIsSquare(int n, int m) {
    if (n == m) {
        printf("The matrix is square (%d x %d).\n", n, m);
    } else {
        printf("The matrix is not square. It has %d rows and %d columns.\n", n, m);
    }
}

// Function to save the distance matrix to a CSV file
void saveMatrixToCSV(const char* outputFilePath, double** matrix, int n) {
    FILE* file = fopen(outputFilePath, "w");
    if (!file) {
        printf("Could not open file %s for writing.\n", outputFilePath);
        return;
    }

    // Write matrix to CSV
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%f", matrix[i][j]);
            if (j < n - 1) {
                fprintf(file, ",");  // Add a comma if not the last element in the row
            }
        }
        fprintf(file, "\n");  // Newline after each row
    }

    fclose(file);
    //printf("Matrix saved to %s successfully.\n", outputFilePath);
    return;
}

void addPlaceToCSV(const char* filePath, const char* name, double latitude, double longitude, const char* amenity, const char* highway) {
    // Open the CSV file in append mode
    FILE *file = fopen(filePath, "a");
    if (file == NULL) {
        printf("Error opening file %s\n", filePath);
        return;
    }

    // Write the new place information to the file
    fprintf(file, "\"%s\",%lf,%lf,\"%s\",\"%s\"\n", name, latitude, longitude, amenity, highway);

    // Close the file
    fclose(file);

    printf("Place added successfully to %s\n", filePath);
    return;
}

void appendToFile(const char* filePath, const char* text) {
    // Open the file in append mode
    FILE *file = fopen(filePath, "a");
    
    if (file == NULL) {
        printf("Error opening file %s\n", filePath);
        return;
    }

    // Write the string to the file
    fprintf(file, "%s\n", text);  // Adding newline at the end for better readability

    // Close the file
    fclose(file);

    printf("Place added successfully to %s\n", filePath);
    return;
}


// graph functions here



// Function to print path and distances between each node in the path
void printPathWithDistances(int* parent, double** graph, int j) {
    // Base case: if there's no parent, return
    if (parent[j] == -1) {
        //printf("%d ", j);
        printFromPlaces("NamesOfplaces.txt", j);
        printf("|\n");
        return;
    }

    // Recur for the parent vertex
    printPathWithDistances(parent, graph, parent[j]);

    // Print distance from parent[j] to j
    printFromPlaces("NamesOfplaces.txt", j);
    printf(" (%.2lf km)\n ", graph[parent[j]][j]);
    printf("|\n");
}

void dijkstra(double** graph, int curr, int dess, int V) {
    double dist[V];      // Output array dist[i] holds the shortest distance from curr to j
    bool sptSet[V];      // sptSet[i] is true if vertex i is included in the shortest path tree
    int* parent = (int*)malloc(V * sizeof(int)); // Dynamically allocated parent array

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1; // No parent initially
    }

    // Distance from source to itself is always 0
    dist[curr] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int minIndex = -1;
        double minValue = INT_MAX;
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] <= minValue) {
                minValue = dist[v];
                minIndex = v;
            }
        }

        // Mark the picked vertex as processed
        sptSet[minIndex] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[minIndex][v] != 0 && dist[minIndex] != INT_MAX 
                && dist[minIndex] + graph[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + graph[minIndex][v];
                parent[v] = minIndex; // Update parent
            }
        }
    }

    // Check if there is a path to the destination
    if (dist[dess] == INT_MAX) {
        printf("No path from %d to %d\n", curr, dess);
    } else {
        // Print the shortest path and distances between links
        //printf("Shortest path from %d to %d: ", curr, dess);
        printf("Shortest path from\n");
        printFromPlaces("NamesOfplaces.txt", curr);
        printf(" to\n");
        printFromPlaces("NamesOfplaces.txt", dess);
        printf("\n");
        printPathWithDistances(parent, graph, dess);
        printf("\nTotal distance: %.2lf km\n", dist[dess]);
    }

    // Free dynamically allocated memory for parent
    free(parent);
}


void FindNearMetrostation(double** graph, int cur, int V, char* metro, int* metno){
	int storemetro[26] = {7, 24, 43, 55, 171, 381, 717, 808, 861, 1281, 1426, 1711, 2248, 2590, 2615, 2904, 3224, 3479, 3799, 4064, 4206, 5085, 5144, 5170, 5423, 5482};
	
	int meto[V];
	for(int i = 0; i < V; i++)
		meto[i] = 0;
		
	for(int i = 0; i < 26; i++)
		meto[storemetro[i]]++;
	
	double dist[V];      // Output array dist[i] holds the shortest distance from curr to j
    bool sptSet[V];      // sptSet[i] is true if vertex i is included in the shortest path tree
    int* parent = (int*)malloc(V * sizeof(int)); // Dynamically allocated parent array

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1; // No parent initially
    }

    // Distance from source to itself is always 0
    dist[cur] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int minIndex = -1;
        double minValue = INT_MAX;
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] <= minValue) {
                minValue = dist[v];
                minIndex = v;
            }
        }

        // Mark the picked vertex as processed
        sptSet[minIndex] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[minIndex][v] != 0 && dist[minIndex] != INT_MAX 
                && dist[minIndex] + graph[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + graph[minIndex][v];
                parent[v] = minIndex; // Update parent
            }
        }
    }
    
    int min = INT_MAX, metrono = storemetro[0];
    
    for(int i = 0; i < V; i++){
    	if(meto[i] == 1){
    		if(dist[i] < min){
    			min = dist[i];
    			metrono = i;
    		}	
    	}
    }
    //printf("\n\n\n\n%d\n\n\n\n", metrono);
    *metno = metrono;
    
    //printFromPlaces("NamesOfplaces.txt", metrono);
    
    FILE* fptr = fopen("NamesOfplaces.txt", "r");
    if (!fptr) {
        printf("Error opening file.\n");
        return;
    }
    char buffer[100]; 
	int count = 0;
    // Read each line from the file
    while (fgets(buffer, sizeof(buffer), fptr)) {
    	if(count == metrono){
    		int le = strlen(buffer);
    		buffer[le-1] = '\0';
    		strcpy(metro, buffer);
    		break;
    	}
    	count++;
    }
	return;

}






