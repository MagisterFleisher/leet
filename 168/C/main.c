#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <math.h>
#include <assert.h>


char
convertNumberToLetter(int num) {
    return (char) num + 64;
}


char*
test3_convertToTitle(int columnNumber) {
    const int base = 26;
    if(base > columnNumber) {
        char *excel_column = calloc(2, sizeof(char));
        excel_column[0] = convertNumberToLetter(columnNumber % base);
        (void) printf("%d - %s:\tcolumnNumber: %d\t%c\n", __LINE__, __FUNCTION__, columnNumber, excel_column[0]);
        excel_column[1] = '\0';
        return excel_column; 
    }
    const int exponent = log(columnNumber) / log(base);

    char *excel_column = calloc(exponent + 1, sizeof(char));
    int modulo = 0;
    int dividend = columnNumber;
    for(int i = exponent; i > 0; --i) {
        modulo = dividend % base;
        if(base == dividend) {
            (void) printf("grrrrrr\n");
            ``if (0 == dividend)
            {
                excel_column[0] = convertNumberToLetter(1);
            }
            else
            {
                excel_column[0] = convertNumberToLetter(dividend);
            }
            excel_column[exponent] = '\0';
            (void) printf("\t\t\t%s\n", excel_column);
            return excel_column;
        }
        if(0 == modulo) {
            excel_column[i - 1] = convertNumberToLetter(base);
            //(void) printf("%d - %s:\tindex: %d\tletter: %c\n", __LINE__, __FUNCTION__, i, convertNumberToLetter(base));
        } else {
            excel_column[i - 1] = convertNumberToLetter(modulo);
            //(void) printf("%d - %s:\tindex: %d\tletter: %c\n", __LINE__, __FUNCTION__, i, convertNumberToLetter(modulo));
        }
        (void) printf("dividend: %d\t", dividend);
        dividend /= base;
    }
    (void) printf("\n");
    
    excel_column[exponent] = '\0';
    (void) printf("%d - %s: Answer: %s\n", __LINE__, __FUNCTION__, excel_column);
    
    return excel_column;
}

char*
test2_convertToTitle(int columnNumber) {
    assert(1 <= columnNumber && columnNumber <= (pow(2, 31) -1));
    //(void) printf("\n%s\t%d:\tTest Value: %d\n\n", __FUNCTION__, __LINE__, columnNumber);
    const int base = 26;
    const int exponent = (int) (log((double) columnNumber) / log((double) base));
    /**
     * Allocate a sufficient number of digits for the number and the null terminator '\0'
     */
    if(base >= columnNumber) {
        char *returnChar = calloc(2, sizeof(char));
        (void) printf("\t\tExponent = 0\tShould return: %c\n", convertNumberToLetter(columnNumber));
        returnChar[0] = convertNumberToLetter(columnNumber);
        returnChar[1] = '\0';
        (void) printf("Answer: %s\n\n", returnChar);
        return returnChar;
    }

    char *returnChar = calloc((exponent+ 1), sizeof(char));

    int temp_total = columnNumber;
    int temp_modulo = 0;
    for(int index = exponent; index >= 1; --index) {
        temp_modulo = temp_total % base;
        if(0 == temp_modulo) {
            (void) printf("%d - %s:\tindex: %d\n", __LINE__, __FILE__, index);
            returnChar[index - 1] = convertNumberToLetter(temp_modulo + 26);    
        } else {
            (void) printf("%d - %s\tindex: %d", __LINE__, __FILE__, index);
            returnChar[index - 1] = convertNumberToLetter(temp_modulo);
        }
        (void) printf("%d - %s\tindex: %d\ttemp_modulo: %d", __LINE__, __FILE__, index, temp_modulo);
        temp_total = (temp_total - temp_modulo) / base;
        (void) printf("\n\t\ttemp_total: %d\ttemp_modulo: %d\n", temp_total, temp_modulo);
    }
    returnChar[exponent] = '\0';
    
    (void) printf("Answer: %s\n", returnChar);
    return returnChar;
}


