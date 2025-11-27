    
#include "file.h"         


void search_database(main_node **hash_table, char *word)
{
    // Check if the word is NULL or empty
    if (word == NULL || strlen(word) == 0)
    {
        printf("No word for search.\n");
        return;
    }

    // Compute index using the first character of the word
    int index = tolower(word[0]) - 'a';
    
    // Validate index (should be in range 0 to 26)
    if (index < 0 || index >= 27)
    {
        printf("Invalid word index.\n");
        return;
    }

    main_node *mtemp = hash_table[index];  // Get the main_node list at that index
    int found = 0;  // Flag to track if the word is found

    // Traverse the main_node list
    while (mtemp)
    {
        // Compare the current word with the target word
        if (strcmp(mtemp->word, word) == 0)
        {
            found = 1;  // Mark as found
            printf("Word: %s\n", mtemp->word);
            printf("File Count: %d\n", mtemp->file_count);

            sub_node *stemp = mtemp->sub_link;  // Get list of files containing the word

            // Print each file name and its word count
            while (stemp)
            {
                printf("File Name: %s, Word Count: %d\n", stemp->file_name, stemp->word_count);
                stemp = stemp->link;
            }
            break;  // Exit loop after word is found
        }
        mtemp = mtemp->link;  // Move to next main_node
    }

    // If word is not found
    if (!found)
    {
        printf("Word '%s' not found in the database.\n", word);
    }
    else
    {
        printf("Search completed successfully.\n");  // Word found and displayed
    }
    printf("------------------------------------------------------------------\n");
}
