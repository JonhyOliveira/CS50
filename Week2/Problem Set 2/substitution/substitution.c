#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

int str_len(char *str)
{
  char *str_it = str;
  while (*str_it)
    str_it++;
  return str_it - str;
}

// converts lower case characters to uppercase in dup string
char *cypherize(char *str)
{
  char  *cypher = malloc(sizeof(char) * str_len(str));
  char  *cypher_it = cypher;

  while (*str)
  {
    *cypher_it = *str++;
    if (*cypher_it >= 'a' && *cypher_it <= 'z')
      *cypher_it -= 32;
    cypher_it++;
  }

  return cypher;
}

char    to_cypher(char c, char *cypher)
{
  if (c >= 'a' && c <= 'z')
    return cypher[c - 'a'] + 32;
  else if (c >= 'A' && c <= 'Z')
    return cypher[c - 'A'];
  else
    return c;
}

int main(int argc, char *argv[]) 
{
  if (argc != 2)
  {
    printf("Usage: %s <key>\n", argv[0]);
    return 1;
  }

  if (str_len(argv[1]) != 26)
  {
    printf("Key must contain 26 characters. Contains %d instead.\n", str_len(argv[1]));
    return 1;
  }

  char *cypher = cypherize(argv[1]);
//  printf("Cypher: %s\n", cypher);

  char *plain_text = get_string("plaintext: ");
  printf("cyphertext: ");
  while (*plain_text)
  {
    printf("%c", to_cypher(*plain_text, cypher));
    plain_text++;
  }
  printf("\n");
}
