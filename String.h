#ifndef _STRINGH_
#define _STRINGH_

void stringCpy(char [], char []);
int stringCmp(char [],char []);
int  stringLen(char []);

/// function that copy string to another
void stringCpy(char a[], char b[])
{
    int i ;
    for(i = 0; b[i] != '\0'; ++i)
        a[i] = b[i];

    a[i] = '\0';
}

/// function compare between to strings , return 1 if they same , 0 if not
int stringCmp(char input1[],char input2[])
{
    int i;
    char c ;
    for(i=0; input1[i]!='\0' || input2[i]!='\0'; i++)
    {
        if(input1[i]>90)
             c = input1[i] - 32 ;
        else
             c = input1[i] + 32 ;
        if (input1[i]!= input2[i] && c!=input2[i])
            return 0 ;
    }
    return 1;
}

/// function return a number of character in string (string length )
int  stringLen(char a[])
{
    int nameLength = 0 ;

    while(a[nameLength]!=0 )
        ++nameLength ;

    return nameLength ;
}

#endif
