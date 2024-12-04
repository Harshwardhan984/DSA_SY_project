Pune Metro Navigator: A Data Structure-Based Route Optimization System

Project Overview

This project, Pune Metro Navigator, is a system designed to help users find the optimal metro route in Pune.
It employs data structures like Doubly Linked Lists and Graphs to optimize routes between metro stations,
considering parameters like total distance, travel time, and fare.


Key Features

1. Optimal Route Finder: Provides the best metro route based on the user's starting and destination addresses.
2. Distance and Travel Time Estimation: Displays walking and metro travel times.
3. Fare Estimation: Calculates fare based on travel distance and lane switches.
4. Efficient Data Structures:
   - Graph: Models the metro network.
   - Doubly Linked List: Manages connections between adjacent metro stations for bidirectional traversal.


Requirements

1. Compiler: A GCC compiler is required to run the program.
2. Code Files: Ensure the following source files are present in the same directory:
   - metro.c
   - metromain.c
   - matrixmakecheak.c
   - metro.h
   - metroMatrix.h
   - [All csv and txt files( Data files )]


How to Run the Project

1. Compile the Source Code:
   Open a terminal and execute the following command to compile the project:
   
   gcc -Wall -c metro.c metromain.c matrixmakecheak.c -lm
   
   cc metro.o metromain.o matrixmakecheak.o -o project -lm

3. Run the Program:
   Execute the compiled binary to run the project:
   ./project

4. Provide Inputs:
   - Enter your starting address.
   - Enter your destination address.
   The system will output the nearest metro stations, the optimal route, total travel time, and fare estimation.


Contributors

- Harshwardhan Mane
  Roll No: 612303112


Division: 2 S1, COEP Technological University.


Acknowledgments

This project demonstrates the practical application of advanced data structures in solving real-world urban commuting challenges.
