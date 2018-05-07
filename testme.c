/* Author: Matthew Frank
** Class: CS362
** Assignment: Random Testing Quiz
** Citation: The bulk of this code was provided by the professor of the class
** - the only work I did was the implementation of inputChar() and inputString();
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/* I decided to just brute force the random character creation
** and lo and behold, it runs faster enough that it's worth
** using it and ignoring anything fancier.
*/
char inputChar()
{
	char rando = '\0';
	rando += (rand() % 127);
    return rando;
}

char *inputString()
{
	/* My idea to use a pre-defined character set and make random selections from that
	** comes from the StackOverflow answer by Ates Goral, found here:
	** https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
	*/

	char *cPtr;
	cPtr = (char*)malloc(6 * sizeof(char));

	char listing[5] = { 'r', 'e', 's', 't', '\0' };

	int counter;
	for (counter = 0; counter < 5; counter++) {
		cPtr[counter] = listing[rand() % 5];
	}

    return cPtr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();

    return 0;
}
