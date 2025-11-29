#include <stdio.h>                                                      //imports the standard input output functions from the file stdio.h which comes with the compiler
#include <stdlib.h>
#include <time.h>
#include <string.h>

char subject[100];
char yesNo;
FILE *fpt;

void flushBuffer() {                                                    //this clears the subject buffer so it doesn't submit any eronious entries
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n'));
}

int main(){                                                             //this establishes the main function of the program, all subroutines will fall within the main brackets {}
startProgram:

time_t t ;                                                              //this sets up the time variables
    char MY_TIME[80];
    time_t rawtime;
    struct tm *info;
    time(&rawtime);                                                     // Get current time
    info = localtime(&rawtime);                                         // Convert to local time
    strftime(MY_TIME, sizeof(MY_TIME), "%m%d%Y, %H:%M:%S", info);       //this sets the output format of the time and date

printf("\nEnter the time stamp subject: ");
    fgets(subject, sizeof(subject), stdin);                             //this allows user input for a the subject not to exceed 100 characters

fpt = fopen("logs/time_log.csv", "a");                                       //this opens and appends the time_log.csv file
      fprintf(fpt, "%s", MY_TIME );
      fprintf(fpt, ",%s", subject);
fclose(fpt);                                                            //this closes the time_log.csv file

printf("Time Captured: ");
printf ("%s", MY_TIME );
printf ("\n");

anotherOption:                                                          //this allows a reset of the yes/no options if another character is entered
printf("\nCapture time again? Y/N: ");
scanf("%c", &yesNo);                                                    //this sets the loop for yes or no entry
if (yesNo == 'y' || yesNo == 'Y') {
    flushBuffer();                                                      //this clears out any remaining character from the previous subject entry
    goto startProgram;
}
else if (yesNo == 'n' || yesNo == 'N'){
    return 0;
}
else{
    printf("\nPlease enter another option\n");
    goto anotherOption;
}
}
