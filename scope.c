#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define MAX_NAME_LENGTH 20

typedef struct symbol
{
    char name[MAX_NAME_LENGTH];
    int value;
    struct symbol *next;
} symbol;

typedef struct symbol_table
{
    symbol *table[TABLE_SIZE];
    struct symbol_table *prev;
} symbol_table;

symbol_table *curr = NULL;

// function to create hash function
int hash(const char *name)
{
    int hash_value = 0;
    for (int i = 0; name[i] != '\0'; i++)
    {
        hash_value += name[i];
    }
    return (hash_value % TABLE_SIZE);
}

// function to create symbol
symbol *create_symbol(char *name, int val)
{
    symbol *new;
    new = (symbol *)malloc(sizeof(symbol));
    strcpy(new->name, name);
    new->value = val;
    new->next = NULL;
    return new;
}

// function to insert symbol
void insert_symbol(char *name, int val, symbol_table *curr)
{
    symbol *new, *nptr;
    int index;
    index = hash(name);
    if (curr->table[index] == NULL)
    {

        new = create_symbol(name, val);
        curr->table[index] = new;
    }
    else
    {
        int flag = 0;
        nptr = curr->table[index];
        if (strcmp(nptr->name, name) == 0)
        {
            nptr->value = val;
            flag = 1;
        }
        while (nptr->next != NULL && flag == 0)
        {
            if (strcmp(nptr->name, name) == 0)
            {
                nptr->value = val;
                flag = 1;
            }
            nptr = nptr->next;
        }
        if (nptr->next == NULL && flag == 0)
        {
            new = create_symbol(name, val);
            nptr->next = new;
        }
    }
}

// function to look for variables
int lookup_symbol(const char *name, symbol_table *curr)
{
    int retval;
    if (curr == NULL)
    {
        printf("ERROR: %s is not assigned\n", name);
        retval = -1;
        return retval;
    }
    else
    {
        int index = hash(name);
        symbol *nptr = curr->table[index];
        while (nptr != NULL)
        {
            if (strcmp(name, nptr->name) == 0)
            {
                retval = nptr->value;
                return retval;
            }
            nptr = nptr->next;
        }
        lookup_symbol(name, curr->prev);
    }
}
// function to make all pointer entries in symbol table NULL
symbol_table *initialize_symbol_table(symbol_table *new_scope)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        new_scope->table[i] = NULL;
    }
}

// function to begain scope
symbol_table *begin_scope(symbol_table *prev)
{
    symbol_table *new_scope = (symbol_table *)malloc(sizeof(symbol_table));
    if (new_scope != NULL)
    {
        new_scope->prev = prev;
    }
    new_scope = initialize_symbol_table(new_scope);
    return new_scope;
}

void print_symbol_table(symbol_table *curr)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (curr->table[i] == NULL)
        {
            printf("table[%d]-->null\n", i);
        }
        else
        {
            printf("table[%d]-->", i);
            symbol *nptr = curr->table[i];
            while (nptr != NULL)
            {
                printf(" %s->%d ", nptr->name, nptr->value);
                nptr = nptr->next;
            }
            printf("\n");
        }
    }
}

// function to free all entries end scope
symbol_table *end_scope(symbol_table *curr)
{
    symbol_table *retval;
    if (curr != NULL)
    {
        retval = curr->prev;
        int i = TABLE_SIZE - 1;
        symbol *nptr, *temp;

        while (i >= 0)
        {
            nptr = curr->table[i];
            while (nptr != NULL)
            {
                temp = nptr;
                nptr = nptr->next;
                free(temp);
            }
            i--;
        }
        free(curr);
    }
    else
    {
        retval = NULL;
        printf("ERROR: corresponding 'begin' is not found \n");
    }
    return retval;
}

int main()
{
    FILE *fptr;
    fptr = fopen("data.txt", "r");
    if (fptr == NULL)
    {
        printf("Error: File not opened\n");
        return 1;
    }

    char operation[10], name[MAX_NAME_LENGTH];
    int val;
    int i = 1;
    symbol_table *curr = NULL;
    fscanf(fptr, "%s", operation);
    if (strcmp(operation, "begin") == 0)
    {
        curr = begin_scope(curr);
        printf("-----------------------------------------\n");
        printf("begin scope: %d\n",i++);

        while (!feof(fptr))
        {
            fscanf(fptr, "%s", operation);
            if (strcmp(operation, "begin") == 0)
            {
                curr = begin_scope(curr);
                printf("-----------------------------------------\n");
                printf("begin scope: %d\n", i++);
            }
            else if (strcmp(operation, "end") == 0)
            {
                print_symbol_table(curr);
                curr = end_scope(curr);
                printf("end scope: %d\n",--i);
                printf("-----------------------------------------\n");
            }
            else if (strcmp(operation, "assign") == 0)
            {
                fscanf(fptr, "%s %d", name, &val);
                insert_symbol(name, val, curr);
                printf("   assign\n");
            }
            else if (strcmp(operation, "print") == 0)
            {
                fscanf(fptr, "%s", name);
                int value = lookup_symbol(name, curr);
                printf("The value of variable %s == %d\n", name, value);
                // printf("print\n");
            }
            else
            {
                printf("%s", operation);
            }
        }
    }
    else
    {
        printf("ERROR: No begin operation\n");
    }

    fclose(fptr);
    return 0;
}
