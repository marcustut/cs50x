#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <cs50.h>

// Prototypes
int getLetters(string text);
int getWords(string text);
int getSentences(string text);
double getLettersPerHundredWords(int letters, int words);
double getSentencesPerHundredWords(int sentences, int words);
double countColemanLiauIndex(double lphw, double sphw);

int main(void)
{
    // Getting user input
    string text = get_string("Text: ");

    // Parsing the text
    int letters = getLetters(text);
    int words = getWords(text);
    int sentences = getSentences(text);

    // Calculating letters and senteces per hundered words
    double lphw = getLettersPerHundredWords(letters, words);
    double sphw = getSentencesPerHundredWords(sentences, words);

    // Calculate the coleman-liau index
    int grade = round(countColemanLiauIndex(lphw, sphw));

    // Formatting output for different grade
    if (grade < 1)
    {
        printf("Before Grade 1");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", grade);
    }

    // Prints a new line
    printf("\n");
}

// Calculate letters from the text
int getLetters(string text)
{
    int count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }

    return count;
}

// Calculate words from the text
int getWords(string text)
{
    int count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }

    return count + 1;
}

// Calculate sentences from the text
int getSentences(string text)
{
    int count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            count++;
        }
    }

    return count;
}

// Calculate letters per hundred words
double getLettersPerHundredWords(int letters, int words)
{
    // Casting int to double before calculation
    return ((double) letters / words) * 100;
}

// Calculate sentences per hundred words
double getSentencesPerHundredWords(int sentences, int words)
{
    return ((double) sentences / words) * 100;
}

// Calculate Coleman-Liau Index
double countColemanLiauIndex(double lphw, double sphw)
{
    return (0.0588 * lphw) - (0.296 * sphw) - 15.8;
}