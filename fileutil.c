#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.

// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// Allocate memory for an array of strings (arr).
	char **arr = NULL;
	char lbuff[256];
	int lnCounter = 0;

	// Read the file line by line.
	while (fgets(lbuff, sizeof(lbuff), in))
	{
		//	Trim newline.
		lbuff[strcspn(lbuff, "\n")] = '\0';

		//Expand array if necessary (realloc).
		arr = realloc(arr, (lnCounter + 1) * sizeof(char *));
		if(arr == NULL)
		{
			perror("Error reallocating in loadFileAA.");
			fclose(in);
			return NULL;
		}
		//   Allocate memory for the string.
		arr[lnCounter] = malloc(strlen(lbuff) + 1);
		if (arr[lnCounter] == NULL)
		{
			perror("Error allocating the line memory in loadFileAA.");
			fclose(in);
			return NULL;
		}
	
		//   Copy each line into the string (use strcpy).
		strcpy(arr[lnCounter], lbuff);
		lnCounter++;
	}

    // Close the file.
	fclose(in);

	// The size should be the number of entries in the array.
	if (lnCounter == 0)
	{
    	printf("Warning: File is empty.\n");
	}
	*size = lnCounter;
	
	// Return pointer to the array of strings.
	return arr;
}


// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	for (int i = 0; i < size; i++)
	{
		if(strstr(lines[i], target) != NULL)
		{
			return lines[i];
		}
	}

	return NULL;
}


// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	//Loop through each element of array and free memory of each string
	for (int i = 0; i < size; i++)
	{
		free(arr[i]);
	}

	//free the array of pointers
	free(arr);
}
