HOMEWORK 3: MATRIX CLASS


NAME:  Jimmy Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

www.programiz.com, cplusplus.com, Josh Sundararaman, Ethan Garcia, Joseph Pan

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get O(1)

set O(1)

num_rows O(1)

get_column O(m*n)

operator<< O(m*n)

quarter O(n^2)

operator== O(m * n)

operator!= O(m * n)

swap_rows O(1)

rref (provided in matrix_main.cpp) O(n^3)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I used valgrind to find where the memory leaks originated from. I also used drmemory to find out where seg faults
originate from. Valgrind also helped me find when I should delete pointers and deconstruct. 
For quarter(), there is a corner case where row and columns are odd, and quadrants will share values. 
I tested this by creating a condition that checks if there is an odd amount and writing code that adjusts to when its odd and even.
I used std::cout print to find errors where I am indexing the wrong values.
I tried using GDB to find where exactly in the code seg faults occur, but sometimes gdb crashes in my termial.

EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

