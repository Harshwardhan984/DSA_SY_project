#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include<ctype.h>
#include "metro.h"
#include "metroMatrix.h"


int main() {
    list purpal;
    init(&purpal);
    list aqua;
    init(&aqua);

    int cas;
    bool flag = true;

    while (flag) {
        printf("Choose the following:\n");
        printf("0 : Exit\n");
        printf("1 : Customer\n");
        printf("2 : Manager\n");
       
        scanf("%d", &cas);

        switch (cas) {
        	case 0:
                flag = false;
                break;
        
case 1: {
    
    while(1){
    int choice;
    
    printf("Select the path type:\n");
    printf("0. BACK\n");
    printf("1. Metro Path (Using Metro stations)\n");
    printf("2. Shortest Path without Metro (Using pre-calculated places)\n");
    printf("3. Shortest Path with Metro (Using Metro stations + pre-calculated places)\n");
    
    printf("Enter your choice : ");
    scanf("%d", &choice);
	if(choice == 0){
		break;
	}
    else if (choice == 1) {
    	
    	char curstation[50];
        char desstation[50];
    	
        // Metro path option
        while (true) {
            printf("Enter your current station: ");
            scanf("%99s", curstation);
            strlwr(curstation);

            if (!isinfile(curstation, "purpal.txt") && !isinfile(curstation, "aqua.txt")) {
                printf("Not a metro station.\nHere are names with similar stations you can enter:\n");
                printwithinit(curstation[0], "purpal.txt");
                printwithinit(curstation[0], "aqua.txt");
                continue;  // Retry if station not found
            }
            break;
        }

        while (true) {
            printf("Enter your destination station: ");
            scanf("%99s", desstation);
            strlwr(desstation);

            if (!isinfile(desstation, "purpal.txt") && !isinfile(desstation, "aqua.txt")) {
                printf("Not a metro station.\nHere are names with similar stations you can enter:\n");
                printwithinit(desstation[0], "purpal.txt");
                printwithinit(desstation[0], "aqua.txt");
                continue;  // Retry if station not found
            }
            break;
        }

        // Load metro lists and remove duplicates
        loadmetrolist(&purpal, "purpal.txt");
        loadmetrolist(&aqua, "aqua.txt");
        removeDuplicates(&purpal);
        removeDuplicates(&aqua);
	
	//printf("\n\n%s\n\n",curstation);
	//printf("\n\n%s\n\n",desstation);
	
	
        // Find the road between stations
        findtheroad(&purpal, &aqua, curstation, desstation);

    } 
    else if (choice == 2) {
        // Shortest path option using pre-calculated distance matrix
					char curstation[50];
					char desstation[50];
					int cur, des;
					repetcur:
					printf("enter ur current place:");
					fgets(curstation, sizeof(curstation), stdin);
					//scanf("%99s",curstation);
					strlwr(curstation);
					if(!isinfilematrix(curstation, "NamesOfplaces.txt", &cur) ){
						printf("not a place \n here are names with similar u can enter same\n");
						printwithsamematrix(curstation, "NamesOfplaces.txt");
						goto repetcur;
					}
					repetdes:
					printf("enter ur destination place:");
					fgets(desstation, sizeof(desstation), stdin);
					//scanf("%99s",desstation);
					strlwr(desstation);
					if(!isinfilematrix(desstation, "NamesOfplaces.txt", &des) ){
						printf("not a place \n here are names with similar u can enter same\n");
						printwithsamematrix(desstation, "NamesOfplaces.txt");
						goto repetdes;
					}
	
printf("\n\nPlease wait this will take a while\n\n");

	const char* csvFilePath = "osm_places_with_road_names_final_cleaned.csv";
	//const char* csvFilePath = "sorted_places_by_C.csv";
 	   //const char* outputFilePath = "distance_matrix_inC.csv";
 	   const char* txtFile = "NamesOfplaces.txt";
    
    // Allocate memory for the distance matrix (assuming max 6000x6000 )
    double** distanceMatrix = (double**)malloc(6000 * sizeof(double*));
     if (distanceMatrix == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 6000; i++) {
        distanceMatrix[i] = (double*)malloc(6000 * sizeof(double));
    }
	
	for (int i = 0; i < 6000; i++) {
        for (int j = 0; j < 6000; j++) {
            distanceMatrix[i][j] = 0;
        }
    }
	
    int n = 0; // This will store the number of rows/columns
	 
    // Calculate distance matrix
    calculateDistanceMatrix(csvFilePath, distanceMatrix, &n, txtFile);
	//printf("%d \n", n);
    // Check if matrix is square
    //checkIfMatrixIsSquare(n, n);
    
    
    //addplaces(csvFilePath, "Pune Metro Station 1", "18.5308 ", " 73.8475");
	
	
	
	// Optional: Print the matrix to check if it's loaded correctly
   /* for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1; j++) {
            printf("%lf ", distanceMatrix[i][j]);
        }
        printf("\n");
    }
	*/
	//saveNamesTOtex(txtFile, names); ths is done in calculateDistanceMatrix(csvFilePath, distanceMatrix, &n, txtFile); only
	//saveMatrixToCSV(outputFilePath, distanceMatrix, n);
	

	
	dijkstra(distanceMatrix, cur, des, n);


    // Free allocated memory
    for (int i = 0; i < 6000; i++) {
        free(distanceMatrix[i]);
    }
    free(distanceMatrix);
    }
    
    else if(choice == 3){
    
    					char curstation[50];
					char desstation[50];
					int cur, des;
					repetcur2:
					// Clear the input buffer after reading an integer
    					while (getchar() != '\n');  // Flush the buffer to remove any leftover newline

					printf("enter ur current place:");
					fgets(curstation, sizeof(curstation), stdin);
					//scanf("%99s",curstation);
					strlwr(curstation);
					if(!isinfilematrix(curstation, "NamesOfplaces.txt", &cur) ){
						printf("not a place \n here are names with similar u can enter same\n");
						printwithsamematrix(curstation, "NamesOfplaces.txt");
						goto repetcur2;
					}
					repetdes2:
					

					printf("enter ur destination place:");
					fgets(desstation, sizeof(desstation), stdin);
					//scanf("%99s",desstation);
					strlwr(desstation);
					if(!isinfilematrix(desstation, "NamesOfplaces.txt", &des) ){
						printf("not a place \n here are names with similar u can enter same\n");
						printwithsamematrix(desstation, "NamesOfplaces.txt");
						goto repetdes2;
					}
	printf("\n\nPlease wait this will take a wile\n\n");
	
	//find near metrostation from curr place
	//find near metrostation from dess place
	//print short path from curr place to near metro station of curr place
	//print path of metro 
	//print path from near metro of dess place station to dess place
	

	const char* csvFilePath = "osm_places_with_road_names_final_cleaned.csv";
	//const char* csvFilePath = "sorted_places_by_C.csv";
 	   //const char* outputFilePath = "distance_matrix_inC.csv";
 	   const char* txtFile = "NamesOfplaces.txt";
    
    // Allocate memory for the distance matrix (assuming max 6000x6000 )
    double** distanceMatrix = (double**)malloc(6000 * sizeof(double*));
     if (distanceMatrix == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 6000; i++) {
        distanceMatrix[i] = (double*)malloc(6000 * sizeof(double));
    }
	
	for (int i = 0; i < 6000; i++) {
        for (int j = 0; j < 6000; j++) {
            distanceMatrix[i][j] = 0;
        }
    }
	
    int n = 0; // This will store the number of rows/columns
	 
    // Calculate distance matrix
    calculateDistanceMatrix(csvFilePath, distanceMatrix, &n, txtFile);
    
    int curNearMetro = 717, dessNearMetro = 5482;
    char curstat[50];
    char desstat[50];
    
    
    //find near metrostation from curr place
    
    FindNearMetrostation(distanceMatrix, cur, n, curstat, &curNearMetro);
    
    //find near metrostation from dess place
    
     FindNearMetrostation(distanceMatrix, des, n, desstat, &dessNearMetro);
    
	//print short path from curr place to near metro station of curr place
	
	dijkstra(distanceMatrix, cur, curNearMetro, n);
	
	//print path of metro
	
	list purpal1;
    init(&purpal1);
    list aqua1;
    init(&aqua1);
	
	 // Load metro lists and remove duplicates
        loadmetrolist(&purpal1, "purpal.txt");
        loadmetrolist(&aqua1, "aqua.txt");
        removeDuplicates(&purpal1);
        removeDuplicates(&aqua1);
	 
	 strlwr(curstat);
	 strlwr(desstat);
	 //printf("\n\n%s\n\n",curstat);
	 //printf("\n\n%s\n\n",desstat);
	 
	 //printlistLR(purpal1);
	//printlistLR(aqua1);
	 
        findtheroad(&purpal1, &aqua1, curstat, desstat);
	 
	//print path from near metro of dess place station to dess place
	
	dijkstra(distanceMatrix, dessNearMetro, des, n);
    
	
	
    	
    }
    
     else {
        printf("Invalid choice! Please choose 1 or 2.\n");
    }
	}
    break;
}
            case 2: {
                // Manager flow
                loadmetrolist(&purpal, "purpal.txt");
                loadmetrolist(&aqua, "aqua.txt");
                removeDuplicates(&purpal);
                removeDuplicates(&aqua);

                int cas1;
                bool flag1 = true;

                while (flag1) {
                    printf("Choose an action:\n");
                    printf("0 : Exit\n");
                    printf("1 : Add station at terminals\n");
                    printf("2 : Add station in between\n");
                    printf("3 : Remove station\n");
                    printf("4 : Add Place By its  latitude(double) and longitude(double)\n");
                    scanf("%d", &cas1);

                    switch (cas1) {
                        case 0:
                            flag1 = false;
                            break;

                        case 1: {
                            // Add station at terminals
                            char newstation[50];
                            printf("Enter station name: ");
                            scanf("%99s", newstation);
                            strlwr(newstation);

                            printf("Choose where to add the station:\n");
                            printf("1 : %s\n2 : %s\n3 : %s\n4 : %s\n", purpal.front->data, purpal.rear->data, aqua.front->data, aqua.rear->data);
                            int st;
                            scanf("%d", &st);

                            if (st == 1) insertAtLeft(&purpal, newstation);
                            else if (st == 2) insertright(&purpal, newstation);
                            else if (st == 3) insertAtLeft(&aqua, newstation);
                            else if (st == 4) insertright(&aqua, newstation);

                            printf("Station added successfully.\n");

                            // Save lists
                            savelist(&purpal, "purpal.txt");
                            savelist(&aqua, "aqua.txt");

                            break;
                        }
                        case 2:
                             printf("Enter the name of the new station to add: ");
    				char newStation[100];
    				scanf("%s", newStation);
   				 strlwr(newStation);

   				 int lineChoice;
   				 do {
     				   printf("Select the metro line to add the station:\n");
     				   printf("1. Purple Line\n");
				        printf("2. Aqua Line\n");
			        printf("Enter your choice (1 or 2): ");
			        scanf("%d", &lineChoice);

 			       if (lineChoice == 1) {
			            printf("Adding station to the Purple Line.\n");
			            addStation(&purpal, newStation, "purpal.txt"); // Assuming `purpal` is the purple line list
		       		     break;
		        } else if (lineChoice == 2) {
		            printf("Adding station to the Aqua Line.\n");
 	           		addStation(&aqua, newStation, "aqua.txt"); // Assuming `aqua` is the aqua line list
 		           break;
  		     	 } else {
  		          printf("Invalid choice. Please enter 1 or 2.\n");
  		      }
  			  } while (1);
  			  // Save updated lists
                            savelist(&purpal, "purpal.txt");
                            savelist(&aqua, "aqua.txt");
                            break;

                        case 3: {
                            // Remove station
                            char newstationd[50];
                            while (true) {
                                printf("Enter station name to delete: ");
                                scanf("%99s", newstationd);
                                strlwr(newstationd);

                                if (!isinfile(newstationd, "purpal.txt") && !isinfile(newstationd, "aqua.txt")) {
                                    printf("Not a metro station.\nHere are names with similar stations you can enter:\n");
                                    printwithinit(newstationd[0], "purpal.txt");
                                    printwithinit(newstationd[0], "aqua.txt");
                                    continue;  // Retry if station not found
                                }
                                break;
                            }

                            // Remove the station from the appropriate list
                            if (isinfile(newstationd, "purpal.txt")) 
                            	removeEle(&purpal, newstationd);
                            else 
                            	removeEle(&aqua, newstationd);

                            // Save updated lists
                            savelist(&purpal, "purpal.txt");
                            savelist(&aqua, "aqua.txt");

                            break;
                        }
                       case 4: {
                       
                       char name[100];
   		 double latitude, longitude;
   		 char amenity[100];
 		   char highway[100];
		const char* csvFilePath = "osm_places_with_road_names_final_cleaned.csv";
 	   //const char* outputFilePath = "distance_matrix_inC.csv";
 	   const char* txtFile = "NamesOfplaces.txt";
    			// Take user input for place details
    			// Clear the input buffer after reading an integer
    		while (getchar() != '\n');  // Flush the buffer to remove any leftover newline

    			
   	 	printf("Enter the name of the place: ");
  		  scanf("%99[^\n]%*c", name);  // This allows spaces in the string input

  		  // Prompt and take input for latitude and longitude
  		  printf("Enter the latitude of the place: ");
  		  scanf("%lf", &latitude);

  		  printf("Enter the longitude of the place: ");
  		  scanf("%lf", &longitude);

			// Clear the input buffer after reading an integer
    			while (getchar() != '\n');  // Flush the buffer to remove any leftover newline

  		  // Prompt and take input for amenity
  		  printf("Enter the amenity of the place (e.g., restaurant, fuel, etc.): ");
  		  scanf("%49[^\n]%*c", amenity);  // This allows spaces in the string input


  		  // Prompt and take input for highway or road name
  		  printf("Enter the highway or road name (if applicable): ");
  		  scanf("%49[^\n]%*c", highway);  // This allows spaces in the string input

 		   // Add the place to the CSV file
 		   addPlaceToCSV(csvFilePath, name, latitude, longitude, amenity, highway);
 		   appendToFile(txtFile, name);
                       
                       	break;
                       }
                    }
                }
                break;
            }
            
            default:
                printf("Invalid option!\n");
                break;
        }
    }

    return 0;
}
