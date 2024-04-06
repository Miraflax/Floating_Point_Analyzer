#include <stdio.h>

#include "fp_analyzer.h"

void print_bits(unsigned INTEGRAL input_bits, int length) { 
    //do I have an issue in that ONE is too long?
    for(int i = length - 1; i >=0; --i) {
        putchar((((ONE << i) & input_bits) != 0) + '0');
    }
    putchar('\n');
}

void print_components(Converter converter) {
    printf("%f\n", converter.inputf);
    printf("All bits : ");
    print_bits(converter.bits, FP_SIZE);
    printf("Sign: ");
    print_bits(converter.data.sign, COMPONENTS_SIGN);
    printf("Exponent: ");
    print_bits(converter.data.exponent, COMPONENTS_EXPONENT); 
    printf("Mantissa: ");
    print_bits(converter.data.mantissa, COMPONENTS_MANTISSA);
} 

FP_TYPE power_of_2(int exponent) {
    if (exponent == 0) {
       return 1.0;
   } else if (exponent > 0) { 
       return 2 * power_of_2(exponent-1);  
   } else {
       return power_of_2(exponent+1) / 2;
   }
}

void print_normalized(Converter input) {
    int sign;
    if (input.data.sign) {
        sign = -1;
    } else {
        sign = 1;
    }
    
    int true_exponent = (int) input.data.exponent - BIAS;
    int abs_exponent;

    if (true_exponent < 0) {
        abs_exponent = -true_exponent;
    } else {
        abs_exponent = true_exponent;
    }
    
    FP_TYPE mantissa_value = ((FP_TYPE) input.data.mantissa / power_of_2(COMPONENTS_MANTISSA));
    FP_TYPE significand = (mantissa_value + 1);
    
    unsigned long positive_two_power = (unsigned long) power_of_2(abs_exponent);
    FP_TYPE right_operand = power_of_2(true_exponent);
    FP_TYPE final_value = sign * significand * right_operand;

    printf("Original value:\n");
    printf("(-1)^{%u} x (1 + %.6f) x 2^{%u - %d}\n", input.data.sign, mantissa_value, input.data.exponent, BIAS);
    printf("  = %d x %.6f x 2^{%d}\n", sign, significand, true_exponent); 
    if (true_exponent < 0) {
        if (sign < 0) {
            printf("  = %d x %.6f x 1/%lu\n", sign, significand, positive_two_power);
            printf("  = %.45f\n", final_value);
        } else {
            printf("  = %.6f x 1/%lu\n", significand, positive_two_power);
            printf("  = %.45f\n", final_value); 
        }
    } else {     
        if (sign < 0) {
            printf("  = %d x %.6f x %lu\n", sign, significand, positive_two_power);
            printf("  = %.45f\n", final_value); 
        } else { 
            printf("  = %.6f x %lu\n", significand, positive_two_power);
            printf("  = %.45f\n", final_value); 
        }
    }
}
   
void print_denormalized(Converter input) {
    int sign;
    if (input.data.sign) {
        sign = -1;
    } else {
        sign = 1;
    }
    FP_TYPE mantissa_value = ((FP_TYPE) input.data.mantissa / power_of_2(COMPONENTS_MANTISSA));
    FP_TYPE left_operand = mantissa_value * sign;
    FP_TYPE true_right_operand = power_of_2(DENORM_BIAS);
    double denominator_right_operand = (double) power_of_2(-DENORM_BIAS);
    FP_TYPE final_value = sign * mantissa_value * true_right_operand;

    printf("Original value:\n");
    printf("(-1)^{%u} x %lf x 2^{1 - %d}\n", input.data.sign, mantissa_value, BIAS);
    printf("  = %d x %.6f x 2^{%d}\n", sign, mantissa_value, DENORM_BIAS);
    printf("  = %lf x 1/%.0lf\n", left_operand, denominator_right_operand);
    printf("  = %.45f\n", final_value);
}

void print_reconstitution(Converter input) {
    if (input.data.exponent) {
        print_normalized(input);
    } else {
        print_denormalized(input);
    }
}
