#include <stdio.h>
#include <cs50.h>
#include <string.h>

bool validateCard(char *cardNum)
{
    // Check if card is not within 13 to 16 digits
    if (strlen(cardNum) < 13 || strlen(cardNum) > 16)
    {
        return false;
    }

    int sum1 = 0, sum2 = 0;
    char productStr[20];
    productStr[0] = '\0';

    // Looping cardNum from the second-to-last digit by 2 steps
    for (int i = strlen(cardNum) - 2; i >= 0; i -= 2)
    {
        int x = 2 * (int)(cardNum[i] - '0');
        char tempStr[2];
        sprintf(tempStr, "%d", x);

        // Forming a new string with the products
        strcat(productStr, tempStr);
    }

    // Looping productStr to calculate the sum of product's digits
    for (int i = 0; i <= strlen(productStr) - 1; i++)
    {
        sum1 += (int)(productStr[i] - '0');
    }

    // Looping cardNum from the last digit by 2 steps
    for (int i = strlen(cardNum) - 1; i >= 0; i -= 2)
    {
        sum2 += (int)(cardNum[i] - '0');
    }

    // if the final sum mod 10 is not equals to 0 then it's invalid
    if (!((sum1 + sum2) % 10 == 0))
    {
        return false;
    }

    return true;
}

bool isVisa(char *cardNum)
{
    if (strlen(cardNum) != 13 && strlen(cardNum) != 16)
    {
        return false;
    }

    if (cardNum[0] == '4')
    {
        return true;
    }

    return false;
}

bool isAmericanExpress(char *cardNum)
{
    if (strlen(cardNum) != 15)
    {
        return false;
    }

    if ((cardNum[0] == '3' && cardNum[1] == '4') || (cardNum[0] == '3' && cardNum[1] == '7'))
    {
        return true;
    }

    return false;
}

bool isMasterCard(char *cardNum)
{
    if (strlen(cardNum) != 16)
    {
        return false;
    }

    for (int i = 1; i <= 5; i++)
    {
        if (cardNum[0] == '5' && cardNum[1] == (int)(i + '0'))
        {
            return true;
        }
    }

    return false;
}

int main(void)
{
    // Take a long input from user
    long userInput = get_long("Number: ");

    // Declare a string variable
    char cardNum[20];

    // A state to represent is cardNum valid
    bool isValid;

    // Converting long to string and store it in cardNumStr
    sprintf(cardNum, "%ld", userInput);

    // Validate the card
    isValid = validateCard(cardNum);

    if (!isValid)
    {
        printf("INVALID\n");
    }
    else
    {
        if (isVisa(cardNum))
        {
            printf("VISA\n");
        }
        else if (isAmericanExpress(cardNum))
        {
            printf("AMEX\n");
        }
        else if (isMasterCard(cardNum))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}