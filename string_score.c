
#include <ctype.h>
#include <string.h>

#define STARTOFSTRING_BONUS 0.15
#define ACRONYM_BONUS       0.8
#define CONSECUTIVE_BONUS   0.6
#define SAMECASE_BONUS      0.1
#define MATCH_BONUS         0.1

double string_score_impl( const char* a, const char* b, double fuzziness );
double string_fuzzy_score( const char* a, const char* b, double fuzziness );

double string_score( const char* a, const char* b )
{
    return string_fuzzy_score( a, b, 0.0 );
}

double string_fuzzy_score( const char* a, const char* b, double fuzziness )
{
    return string_score_impl( a, b, fuzziness );
}

double string_score_impl( const char* a, const char* b, double fuzziness )
{
    /* If the original string is equal to the abbreviation, perfect match. */
    if( strcmp( a, b ) == 0 ) return 1.0;
    /* If the comparison string is empty, perfectly bad match. */
    if( strlen(b) == 0 ) return 0.0;
    
    size_t a_len = strlen(a);
    size_t b_len = strlen(b);
    
    /* Create a copy of original string, so that we can manipulate it. */
    const char* aptr = a;
    
    double score = 0.0;
    double final_score = 0.0;
    
    int c;
    size_t c_index;
    char c_cases[] = "  ";
    
    double fuzzies = 1.0;
    
    /* Walk through abbreviation and add up scores. */
    size_t i;
    for( i = 0; i < b_len; ++i )
    {
        /* Find the first case-insensitive match of a character. */
        c = b[i];
        c_cases[0] = (char)toupper(c);
        c_cases[1] = (char)tolower(c);
        c_index = strcspn( aptr, c_cases );
        
        /* Set base score for any matching char. */
        if( c_index == strlen(aptr) )
        {
            if( fuzziness > 0.0 )
            {
                fuzzies += 1.0 - fuzziness;
                continue;
            }
            return 0.0;
        }
        else
            score += MATCH_BONUS;
        
        /* Same-case bonus. */
        if( aptr[c_index] == c )
            score += SAMECASE_BONUS;
        
        /* Consecutive letter & start-of-string bonus. */
        if( c_index == 0 )
        {
            /* Increase the score when matching first character of the
               remainder of the string. */
            score += CONSECUTIVE_BONUS;
            if( i == 0 )
                /* If match is the first char of the string & the first char
                   of abbreviation, add a start-of-string match bonus. */
                final_score += STARTOFSTRING_BONUS;
        }
        else if( aptr[c_index - 1] == ' ' )
            /* Acronym Bonus
             * Weighing Logic: Typing the first character of an acronym is as
             * if you preceded it with two perfect character matches. */
            score += ACRONYM_BONUS;
        
        /* Left trim the already matched part of the string.
           (Forces sequential matching.) */
        aptr += c_index + 1;
    }
    
    score /= (double)b_len;
    
    /* Reduce penalty for longer strings. */
    final_score += ( ( score * ( (double)b_len / (double)a_len) ) + score ) / 2.0;
    final_score /= fuzzies;
    
    return ( final_score > 1.0 ) ? 1.0 : final_score;
}

