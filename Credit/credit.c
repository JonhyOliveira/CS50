#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

// sums digits of a number 123 = 1 + 2 + 3 = 6
int     digit_sum(int number)
{
  if (!number)
    return 0;
  return (number % 10) + digit_sum(number / 10);
}

// checks if card is valid according to Luhn's Algorithm
int     is_card_valid(char *card)
{
  int   even_double_sum = 0;
  int   odd_sum = 0;

  if (!*card)
    return 0;

  char *card_iterator = card;
  while (*card_iterator)
    card_iterator++;
  card_iterator-=2;
  // arithmetic
  while (card_iterator + 1 >= card)
  {
    if (is_numeric(card_iterator))
      even_double_sum += digit_sum((*card_iterator - '0') * 2);
    odd_sum += (*(card_iterator + 1) - '0');
    printf("e: %d ", digit_sum((*card_iterator - '0') * 2));
    printf("o: %d ", (*(card_iterator + 1) - '0'));
    printf("sum: %d ", even_double_sum + odd_sum);
    printf("\n");
    card_iterator -= 2;
  }
  // validation
  if ((odd_sum + even_double_sum) % 10 == 0)
    return 1;
  return 0;
}

int     digit_count(char *card)
{
  int   count = 0;
  while (is_numeric(card))
  {
    count++;
    card++;
  }

  return count;
}

int     str_starts_with(char *str, char *prefix)
{
  if (!*prefix)
    return 1;
  else if (*str == *prefix)
    return str_starts_with(str + 1, prefix + 1);
  return 0;
}

// RE-WRITE THIS PLEASE!
char    *get_card_issuer(char *card)
{
  int digits = digit_count(card);

  if (digits == 15)
  {
    if (str_starts_with(card, "34") || str_starts_with(card, "37"))
      return AE;
  }
  else if (digits == 13)
  {
    if (str_starts_with(card, "4"))
      return VISA;
  }
  else if (digits == 16)
  {
    if (str_starts_with(card, "4"))
      return VISA;
    else 
    {
      if (str_starts_with(card, "51"))
        return MC;
      if (str_starts_with(card, "52"))
        return MC;
      if (str_starts_with(card, "53"))
        return MC;
      if (str_starts_with(card, "54"))
        return MC;
      if (str_starts_with(card, "55"))
        return MC;
    }
  }
  return INVALID;
}

int main(void) 
{
  char *card = get_number();
  if (is_card_valid(card))
    printf("%s\n", get_card_issuer(card));
  else
    printf("%s\n", INVALID);
}
