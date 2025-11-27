#ifndef FILE_H
#define FILE_H

#define FAILURE -1
#define SUCCESS 0
#include <stdio.h>      
#include <string.h>    
#include <stdlib.h>      
#include <ctype.h>
typedef struct sub_node
{
    int word_count;
    char file_name[50];
    struct sub_node *link;
} sub_node;

typedef struct hash_t
{
    unsigned int key;
    struct main_node *link;
} hash_t;


typedef struct slist
{
    char file_name[30];
    struct slist *link;
} slist;

typedef struct main_node
{
    int file_count;
    char word[50];
    struct sub_node *sub_link;
    struct main_node *link;
} main_node;

typedef struct list_node
{
    char filename[100];
    struct list_node *next;
} list_node;

// Prototypes
list_node *add_to_list(list_node *head,const char *filename);
int is_in_list(list_node *head,const char *filename);
void print_list(list_node *head);
int hash_function( char *word);

int create_database(list_node *file_list, main_node **hash_table);
void display_database(main_node **hash_table);
void save_database(main_node **hash_table,  char *filename);
void update_database(main_node **hash_table,  char *filename);
void search_database(main_node **hash_table,  char *word);



#endif // FILE_H
