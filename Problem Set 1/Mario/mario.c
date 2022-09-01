#include <stdio.h>

int main()
{
  printf("Height: ");

  int height;

  scanf("%d", &height);

  if (height > 8)
    return 1;
  int curr_height=1;
  while (curr_height<=height)
  {
    int space_count=1;
    while (space_count<=height-curr_height)
    {
      printf(" ");
      space_count++;
    }

    int block_count=1;
    while (block_count<=curr_height)
    {
      printf("#");
      block_count++;
    }
    printf("  ");

    block_count=1;
    while (block_count<=curr_height)
    {
      printf("#");
      block_count++;
    }
    printf("\n");
    curr_height++;
  }
}
