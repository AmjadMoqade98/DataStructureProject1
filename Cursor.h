#ifndef _CURSORH_
#define _CURSORH_
#include "String.h"

/// structure of node
typedef unsigned int ptr ;
struct node
{
    char data [50] ;
    ptr next  ;
};
typedef ptr position ;
typedef ptr LIST ;
//////////////////////////////////////////////////////////////////////////

position findPrevious(struct node [] , LIST , position  );
position stringSearch(struct node  [] , LIST ,char []);
void initializeCursors(struct node [] , int );
position cursorAlloc(struct node []);
void cursorFree(struct node [] , position );
position addNode(struct node  [] , LIST );
int isListEmpty(struct node [] , LIST );
int isCursorFull(struct node [] );
void deleteString(struct node [] , LIST , char []);
position findPrevious(struct node  [] , LIST , position  );
position stringSearch(struct node [] , LIST ,char []);
void printList(struct node [] , LIST );
int numOfElement(struct node [] , LIST );
void fromListToList(struct node [] , LIST  , LIST , position );
void radixSortString(struct node [] ,LIST  );
int maxStrLen(struct node  [] , LIST );
void removeFirst(struct node  [] , LIST );
void clearList(struct node  [] , LIST );
////////////////////////////////////////////////////////////////////////

/// function use to initialize cursor
void initializeCursors(struct node cursor[] , int cursorSize){
    int i ;
    for(i=0 ; i<cursorSize  ; i++)
    {
        cursor[i].next = i + 1 ;         // make each node have a index of next node
        stringCpy(cursor[i].data , "");  // initialize the data of nodes to empty string
    }
    cursor[cursorSize -1 ].next = 0 ;    // the next for last node = 0
}

/// function use to reserve element from cursor to use it as list or header and return it's position
position cursorAlloc(struct node cursor[])
{

    if(!isCursorFull(cursor))
    {
        position p = cursor[0].next ;
        cursor[0].next = cursor[p].next ;
        cursor[p].next = 0 ;
        return p ;
    }

        printf("cursor are full of !!");
        return 0 ;
}

/// function use to release a specific element to cursor to used again
void cursorFree(struct node cursor[] , position p)
{
    cursor[p].next = cursor[0].next ;
    cursor[0].next = p ;
}

/// function return 1 if specific list are empty and 0 if not
int isListEmpty(struct node cursor[] , LIST l){
return (cursor[l].next==0) ;
}

/// function return 1 if cursor are full and 0 if not
int isCursorFull(struct node cursor[] ){
return (cursor[0].next ==0);
}

/// function used to reserve element from cursor and link it with specific list and return it's position
position addNode(struct node cursor [] , LIST l)
{
    position p = cursorAlloc(cursor) ;
    if(p){
    cursor[p].next = cursor[l].next ;
    cursor[l].next = p ;
    }
    return p ;
}

/// function used to release element from specific list in cursor which contain specific string
void deleteString(struct node cursor[] , LIST l, char a[])
{

    position p = stringSearch(cursor , l, a);
    position temp ;
    if (p){
        p = findPrevious(cursor , l , p);
        temp = cursor[p].next ;
        cursor[p].next = cursor[temp].next ;
        cursorFree(cursor , temp );
        }
    else
         printf("\n%s are not exist in the list\n",a);

}

/// function return a position of previous element for specific element
position findPrevious(struct node cursor [] , LIST l, position p )
{
    position temp = l ;
    while(cursor[temp].next != p )
        temp  = cursor[temp].next ;
    return temp ;
}

/// function return a position for element contain specific string in list
position stringSearch(struct node cursor [] , LIST l,char a[])
{
    position p = cursor[l].next ;
    while(p!= 0 )
    {
        if(stringCmp(a,cursor[p].data))
            return p ;
        p = cursor[p].next ;
    }
        return 0 ;
}

/// function use to print all elements data from specific list
void printList(struct node cursor[] , LIST l)
{
    position p = cursor[l].next ;
    if(cursor[l].next == 0)
    printf("List are empty !");
    else {
    printf("List Of Names :\n") ;
    while(p!=0)
    {
        printf("\n- %s",cursor[p].data);
        p = cursor[p].next ;
    }
    printf("\n");
    }
}

/// function return number of element in specific list
int numOfElement(struct node cursor[] , LIST l){
int counter =0 ;
position p = cursor[l].next ;
while(p!=0){
    counter++ ;
    p = cursor[p].next ;
}
return counter ;
}

/// function use to move an element from list to another inside cursor
void fromListToList(struct node cursor[] , LIST l1 , LIST l2 , position p){
cursor[l2].next = cursor[p].next ;
cursor[p].next = cursor[l1].next ;
cursor[l1].next = p ;
}

/// function use to sort a list of string inside cursor
/// first 27 element are buckets used in sort , a list contain strings which we need to sort is not from first 27 element in cursor
void radixSortString(struct node cursor[] ,LIST names )
{
    int i, j ;

    position p;
    int len = maxStrLen(cursor , names); // find a length of longest string in the list

    // i index to characters start from last
    for(i = len-1 ; i>=0; i--)
    {
        p = cursor[names].next ; // position used to pointing to elements in list

        // put the element on buckets according to char in index i
        while(p!=0)
        {
            if(stringLen(cursor[p].data)< (i+1))
                j = 1 ;
            else {
              j = cursor[p].data[i];
              if(j==' ')
                j= 1 ;                     // find the buckets number
                else if (j>90)
                j-=95 ;
                else
                j-=63 ;
            }

           fromListToList(cursor , j , names , p); // move the element from our list to bucket
            p = cursor[names].next;
        }

        // return all element from bucket to our list start from last buckets
       for(j=27 ; j>=1 ; j--){
            p = cursor[j].next ;

            while(p!= 0){
                fromListToList(cursor , names,j,p);
                p=cursor[j].next ;
            }
            }
    }
}

/// function return a length of longest string in specific list in cursor
int maxStrLen(struct node cursor [] , LIST l)
{
    position p  = cursor[l].next ;
    int max =0 ;
    while(p!= 0)
    {
        if(stringLen(cursor[p].data) > max)
            max = stringLen(cursor[p].data) ;
        p = cursor[p].next ;
    }
    return max ;
}

/// function used to release first element from specific list in cursor
void removeFirst(struct node cursor [] , LIST l)
{
    if(cursor[l].next != 0)
    {
        position p = cursor[l].next;
        cursor[l].next = cursor[p].next ;
        stringCpy(cursor[p].data,"");
        cursorFree(cursor , p);
    }
}

/// function use to release all elements from specific list
void clearList(struct node cursor [] , LIST l){
while(cursor[l].next != 0)
    removeFirst(cursor , l );
}

#endif
