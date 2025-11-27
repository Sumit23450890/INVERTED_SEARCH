/*Name : Sumit Kumar Pradhan
  project: inverted search
*/


#include "file.h"
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("INFO: Insufficient arguments\n");
        printf("Please pass the arguments like ./a.out <txt file>\n");
        return FAILURE;
    }
    list_node *head = NULL;
    for (int i = 1; i < argc; i++)
    {
        char *filename = argv[i];
        int len = strlen(filename);
        char *ext = strstr(filename, ".txt");

        if (ext != NULL && ext == filename + len - 4)
        {
            if (is_in_list(head, filename))
            {
                printf("INFO: %s =>This file is repeated ,so it will not store into the sll \n", filename);
                continue;
            }

            FILE *fptr = fopen(filename, "r");
            if (fptr != NULL)
            {
                fseek(fptr, 0, SEEK_END);
                long size = ftell(fptr);
                fclose(fptr);

                if (size > 0)
                {
                    head = add_to_list(head, filename);
                    printf("INFO: Successful: The file %s has been added to the file linked list\n", filename);
                }
                else
                {
                    printf("INFO: The file %s is empty, so it will not be added\n", filename);
                }
            }
            else
            {
                printf("INFO: The file %s does not exist in the directory, so it will not be added to the list\n", filename);
            }
        }
        else
        {
            printf("INFO: this file has not a .txt file %s\n", filename);
        }
    }
    print_list(head);
    main_node *hash_table[27] = {NULL}; 
    int flag=0; 
    int option;
    while(1)
    {
        printf("1. Create database\n");
        printf("2. Display database\n");
        printf("3. Search database\n");
        printf("4. Update database\n");
        printf("5. Save database\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
        if(flag==1)
        {
            printf("INFO: Database has already exits created not allowed\n");
            break;
        }
            printf("Create database\n");
            if (create_database(head, hash_table) == SUCCESS)
            {
                printf("Database created successfully.\n");
                flag=1;
            }
            else
            {
                printf("Database creation failed.\n");
            }
            break;
        case 2:
            printf("Display database\n");
            display_database(hash_table); 
            // Call function to display database
            break;
        case 3:
            printf("Search database\n");
            // Call function to search in database
            char word[100];
            printf("Enter the word to search: ");
            scanf("%s", word);
            search_database(hash_table, word);
            break;
        case 4:
            printf("Update database\n");
            char filename[100];
            printf("Enter the filename to update the database: ");
            scanf("%s", filename);
            update_database(hash_table, filename);
            if (flag==1 && is_in_list(head, filename))
                {
                    printf("INFO: The file %s was already exits not update again\n", filename);
                    break;
                }
            if (is_in_list(head, filename))
                {
                    printf("INFO: The file %s is already present in the list\n", filename);
                }
                else
                {
                    printf("INFO: Database update completed for file %s\n", filename);
                }
            break;
        case 5:
            printf("Save database\n");
             
                    char output_file[100];
                    printf("Enter the output filename to save database ");
                    scanf("%s", output_file);
                    save_database(hash_table, output_file);
            break;
        case 6:
            printf("Exit\n");
            exit(0);
        default:
            printf("Invalid option. Please try again.\n");
    }
    }
    return SUCCESS;
}


