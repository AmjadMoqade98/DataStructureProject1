/// Amjad moqade , 1160695


/*
this project use cursor implemntations to store string , this string are names .
names are brought from file or from user .
also this project can do radix sort for these names .
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "String.h"
#include "Cursor.h"
#define cursorSize 129


/////////////////////////////////////////////////////
int isValidName(char []);
void readFromFile(struct node [], LIST );
int searchByChar(struct node [], LIST, char  );
void searchByCharToFile(LIST, char, FILE  );
void printOnFile(struct node [], LIST );
void printOnScreen(struct node [], LIST );
void printMenu();
void displaycursor();
/////////////////////////////////////////////////////





int main()
{
    struct node cursor[cursorSize];    // creating a cursor
    initializeCursors(cursor,cursorSize);

    int i ;
    int choice ;      // used in menu
    char name[50]  ; // used in add names

    // create 28 list in cursor , one of them is header of names list , remaining lists are the buckets of radix sort
    for(i=0; i<28; i++)
    {
        cursorAlloc(cursor);
    }

    LIST names = 28 ;    // the index of header
    position p ;

    while(1)
    {
        system("cls");
        printMenu();
        scanf("%d",&choice); // enter number of operation

        // add name , when user enter 1
        if(choice == 1)
        {
            system("cls");
            if(!isCursorFull(cursor)){  //  check if there space in cursor to add name
            printf("Enter name to add : ");
            gets(name);
            gets(name);
            if(!isValidName(name))     // cheack the name that use enter if it valid or not
                printf("\n\nYou Entered a wrong name!!\nmaybe you enter empty string or very large name or nonvalid characters !");
            else
            {
                position p = addNode(cursor, names); // add new node to out list if name
                if(p)
                {
                    stringCpy(cursor[p].data,name);  // add the name that user enter to node we added
                    printf("\nName Was Added !");
                }
            }
            }
            else
                printf("There no space to add names !!");


            printf("\n\nPress any key to back to menu..");
            getch();
        }

        //delete name , when user enter 2
        else if (choice == 2)
        {
            system("cls");
            if(isListEmpty(cursor, names))
                printf("List is empty ,There no names to delete !!");
            else
            {
                printf("Enter name to delete : ");
                gets(name);
                gets(name);

                if(!isValidName(name))
                    printf("\n\nError : You Enter a Wrong Name !!");
                else
                    deleteString(cursor, names, name);
                printf("\n%s was deleted !!",name);
            }
            printf("\n\nPress any key to back to menu..");
            getch();

        }
        // print the list of names , when user enter 3
        else if(choice == 3)
        {
            system("cls");
            printList(cursor, names);
            printf("\n\nPress any key to back to menu..");
            getch();
        }

        // read from any file , when user enter 4
        else if (choice == 4)
        {
            system("cls");
            if(!isCursorFull(cursor))
            readFromFile(cursor, names);
            else
                printf("There no space to add names !!");

            printf("\n\nPress any key to back to menu..");
            getch();
        }

        // print number of names in the list ,when user enter 5
        else if(choice == 5 )
        {
            system("cls");
            printf("Number of Names = %d",numOfElement(cursor, names));
            printf("\n\nPress any key to back to menu..");
            getch();
        }

        // sort the list , when user enter 6
        else if (choice == 6)
        {
            system("cls");
            radixSortString(cursor, names );
            printf("Cursor was sorted !");
            printf("\n\nPress any key to back to menu..");
            getch();
        }

        // search for specific name , when user enter 7
        else if (choice == 7)
        {
            system("cls");
            printf("Enter the name to search : ");
            gets(name);
            gets(name);
            p = stringSearch(cursor,names,name);
            if(p)
                printf("%s are exist in the list ",name);
            else
                printf("%s are not exist in the list ",name);
            printf("\n\nPress any key to back to menu..");
            getch();
        }

        // print a names start with specific character , when user enter 8
        else if (choice == 8)
        {
            system("cls");
            printf("Enter the character : ");
            scanf("%s",name);
            printf("\n");
            i = searchByChar(cursor,names,name[0]);
            if(i==0)
                printf("There is no names start with character %c !!",name[0]);
            printf("\n\nPress any key to back to menu..");
            getch();
        }

        // print names as Catalogue in screen , when user enter 9
        else if(choice == 9)
        {
            system("cls");
            printOnScreen(cursor, names);
            printf("\n\nPress any key to back to menu..");
            getch();

        }

        // print names as Catalogue in file , when user enter 10
        else if (choice == 10)
        {
            system("cls");
            printOnFile(cursor, names);
            printf("\n\nPress any key to back to menu..");
            getch();
        }

        // clear the list of names , when user enter 11
        else if (choice == 11)
        {
            system("cls");
            clearList(cursor, names);
            printf("List are cleared !!");
            printf("\n\nPress any key to back to menu..");
            getch();

        }

        // exit , when user enter 12
        else if (choice == 12)
        {
            system("cls");
            printf("\nI hope that my program was impressed you !!\n\n");
            break ;
        }

        // return to menu without do anything , when user enter a wrong input
        else
        {
            system("cls");
            printf("You Entered a wrong operation !!\n");
            printf("go back and enter correct operation please !!\n\nPress any key to back to menu..");
            getch();
        }
    }
    return 0 ;
}

/// function to check if a name is valid or not , return 1 if name is valid and 0 if not
int isValidName(char a[])
{
    int x ;
    if(stringLen(a) < 1 )   // empty string not valid name
        return 0 ;

    if(stringLen(a) > 50 ) // if name is more than 50 char , then it is not valid
        return 0 ;

    for(x =0 ; a[x]!= '\0' ; x++)  // cheack if name contain any non valid char , then name is not valid
        if ((a[x] <65 && a[x] != 32 && a[x] != 45) || a[x] > 122 || (a[x] > 90 && a[x] < 97))
            return 0 ;

    return 1 ;
}

/// function use to read names from files to list
void readFromFile(struct node cursor [], LIST l)
{
    FILE *in ;  // pointer to file using to reading from it
    int flag = 0 ;
    position p ;
    char name[50] = "" ;
    char filname[50]  ;

    printf("Enter name of file : ");
    scanf("%s",filname);        // enter file name
    sprintf(filname , "%s.txt",filname);
    in = fopen(filname,"r");             // open file
    if (in == NULL)
        printf("\n\nfile <%s> are not found !",filname);    // when file not exist
    else
    {
        // when file exist
        while(fgets(name,50, in )!= NULL)   // to get all names from file line by line and store them
        {
            if (stringLen(name) != 0)
                name[stringLen(name)-1] = '\0';  // add null char insted of new line char to end of name

            if(isValidName(name))
            {
                flag = 1 ;                          // when name valid add node to list and store the name on it .
                p = addNode(cursor, l);
                stringCpy(cursor[p].data, name);
            }
        }

        // flag = 1 when there any valid names in file
        // flag = 0 when file does not exist any valid name , then no names stored from it
        if(flag)
            printf("\n\nNames was brought from file <%s>.",filname);
        else
            printf("\n\nFile was empty !");
    }
}

/// fucntion to print the names as Catalgue in file
void printOnFile(struct node cursor[], LIST l)
{
    FILE *out ; // pointer to file using to writing on it
    int flag = 0 ;
    char filename [50] = "";
    printf("Enter File Name : "); // enter file name
    scanf("%s",filename);
    sprintf(filename , "%s.txt",filename);

    out = fopen(filename,"w");     // open the file

    char c1 = 'A',c2;              // using as first char of names

    // print the names according first char
    while(c1 <= 'Z')
    {
        flag = 0 ;
        c2 = c1 + 32 ;             // c1 a capital char , c2 same of c1 but small char

        position p = cursor[l].next ;

        // print names that start of char c1 or c2
        while(p!=0)
        {
            if(cursor[p].data[0]==c1 || cursor[p].data[0]== c2 ){
                if(!flag)
                fprintf(out,"%c:\n",c1);
                flag = 1 ;
                fprintf(out,"  %s\n",cursor[p].data);
            }


            p=cursor[p].next ;
        }
        c1++ ;
        fprintf(out,"\n");
    }
    printf("Names was printed in file <%s>.",filename);
    fclose(out);       // close the file
}

/// function use to print on screen a names which starts with specific character c1 from list l
/// this function return 1 if there any names start with char c1 , if no it's return 0
int searchByChar(struct node cursor[],LIST l, char c1 )
{

    int flag = 0 ;
    char c2 ;
    if(c1 > 90 )
        c2 = c1  - 32 ;      // if c1 small latter then c2 is same but capital
    else
        c2 = c1 + 32 ;       // if c1 capital latter then c2 is same but small

    position p = cursor[l].next ; // position pointing to nodes in the list
    char capital ;
    if(c2>c1 )
        capital = c1;
    else
        capital = c2 ;

    // print all names start with char c1 or c2
    while(p!=0)
    {
        if(cursor[p].data[0]==c1 || cursor[p].data[0]== c2 )
        {
            if(!flag)
            printf("%c : \n\n",capital);
            printf("- %s\n",cursor[p].data);
            flag = 1 ;
        }
        p = cursor[p].next ;
    }
    printf("\n");
    return flag ;

}

/// function use to print a names as  catalouge on screen
void printOnScreen(struct node cursor [], LIST l)
{
    char char1 = 'A';
    while(char1 <= 'Z')
    {
        if(searchByChar(cursor, l, char1++)){
        printf("__________________");
        }
    }
}

/// function print the menu
void printMenu()
{
    printf("\t ________________________________________________________\n");
    printf("\t|                                                        |\n");
    printf("\t|  List Of Operations  :                                 |\n");
    printf("\t|                                                        |\n");
    printf("\t|     1.Add Name.                                        |\n");
    printf("\t|                                                        |\n");
    printf("\t|     2.Delete Name.                                     |\n");
    printf("\t|                                                        |\n");
    printf("\t|     3.Print Names.                                     |\n");
    printf("\t|                                                        |\n");
    printf("\t|     4.Read Names From File.                            |\n");
    printf("\t|                                                        |\n");
    printf("\t|     5.Print Number Of Names.                           |\n");
    printf("\t|                                                        |\n");
    printf("\t|     6.Sort The List.                                   |\n");
    printf("\t|                                                        |\n");
    printf("\t|     7.Search For Name.                                 |\n");
    printf("\t|                                                        |\n");
    printf("\t|     8.Search By Character.                             |\n");
    printf("\t|                                                        |\n");
    printf("\t|     9.Print Name As Catalogue.                         |\n");
    printf("\t|                                                        |\n");
    printf("\t|     10.Print As Catalgue On File.                      |\n");
    printf("\t|                                                        |\n");
    printf("\t|     11.Clear The List.                                 |\n");
    printf("\t|                                                        |\n");
    printf("\t|     12.Exit.                                           |\n");
    printf("\t|________________________________________________________|\n\t\t* Enter Number Of Operation you need : ");
}

/*void displaycursor(struct node cursor [])
{
    int i ;
    printf("index            data                            next\n\n");
    for(i=0 ; i< cursorSize ; i++)
        printf(" %-11d%-38s %d\n\n",i,cursor[i].data,cursor[i].next);
    printf("\n\n");
}*/
