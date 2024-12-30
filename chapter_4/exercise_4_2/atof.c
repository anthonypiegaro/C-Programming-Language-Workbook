#include <stdio.h>
#include <ctype.h>

#define MAX_SIZE 1000
#define POS 1
#define NEG 0

double atof(char s[]);

int main() {
    printf("%f\n", atof("+12E+2"));

    return 0;
}

double atof(char s[]) {
    double val, power;
    int i, sign, expo, exposign, power_of_10;

    for (i = 0; isspace(s[i]); ++i)
        ;
    
    sign = (s[i] == '-') ? NEG : POS;

    if (s[i] == '-' || s[i] == '+') {
        ++i;
    }

    for (val = 0.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
    }

    if (s[i] == '.') {
        ++i;
        for (power = 1.0; isdigit(s[i]); ++i) {
            val = 10.0 * val + (s[i] - '0');
            power *= 10.0;
        }

        val /= power;
    }

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        exposign = (s[i++] == '-') ? NEG : POS;

        for (expo = 0; isdigit(s[i]); ++i) {
            expo = 10 * expo + (s[i] - '0');
        }

        for (power_of_10 = 1; expo > 0; --expo) {
            power_of_10 *= 10;
        }

        if (exposign == NEG) {
            val /= power_of_10;
        } else {
            val *= power_of_10;
        }
    }

    return (sign == NEG) ? -val : val;
}
