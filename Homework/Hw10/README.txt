HOMEWORK 10: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  JIMMY CHEN


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >



NAIVE ALGORITHM:

Order Notation: O(((w*h)^2)*p)

Timing Experiment Data:

squiggle_30x30.ppm (grey_bands)
real    0m0.025s
user    0m0.016s
sys     0m0.016s

lines_100_100.ppm (grey_bands)
real    0m0.466s
user    0m0.422s
sys     0m0.000s

data_structures_300x300.ppm (grey_bands)
real    2m56.966s
user    2m56.188s
sys     0m0.156s

Discussion:
The order notation for the naive algorithm is w*h^2 times p because the function loops
through the width and height and inside those two loops it double loops through the width and height again
then all that is multiplied by p (the total number of black pixels) because it checks if it is a black pixel.
The runtime is extremely fast with 0.25 seconds in the squiggle, but as it gets progressively larger,
the runtime grows exponentially, which matches the order notation. In the 100x100 file the time is .4 seconds
and it is close to 3 mins on the 300x300 file.  


IMPROVED ALGORITHM:

Order Notation: O((w*h*p))

Timing Experiment Data:

squiggle_30x30.ppm (grey_bands)
real    0m0.022s
user    0m0.000s
sys     0m0.016s

lines_100_100.ppm (grey_bands)
real    0m0.081s
user    0m0.047s
sys     0m0.000s

data_structures_300x300.ppm (grey_bands)
real    0m25.358s
user    0m25.203s
sys     0m0.094s

Discussion:

The order notation for the improved algorithm is w*h*p. The first set of double for loops
loops through the pixels to add to the list. This just drops off the order notation bc it's smaller.
Then I loop through all the pixels again and then loop through the list while holds the amount of 
black pixels (p). Looping though the each pixel is w*h and when I loop through all the black pixels
inside of that, it is w*h*p. The runtime matches my order notation because runtime doesn't exponentially increase. 
It runs at only 25 seconds for the 300x300 compared to the 3 minutes.

FAST MARCHING METHOD (with a map):

Order Notation:  O(l*w*log(p))

Timing Experiment Data:

squiggle_30x30.ppm (grey_bands)
real    0m0.014s
user    0m0.016s
sys     0m0.000s

lines_100_100.ppm (grey_bands)
real    0m0.078s
user    0m0.031s
sys     0m0.016s

data_structures_300x300.ppm (grey_bands)
real    0m0.547s
user    0m0.500s
sys     0m0.016s

Discussion:

The order notation for the fast marching is w*h*log(p). My program to find the neighbors loops through all the black pixels and insert it 
into a priority queue, which takes log(p) time. It is multiplied by w*h because for each pixel, we check it's neighbors
which is a double for loop of width and height. The experiment proves my Big O because every run takes less than a second to run. The width and height
is always from -1 to 1 so the number of black pixels is what causes the program to run slower. 

DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






