#include <stdio.h>

int main()
{
    FILE *file;
    FILE *tempFile;
    
    char buffer[100];
    char query[32];
    char replace[32];
    int count = 0;
    
    //Choose the file you want to edit by placing its name in the string below
    char *fileName = "text.txt";

    //User inputs the query word and the replacement word
    printf("Insert query word: ");
    scanf("%s", query);
    printf("Input replacement word: ");
    scanf("%s", replace);

    //Opens the file with text and the temporary file with reading and writing modes respectively.
    file = fopen(fileName, "r");
    tempFile = fopen("temp.txt", "w");
    
    //Ends program if either is not opened correctly
    if (file == NULL || tempFile == NULL) 
    {
        printf("file opened unsucessfully\n");
        return 0;
    } 

    //For every string, separated by a space, check if each letter, within said string, corresponds to the query word
    int i = 0;
    while (fscanf(file, "%s", buffer) != EOF)
    {
        i = 0;
        //'i' represents the index of the character within the string.
        //If every character matches within both strings, and both are the same length, they are equivalent
        while (buffer[i] != '\0' && query[i] != '\0')
        {
            //If a character does not match, end the while loop
            if (buffer[i] != query[i]) break;
            i++;
        }

        //Check if both strings have the null terminator at the same index
        if (buffer[i] == '\0' && query[i] == '\0')
        {
            //Both strings are equvalent, so place the replacement string instead
            fprintf(tempFile, "%s", replace);
            //Increment the count of replacements
            count++;
        } 
        else 
        {
            //If streamed word does not match query word place the stream word into the file
            fprintf(tempFile, "%s", buffer);
        }
        fprintf(tempFile, " ");
    }

    //close both files
    fclose(tempFile);
    fclose(file);

    //Open both files but with the permission switched, write the file, read the tempfile
    file = fopen(fileName, "w");
    tempFile = fopen("temp.txt", "r");

    //Place every word from the temp file to the original file
    while (fscanf(tempFile, "%s", buffer) != EOF)
    {
        fprintf(file, "%s ", buffer);
    }

    //Close and remove the temp file
    fclose(file);
    fclose(tempFile);
    remove("temp.txt");

    //Print out the number of replacements.
    printf("Number of Replacements: %d\n", count);
    
    return 0;
}