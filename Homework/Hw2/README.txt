HOMEWORK 2: HOCKEY CLASSES


NAME:  Jimmy Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com, w3schools.com, geeksforgeeks.org, Ethan Garcia, Taein Yi, Joseph Pan

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20



DESCRIPTION OF 3RD STATISTIC:
Please be concise! (< 200 words)
What question you are trying to answer with your statistic? 
What data did you need to organize? 
What was interesting or challenging about the implementation of this statistic? 

With my statistic I'm trying to figure out what the dates are that the teams have played.
I needed to parse through the file to find the two teams that played and the date that they both played on.
Since my data was parsed by string, whenever the string in the loop was "PERIOD" and "1", there are dates
a few indexes before the current index. Since the month, day, and year were split up, I needed to
concatenate the strings together. The final string is put into a vector, where each team object has a 
vector of dates. Finally, I needed to organize the dates from the vector to be printed out. I created dashes
and spacings for each team. What was interesting about my data is that you can see how many games a team has each month.
The most challenging part was trying to fix the data so it fits in a table.


NAME OF FILE WITH SAMPLE OUTPUT FROM 3RD STATISTIC:
Be sure to select (or create) a dataset with interesting results


custom_stats_output.txt



MISC. COMMENTS TO GRADER:  
Optional, please be concise!

