# ABCU
##What was the problem you were solving in the projects for this course?
The primary goal of this project was to build an advising tool for the Computer Science department at ABCU. The program reads course data from a CSV file, stores the information into a vector data structure, and allows users to either search for a course or view all courses in alphanumeric order. 

## How did you approach the problem? Consider why data structures are important to understand.
I approached the problem by carefully considering the size and structure of the dataset. Since the course list was small, I chose to use a vector to store course data. Vectors are simple to implement and efficient for linear operations when working with small datasets. Understanding data structures was crucial because it allowed me to evaluate trade-offs: while hash tables and binary search trees offer faster search times for larger datasets, their overhead and complexity weren't justified for this case. The vector’s straightforward behavior made it an ideal choice for this advising tool.

## How did you overcome any roadblocks you encountered while going through the activities or project?
One challenge I encountered was validating the prerequisites to ensure that each one existed within the dataset. This required cross-referencing the prerequisites of a course against all available courses. I solved this by implementing a validatePrerequisite function that iterates through the course list and confirms whether a given prerequisite is valid. 

## How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
Working with vectors, validation checks, and user input highlighted the importance of writing clean, maintainable code. I started using more meaningful variable names, consistent indentation, and inline comments to explain my logic. 
