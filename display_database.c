    
#include "file.h"            


void display_database(main_node **hash_table)
{
   
    printf("Index\tWord\tFile count\tFile name\tWordcount\n");
    printf("------------------------------------------------------------------\n");

   
    for (int i = 0; i < 27; i++)
    {
        main_node *mtemp = hash_table[i];  // Pointer to traverse main_node list at index i
        while (mtemp)  // Traverse through all words at this hash index
        {
            sub_node *stemp = mtemp->sub_link;  // Pointer to traverse sub_node list (file list)

            // Calculate total word count for this word across all files
            int total_word_count = 0;
            sub_node *current_sub_node = stemp;
            while (current_sub_node)
            {
                total_word_count = total_word_count + current_sub_node->word_count;
                current_sub_node = current_sub_node->link;
            }

            if (stemp != NULL)
            {
                // Print the first sub_node with including word and file count
                printf("%d\t%s\t%d\t\t%s\t\t%d\n", i, mtemp->word, mtemp->file_count, stemp->file_name, total_word_count);
                stemp = stemp->link;  // Move to next sub_node

                // Print remaining sub_nodes (files containing the word)
                while (stemp)
                {
                    printf("\t\t\t\t%s\t\t%d\n", stemp->file_name, stemp->word_count);
                    stemp = stemp->link;
                }
            }
            else
            {
                // If no sub_node exists, print placeholder values
                printf("%d\t%s\t%d\n", i, mtemp->word, mtemp->file_count);
            }

            mtemp = mtemp->link;  // Move to next main_node
        }
    }

   
    printf("------------------------------------------------------------------\n");
}
