    
#include "file.h"       
    
// Function to generate hash index based on the first character of the word
int hash_function(char *word)
{
    char ch = tolower(word[0]);  // Convert first character to lowercase
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a';         // Return index 0-25 for 'a' to 'z'
    else
        return 26;               // Return 26 for non-alphabet characters
}

// Function to create the database from a list of files and store in hash table
int create_database(list_node *file_list, main_node **hash_table)
{
    char word[100];  // Buffer to store words read from file

    while (file_list != NULL)  // Traverse each file in the file list
    {
        FILE *fptr = fopen(file_list->filename, "r");  // Open the current file
        if (fptr == NULL)  // Check for file open failure
        {
            printf("ERROR: Could not open file %s\n", file_list->filename);
            file_list = file_list->next;
            continue;  // Move to next file
        }

        // Read words from the file
        while (fscanf(fptr, "%s", word) != EOF)
        {
            int index = hash_function(word);  // Get hash index for the word
            main_node *temp = hash_table[index];  // Start from the head of hash_table[index]

            // Check if the word already exists in hash_table[index]
            while (temp != NULL)
            {
                if (strcmp(temp->word, word) == 0)  // Word match found
                {
                    // Check if the word already exists for this file in sub_node list
                    sub_node *sub_temp = temp->sub_link;
                    while (sub_temp != NULL)
                    {
                        if (strcmp(sub_temp->file_name, file_list->filename) == 0)
                        {
                            sub_temp->word_count++;  // Increment word count for this file
                            goto next_word;  // Move to next word in file
                        }
                        sub_temp = sub_temp->link;
                    }

                    // File not found in sub_node list, add new sub_node
                    sub_node *new_sub = malloc(sizeof(sub_node));
                    if (new_sub == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }
                    strcpy(new_sub->file_name, file_list->filename);  // Set file name
                    new_sub->word_count = 1;  // Initialize count
                    new_sub->link = temp->sub_link;  // Link to existing sub_nodes
                    temp->sub_link = new_sub;  // Add new sub_node at the beginning
                    temp->file_count++;  // Increment number of files containing this word
                    goto next_word;  // Move to next word
                }
                temp = temp->link;  // Move to next main_node
            }

            // Word not found in hash_table[index], create new main_node
            main_node *new_node =malloc(sizeof(main_node));
            if (new_node == NULL)
            {
                fclose(fptr);
                return FAILURE;
            }
            strcpy(new_node->word, word);  // Store word
            new_node->file_count = 1;  // One file contains this word initially
            new_node->sub_link = NULL;
            new_node->link = hash_table[index];  // Link to existing nodes in hash_table
            hash_table[index] = new_node;  // Insert new_node at head
            // Create sub_node for this word for the current file
            sub_node *new_sub = malloc(sizeof(sub_node));
            if (new_sub == NULL)
            {
                fclose(fptr);
                return FAILURE;
            }
            strcpy(new_sub->file_name, file_list->filename);  // Set file name
            new_sub->word_count = 1;  // Initialize word count
            new_sub->link = NULL;
            new_node->sub_link = new_sub;  // Link sub_node to main_node

        next_word:
            continue;  // Go to next word in file
        }

        fclose(fptr);  // Close the current file
        printf("Info :successfully:creation of DATABASE for file :%s\n", file_list->filename);

        file_list = file_list->next;  // Move to next file in the list
    }

    return SUCCESS;  // Indicate successful completion
}
