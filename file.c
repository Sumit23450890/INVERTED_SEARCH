#include "file.h"   // Include header file

list_node *add_to_list(list_node *head, const char *filename)
{
    list_node *new_node = malloc(sizeof(list_node));   // Allocate memory for new node
    if (new_node == NULL)
    {
        printf("ERROR: Memory allocation failed\n");   // Print error if allocation fails
        return head;                                   // Return existing list
    }

    strcpy(new_node->filename, filename);              // Copy filename into node
    new_node->next = NULL;                             // Set next pointer to NULL

    if (head == NULL)                                  // If list empty, new node becomes head
        return new_node;

    list_node *temp = head;                            // Temporary pointer to traverse list
    while (temp->next != NULL)                         // Move to last node
        temp = temp->next;

    temp->next = new_node;                             // Link new node at end
    return head;                                       // Return head of list
}

int is_in_list(list_node *head, const char *filename)
{
    while (head != NULL)                               // Traverse list
    {
        if (strcmp(head->filename, filename) == 0)     // Check if filename matches
            return 1;                                   // File found in list
        head = head->next;                             // Move to next node
    }
    return 0;                                          // File not found
}

void print_list(list_node *head)
{
    //printf("Final File List:\n");                    // Optional print header
    while (head)                                       // Traverse list
    {
        printf("%s", head->filename);                  // Print filename
        head = head->next;                             // Move to next node
        if (head)
            printf(" -> ");                            // Print arrow between nodes
    }
    printf(" -> NULL\n");                              // Indicate end of list
}
