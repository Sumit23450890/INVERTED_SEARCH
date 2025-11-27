   
#include "file.h"          
void update_database(main_node **hash_table, char *filename)
{
    FILE *fptr = fopen(filename, "r");  // Open the file in read mode
    if (fptr == NULL)  // Check if file opening failed
    {
        printf("ERROR: Could not open file %s for reading\n", filename);
        return;
    }

    char word[100];  // Buffer to store each word read from the file

    // Read words from the file one by one
    while (fscanf(fptr, "%s", word) != EOF)
    {
        int index = hash_function(word);  // Get index using first character of the word
        main_node *temp = hash_table[index];  // Start at head of the list at that index

        // Search if the word already exists in the hash table
        while (temp != NULL)
        {
            if (strcmp(temp->word, word) == 0)  // Word found
            {
                // Check if the word already exists for this file
                sub_node *sub_temp = temp->sub_link;
                while (sub_temp != NULL)
                {
                    if (strcmp(sub_temp->file_name, filename) == 0)
                    {
                        sub_temp->word_count++;  // Increment count if file already listed
                        goto next_word;  // Move to next word from file
                    }
                    sub_temp = sub_temp->link;  // Move to next sub_node
                }

                // File not found in sub_node list — create a new sub_node
                sub_node *new_sub = malloc(sizeof(sub_node));
                if (new_sub == NULL)
                {
                    printf("ERROR: Memory allocation failed for sub_node\n");
                    fclose(fptr);
                    return;
                }
                strcpy(new_sub->file_name, filename);  // Set file name
                new_sub->word_count = 1;  // Initialize count
                new_sub->link = temp->sub_link;  // Link to existing sub_nodes
                temp->sub_link = new_sub;  // Insert at beginning
                temp->file_count++;  // Increase file count for the word
            }
            temp = temp->link;  // Move to next main_node in chain
        }

        // Word not found — create a new main_node
        main_node *new_main = malloc(sizeof(main_node));
        if (new_main == NULL)
        {
            printf("ERROR: Memory allocation failed for main_node\n");
            fclose(fptr);
            return;
        }
        strcpy(new_main->word, word);  // Store new word
        new_main->file_count = 1;  // Initialize file count

        // Create a sub_node for this word and file
        sub_node *new_sub = malloc(sizeof(sub_node));
        if (new_sub == NULL)
        {
            printf("ERROR: Memory allocation failed for sub_node\n");
            free(new_main);  
            fclose(fptr);
            return;
        }
        strcpy(new_sub->file_name, filename);  // Store file name
        new_sub->word_count = 1;  // Start word count at 1
        new_sub->link = NULL;  // No other sub_nodes yet

        // Link sub_node to main_node and insert main_node into hash table
        new_main->sub_link = new_sub;
        new_main->link = hash_table[index];  // Insert at head of list
        hash_table[index] = new_main;

    next_word:
        continue;  // Continue with the next word
    }

    fclose(fptr);  // Close the file after processing
}
