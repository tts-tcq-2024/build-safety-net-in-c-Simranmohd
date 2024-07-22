

#include "Soundex.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define MAX_CODE_LENGTH 4

char getSoundexCode(char c) {        // Function to map a character to its corresponding Soundex digit
    c = toupper(c);
    switch (c) {
        case 'B': case 'F': case 'P': case 'V': return '1';
        case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z': return '2';
        case 'D': case 'T': return '3';
        case 'L': return '4';
        case 'M': case 'N': return '5';
        case 'R': return '6';
        default: return '0'; // For A, E, I, O, U, H, W, Y
    }
}
// Function to remove vowels and specific consonants
void removeVowelsAndSpecificConsonants(const char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        char c = toupper(input[i]);
        if (c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U' && c != 'Y' && c != 'H' && c != 'W') {
            output[j++] = c;
        }
    }
    output[j] = '\0';
}

// Function to encode the string to Soundex digits
void encodeToSoundexDigits(const char *input, char *output) {
    int j = 0;
    char lastDigit = '\0';
    for (int i = 0; input[i] != '\0'; i++) {
        char currentDigit = getSoundexCode(input[i]);
        if (currentDigit != '0' && currentDigit != lastDigit) {
            output[j++] = currentDigit;
            lastDigit = currentDigit;
        }
    }
    output[j] = '\0';
}

// Function to generate the Soundex code
void generateSoundexCode(const char *input, char *output) {
    // Retain the first letter and convert to uppercase
    output[0] = toupper(input[0]);

    // Remove vowels and specific consonants
    char filteredInput[100];
    removeVowelsAndSpecificConsonants(input, filteredInput);

    // Encode to Soundex digits
    char encodedDigits[100];
    encodeToSoundexDigits(filteredInput, encodedDigits);

    // Copy the encoded digits to the output
    strncpy(output + 1, encodedDigits, MAX_CODE_LENGTH - 1);

    // Pad with zeros if necessary
    int len = strlen(output);
    while (len < MAX_CODE_LENGTH) {
        output[len++] = '0';
    }

    // Null-terminate the output string
    output[MAX_CODE_LENGTH] = '\0';
}

// Function to run tests
void runTests() {
    struct {
        const char *input;
        const char *expected;
    } testCases[] = {
        {"Example", "E251"},
        {"Ashcraft", "A261"},
        {"Tymczak", "T522"},
        {"Robert", "R163"},
        {"Rupert", "R163"},
        {"Rubin", "R150"},
        {"Soundex", "S532"},
        {"Sownteks", "S532"},
        {"Ekzampul", "E251"},
        {"Lissajous", "L222"},
        {"Smith", "S530"},
        {"Schmit", "S530"}
    };

    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    for (int i = 0; i < numTests; i++) {
        char output[MAX_CODE_LENGTH + 1];
        generateSoundexCode(testCases[i].input, output);
        printf("Input: %s, Expected: %s, Output: %s\n", testCases[i].input, testCases[i].expected, output);
    }
}

int main() {
    runTests();
    return 0;
}
