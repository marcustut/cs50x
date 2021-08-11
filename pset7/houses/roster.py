from cs50 import SQL
from sys import argv, exit


# If not one command-line arguments are given
if len(argv) != 2:
    # Print the usage and exits the program
    print("[Usage] python roster.py <house_name>")
    exit()
    
# Establish SQL Connection
db = SQL('sqlite:///students.db')

# Parsing the first command-line argument as house
house = argv[1]

# Query the database
results = db.execute(
    f"SELECT first, middle, last, birth FROM Students WHERE house == '{house}' ORDER BY last, first;"
)

# Iterate over results
for result in results:
    # If middle name exists
    if result['middle']:
        # Print with middle name
        print(f"{result['first']} {result['middle']} {result['last']}, born {result['birth']}")
    else:
        # Else print without middle name
        print(f"{result['first']} {result['last']}, born {result['birth']}")
