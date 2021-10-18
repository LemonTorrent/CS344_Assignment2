CS 344 Assignment 2 - Movies
Created by Nicole Yarbrough

This project was created to solve the prompt provided for assignment 2 in the Oregon State 
University Operating Systems I course.

This program process a file to create a new subdirectory with text files listing the movies 
produced in specific years. For example, 2012.txt will contain movies produced in 2012. If
a text file doesn't exist, then the file to be processed did not have any movies of that year.

To compile the code, unzip all files and run the command "make". If you would like to delete
the executable, use the command "make clean"

To start running the executable, you must have at least one file with 4 columns of data: title, 
year, languages, and rating value. All of the values for each movie must be separated with columns,
and each movie must be contained within a new line. Once this file is attained, the executable
is ran by "./movie." The user is then prompted to process a file or exit. If you wish to process a
file, you will be prompted to choose whether to process the largest file, smallest file, or file
of your specification.
