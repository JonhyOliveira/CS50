#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
char locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

char    *get_string(char *prompt)
{
  char *ret = (char *) malloc(sizeof(char) * 2000);

  while (*prompt)
    write(1, prompt++, 1);

  char  *ret_iterator = ret;
  read(0, ret_iterator, 1);
  while (*ret_iterator && *ret_iterator != '\n')
    read(0, ++ret_iterator, 1);
  *ret_iterator = 0;
  return ret;
}

int get_int(char *prompt)
{
  char  *str = get_string(prompt);
  int   ret = atoi(str);
  free(str);
  return ret;
}

// Array of candidates
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
char vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, char *argv[])
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
            locked[i][j] = 0;
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
        for (int j = 0; j < candidate_count;)
        {
            char prompt[50];
            sprintf(prompt, "Rank %i: ", j + 1);
            char *name = get_string(prompt);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                continue;
            }
            j++;
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
char vote(int rank, char *name, int ranks[])
{
    char *c_name_it;
    char *name_it;

    for (int i = 0; i < candidate_count; i++)
    {
        c_name_it = candidates[i];
        name_it = name;
        while (*name_it && *c_name_it)
        {
            if (*name_it != *c_name_it)
              break;
            name_it++;
            c_name_it++;
        }
        if (!*name_it && !*c_name_it)
        {
          ranks[rank] = i;
          return 1;
        }
    }
    return 0;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
        for (int j = i + 1; j < candidate_count; j++)
          preferences[ranks[i]][ranks[j]]++;
    return;
}

int sum_until(int curr, int first)
{
  if (curr == first)
    return 0;
  else
    return curr + sum_until(curr + 1, first);
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
      for (int j = i + 1; j < candidate_count; j++)
      {
        int winner = -1;
        int loser = -1;
        if (preferences[i][j] >= preferences[j][i]) {
          winner = i;
          loser = j;
        }
        else {
          winner = j;
          loser = i;
        }
        pairs[(j - i - 1) + sum_until(candidate_count - i, candidate_count)].winner = winner;
        pairs[(j - i - 1) + sum_until(candidate_count - i, candidate_count)].loser = loser;
        pair_count++;
      }
    return;
}

int pair_margin(pair p)
{
  return preferences[p.winner][p.loser] - preferences[p.loser][p.winner];
}

int pair_compare(pair p1, pair p2)
{
  return pair_margin(p1) - pair_margin(p2);
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair    temp;
    for (int i = 0; i < pair_count; i++)
      for (int j = i + 1; j < pair_count; j++)
        if (pair_compare(pairs[i], pairs[j]) < 0)
        { // swap
          temp = pairs[i];
          pairs[i] = pairs[j];
          pairs[j] = temp;
        }
    return;
}

int has_path(int start, int finish)
{
  if (start == finish)
    return 1;
  for (int other = 0; other < candidate_count; other++)
    if (locked[start][other] > 0 && has_path(other, finish))
      return 1;
  return 0;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        //printf("The people prefer %s over %s with a margin of %d.\n", candidates[pairs[i].winner], candidates[pairs[i].loser], pair_margin(pairs[i]));
      if (!locked[pairs[i].winner][pairs[i].loser] && !has_path(pairs[i].loser, pairs[i].winner))
      {
        locked[pairs[i].winner][pairs[i].loser] = pair_margin(pairs[i]);
        locked[pairs[i].loser][pairs[i].winner] = -pair_margin(pairs[i]);
      }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int has_incoming;
    int has_votes;
/*
    for (int i = 0; i < candidate_count; i++)
    {
      for (int j = 0; j < candidate_count; j++)
        printf("%d\t", locked[i][j]);
      printf("\n");
    }
*/
    for (int i = 0; i < candidate_count; i++)
    {
      has_incoming = 0;
      has_votes = 0;
      for (int j = 0; j < candidate_count && !has_incoming; j++)
        if (locked[i][j] < 0)
          has_incoming = has_votes = 1;
        else if (locked[i][j] > 0)
          has_votes = 1;

      if (!has_incoming && has_votes)
      {
        printf("Winner is %s!\n", candidates[i]);
        return;
      }
    }
    printf("No winner :(");
    return;
}
