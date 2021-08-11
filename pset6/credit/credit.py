from cs50 import get_int


def validateCard(cardNum):
    # Check if card is not within 13 to 16 digits
    if len(cardNum) < 13 or len(cardNum) > 16:
        return False

    sum1, sum2 = 0, 0
    productStr = ""

    # Looping cardNum from the second-to-last digit by 2 steps
    for i in range(len(cardNum) - 2, -1, -2):
        # Multiply the numeric value by 2
        x = 2 * (ord(cardNum[i]) - ord('0'))

        # Concatenate x to productStr
        productStr += str(x)

    # Sum the individual digit in productStr
    for productChar in productStr:
        sum1 += (ord(productChar) - ord('0'))

    # Looping cardNum from the last digit by 2 steps
    for i in range(len(cardNum) - 1, -1, -2):
        # Add the sum numeric value to sum2
        sum2 += (ord(cardNum[i]) - ord('0'))

    # Check if both sums mod 10 is 0
    if (sum1 + sum2) % 10 == 0:
        # If yes then it's valid
        return True

    # Else it's invalid
    return False


def isVisa(cardNum):
    if len(cardNum) != 13 and len(cardNum) != 16:
        return False

    if cardNum[0] == '4':
        return True

    return False


def isAmericanExpress(cardNum):
    if len(cardNum) != 15:
        return False

    if (cardNum[0] == '3' and cardNum[1] == '4') or (cardNum[0] == '3' and cardNum[1] == '7'):
        return True

    return False


def isMasterCard(cardNum):
    if len(cardNum) != 16:
        return False

    for i in range(1, 6):
        if cardNum[0] == '5' and cardNum[1] == chr(i + ord('0')):
            return True

    return False


if __name__ == "__main__":
    userInput = str(get_int("Number: "))

    if not validateCard(userInput):
        print("INVALID")
    else:
        if isVisa(userInput):
            print("VISA")
        elif isMasterCard(userInput):
            print("MASTERCARD")
        elif isAmericanExpress(userInput):
            print("AMEX")
        else:
            print("INVALID")
