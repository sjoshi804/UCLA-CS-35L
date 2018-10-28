#include <stdio.h>
#include <stdlib.h>

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

int main (void)
{
  //Pointer to the first element of a string
  char* currentWord = NULL;
  //Pointer to multiple string pointers like the one above
  char** text = NULL;
  
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
    //Exit program
    fprintf(stderr, "I/O error. exiting \n");
    free(currentWord);
    exit(1);
   }
  
  while (currentWord[numChars] != EOF && !(ferror(stdin)))
  {
    //Read stdin to get next character
    char nextChar = getchar();
    
    if (ferror(stdin))
    {
      //Exit program
      fprintf(stderr, "I/O error. exiting \n");
      free(currentWord);
      for (int i = 0; i < numWords; i++)
	free(text[i]);
      free(text);
      exit(1);
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
      if (nextChar == EOF)
	//Execution completed, break out of loop and exit normally
	break;
      
      while (nextChar == ' ')
      {
	nextChar = getchar();
	if (ferror(stdin))
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
    }
    
    else if (nextChar == EOF)
      nextChar = ' ';

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
      printf("%c", text[i][j]);
    printf (" ");
  }
  
  //Free all memory
  for (size_t i = 0; i < numWords; i++)
    free(text[i]);
  free(text);
  free(currentWord);
  
  return 0;
}


