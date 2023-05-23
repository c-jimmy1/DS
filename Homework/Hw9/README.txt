HOMEWORK 9: MINIBLAST


NAME:  Jimmy Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com, topcoder.com, tutorialspoint.com, Ethan Garcia, Taein Yi, Jack Dechiro, Ben Kushner

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  15


HASH FUNCTION DESCRIPTION

My Hash function is taken from Lab 11 and the implementation comes from
http://www.partow.net/programming/hashfunctions/. The hash function has a large number 
to reduce collisions. It has a artimetic operations to convert the given string to a hash number.
This number can then be used in a hash table to quickly find the indexes of the values in the table.


HASH TABLE IMPLEMENTATION

For my hash table I use a vector of pairs that have a string and a vector of integers. The string in the pair
represents a Kmer length of a genome, which is the key used to access it. The vector of integers represent
the indexes where the kmer appears in the entire genome. To find the exact index given a string
I use the formula hash(string) % the entire table size. Using this formula I was able to find out the exact
places I can place and access my pairs in the vector. Sometimes, there are collisions where the hashes are the same
but the kmer isn't. When I hit that problem I use linear probing to find the next avaliable space in the hash
table. In my hash table implementation I also have 3 main functions.
Insert- which inserts into the hash table given the key, and position in the entire genome.
Resize- which resizes the entire table to a set amount. I do this by creating a temporary table with the new size
and adding the old information to the new one by rehashing and then setting the old table to the temporary new table.
GetIndex (find)- which searches through the hash table to find the places where the given query string matches.


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?

O((k + p + )L/k)

What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

Resize: O(L + q + p * k)
Find: O(p + k)
Insert: O(L*k)


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


