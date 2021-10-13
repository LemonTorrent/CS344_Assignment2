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

int userInput(){
    int continueChoice = 0;

    // do {
        printf("1. Select file to process\n");
        printf("2. Exit the program\n\n");

        printf("Enter a choice 1 or 2: ");
        scanf("%d", &continueChoice);


        
        //printf("\n\n")

    // } while (continueChoice != 2);
    if (continueChoice == 2){
        continueChoice = 0;
    }
    return continueChoice;

}

int processFile() {
    int choice = 0;

    printf("\nWhich file do you want to process?\n");
    printf("Enter 1 to pick the largest file\n");
    printf("Enter 2 to pick the smallest file\n");
    printf("Enter 3 to specify the name of a file\n\n");

    printf("Enter a choice from 1 to 3: ");
    scanf("%d", &choice);
    return choice;
}

int largest(){
    // Open the current directory
    DIR* currDir = opendir(".");
    struct dirent *aDir;
    time_t lastModifTime;
    struct stat dirStat;
    int i = 0;
    char entryName[256];

    // Go through all the entries
    while((aDir = readdir(currDir)) != NULL){

        if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
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
    printf("The last file/directory starting with the prefix \"%s\" modified in the current directory is %s\n", PREFIX, entryName);
    return 0;
}

int smallest(){
    NULL;
}

int openName(){
    DIR* currDir = opendir(".");
    struct dirent *aDir;
    time_t lastModifTime;
    struct stat dirStat;
    int i = 0;
    char entryName[256];

    char str[] = "movies_sample_1.csv";

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

int main(int argc, char *argv[]) {
    int choice = 0;

    largest();
    // openName();

    return;

    do {
        choice = userInput();

        if (choice != 0){
            choice = processFile();
        }

        if (choice == 1){
            largest();
        } else if (choice == 2){
            smallest();
        } else if (choice == 3){
            openName();
        }

    } while (choice != 0);
    

	return 0;
}
