#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char *word);

char    *get_string(char *prompt)
{
  char *ret = (char *) malloc(sizeof(char) * 50);

  printf(prompt);
  scanf("%s", ret);

  return ret;
}

int main(void)
{
    // Get input words from both players
    char    *word1 = get_string("Player 1: ");
    char    *word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    free(word1);
    free(word2);

    // Print the winner
    if (score1 > score2)
      printf("Player 1 wins! %d points ahead!", score1 - score2);
    else if (score2 > score1)
      printf("Player 2 wins! %d points ahead!", score2 - score1);
    else
      printf("DRAW!! %d points each.", score1);
    printf("\n");
}

int compute_score(char *word)
{
    int score = 0;
    int offset;
    // Compute and return score for string
    while (*word)
    {
        offset = 0;
        if (*word >= 'a' && *word <= 'z')
          offset = 'a';
        else if (*word >= 'A' && *word <= 'Z')
          offset = 'A';

        if (offset)
          score += POINTS[*word - offset];

        word++;
    }

    return score;
}
