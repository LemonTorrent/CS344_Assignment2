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


    printf("1. Select file to process\n");
    printf("2. Exit the program\n\n");

    printf("Enter a choice 1 or 2: ");
    scanf("%d", &continueChoice);

    // Action choice 2 is already taken by functionality in later code, so change to 0.
    if (continueChoice == 2){
        continueChoice = 0;
    }

    // Return action choice
    return continueChoice;

}

/*
*   Gets user input on which file to process
*/
int processFileInput() {
    int choice = 0;

    printf("\nWhich file do you want to process?\n");
    printf("Enter 1 to pick the largest file\n");
    printf("Enter 2 to pick the smallest file\n");
    printf("Enter 3 to specify the name of a file\n\n");

    printf("Enter a choice from 1 to 3: ");
    scanf("%d", &choice);
    return choice;
}

char* largest(){
    // Open the current directory
    DIR* currDir = opendir(".");
    struct dirent *aDir;
    time_t lastModifTime;
    struct stat dirStat;
    int i = 0;
    char entryName[256];

    char *largestName;
    int largestLength = 0;
    int fd;
    int howMany;
    int lLength;

    // Go through all the entries
    while((aDir = readdir(currDir)) != NULL){

        if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
            // Get meta-data for the current entry
            stat(aDir->d_name, &dirStat);  

            printf("length = %d\n", dirStat.st_size);
            printf("name = %s\n", aDir->d_name);

            // Use the difftime function to get the time difference between the current value of lastModifTime and the st_mtime value of the directory entry
            if(i == 0 || (dirStat.st_size > lLength)){
                lLength = dirStat.st_size;
                printf("length = %d\n", lLength);
                memset(entryName, '\0', sizeof(entryName));
                strcpy(entryName, aDir->d_name);

            }

            /*
            // We first open a file for read write, creating it if necessary and truncating it if it already exists
            fd = open(entryName, O_WRONLY | O_CREAT|O_TRUNC, 00600);
                if (fd == -1){
                    printf("open() failed on \"%s\"\n", entryName);
                    perror("Error");
                    exit(1);
                }

            // We open the file for reading
            close(entryName);
            
            // We allocate a buffer to read from the file
            char* readBuffer = malloc(50 * sizeof(char));
            howMany = read(fd, readBuffer, 2000);
            printf("read %d bytes from the file\n", howMany);
            
            printf("%s\n", readBuffer);

            */

            i++;
        }
        }
    // Close the directory
    closedir(currDir);
    printf("The last file/directory starting with the prefix \"%s\" modified in the current directory is %s\n", PREFIX, entryName);
    return entryName;
}

char* smallest(){
    // Open the current directory
    DIR* currDir = opendir(".");
    struct dirent *aDir;
    time_t lastModifTime;
    struct stat dirStat;
    int i = 0;
    char entryName[256];
    int sLength;
    char sName[256];

    // Go through all the entries
    while((aDir = readdir(currDir)) != NULL){

    if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
        // Get meta-data for the current entry
        stat(aDir->d_name, &dirStat);  

        //printf(dirStat.st_dev);
        // sLength = dirStat.st_size;

        //printf("length = %d\n", dirStat.st_size);
        

        // Use the difftime function to get the time difference between the current value of lastModifTime and the st_mtime value of the directory entry
        if(i == 0 || (dirStat.st_size < sLength)){
            printf("yes");
            sLength = dirStat.st_size;
            memset(entryName, '\0', sizeof(entryName));
            strcpy(entryName, aDir->d_name);


        }
        i++;
    }
    }
    // Close the directory
    closedir(currDir);
    printf("The smallest file/directory starting with the prefix \"%s\" modified in the current directory is %s\n", PREFIX, entryName);


    return entryName;
}

char* openNameInput() {

}

char* openName(int *choice){
    DIR* currDir = opendir(".");
    struct dirent *aDir;
    time_t lastModifTime;
    struct stat dirStat;
    int i = 0;
    char entryName[256];


    char str[] = "movies_sample_1.csv";

	int file_descriptor;
	//char* newFilePath = "nonExistingFile.txt";
    char newFilePath [256];

    printf("Enter the complete file name: ");
    scanf("%s", newFilePath);

    // printf("New file = %s\n", newFilePath);

  // TO DO: set the flags argument so that the attempt to open the file for reading and writing fails
  // What is the error message printed by perror?
	file_descriptor = open(newFilePath, S_IRUSR | S_IWUSR);
	if (file_descriptor == -1){
		// printf("open() failed on \"%s\"\n", newFilePath);
        printf("The file %s was not found. Try again\n", newFilePath);
		//perror("Error");
        *choice = file_descriptor;
		//exit(1);
	}
	
	// printf("file_descriptor = %d\n", file_descriptor);
	
	return newFilePath;

    return 0;

    // Go through all the entries
    while((aDir = readdir(currDir)) != NULL){

        if(strncmp(str, aDir->d_name, strlen(str)) == 0){
            // Get meta-data for the current entry
            stat(aDir->d_name, &dirStat);  

            // Use the difftime function to get the time difference between the current value of lastModifTime and the st_mtime value of the directory entry
            if(i == 0 || difftime(dirStat.st_mtime, lastModifTime) > 0){
                lastModifTime = dirStat.st_mtime;
                memset(entryName, '\0', sizeof(entryName));
                strcpy(entryName, aDir->d_name);
            }
            i++;
        }
    }
    // Close the directory
    closedir(currDir);
    printf("The last file/directory starting with the prefix \"%s\" modified in the current directory is %s\n", str, entryName);
    return 0;
}



