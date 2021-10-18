#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include <time.h>


#define PREFIX "movies_"
#define SUFFIX ".csv"
#define DIRPREFIX "yarbroni.movies."

/* struct for movie information */
struct movie
{
    char *title;
    char *year;
    char *language;
    char *ratingValue;
    struct movie *next;
};

/*
*   Gets user input on whether to quit or continue
*/
int userInput(){
    int continueChoice = 0;

    do {
        printf("1. Select file to process\n");
        printf("2. Exit the program\n\n");

        printf("Enter a choice 1 or 2: ");
        scanf("%d", &continueChoice);

        // If invalid input, print error message
        if (continueChoice != 1 && continueChoice != 2) {
            printf("Invalid input. Please enter 1 or 2\n\n");
        }

    } while (continueChoice != 1 && continueChoice != 2);
    // Action choice 2 is already taken by functionality in later code, so change to 0.
    if (continueChoice == 2){
        continueChoice = 0;
    }

    // Return action choice
    return continueChoice;

}

/*
*   Gets user input on which file to process. 
*/
int processFileInput() {
    int choice = 0;

    do {
        printf("\nWhich file do you want to process?\n");
        printf("Enter 1 to pick the largest file\n");
        printf("Enter 2 to pick the smallest file\n");
        printf("Enter 3 to specify the name of a file\n\n");

        printf("Enter a choice from 1 to 3: ");
        scanf("%d", &choice);

        // If invalid input, print error message
        if (choice < 1 || choice > 3){
            printf("Invalid input. Please enter number between 1 and 3\n");
        }

    // Loop until valid input
    } while (choice < 1 || choice > 3);

    // Then return
    return choice;
}

/*
*   Finds the largest file in the current directory
*   Much of this function is from the directory page in class (more specifically, the Getting 
*   File and Directory Meta-Data example)
*/
char* largest(){
    // Open the current directory
    DIR* currDir = opendir(".");
    struct dirent *aDir;
    // time_t lastModifTime;
    struct stat dirStat;
    int i = 0;
    char entryName[256];
    int lLength;

    // Go through all the entries
    while((aDir = readdir(currDir)) != NULL){

        if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
            // Get meta-data for the current entry
            stat(aDir->d_name, &dirStat);  

            // Use the difftime function to get the time difference between the current value of lastModifTime and the st_mtime value of the directory entry
            if(i == 0 || (dirStat.st_size > lLength)){
                lLength = dirStat.st_size;
                // printf("length = %d\n", lLength);
                memset(entryName, '\0', sizeof(entryName));
                strcpy(entryName, aDir->d_name);

            }

            i++;
        }
        }
    // Close the directory
    closedir(currDir);
    printf("Now processing the chosen file named %s\n", entryName);
    return entryName;
}

/*
*   Finds the smallest file in the current directory
*   Much of this function is from the directory page in class (more specifically, the Getting 
*   File and Directory Meta-Data example)
*/
char* smallest(){
    // Open the current directory
    DIR* currDir = opendir(".");
    struct dirent *aDir;
    // time_t lastModifTime;
    struct stat dirStat;
    int i = 0;
    char entryName[256];
    int sLength;
    // char sName[256];

    // Go through all the entries
    while((aDir = readdir(currDir)) != NULL){

    if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
        // Get meta-data for the current entry
        stat(aDir->d_name, &dirStat);  
       

        // Use the difftime function to get the time difference between the current value of lastModifTime and the st_mtime value of the directory entry
        if(i == 0 || (dirStat.st_size < sLength)){
            // printf("yes");
            sLength = dirStat.st_size;
            memset(entryName, '\0', sizeof(entryName));
            strcpy(entryName, aDir->d_name);


        }
        i++;
    }
    }
    // Close the directory
    closedir(currDir);
    printf("Now processing the chosen file named %s\n", entryName);


    return entryName;
}

/*
*   Finds the file with the indicated name in the current directory
*/
char* openName(int *choice){
    DIR* currDir = opendir(".");
    struct dirent *aDir;
    time_t lastModifTime;
    struct stat dirStat;
    int i = 0;
    char entryName[256];


    // char str[] = "movies_sample_1.csv";

	int file_descriptor;
	//char* newFilePath = "nonExistingFile.txt";
    char newFilePath [256];

    // Get file name as input
    printf("Enter the complete file name: ");
    scanf("%s", newFilePath);

    // Check if file exists
	file_descriptor = open(newFilePath, S_IRUSR | S_IWUSR);
	if (file_descriptor == -1){
        printf("The file %s was not found. Try again\n", newFilePath);

        // if file is not found, change the value of choice to -1
        *choice = file_descriptor;
		
	}
	
	return newFilePath;
}



