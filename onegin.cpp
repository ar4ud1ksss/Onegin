#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <iostream>

#define $(var)  std::cout << "[" << #var << " = " << (var) << "]\n";

char* FileRead (FILE* text, int fileLength);
int FileLength (FILE* text);
char** FindEndOfString (char* originaltext, int fileLength, int* numberOfString);
char** Sort (char** address, int numberOfString);
char** AddressCopy (char** address, int numberOfString);
int StringCmp(const void* a, const void* b);
int StringBackCmp(const void* a, const void* b);
void Print (char** copyText, int numberOfString, FILE* output);

int main ()
    {
    char* originaltext = NULL;
    char** address = NULL;
    char** copyText = NULL;
    FILE* text = fopen ("text3.txt", "r");
    int numberOfString = 0;
    FILE* output = fopen ("output.txt", "w");

    int fileLength = FileLength (text);
    originaltext = FileRead (text, fileLength);
    address = FindEndOfString (originaltext, fileLength, &numberOfString);
    copyText = AddressCopy (address, numberOfString);

    for (int i = 0; i < numberOfString; i++)
        for (;copyText[i][0] == ' ';copyText[i]++);

    qsort(copyText, numberOfString, sizeof(char*), StringCmp);
    Print (copyText, numberOfString, output);

    qsort(copyText, numberOfString, sizeof(char*), StringBackCmp);

    fprintf (output,"\n\nBack Sorted\n\n");
    Print (copyText, numberOfString, output);

    fprintf (output,"\n\nOriginal Text\n\n");
    Print (address, numberOfString, output);
    
    free (originaltext);
    free (address);
    free (copyText);

    fclose (text);
    fclose (output);
    }

/*!
    \brief Function for calculate length of file
    \param text 
    Input file
*/
int FileLength (FILE* text)
    {
    assert (text != NULL);
    
    fseek (text, 0L, SEEK_END);
    int fileLength = ftell (text);
    fseek (text, 0L, SEEK_SET);

    assert (fileLength >= 0);

    return (fileLength);
    }

/*!
    \brief Read function
    \param text
    Input file
    \param fileLength 
    Length of file
*/
char* FileRead (FILE* text, int fileLength) 
    {
    assert (text != NULL);
    assert (fileLength >= 0);    

    char* originaltext = (char*) calloc (fileLength+1, sizeof (char));
    fread (originaltext, fileLength, 1, text);

    return (originaltext);
    }

/*!
    \brief Function for linked string
    \param originaltext 
    String with data
    \param fileLength 
    Length of file
    \param numberOfString
    Number of string
*/
char** FindEndOfString (char* originaltext, int fileLength, int* numberOfString)
    {
    assert (originaltext != NULL);
    assert (fileLength >= 0);
    assert (numberOfString != NULL);

    int counter = 0;
    for (int i = 0; i < fileLength; i++)
        {
        if ((originaltext[i] == '\n') || (originaltext[i] == '\0'))
            {
            counter++; 
            }
        }

    char** address = (char**) calloc (counter+2, sizeof (char*));
    *numberOfString = counter;

    address[0] = &originaltext[0];
    counter = 1;

    for (int i = 0; i < fileLength; i++) 
        {
        if (originaltext[i] == '\n')
            {
            assert (counter <= *numberOfString);
 
            address[counter++] = &originaltext[i + 1];
            originaltext[i] = '\0';
            } 
        }

    for (int i = 0; i < counter; i++)

    return (address); 
    }

/*!
    \brief function create text copy 
    \param address 
    Array of linked string
    \param numberOfString 
    Number of string
*/

char** AddressCopy (char** address, int numberOfString)
    {
    assert (address != NULL);
    assert (numberOfString >= 0);
  
    char** Copy = (char**) calloc (numberOfString, sizeof(char*));
    int i = 0;
    for(i = 0; i < numberOfString; i++)
        {
        Copy[i] = address[i];
        }
    return (Copy);
    }

/*!
    \brief function for comparare string  
*/
int StringCmp(const void* a, const void* b)
    {
    assert(a != NULL);
    assert(b != NULL);  

    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return (strcasecmp(str1, str2));
    }

/*!
    \brief function for comparare string for back sorted  
*/
int StringBackCmp(const void* a, const void* b)
    {
    assert(a != NULL);
    assert(b != NULL);  

    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
  
    while ((str1[len1 - 1] == str2[len2-1]) || (ispunct (str1[len1 - 1])) || (ispunct (str2[len2 - 1])) && (len1 > 1) && (len2 > 1))
        {
        if (ispunct (str1[len1 - 1])) len1--;
        else
            if (ispunct (str2[len2 - 1])) len2--;
            else 
                {
                len1--;
                len2--;
                }
        }
    return (len1 - len2);
    }

/*!
	\brief Print function
    \param copyText 
    Array of link to sorted string.
    \param numberOfString 
    Number of string
    \param output
    Output file
*/
void Print (char** copyText, int numberOfString, FILE* output)
    {
    assert (copyText != NULL);
    assert (numberOfString >= 0);
    assert (output != NULL);
   
    for (int i = 0; i < numberOfString; i++) 
        {
        if (copyText[i][0] != '\0') fprintf (output, "%s\n", copyText[i]);
        }
    }

