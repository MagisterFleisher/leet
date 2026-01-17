#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>


/**
 * @brief Gives the length of a string.  Simple pointer arithmatic implementation
 * @param string Double pointer, i.e. char array
 * @return size_t - string length
 */
size_t
strLenMine(char string[]) {
    assert(NULL != string);
    size_t length = 0;
    if('\0' == string[0]) {
        return length;
    }
    char *char_ptr;
    char_ptr = &string[0];
    while('\0' != *char_ptr) {
        length++;
        char_ptr++;
    }
    return length;
}

char*
longestCommonPrefix(char** strs, int strsSize)  {
    assert(0 < strsSize);
    if(1 == strsSize) {
        char *longest_common_prefix = malloc(sizeof(char) * (strlen(strs[0]) + 1));
        (void) memcpy(longest_common_prefix, strs[0], strlen(strs[0]) + 1);
        return longest_common_prefix;
    }
    if('\0' == strs[0][0]) {
        char *longest_common_prefix = malloc(sizeof(char));
        longest_common_prefix[0] = '\0';
        return longest_common_prefix;
    }

    char prefix_buffer[201];
    int length = 0;
    char current_char = strs[0][length];
    bool same = true;
    while(same && '\0' != current_char) {
        for(int index = 1; index < strsSize; index++) {
            if(strs[index][length] != current_char) {
                same = false;
            }
        }
        if(same) {
            prefix_buffer[length] = current_char;
            length++;
            current_char = strs[0][length];
        }
    }

    char *longest_common_prefix = malloc((sizeof(char)* length) + 1);
    for(int i = 0; i < length; i++) {
        longest_common_prefix[i] = prefix_buffer[i];
    }
    longest_common_prefix[length] = '\0';
    return longest_common_prefix;
}

/**
 * ["flower","flow","flight"]
 * ["dog","racecar","car"]
 */

int
main(int argument_count, char **argument_vector) {
    char *string_set[] = { "flower", "flow", "flight"};

    char *lcp = longestCommonPrefix(string_set, 3);

    (void) printf("%s\n\n", lcp);

    (void) free(lcp);

    for(int index = 0; index < 3; index++) {
        clock_t start_time = clock();
        size_t string_len_mine = strLenMine(string_set[index]);
        clock_t end_time = clock();
        float performance_mine = ((float) (end_time - start_time)) / CLOCKS_PER_SEC;
        (void) printf("%s : %ju - My function, time: %f\n", string_set[index], string_len_mine, performance_mine);
        (void) printf("%s : %zu - Built in\n", string_set[index], strlen(string_set[index]));
    }

    return EXIT_SUCCESS;
}