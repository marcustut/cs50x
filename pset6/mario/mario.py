from cs50 import get_int

height = get_int("Height: ")

# Input validation
while height not in range(1, 9):
    height = int(input("Height: "))

# Looping through each row
for i in range(1, height+1):
    # Print the spaces padded in front
    for j in range(0, height-i):
        print(" ", end='')

    # Print the hashtags
    for j in range(0, i):
        print("#", end='')

    # Print the 2 spaces in between hashtags
    print("  ", end='')

    # Print the hashtags
    for j in range(0, i):
        print("#", end='')

    print()