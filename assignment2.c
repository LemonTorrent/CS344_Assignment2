#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    int continueChoice = 0;
    int choice = 0;
    
    do {
        printf("1. Select file to process\n");
        printf("2. Exit the program\n\n");

        printf("Enter a choice 1 or 2: ");
        scanf("%d", &continueChoice);

        if (continueChoice != 2){
            printf("\nWhich file do you want to process?\n");
            printf("Enter 1 to pick the largest file\n");
            printf("Enter 2 to pick the smallest file\n");
            printf("Enter 3 to specify the name of a file\n\n");

            printf("Enter a choice from 1 to 3: ");
            scanf("%d", &choice);

            if (choice == 1){
                NULL;
            } else if (choice == 2) {
                NULL;
            } else if (choice == 3){
                NULL;
            } else {
                NULL;
            }

        }
        
        //printf("\n\n")

    } while (continueChoice != 2);

	return 0;
}
