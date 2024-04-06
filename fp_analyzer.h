#ifdef DOUBLE
#define FP_TYPE double
#define FP_SIZE 64
#define INTEGRAL long
#define COMPONENTS_SIGN 1 
#define COMPONENTS_EXPONENT 11
#define COMPONENTS_MANTISSA 52
#define FORMAT_FLOATING "%lf"
#define ONE 1lu
#define BIAS 1023
#define DENORM_BIAS -1022
#else
#define FP_TYPE float
#define FP_SIZE 32
#define INTEGRAL int
#define COMPONENTS_SIGN 1
#define COMPONENTS_EXPONENT 8
#define COMPONENTS_MANTISSA 23
#define FORMAT_FLOATING "%f"
#define ONE 1u
#define BIAS 127
#define DENORM_BIAS -126
#endif

typedef struct {
    unsigned INTEGRAL mantissa : COMPONENTS_MANTISSA;
    unsigned INTEGRAL exponent : COMPONENTS_EXPONENT;
    unsigned INTEGRAL sign : COMPONENTS_SIGN;
} Components;

typedef union {
    FP_TYPE inputf;
    unsigned INTEGRAL bits;
    Components data;
} Converter;

void print_bits(unsigned INTEGRAL input, int size);
void print_components(Converter input);
void print_normalized(Converter input);
void print_denormalized(Converter input);
void print_reconstitution(Converter input);
FP_TYPE power_of_2(int exponent);
