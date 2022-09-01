#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int is_sentence_end(char c)
{
  return c == '.' || c == '?' || c == '!';
}

int is_letter(char c)
{
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

void count(char *text, int *letter_counter, int *word_counter, int *sentence_counter)
{
  int word_flag = 0;
  
  while (*text)
  {
//    printf("%s\n", text);
    if (is_letter(*text))
        (*letter_counter)++;
    if (is_sentence_end(*text))
        (*sentence_counter)++;

    // Count words
    if (*text == ' ')
    {
//      printf("%d ", word_flag);
      if (word_flag)
        (*word_counter)++;
      word_flag = 0;
    }
    else
      word_flag = 1;
    text++;
  }
  if (word_flag)
    (*word_counter)++;
}

int round_int(float number)
{
  int round = (int) number;
//  printf("%f\n", number - round);
  if (number - round > 0.5)
    round++;
  return round;
}

int main(void) 
{
  char  *text = get_string("Text: ");
  int   letters = 0;
  int   words = 0;
  int   sentences = 0;
  count(text, &letters, &words, &sentences);
//  printf("%d letters, %d words, %d sentences.\n", letters, words, sentences);
//  printf("%f letters per 100 words && %f sentences per 100 words\n", 100 * (letters/(float) words), 100 * (sentences/(float) words));

  float index = 0.0588 * 100 * (letters/(float) words) - 0.296 * 100 * (sentences/(float) words) - 15.8;
  int grade = round_int(index);
  if (grade < 1)
    printf("Before grade 1.\n");
  else if (grade >= 16)
    printf("Grade 16+!\n");
  else
    printf("Grade: %d\n", grade);
}