/* Parse the current line which is space delimited and create a
*  student struct with the data in this line
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

    // printf(token);
    // char *strTemp = calloc(strlen(token) + 1, sizeof(char));
    // strcpy(strTemp, token);

    // printf(strTemp);

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
*/
struct movie *processFile(char *filePath)
{
    // printf("Inside processFile\n");
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
        // printf("After createStudent\n");
		// *numMovies = *numMovies + 1;
		

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

    // printf("\n\n printMovie:\n");
    

    return head;
}

/*
* This function prints an individual movie and its data.
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
*/
void printMovieList(struct movie *list)
{
    while (list != NULL)
    {
        printMovie(list);
        list = list->next;
    }
}

struct movie* createFile(struct movie* list, char* dirName){

    char* newFilePath [256];
    int file_descriptor;

    strcpy(newFilePath, dirName);

    strcat(newFilePath, "/");
    strcat(newFilePath, list->year);
    strcat(newFilePath, ".csv");

    printf("fileName = %s\n", dirName);

    file_descriptor = open(newFilePath, O_WRONLY | O_CREAT |O_APPEND, 00640);
    write(file_descriptor, list->title, strlen(list->title));
    write(file_descriptor, "\n", 1);

    close(file_descriptor);

    return list->next;
}

void freeList(struct movie* head)
{
   struct movie* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}

struct movie *createDir(struct movie* list){//char fileName[]){
    // printf("Inside readFile\n");
    int numMovies = 0;
    int file_descriptor;
    // struct movie *list = processFile(fileName);
    struct dirent *aDir;
    printMovieList(list);
    char dirName [256];
    char buffer [256];

    char* pathname = "./yarbroni.movies2";
    // char* newFilePath = "./yarbroni.movies2/test.csv";
    char* newFilePath [256];

    int randomInt = random();

    strcpy(dirName, DIRPREFIX);
    sprintf(buffer, "%i", randomInt);
    strcat(dirName, buffer);

    printf("Created directory with name %s\n", dirName);

    //return;

    int check = mkdir(dirName, 0755); // mode_t "rwxr-x---"); Check that this is correct
    DIR * currDir = opendir(dirName);
    

    printf("Opening dir\n");
    if (file_descriptor == -1){
		printf("open() failed on \"%s\"\n", dirName);
		perror("Error");
		exit(1);
	}
	
    file_descriptor = open(newFilePath, O_WRONLY | O_CREAT|O_APPEND, 00640);

    close(newFilePath);

    while((aDir = readdir(currDir)) != NULL){
        printf("%s  %lu\n", aDir->d_name, aDir->d_ino);    
    }

    closedir(currDir);

    while (list != NULL){
        list = createFile(list, dirName);
    }
    
    

    // delete list after creating files

    return 0;
}



int main(int argc, char *argv[]) {
    int choice = 0;

    char* file;
    struct movie *list;
    /*
    file = smallest();

    printf("Name = %s\n", smallest());
    printf("Returned file name is %s\n", file);
    file = largest();
    printf("Returned file name is %s\n", file);
    return 0;
    */

    char fileName [] = "movies_sample_1.csv";

    //largest();

    /*
    file = openName(&choice);
    printf("after open name\n");

    printf("openName = %s\n", file);
    printf("choice = %d\n", choice);
    */
    //printf("Processing file %s\n", fileName);

    //readFile(fileName);

    

    //return 0;

    do {
        if (choice != -1){
            choice = userInput();
        }
        
        if (choice == 0){
            return 0;
        }
        if (choice != 0){
            choice = processFileInput();
        }

        if (choice == 1){
            file = largest();
        } else if (choice == 2){
            file = smallest();
        } else if (choice == 3){
            file = openName(&choice);
        }

        if (choice != -1) {
            list = processFile(file);
            printMovieList(list);
            createDir(list);
            // list = readFile(file);
            freeList(list);
            NULL;
        }

//        printf("openName = %s\n", file);
//        printf("choice = %d\n", choice);

        printf("\n");

    } while (choice != 0);
    

	return 0;
}
