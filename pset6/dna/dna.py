from sys import argv, exit
import csv
import collections


# Returns a reader to csv file given its opened file object
def read_csv(csv_file):
    # Reads the file with DictReader as an OrderedDict
    return csv.DictReader(csv_file)


# Returns a string of txt file read without newline character
def read_dna_sequence(txt_file):
    return txt_file.readline().rstrip()


if __name__ == "__main__":
    # If not exactly 2 command-line arguments are given
    if len(argv) != 3:
        # Print the correct usage
        print("Usage: python dna.py data.csv sequence.txt")
        # Exits the program
        exit()

    # Open csv and txt file with read priviledges
    csv_file = open(argv[1], mode='r')
    txt_file = open(argv[2], mode='r')

    # Read the CSV as OrderedDict
    csv_reader = read_csv(csv_file)

    # Read the txt file as a string
    dna_sequence = read_dna_sequence(txt_file)

    # Store list of OrderedDict of candidates
    candidates = [row for row in csv_reader]

    # List of STR
    listSTR = list(candidates[0].keys())[1:]

    # Dictionary to store counters of each STR
    STRCount = dict([(listSTR[i], 0) for i in range(len(listSTR))])

    # Iterate through each STR
    for STR in listSTR:
        # Find the first index of STR occurence
        index = dna_sequence.find(STR)

        # List of counters
        counters = []

        # Counter for each STR encounter
        counter = 0

        # Copy of dna_sequence
        dna = dna_sequence

        # Iterate through dna_sequence by each STR
        while index < len(dna):
            # If STR is found
            if dna[index:index+len(STR)] == STR:
                # Increment the counter
                counter += 1
                # Move index to the next group of STR
                index += len(STR)
            # If STR is not found
            else:
                if counter != 0:
                    # Append the current counter
                    counters.append(counter)
                # Reset the counter
                counter = 0
                # Slice sequence up to current index
                dna = dna[index:]
                # Find index of next occurence of STR
                index = dna.find(STR)
                # If no occurence then break out of the loop
                if index == -1:
                    break

        # If counters is not empty
        if counters != []:
            # Set highest counter be the STRCount
            STRCount[STR] = max(counters)

    # For each candidate
    for candidate in candidates:
        # List of equality flags for comparison
        equals = []

        # For each STR
        for STR in listSTR:
            # If STRCount in current dna sequence match candidate STRCount
            if STRCount[STR] == int(candidate[STR]):
                equals.append(True)
            else:
                equals.append(False)

        # If candidate has all True flags
        if False not in equals:
            # It is the owner of this DNA
            print(candidate['name'])
            csv_file.close()
            txt_file.close()
            exit()

    # Close all opened files
    csv_file.close()
    txt_file.close()

    print("No match")