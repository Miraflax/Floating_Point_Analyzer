float power_of_2(int exponent) {
        if (exponent == 0) {
                   return 1.0;
                      } else if (exponent > 0) {
                                 return 2 * power_of_2(exponent-1);
                                    } else {
                                               return power_of_2(exponent+1) / 2;
                                                  }
}

int main() {
    float gary = power_of_2(-3);
    printf("%f", gary);
    return 1;
} 
