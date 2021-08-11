from cs50 import get_string


# Parse letters from text
def getLetters(text):
    # Set a counter variable
    count = 0
    
    # For every character in text
    for char in text:
        # If character is an alphabet
        if char.isalpha():
            # Increment counter
            count += 1

    return count


# Parse words from text
def getWords(text):
    # Set a counter variable
    count = 0
    
    # For every character in text
    for char in text:
        # If character is a space
        if char.isspace():
            # Increment counter
            count += 1

    # Num of spaces is one lesser than total words
    return count + 1


# Parse sentences from text
def getSentences(text):
    # Set a counter variable
    count = 0
    
    # For every character in text
    for char in text:
        # If character is a '.' or '!' or '?'
        if char == '.' or char == '!' or char == '?':
            # Increment counter
            count += 1

    return count


# Calculate letters per hundred words
def getLettersPerHundredWords(letters, text):
    return (letters / words) * 100


# Calculate sentences per hundred words
def getSentencesPerHundredWords(sentences, text):
    return (sentences / words) * 100


# Calculate ColemanLiauIndex
def countColemanLiauIndex(lphw, sphw):
    return (0.0588 * lphw) - (0.296 * sphw) - 15.8


if __name__ == "__main__":
    # Getting user input
    text = get_string("Text: ")

    # Parsing the text
    letters = getLetters(text)
    words = getWords(text)
    sentences = getSentences(text)

    # Calculating letters and senteces per hundered words
    lphw = getLettersPerHundredWords(letters, words)
    sphw = getSentencesPerHundredWords(sentences, words)

    # Calculate the coleman-liau index
    grade = round(countColemanLiauIndex(lphw, sphw))

    # Formatting output for different grade
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade ", grade)
