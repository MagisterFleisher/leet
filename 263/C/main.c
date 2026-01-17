#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool
isUgly(int n) {
    bool ugly = false;
    if(2 > n) {
        ugly = true;
        (void) printf("%s %d] Init number? %d\n", __FUNCTION__, __LINE__,  n);
        return ugly;
    }
    (void) printf("%s %d] Init number? %d\n", __FUNCTION__, __LINE__,  n);

    while (0 == n % 2) {
        (void) printf("%s %d] Init number? %d\n", __FUNCTION__, __LINE__,  n);
        n = n / 2; }
    while (0 == n % 3) {
        (void) printf("%s %d] Init number? %d\n", __FUNCTION__, __LINE__,   n); 
        n = n / 3; }
    while (0 == n % 5) {
        (void) printf("%s %d] Init number? %d\n", __FUNCTION__, __LINE__,   n);
        n = n / 5; }

    (void) printf("%s %d] Init number? %d\n", __FUNCTION__, __LINE__,  n);
    
    if(1 == n) {
        (void) printf("%s %d] Init number? %d\n", __FUNCTION__, __LINE__,  n);
        ugly = true; }
    
    return ugly;
}

int
main(int argument_count, char **argument_vector) {
    (void) printf("is ugly: %d\n", isUgly(6));
}