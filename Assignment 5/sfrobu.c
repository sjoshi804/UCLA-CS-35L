#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
char memFrobByte (const char current)
{
  return (current ^ 42);
}

int frobcmp (char const* first, char const* second)
{
  while (1)
    {
      //Null bytes need to be skipped but are accepted as valid
      while (*first == '\0')
	first++;
      while (*second == '\0')
	second++;

      if (*first == ' ' && *second == ' ')
	// Both words ended, must be equal hence return 0
	return 0;

      if (*first == ' ' || memFrobByte(*first) < memFrobByte (*second))
	return -1;

      if (*second == ' ' || memFrobByte(*first) > memFrobByte(*second))
	return 1;

      first++; second++;
    }
}

int universalfrobcmp(const void* wordA, const void* wordB)
{
  //Typecast pointers for the qsort function
  const char* word1 = *(const char**)wordA;
  const char* word2 = *(const char**)wordB;
  return frobcmp(word1, word2);
}



int main (int argc, char** argv)
{
  //Default is set to 0
  int flag_optf = 0;
  
  if (argc > 2)
    {
      fprintf(stderr, "Too many options");
      exit(1);
    }

  //Pointer to the first element of a string
  char* currentWord = NULL;
  //Pointer to multiple string pointers like the one above
  char** text = NULL;
  

  const char* options = argv[1];
  const char* option_f = "-f";
  
  if (argc == 2 && strcmp (options, option_f) != 0)
    {
      fprintf(stderr, "Only option -f allowed");
      exit(1);
    }
  else if (argc == 2 && strcmp(options, option_f) == 0)
    {
      flag_optf = 1;
    }
  
  struct stat data;
  if (fstat(0, &data) < 0)
    {
      fprintf(stderr, "Error in fstat.");
      exit(1);
    }

  char* buffer;
  int counter = 0;
  int maxSize = 0;
  
  if (S_ISREG(data.st_mode))
    {
      buffer = (char*)malloc(data.st_size * sizeof(char));
      if (buffer == NULL)
	{
	  fprintf(stderr, "Memory allocation error");
	  exit(1);
	}

      if (read(0, buffer, data.st_size) < 0)
	{
	  fprintf(stderr, "Read error");
	  exit(1);
	}

      maxSize = data.st_size;
    }


  int numChars = 0;
  int numWords = 0;
  
  currentWord = (char*) malloc (sizeof(char)); 
  
  if (currentWord == NULL)
  {
    //Memory not allocated successfully hence program must exit indicating
    //this error
    fprintf(stderr, "memory allocation unsuccessful. exiting \n");
    exit (1);
  }

  currentWord[numChars] = getchar();
  
  if (ferror(stdin))
  {

   }
  
  ssize_t IOStatus;
  if (counter >= maxSize)
    {
      IOStatus = read(0, (currentWord), 1);
      if (IOStatus < 0)
	{
	  //Exit program
	  fprintf(stderr, "I/O error. exiting \n");
	  free(currentWord);
	  exit(1);
	}
    }
  else
    {
      currentWord[numChars] = buffer[counter++];
      IOStatus = 1;
    }
 

  while (IOStatus > 0)
  {
    //next character
    char nextChar;
    
    if (counter >= maxSize)
    {
      IOStatus = read(0, &(nextChar), 1);
      if (IOStatus < 0)
	{
	  //Exit program
	  fprintf(stderr, "I/O error. exiting \n");
	  free(currentWord);
	  for (int i = 0; i < numWords; i++)
	    free(text[i]);
	  free(text);
	  exit(1);
	}
    }

    else
      {
	nextChar = buffer[counter++];
      }


    if (currentWord[numChars] == ' ') //New word starting
    {
      //Allocate memory for numWords + 1 for the new word
      char** temp_ptr = realloc (text, (numWords + 1) * sizeof(char*));
      if (temp_ptr == NULL)
      {
	//Memory allocation unsuccesful
	//Exit program
	fprintf(stderr,"memory allocation unsuccessful. exiting \n");
	free(currentWord);
	for (int i = 0; i < numWords; i++)
	  free(text[i]);
	free(text);
	exit(1);
      }
      
      text = temp_ptr;
      text[numWords] = currentWord;
      numWords++;
      numChars = -1; //So that later ++ makes it 0 again
      currentWord = (char*) malloc (sizeof(char));
      if (IOStatus == 0)
	//Execution completed, break out of loop and exit normally
	break;
      
      while (nextChar == ' ')
      {
	if (counter >= maxSize)
	  {
	    IOStatus = read(0, &(nextChar), 1);
	    if (IOStatus < 0)
	      {
		//Exit program
		fprintf(stderr, "I/O error. exiting \n");
		free(currentWord);
		for (int i = 0; i < numWords; i++)
		  free(text[i]);
		free(text);
		exit(1);
	      }
	  }
	else
	  {
	    nextChar = buffer[counter++];
	  }
      }
    }
    else if (IOStatus == 0)
      {
	nextChar = ' ';
	IOStatus = 1;
      }

    numChars++;
    char* temp_str_ptr = realloc (currentWord, (numChars + 1) * sizeof(char));
    
    if (temp_str_ptr == NULL)
    {
      //Memory allocation unsuccesful                                                              
      //Exit program                                                                               
      fprintf(stderr,"memory allocation unsuccessful. exiting \n");
      free(currentWord);
      for (int i = 0; i < numWords; i++)
	free(text[i]);
      free(text);
      exit(1);
    }
    
    currentWord = temp_str_ptr;
    currentWord[numChars] = nextChar;
    
  }

  qsort(text, numWords, sizeof(char*), universalfrobcmp);
  
  //Print sorted list
  for (size_t i = 0; i < numWords; i++)
  {
    for (size_t j = 0; text[i][j] != ' '; j++)
      write(1, &text[i][j], 1);
    write(1, " ", 1);
  }
  
  //Free all memory
  for (size_t i = 0; i < numWords; i++)
    free(text[i]);
  free(text);
  free(currentWord);
  
  return 0;
}


