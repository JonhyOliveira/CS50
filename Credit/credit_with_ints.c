#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INVALID "INVALID"
#define AE "AMERICAN EXPRESS"
#define MC "MASTER CARD"
#define VISA "VISA"

// checks if a string is numeric
int is_numeric(char *card)
{
  char *card_iterator = card;

  if (!*card_iterator)
    return 0;
  while (*card_iterator)
  {
    if (*card_iterator < '0' || *card_iterator > '9')
      return 0;
    card_iterator++;
  }

  return 1;
}

// gets a numeric string from standard input 
char *get_number()
{
  char *card = malloc(50 * sizeof(char));
  card[0] = 1;
  while (!is_numeric(card))
  {
    printf("Number: ");
    scanf("%s", card);
  }

  return card;
}

int str_len(char *str)
{
  int length=0;

  while (*str)
  {
    length++;
    str++;
  }
  return length;
}

int num_digits(long number)
{
  if (!number)
    return 0;
  else
    return 1 + num_digits(number / 10);
}

char    *card_emitter(long card_number)
{
  int digits = num_digits(card_number);
  int first_2;
  if (digits >= 2)
    first_2 = card_number / pow(10, digits - 2);
  else
    first_2 = card_number;

  if (digits == 15)
  {
    if (first_2 == 34 || first_2 == 37)
      return AE;
  }
  else if (digits == 13)
  {
    if (first_2 / 10 == 4)
      return VISA;
  }
  else if (digits == 16)
  {
    if (first_2 / 10 == 4)
      return VISA;
    else if (first_2 >= 51 && first_2 <= 55)
      return MC;
  }

  printf("digits: %d, first_2: %d\n", digits, first_2);
  return INVALID;
}

int main(void)
{
  long card_number = atol(get_number());
  printf("%s\n", card_emitter(card_number));
}
