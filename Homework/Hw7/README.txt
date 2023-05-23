HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME:  Jimmy Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Taein Yi, Jack Dechiro, geeksforgeeks.org, pencilprogrammer.com, cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  12



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of moves that have the same starting frame for a particular move


reading the database/populating your initial data structure:

-q (specific move): O(log(f)) (.find() function for mad is always log(f) where f is the size of the map.)

-q (all): O(log (f) + 7 (bc 7 moves for 1 fighter)) 
simplified -> O(log(f)) 

-f: O(f + t*log(f)) 
(bc if t is referring to the desired move as the "particular" move then there are a t amount of insertions my code completes)

-s: O(f + t*log(f))
(bc -s is written the same way as -f except the set is backwards.)

-d: O(f*log(m)) 
(bc I iterate through a certain number of fighters and conduct a .find() on a map of moves)


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






