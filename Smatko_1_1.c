#include "list.h"//Header file is included to the folder
#include <stdio.h>
#include <stdlib.h>
#include "fatal.h"//Header file is included to the folder

typedef int ElementType;//This will be defined as integer.
//Node structure for the players list.
struct Node {
    ElementType Element;
    Position Next;
};
void PrintList(const List L);//Printlist function declaration. All functions are defined after Main.

int main() {
    List L; //Declaring L list.
    int m, n; //Variables for number of players(N) and the elimination count(M).
    Position P; //Pointer P will work through the list of players.
    //Requesting user inputs.
    printf("Please enter the number of players (N): ");
    scanf("%d", &n);
    printf("Please enter M: ");
    scanf("%d", &m);

    L = MakeEmpty(NULL); //Using function to make the empty list.
    P = Header(L); //Pointer will point to the header for now.

    //Put players into the list with player number as  current 'i' till N.
    for (int i = 1; i <= n; i++) 
    {
        Insert(i, L, P);
        P = Advance(P);
    }
    Position Last = P; //New pointer for the last node.
    Last->Next = Header(L);//Here the list is closed/made circular.


    P = Header(L);// Making sure pointer is at the start of the list.

    for (int k = 1; k < n; k++)//I chose to loop till N, as this number is known.
    {
        //Pass the potato M-1 times.
        for (int i = 0; i <= m-1 ; i++) 
        {
            P =Advance(P);//Advancing through nodes player by player.
            if (IsLast(P, L)) 
            {
                P=Header(L);
            }
        }
        //Eliminate the player.
        ElementType X = Retrieve(Advance(P)); //Getting the value of the next node for X.
        Delete(X, L);
        if (IsLast(P, L)) {
                P=Header(L);
            }
        printf("Eliminated player %d\n", X);
    } ;

    printf("Winner is player %d\n", Retrieve(Advance(P)));
    //Free memory.
    free(L);
    return 0;
}



// Function definitions
//********************************************************************
List MakeEmpty(List L) {
    if (L != NULL)
        DeleteList(L);
    L = malloc(sizeof(struct Node));
    //if (L == NULL)
        //FatalError("Out of memory!");
    L->Next = NULL;
    return L;
}

//********************************************************************
void 
Insert(ElementType X, List L, Position P) {
    Position TmpCell = malloc(sizeof(struct Node));
    //if (TmpCell == NULL)
        //FatalError("Out of space!!!");
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

//********************************************************************
Position
Header( List L )
{
    return L;
}

//********************************************************************
int
IsEmpty( List L )
{
    return L->Next == Header(L);//As I am using a circular list, no nodes should point to NULL any more.
}

//********************************************************************
Position
Advance( Position P )
{
    return P->Next;
}

//********************************************************************
int IsLast( Position P, List L )
{
    return P->Next == Header(L);
}

//********************************************************************
ElementType 
Retrieve(Position P) 
{
    if (P != NULL) {
        return P->Element; 
    } else {
        
        return -1;
    }
}

//********************************************************************
void 
Delete( ElementType X, List L )
{
    Position P, TmpCell;

    P = FindPrevious( X, L ); 

    if( !IsLast( P, L ) )  /* Assumption of header use */
    {                      /* X is found; delete it */
        TmpCell = P->Next; 
        P->Next = TmpCell->Next;  /* Bypass deleted cell */
        free( TmpCell );
    }
}

//********************************************************************
void
DeleteList( List L )
{
    Position P, Tmp;

    P = L->Next;  
    L->Next = Header(L);
    while( P != Header(L) )
    {
        Tmp = P->Next; 
        free( P ); 
        P = Tmp;
    }
}

//********************************************************************
Position
FindPrevious( ElementType X, List L )
{
    Position P;
    P = L;
    while( P->Next != Header(L) && P->Next->Element != X )
        {P = P->Next;}
    return P;
}

//********************************************************************
void 
PrintList(const List L)
{
    Position P=Header(L);

    if(IsEmpty(L))
        printf("Empty list\n");
    else{
        do
        {
            P=Advance(P);
            printf("%d", Retrieve(P));
        } while (!IsLast(P,L));
        {printf("\n");}
        }
    }
//end