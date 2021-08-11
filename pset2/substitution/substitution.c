#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

// Global Variables
string ENCRYPT_KEY;

// Prototypes
string cipher(string plainText);
char substitute(char charToSubstitute);
string toUppercase(string text);
bool validateKey(string encryptKey);

int main(int argc, char *argv[])
{
    // Check if taking only 1 command-line argument
    if (argc != 2)
    {
        printf("substitution only accept one valid encrypt key.\n");
        return 1;
    }
    else
    {
        // Set the first command-line argument as the encrptKey
        ENCRYPT_KEY = toUppercase(argv[1]);

        // Check if the ENCRYPT_KET is valid
        if (!validateKey(ENCRYPT_KEY))
        {
            printf("Invalid encrypt key.\n");
            return 1;
        }

        // Get user input
        string plainText = get_string("plaintext:  ");

        // Print the ciphered text
        printf("ciphertext: %s\n", cipher(plainText));
    }

    return 0;
}

// Cipher the plainText given
string cipher(string plainText)
{
    // Allocate memory for the cipheredText
    char *cipheredText = malloc(strlen(plainText) + 1);

    for (int i = 0; i < strlen(plainText); i++)
    {
        // if the character is an alphabet then substitute
        if (isalpha(plainText[i]))
        {
            cipheredText[i] = substitute(plainText[i]);
        }
        else
        {
            cipheredText[i] = plainText[i];
        }
    }

    // Add a terminating byte to the string
    cipheredText[strlen(plainText)] = '\0';

    return cipheredText;
}

// Substitute the given character
char substitute(char charToSubstitute)
{
    int distance;

    // Check if the character is lowercase
    if (islower(charToSubstitute))
    {
        // Calculate the distance
        distance = charToSubstitute - 'a';
        // Return the lowecase letter of encrypted key
        return tolower(ENCRYPT_KEY[distance]);
    }
    else
    {
        distance = charToSubstitute - 'A';
        return ENCRYPT_KEY[distance];
    }
}

string toUppercase(string text)
{
    // Allocate memory for new string
    char *newStr = malloc(strlen(text) + 1);

    // Checking every character of the text
    for (int i = 0; i < strlen(text); i++)
    {
        // If the character is an alphabet and is lowercase
        if (isalpha(text[i]) && islower(text[i]))
        {
            // Converts it to uppercase and assign to newStr at position i
            newStr[i] = toupper(text[i]);
        }
        else
        {
            newStr[i] = text[i];
        }
    }

    // Adds a null terminating byte to the new string
    newStr[strlen(text)] = '\0';

    return newStr;
}

bool validateKey(string encryptKey)
{
    // Check if the encryptKey is 26 digits long
    if (strlen(encryptKey) != 26)
    {
        printf("Encrypt key must contain 26 characters.\n");
        return false;
    }

    // Check if invalid characters are in the key
    for (int i = 0; i < strlen(encryptKey); i++)
    {
        if (!isalpha(encryptKey[i]))
        {
            printf("Encrypt key must only contains alphabets.\n");
            return false;
        }
    }

    // Check if duplicate characters are in the key
    for (int i = 0; i < strlen(encryptKey); i++)
    {
        for (int j = 0; j < strlen(encryptKey); j++)
        {
            if (j == i)
            {
                continue;
            }

            if (encryptKey[i] == encryptKey[j])
            {
                printf("Encrypt key must not contain duplicated alphabet.\n");
                return false;
            }
        }
    }

    // Returns true if none of the scenario above occured.
    return true;
}