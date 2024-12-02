#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.



int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size = 0;
    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size);
    if (!hashes) {
        fprintf(stderr, "Error loading hashes file.\n");
        return 1;
    }
    // CHALLENGE1: Sort the hashes using qsort.
    // Open the password file for reading.
    FILE *dictFile = fopen(argv[2], "r");
    if (!dictFile) {
        perror("Error opening dictionary file");
        freeAA(hashes, size);
        return 1;
    }

    int foundCount = 0;
    char password[PASS_LEN];
    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    while (fgets(password, sizeof(password), dictFile)) {
        password[strcspn(password, "\n")] = '\0';

        char *hashedPass = md5(password, strlen(password));

        for (int i = 0; i < size; i++) {
            if (strcmp(hashes[i], hashedPass) == 0) {
                printf("Match found! Password: %s, Hash: %s\n", password, hashes[i]);
                foundCount++;
                break;
            }
        }

        free(hashedPass);
    }
    // CHALLENGE1: Use binary search instead of linear search.

    // When done with the file:
    //   Close the file
    fclose(dictFile);

    //   Display the number of hashes found.
    printf("Total hashes cracked: %d\n", foundCount);

    //   Free up memory.
    freeAA(hashes, size);

    return 0;
}
