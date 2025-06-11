# FlightFares_Dijkstra's Algorithm
This project helps find the *minimum total fare* and the *maximum single fare* between two cities using Dijkstra's shortest path algorithm.

OVERVIEW

Given a list of cities connected by flights (with fares), the program:
- Builds a graph where each city is a node and each flight is an edge with fare as weight.
- Uses Dijkstra’s algorithm to find the cheapest path from a source city to a destination city.
- Outputs the *total fare, **maximum fare in the path, and the **actual route* taken.
  
--> These are the SubPaths of this Graph with Fares given below:-
A --(500)--> B ;
A --(300)--> C ;
B --(200)--> C ;
B --(600)--> D ;
C --(400)--> D ;
D --(100)--> E ;
C --(800)--> E .