/* Parse the current line which is space delimited and create a
*  student struct with the data in this line
*  This code was adapted from the provided student example from assignment 1.
*/
struct movie *createStudent(char *currLine)
{
    struct movie *currMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;

    // The first token is the title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->year, token);

    // The next token is the language
    token = strtok_r(NULL, ",", &saveptr);

    // provided code:
    currMovie->language = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->language, token);

    // The last token is the rating value
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->ratingValue = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->ratingValue, token);

    // Set the next node to NULL in the newly created student entry
    currMovie->next = NULL;

    // printMovie(currMovie);

    return currMovie;
}

/*
* Return a linked list of students by parsing data from
* each line of the specified file.
* This code originates from the Student example in assignment 1.
*/
struct movie *processFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    // char *token;

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

	getline(&currLine, &len, movieFile);

    // printf("After getline\n");
	

    // Read the file line by line
    while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
        // printf("Inside while loop\n");
		
        // Get a new student node corresponding to the current line
        struct movie *newNode = createStudent(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(movieFile);    

    return head;
}

/*
* This function prints an individual movie and its data.
* It also originates from the student example from assignment 1
*/
void printMovie(struct movie* aMovie){
  printf("%s, %s, %s, %s\n", aMovie->title,
               aMovie->year,
               aMovie->language,
			   aMovie->ratingValue
			   );
}

/*
* Print the linked list of movies
* It also originates from the student example from assignment 1
*/
void printMovieList(struct movie *list)
{
    while (list != NULL)
    {
        printMovie(list);
        list = list->next;
    }
}

/*
* Creates a file based on year if it doesn't exist, then writes to open file
*/
struct movie* createFile(struct movie* list, char* dirName){

    char* newFilePath [256];
    int file_descriptor;

    // Create file name starting with yarbroni.movies
    strcpy(newFilePath, dirName);

    strcat(newFilePath, "/");
    strcat(newFilePath, list->year);
    strcat(newFilePath, ".csv");

    // Open/create file
    file_descriptor = open(newFilePath, O_WRONLY | O_CREAT |O_APPEND, 00640);

    // Write title of current movie to file
    write(file_descriptor, list->title, strlen(list->title));

    // Write newline char
    write(file_descriptor, "\n", 1);

    // Close file
    close(file_descriptor);

    // return pointer to next movie
    return list->next;
}

/*
*   Free memory in linked list
*/
void freeList(struct movie* head) {
   struct movie* temp;

   while (head != NULL)
    {
       temp = head;
       head = head->next;
       free(temp);
    }
    return;
}

/*
*   Create directory with random int
*/
struct movie *createDir(struct movie* list){//char fileName[]){
    // Sets randomness
    srand(time(0));

    int file_descriptor;
    struct dirent *aDir;
    // printMovieList(list);
    char dirName [256];
    char buffer [256];

    char* newFilePath [256];

    // Get random integer between 0 and 99999
    int randomInt = random() % 100000;

    // Assemble directory name
    strcpy(dirName, DIRPREFIX);
    sprintf(buffer, "%i", randomInt);
    strcat(dirName, buffer);

    printf("Created directory with name %s\n", dirName);

    int check = mkdir(dirName, 0755);
    DIR * currDir = opendir(dirName);
    

    // printf("Opening dir\n");
    if (file_descriptor == -1){
		printf("open() failed on \"%s\"\n", dirName);
		perror("Error");
		exit(1);
	}
	
    file_descriptor = open(newFilePath, O_WRONLY | O_CREAT|O_APPEND, 00640);

    close(newFilePath);

    closedir(currDir);

    // Create files or update files with list info
    while (list != NULL){
        list = createFile(list, dirName);
    }
    
    return 0;
}

/*
*   Main function, runs code functionality
*/
int main(int argc, char *argv[]) {
    int choice = 0;

    char* file;
    struct movie *list;

    // Repeat while 
    do {
        if (choice != -1){
            choice = userInput();
        }
        
        // If user chooses to exit, return
        if (choice == 0){
            return 0;
        }

        // If choice isn't to return, ask user for what type of file input
        if (choice != 0){
            choice = processFileInput();
        }

        // Call functionality from user choice
        if (choice == 1){
            file = largest();
        } else if (choice == 2){
            file = smallest();
        } else if (choice == 3){
            file = openName(&choice);
        }

        // If file input isn't bad, process file
        if (choice != -1) {
            list = processFile(file);
            createDir(list);
            freeList(list);
            NULL;
        }

        printf("\n");

    } while (choice != 0);
    
	return 0;
}
