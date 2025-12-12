//  Created by SARATH R on 26/09/14. 
//  Copyright (c) 2014 SARATH R. All rights reserved. 
//  Insertion Sort 

#include <stdio.h>
int main()
{
  int i, data[25], j, temp, compshift(int*, int);
  int display(int*);
  printf("Enter 25 Numbers\n");
  for(i = 0; i < 25; i++)
    scanf ("%d", &data[i]);
  for(j = 2; j <= 25; j++)
    compshift(&data[0], j);
  for(i = 0; i < 25; i++)
    printf("\n%d", data[i]);
  printf("\n");
  return 0;
}
int compshift(int *sub, int len)
{
  int key, temp;
  key = sub[len - 1];
  for (int i = len-2; i >= 0; i--)
  {
    if (sub[i] < key) 
      continue;
    else
    {
      temp       = sub[i];
      sub[i]     = key;
      sub[i + 1] = temp;
    }
  }
  return 0;
}
