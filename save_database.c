   
#include "file.h"      
     
void save_database(main_node **hash_table, char *filename)
{
    FILE *fptr = fopen(filename, "w");  // Open the file in write mode
    if (fptr == NULL)  // Check if file opening failed
    {
        printf("ERROR: Could not open file %s \n", filename);
        return;  // Exit the function on failure
    }

    for (int i = 0; i < 27; i++)  // Loop over all 27 indices of hash table
    {
        main_node *mtemp = hash_table[i];  // Pointer to current main_node at index i
        while (mtemp)  // Traverse through all main_nodes (words) at this index
        {
            sub_node *stemp = mtemp->sub_link;  // Pointer to the sub_node list 

            if (stemp != NULL)  // Only save if there is at least one sub_node
            {
                
                fprintf(fptr, "#%d;%s;%d", i, mtemp->word, mtemp->file_count);// Print main_node data: #index;word;file_count

               
                while (stemp)
                {
                    fprintf(fptr, ";%s;%d", stemp->file_name, stemp->word_count); // Print all sub_node data: ;filename;word_count
                    stemp = stemp->link;  // Move to next sub_node
                }

                // Mark end of this word entry
                fprintf(fptr, ";#\n");
            }

            mtemp = mtemp->link;  // Move to next main_node
        }
    }

    fclose(fptr);  
    printf("Database successfully saved to %s\n", filename);  
}
