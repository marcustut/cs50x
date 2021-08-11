import csv
from cs50 import SQL
from sys import argv, exit


# Parse a given name and return the first, middle, last name
def parseName(name):
    # If 3 words in name
    if len(name.split()) == 3:
        # Return first, middle, last
        return (name.split()[0], name.split()[1], name.split()[2])
    else:
        # Else return first, None, last
        return (name.split()[0], None, name.split()[1])


# If not one command-line arguments are given
if len(argv) != 2:
    # Print the usage and exits the program
    print("[Usage] python import.py <csv_filepath>")
    exit()

# Setup SQL DB
db = SQL("sqlite:///students.db")

# Open the CSV File as File Object
with open(argv[1], mode='r') as csv_file:
    # Read the CSV File
    csv_reader = csv.reader(csv_file)

    # Consume the first line
    next(csv_reader)

    # Iterate through each row
    for row in csv_reader:
        # Unpack the variables from each row
        name, house, birth = row
        # Parse the first, middle and last from name
        first, middle, last = parseName(name)

        # If middle name exists
        if middle != None:
            # Insert the data into database
            db.execute(
                f"INSERT INTO Students (first, middle, last, house, birth) VALUES ('{first}', '{middle}', '{last}', '{house}', {birth});"
            )
        else:
            # Else insert null for middle (hint: None is Null in SQLite3)
            db.execute(
                f"INSERT INTO Students (first, middle, last, house, birth) VALUES ('{first}', ?, '{last}', '{house}', {birth});", (
                    None, )
            )
            