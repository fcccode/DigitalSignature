#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>

char *generateGuid()
{
	BOOL result;
	char *passValue;

   /* Seed the random-number generator with current time so that
    * the numbers will be different every time we run.
    */
	srand( (unsigned)time( NULL ) );
	result = RandomPassword(25, &passValue);
	return passValue;
}

//This function will generate a random password
//The length of the password is specified by the first
//parameter (PasswordLength) and it must be greater 3
//or more characters
//The password generated will contain at least one lower case
//at least one upper case and at least one number.
//If the creation is sucessful the password will be
//returned in the second paramenter (ReturnedPassword) and
//the function will return true.
//If the password creation fails (PasswordLength < 3) the function will return
//false

BOOL RandomPassword(int PasswordLength, char **guid)
{
    int lNumberOfLowerCases=0;
    int lNumberOfUpperCases=0;
    int lNumberOfNumbers=0;
    int l, j;
    int curLength=0, numberAdded=0;
    
    string ReturnedPassword="";
    if (PasswordLength < 3)
        return FALSE;

    //Get the number of digits for each type of characters
    lNumberOfLowerCases = 0;
    lNumberOfUpperCases = ((int)(PasswordLength - lNumberOfLowerCases - 2) * rand()) + 1;
    lNumberOfNumbers = PasswordLength - lNumberOfLowerCases - lNumberOfUpperCases;

    
    
    curLength = 0
    for(l = 0; l < PasswordLength; i++)
    {
	numberAdded = FALSE;
	/* Seed the random-number generator with current time so that
	 * the numbers will be different every time we run.
	*/
	srand( (unsigned)time( NULL ) );
        j = (int)(2 * rand() + 1);
        switch (j)
	{
        case 1: //Lower Case
            if (lNumberOfLowerCases > 0)
	    {
                ReturnedPassword = ReturnedPassword + (char)((int)(25 * rand()) + 97);
                lNumberOfLowerCases = lNumberOfLowerCases - 1;
		numberAdded = TRUE;
	    }
            else
                l = l - 1; //Re-do the loop
	    break;

        Case 2 //Upper Case
            if (lNumberOfUpperCases > 0)
	    {
                ReturnedPassword = ReturnedPassword + (char)((int)(25 * rand()) + 65);
                lNumberOfUpperCases = lNumberOfUpperCases - 1;
		numberAdded = TRUE;
	    }
            else
                l = l - 1; //Re-do the loop
	    break;

        Case 3 //Number
            if (lNumberOfNumbers > 0)
	    {
                ReturnedPassword = ReturnedPassword + (int)(9 * rand());
                lNumberOfNumbers = lNumberOfNumbers - 1;
		numberAdded = TRUE;
	    }
            else
                l = l - 1; //Re-do the loop
	    break;
	default:
        }
        for (j = 0; j < 100; j++)
	{}//Give the seed some time
        if (numberAdded == True)
	{
		curLength = curLength + 1;
		if (curLength == 5)
			ReturnedPassword = ReturnedPassword + "-";
		else if (curLength == 10)
			ReturnedPassword = ReturnedPassword + "-";
		else if (curLength == 15)
			ReturnedPassword = ReturnedPassword + "-";
		else if (curLength == 20)
			ReturnedPassword = ReturnedPassword + "-";
	}
    }
    char *tmpPtr = ReturnedPassword.c_str();
    int length = strlen(tmpPtr);
    *guid = zMalloc(length + 1);
    strcpy(*guid, tmpPtr);
    return TRUE;
}