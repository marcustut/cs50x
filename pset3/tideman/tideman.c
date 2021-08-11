#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int comp(const void *a, const void *b);
bool hasCycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Check if the name given is a candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate is found
        if (strcmp(candidates[i], name) == 0)
        {
            // Update the voter's ranks according to its preferences
            ranks[rank] = i;
            return true;
        }
    }

    // If candidate is not found
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loop through voter's ranks
    for (int i = 0; i < candidate_count; i++)
    {
        // For each rank after the candidate
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Increment the number of preferences for this candidate.
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Check if preferences for both candidates is not equal
            if (preferences[i][j] != preferences[j][i])
            {
                // The pair that we want to add later on
                pair pairToAdd;

                // Check if candidate i is preferred over candidate j
                if (preferences[i][j] > preferences[j][i])
                {
                    pairToAdd = (pair)
                    {
                        .winner = i, .loser = j
                    };
                }
                // Check if candidate j is preferred over candidate i
                else
                {
                    pairToAdd = (pair)
                    {
                        .winner = j, .loser = i
                    };
                }

                // Add the pair to the pairs array
                pairs[pair_count] = pairToAdd;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // If only a pair or no pair exists in the array then no need to sort
    if (pair_count <= 1)
    {
        return;
    }
    // Sort implementation
    qsort(pairs, pair_count, sizeof(*pairs), comp);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Iterate through pairs
    for (int i = 0; i < pair_count; i++)
    {
        if (!hasCycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Iterate through rows of locked array
    for (int i = 0; i < candidate_count; i++)
    {
        // Initialize a counter
        int counter = 0;
        // Iterate through columns of locked array
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if path exists
            if (!locked[j][i])
            {
                // If false then increment counter
                counter++;
            }
            // If has the most false or equal to number of pairs then it is the winner
            // becuase most false has less edge which is source of the graph
            if (counter >= pair_count)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }
}

// Comparison function for sorting pairs array
int comp(const void *a, const void *b)
{
    pair *x = (pair *) a;
    pair *y = (pair *) b;

    return preferences[y->winner][y->loser] - preferences[x->winner][x->loser];
}

bool hasCycle(int winner, int loser)
{
    // If a path back to winner exists then cycle exists
    if (locked[loser][winner])
    {
        return true;
    }
    // Loop through locked arr
    for (int i = 0; i < pair_count; i++)
    {
        // Check for path between neighbors and winner
        if (locked[i][winner])
        {
            // If there's a path, let it cycle over to return true
            hasCycle(winner, i);
        }
    }
    return false;
}