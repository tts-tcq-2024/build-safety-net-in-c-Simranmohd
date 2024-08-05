#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>

char getSoundexCode(char c) {
    static const char soundexTable[26] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '2', '2', '4', '5', '5', '0', '1', '2', '6', '2', '3', '0', '1', '0', '2', '0', '2'
    };

    c = toupper(c);
    if (c < 'A' || c > 'Z') {
        return '0';
    }

    return soundexTable[c - 'A'];
}

char extractAndCapitalizeInitial(const char *name) {
    return toupper(name[0]);
}

void fillWithZeros(char *soundex, int *index) {
    while (*index < 4) {
        soundex[(*index)++] = '0';
    }
    soundex[4] = '\0';
}

int isCodeDuplicate(char currentCode, char previousCode) {
    return currentCode == previousCode && currentCode != '0';
}

void appendSoundexCode(char *soundex, int *index, char code) {
    if (*index < 4) {
        soundex[(*index)++] = code;
    }
}

int shouldEncode(char currentCode, char lastCode) {
    return currentCode != '0' && !isCodeDuplicate(currentCode, lastCode);
}

void updateLastCode(char currentCode, char *lastCode) {
    if (currentCode != '0') {
        *lastCode = currentCode;
    }
}

void processCharacter(char character, char *soundex, int *index, char *lastCode) {
    char currentCode = getSoundexCode(character);
    if (shouldEncode(currentCode, *lastCode)) {
        appendSoundexCode(soundex, index, currentCode);
    }
    updateLastCode(currentCode, lastCode);
}

void processRemainingLetters(const char *name, char *soundex, int *index, char *lastCode) {
    for (int i = 1; name[i] != '\0'; i++) {
        processCharacter(name[i], soundex, index, lastCode);
    }
}

int isNullOrEmpty(const char *name) {
    return name == NULL || strlen(name) == 0;
}

int isInvalidInput(const char *name, char *soundex) {
    return soundex == NULL || isNullOrEmpty(name);
}

void handleEmptyOrNullInput(const char *name, char *soundex) {
    if (isInvalidInput(name, soundex)) {
        soundex[0] = '\0';
    }
}

void generateSoundex(const char *name, char *soundex) {
    handleEmptyOrNullInput(name, soundex);
    if (soundex[0] == '\0') {
        return;
    }

    soundex[0] = extractAndCapitalizeInitial(name);
    int index = 1;
    char lastCode = getSoundexCode(name[0]);

    processRemainingLetters(name, soundex, &index, &lastCode);
    fillWithZeros(soundex, &index);
}

#endif // SOUNDEX_H



