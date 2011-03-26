
#include "benchmark.h"
#include <stdio.h>

const int ITERATIONS = 1000;

void batch_search( list* dictionary, const char* word )
{
    printf( "Scoring word \"%s\"\t... ", word );
    int i;
    double total_time = 0.0, start, end;
    for( i = 0; i < ITERATIONS; ++i )
    {
        start = get_time();
        search_dictionary( dictionary, word );
        end = get_time();
        total_time += (end - start);
    }
    
    double mean_time = total_time / ITERATIONS;
    printf( "%1.3f ms\n", mean_time * 1000 );
}

int main( int argc, char** argv )
{
    list* dictionary = make_dictionary("american-words.txt");
    if( !dictionary ) return 0;
    
    printf( "Loaded %i words into dictionary.\n\n", dictionary_size(dictionary) );
    
    batch_search( dictionary, "cat" );
    batch_search( dictionary, "cious" );
    batch_search( dictionary, "pre" );
    batch_search( dictionary, "world" );
    
    return 0;
}
