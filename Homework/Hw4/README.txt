HOMEWORK 4: TOOL RENTAL LISTS


NAME:  Jimmy Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Cplusplus.com, w3schools.org, Ethan Garcia

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  25



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file: o(i) // loads through the inventory items which is i

Rental event: o(i*c) // goes through both inventory and customer objects so multiply

Return event - no pending customer(s): o(i*c+r)

Return event - with pending customer(s): o(i*c*p+r)

Entire program: o(e*i*c)



MISC. COMMENTS TO GRADER:
(optional, please be concise!)

Hi, I've been working so hard on this homework and I have so many things done but I'm having so
much trouble on my returns part of the program. I went to alac to ask a TA for help but they
weren't really helping me with much, they just told me what I already knew wasn't working. My program already has
the rentals implemented, im just stuck at a problem with deleting a customer when they return an item, 
as Im not sure how to go back my for loop and delete a customer object, while im still iterating forward.
I havent printed anything out for rentals, but im pretty sure it works. 

