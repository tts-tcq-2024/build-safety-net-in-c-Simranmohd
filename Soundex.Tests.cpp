#include <gtest/gtest.h>
#include "Soundex.h"

TEST(SoundexTestsuite, ReplacesConsonantsWithAppropriateDigits) {
    char soundex[5];
    generateSoundex("AX", soundex);
    ASSERT_STREQ(soundex, "A200");
}

TEST(SoundexTestsuite, RetainsSoleLetterOfOneLetterWord) {
    char soundex[5];
    generateSoundex("A", soundex);
    ASSERT_STREQ(soundex, "A000");
}

TEST(SoundexTestsuite, PadsWithZerosToEnsureThreeDigits) {
    char soundex[5];
    generateSoundex("I", soundex);
    ASSERT_STREQ(soundex, "I000");
}

TEST(SoundexTestsuite, CombinesDuplicateEncodingsSeparatedByVowels) {
    char soundex[5];
    generateSoundex("Abfcg", soundex);
    ASSERT_STREQ(soundex, "A120");
}

TEST(SoundexTestsuite, UppercasesFirstLetter) {
    char soundex[5];
    generateSoundex("abcd", soundex);
    ASSERT_STREQ(soundex, "A123");
}

TEST(SoundexTestsuite, IgnoresCaseWhenEncodingConsonants) {
    char soundex[5];
    generateSoundex("BCDL", soundex);
    ASSERT_STREQ(soundex, "B234");
}

TEST(SoundexTestsuite, HandlesEmptyString) {
    char soundex[5];
    generateSoundex("", soundex);
    ASSERT_STREQ(soundex, "");
}

TEST(SoundexTestsuite, HandlesNullString) {
    char soundex[5];
    generateSoundex(nullptr, soundex);
    ASSERT_STREQ(soundex, "");
}

TEST(SoundexTestsuite, CombinesDuplicateEncodingsWithHAndWInBetween) {
    char soundex[5];
    generateSoundex("Ashcraft", soundex);
    ASSERT_STREQ(soundex, "A261");
}

TEST(SoundexTestsuite, CombinesDuplicateEncodingsWithHAndWInBetween2) {
    char soundex[5];
    generateSoundex("Tymczak", soundex);
    ASSERT_STREQ(soundex, "T520");
}

TEST(SoundexTestsuite, StopsAtThreeDigits) {
    char soundex[5];
    generateSoundex("Washington", soundex);
    ASSERT_STREQ(soundex, "W252");
}
