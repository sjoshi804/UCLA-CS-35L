#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv)
{
  //CHECKING FOR CORRECT NUMBER OF ARGUMENTS
  if (argc != 3)
    {
      fprintf(stderr, "Please provide exactly 2 arguments. \n");
      exit(1);
    }


  char* from = argv[1];
  char* to = argv[2];

  //CHECKING FOR EQUAL LENGTH
  if (strlen(from) != strlen(to))
    {
      fprintf(stderr, "Please provide arguments of equal length. \n");
      exit(1);
    }

  //CHECKING FOR DUPLICATES
  for (size_t i = 0; i < strlen(from); i++)
    {
      for (size_t j = i + 1; j < strlen(from); j++)
	{
	  if (from[j] == from[i])
	    {
	      fprintf(stderr, "Please do not provide duplicate bytes in from argument. \n");
	      exit(1);
	    }
	}
    }

  //TRANSLITERATING BYTES
  int currentChar = getchar();
   
   while (currentChar != EOF)
     {
       for (size_t i = 0; i < strlen(from); i++)
	 {
	   if (currentChar == from[i])
	     {
	       currentChar = to[i];
	       break;
	     }
	 }
       
       putchar(currentChar);
       currentChar = getchar();
     }

  return 0;  
}
