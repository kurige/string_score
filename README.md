string_score
=============

Ported from version 0.1.10 of Joshaven Potter's [string_score][0].

`string_score` is a string ranking algorithm that produced a number between 0 and 1 representing the similarity between two strings.

Usage
-----

    #include "string_score.h"
    #include <string.h>
    #include <stdio.h>

    int main( int argc, char** argv )
    {
        char* a = argv[1];
        char* b = argv[2];
        printf( "normal match: %1.10lf\n", string_score( a, b ) );
        printf( "fuzzy match:  %1.10lf\n", string_fuzzy_score( a, b, 0.5 ) );
        return 0;
    }

(See the original [string_score][0] javascript code for details on the algorithm.)

Running the benchmark
---------------------

To run the benchmark `cd` into the `string_score/benchmark` folder and run the following commands:

    $ gcc -Wall -O3 -I.. ../string_score.c *.c -o benchmark
    $ ./benchmark

Benchmark results
-----------------

Core 2 Duo T6600 Laptop  
Windows 7 x64 (cygwin)

    $ ./benchmark
    Loaded 11925 words into dictionary.

    Scoring word "cat"      ... 2.175 ms
    Scoring word "cious"    ... 2.112 ms
    Scoring word "pre"      ... 2.043 ms
    Scoring word "world"    ... 1.818 ms

2.8GHz Intel Core i5  
MaxOSX 10.6.7

    $ ./benchmark
    Loaded 11925 words into dictionary.
    
    Scoring word "cat"      ... 1.042 ms
    Scoring word "cious"    ... 1.101 ms
    Scoring word "pre"      ... 1.003 ms
    Scoring word "world"    ... 0.812 ms

Misc.
-----

License : [MIT license](http://www.opensource.org/licenses/mit-license.php)

Author : Christopher Gateley | [christopher.gateley@gmail.com](mailto:christopher.gateley@gmail.com)

[0]: http://github.com/joshaven/string_score