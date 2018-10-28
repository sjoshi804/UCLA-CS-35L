#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

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
	      fprintf(stderr, "Please do not provide duplicate bytes in from argument \n");
	      exit(1);
	    }
	}
    }

  //TRANSLITERATING BYTES
  char currentChar[1];
  ssize_t io_success = read(0, currentChar, 1);

  while (io_success > 0)
     {
       for (size_t i = 0; i < strlen(from); i++)
	 {
	   if (currentChar[0] == from[i])
	     {
	       currentChar[0] = to[i];
	       break;
	     }
	 }
       
       write(1, currentChar, 1);
       io_success = read(0, currentChar, 1);
     }

  return 0;  
}
