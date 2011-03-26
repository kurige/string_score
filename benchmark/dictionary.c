
#include "benchmark.h"
#include "string_score.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024

list* new_entry( const char* word )
{
    list* retval = (list*)malloc(sizeof(list));
    retval->word = (char*)calloc( strlen(word)+1, sizeof(*word) );
    strcpy( retval->word, word );
    retval->next = NULL;
    return retval;
}

void add_word( list* head, const char* word )
{
    list* p = head;
    while( p->next != NULL )
        p = p->next;
    
    list* new = new_entry(word);
    p->next = new;
}

int dictionary_size( list* dictionary )
{
    list* p = dictionary;
    int count = 0;
    while(p) { count++; p = p->next; }
    return count;
}

list* make_dictionary( const char* filename )
{
    char line[MAXLEN];
    list* head = new_entry("");
    
    FILE* fp;
    if( !(fp = fopen( filename, "r" ) ) )
    {
        printf( "Failed to open file \"%s\".", filename );
        return NULL;
    }
    while( fgets( line, MAXLEN, fp ) != NULL )
    {
        *(strchr( line, '\n' )) = '\0';
        add_word( head, line );
    }
    fclose(fp);
    
    return head;
}

void search_dictionary( list* dictionary, const char* searchtxt )
{
    list* p = dictionary;
    while(p)
    {
        string_score( p->word, searchtxt );
        p = p->next;
    }
}

void fuzzy_search_dictionary( list* dictionary,
                              const char* searchtxt,
                              double fuzz )
{
    list* p = dictionary;
    while(p)
    {
        string_fuzzy_score( p->word, searchtxt, 0.0 );
        p = p->next;
    }
}
