#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//for matrixs;

void strlwrmatrix(char str[]);
int isinfilematrix(char*str, const char* file, int *n);
void printwithsamematrix(char* a, const char* file);
void printFromPlaces(const char* file, int n);

// MATRIX AND GRAPH FUNCTIONS

#define THRESHOLD_DISTANCE 1.5  // Only connect places within 1.5 km

// Radius of Earth in kilometers
#define R 6371.0

double haversine(double lat1, double lon1, double lat2, double lon2);
void calculateDistanceMatrix(const char* csvFilePath, double** matrix, int* n ,const char* txtFile);
void checkIfMatrixIsSquare(int n, int m);
void saveMatrixToCSV(const char* outputFilePath, double** matrix, int n);
void addPlaceToCSV(const char* filePath, const char* name, double latitude, double longitude, const char* amenity, const char* highway);
void appendToFile(const char* filePath, const char* text);
void printPathWithDistances(int* parent, double** graph, int j);
void dijkstra(double** graph, int curr, int dess, int V);
void FindNearMetrostation(double** graph, int cur, int V, char* metro, int* metno);
