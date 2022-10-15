#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

char* known_names[] = {
    "Name1",
    "Name2",
    "Name3",
};

char* unknown_names[] = {
    "A",
    "B",
    "C",
    "D",
    "E",
};

void output_distances(uint64_t a, uint64_t b, uint64_t c);
int bits_not_matching(uint64_t a, uint64_t b);
double find_distance(uint64_t a, uint64_t b);

int main(int argc, char** argv) {

    uint64_t known1 = 123456789;
    uint64_t known2 = 123456789;
    uint64_t known3 = 123456789;

    /* Unknown iris codes */
    uint64_t unknown1 = 123456789;
    uint64_t unknown2 = 123456789;
    uint64_t unknown3 = 123456789;
    uint64_t unknown4 = 123456789;
    uint64_t unknown5 = 123456789;

    uint64_t known_iris_codes[] = {
        known1,
        known2,
        known3
    };

    uint64_t unknown_iris_codes[] = {
        unknown1,
        unknown2,
        unknown3,
        unknown4,
        unknown5
    };
    
    uint64_t bit_diffs[3][5];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            bit_diffs[i][j] = bits_not_matching(known_iris_codes[i], unknown_iris_codes[j]);
        }
    }

    double distances[3][5];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            distances[i][j] = find_distance(known_iris_codes[i], unknown_iris_codes[j]);
        }
    }

    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf("%s:\n", known_names[i]);
        for (int j = 0; j < 5; j++) {
            printf("bit_diff(%s, %s) = %lu\t\t", known_names[i], unknown_names[j], bit_diffs[i][j]);
            printf("d(%s, %s) = %f\n", known_names[i], unknown_names[j], distances[i][j]);
        }
    }

    
    return 0;
}

void output_distances(uint64_t a, uint64_t b, uint64_t c) {
    printf("d(Alice, Bob) = %d / 64 = %f\n", bits_not_matching(a, b), find_distance(a, b));
    printf("d(Alice, Charlie) = %d / 64 = %f\n", bits_not_matching(a, c), find_distance(a, c));
    printf("d(Bob, Charlie) = %d / 64 = %f\n", bits_not_matching(b, c), find_distance(b, c));
}


int bits_not_matching(uint64_t a, uint64_t b) {
    uint64_t xor_ab = a ^ b;
    int bits_not_matching = 0;
    while (xor_ab != 0) {
        if (xor_ab & 1) {
            bits_not_matching++;
        }
        xor_ab = xor_ab >> 1;
    }
    return bits_not_matching;
}

double find_distance(uint64_t a, uint64_t b) {
    int diff = bits_not_matching(a, b);
    double distance = (double)diff / 64.0;
    return distance;
}
