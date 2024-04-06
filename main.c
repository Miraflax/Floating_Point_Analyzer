/*
 * Usage: make clean && make 
 * ./fp_analyzer_f or ./fp_analyzer_d
 * for nan or inf
 * ./fp_analyzer_f special or ./fp_analyzer_f special
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fp_analyzer.h"

int main(int argc, char * agrv[]) { 
    Converter object;
    FP_TYPE input;

    if (argc > 1) {
        FP_TYPE special[] = {1.0/0.0, -1.0/0.0, NAN, -NAN};
        int length = sizeof(special) / sizeof(special[0]);
        for (int i = 0; i < length; i++) {
            object.inputf = special[i];
            print_components(object);
            printf("\n");
        }
    return EXIT_SUCCESS;
    } 
            
    printf("Please enter a floating-point number or q to quit.\n> ");
    while(scanf(FORMAT_FLOATING, &input)) {
        object.inputf = input;
        print_components(object);
        print_reconstitution(object);
        printf("> ");
    }

    return EXIT_SUCCESS;
}
