#ifndef BENCHMARK_H
#define BENCHMARK_H

// timer.c
double get_time();

// dictionary.c
struct list_t
{
    char* word;
    struct list_t* next;
};

typedef struct list_t list;

list* make_dictionary( const char* filename );
void search_dictionary( list* dictionary, const char* searchtxt );
void fuzzy_search_dictionary( list* dictionary,
                              const char* searchtxt,
                              double fuzz );
int dictionary_size( list* dictionary );

#endif // BENCHMARK_H
