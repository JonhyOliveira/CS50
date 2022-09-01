#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char *name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
char vote(char *name);
void print_winner(void);

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

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count;)
    {
        char *name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
            continue;
        }
        i++;
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
char vote(char *name)
{
    char *c_name_it;
    char *name_it;

    for (int i = 0; i < candidate_count; i++)
    {
        c_name_it = candidates[i].name;
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
          candidates[i].votes++;
          return 1;
        }
    }
    return 0;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest = -1;
    int i;
    for (i = 0; i < candidate_count; i++)
    {
//        printf("%s: %d %d highest\n", candidates[i].name, candidates[i].votes, highest);
        if (candidates[i].votes > candidates[highest].votes)
          highest = i;
    }
    if (highest >= 0)
      printf("Winner is %s!\n", candidates[highest].name);
    else
      printf("Huh??\n");
    return;
}