char*
test_convertToTitle(int columnNumber) {
    assert(1 <= columnNumber && columnNumber <= (pow(2, 31) -1));
    (void) printf("\n%s\t%d:\tTest Value: %d\n", __FUNCTION__, __LINE__, columnNumber);
    /**
     * Find how many digits in number
     * The index of digits will be:
     * n such that: base^n+1 > x >= base^n
     * Thus the quantity of digits will be n+ 1
     */
    const long base = 26;
    long exponent = 0;
    
    /**  
     * Find the number of digits needed to express the resulting number in base n
     * For example, in base 10, the ones digits are 10^0
     * the tens digits are 10^1, the hundreds digits are 10^2 and so on
     * 
    */
   /** Note: pow yields a double */
    /* while((int) pow(base, exponent) < columnNumber) {
        exponent++;
    } */
    exponent = (long) logl(columnNumber) / logl(base);
    (void) printf("exponent: %ld\n", exponent);
    (void) printf("base (%ld) ^ exponent (%ld) : %ld\n", base, exponent, (long) pow(base, exponent));
    /**
     * Allocate a sufficient number of digits for the number and the null terminator '\0'
     */
    char *returnChar = calloc((exponent + 2), sizeof(char));
    /** For more than an exponent of 0, the algorithm should start with the largest
     * digit first.  Then subtract in order to reduce to the final digit.
    */
 /*   if(0 == exponent) {
        (void) printf("%s: %d\t\tExponent = 0\tShould return: %c\n", __FUNCTION__, __LINE__, convertNumberToLetter(columnNumber));
        returnChar[0] = convertNumberToLetter(columnNumber);
        returnChar[1] = '\0';
        (void) printf("Answer: %s\n\n", returnChar);
        return returnChar;
    }

    int current_column_number = columnNumber;
    for(int index = 1; index <= exponent + 1; index++) {
        int current_subtract = (int) pow((double) base, (double) index);
        (void) printf("%s: %d>\t Current Column Number %d\tCurrent Subtract %d\n", __FUNCTION__, __LINE__, current_column_number, current_subtract);
        current_column_number = current_column_number - current_subtract;
    }
 */
    
    returnChar[(int) exponent + 1] = '\0';
    return returnChar;
}

char*
convertToTitle(int columnNumber) {
    assert(1 <= columnNumber && columnNumber <= (pow(2, 31) -1));
    (void) printf("\n%s\t%d:\tTest Value: %d\n", __FUNCTION__, __LINE__, columnNumber);
    /**
     * Find how many digits in number
     * The index of digits will be:
     * n such that: base^n+1 > x >= base^n
     * Thus the quantity of digits will be n+ 1
     */
    const double base = 26;
    double exponent = 0;
    
    /**  
     * Find the number of digits needed to express the resulting number in base n
     * For example, in base 10, the ones digits are 10^0
     * the tens digits are 10^1, the hundreds digits are 10^2 and so on
     * 
    */
   /** Note: pow yields a double */
    /* while((int) pow(base, exponent) < columnNumber) {
        exponent++;
    } */
    exponent = (int) log(columnNumber) / log(base);
    /**
     * Allocate a sufficient number of digits for the number and the null terminator '\0'
     */
    char *returnChar = calloc((exponent + 2), sizeof(char));
    /** For more than an exponent of 0, the algorithm should start with the largest
     * digit first.  Then subtract in order to reduce to the final digit.
    */
    if(0 == exponent) {
        (void) printf("\t\tExponent = 0\tShould return: %c\n", convertNumberToLetter(columnNumber));
        returnChar[0] = convertNumberToLetter(columnNumber);
        returnChar[1] = '\0';
        (void) printf("Answer: %s\n\n", returnChar);
        return returnChar;
    }
    int current_column_number = columnNumber;
    (void) printf("exponent: %d\n", (int) exponent);

    for(int index = (int) exponent; index >= 1; index--) {
        (void) printf("Index: %d\tCurrent_column_number: %d\n", index, current_column_number);
        /**
         * Find the character value for current digits
         */
        int modulus = current_column_number % (int) base;

        (void) printf("\tcurrent_column_number: %d\n", current_column_number);
        (void) printf("\tmodulus: %d\n", modulus);
        
        if(0 == modulus && index == 2) {
            (void) printf("\tLetter equivalent: %c\n", convertNumberToLetter(base));
            returnChar[index - 1] = convertNumberToLetter(base);
            returnChar[(int) exponent + 1] = '\0';
            char *returnChar_smaller = calloc(exponent, sizeof(char));
            for(int index_i = 1; index_i < exponent; index_i++) {
                (void) printf("index_i: %d\nreturnChar: %c\n", index_i, returnChar[index_i]);
                returnChar_smaller[index_i - 1] = returnChar[index_i];
            }
            returnChar_smaller[(int) exponent -1] = '\0';
            free(returnChar);
            (void) printf("Answer is: %s\n", returnChar_smaller);
            return returnChar_smaller;
        } 
        if(0 == modulus) {
            (void) printf("\tLetter equivalent: %c\n", convertNumberToLetter(base + base));
            returnChar[index - 1] = convertNumberToLetter(modulus);
            current_column_number = current_column_number / base;
        } else {
            (void) printf("\tLetter equivalent: %c\n", convertNumberToLetter(modulus));
            returnChar[index - 1] = convertNumberToLetter(modulus);
            current_column_number = (current_column_number - modulus) / base;
        }
        (void) printf("New current column number: %d\n", current_column_number);
    }
    (void) printf("Answer: %s\n", returnChar);
    returnChar[(int) exponent + 1] = '\0';
    return returnChar;
}

int
main(int argument_count, char **argument_vector) {
    (void) printf("Test Leetcode 168.\n");
    free(test3_convertToTitle(1)); /* Answer : A*/

    free(test3_convertToTitle(28)); /* Answer : AB*/
    
    free(test3_convertToTitle(6)); /* Answer : F */
    free(test3_convertToTitle(288)); /* Answer: KB */
    free(test3_convertToTitle(701)); /* Answer: ZY */
    free(test3_convertToTitle(2147483647)); /*  */

    return EXIT_SUCCESS;
}