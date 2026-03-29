/******************************************************************************
 *  Description     : This program is an interpretation of the logical messages from
                      the specifications of the CCDSTRU Machine Project.
 *  Author/s        : Borlasa, Sebastian O.
                      Sanico, Lance Matthew G.
 *                    Toledo, Nyle M.
 *  Section         : S15
 *  Last Modified   : 03/25/2026 @ 11:15am
 ******************************************************************************/

// PRE-PROCESSOR DIRECTIVES------------------------------------------------------------------------------------------------------------------
#include <stdio.h>

#define ROWS 3
#define COLUMNS 3
#define TOTALCELLS 9

typedef short bool;



// DEFINITIONS-------------------------------------------------------------------------------------------------------------------------------

// sys_variables
typedef struct game
{
  int R[9], B[9], S[9], T[9];
  bool good, go, start, over, found;
  int val;
} gameState;


//Helper functions

void displayGrid()
{

    char cOccupant[ROWS][COLUMNS];

    printf("======================\n");
    printf("|  %c  |  %c  |  %c  |\n", cOccupant[0][0], cOccupant[1][0], cOccupant[2][0]);
    printf("======================\n");
    printf("|  %c  |  %c  |  %c  |\n", cOccupant[0][1], cOccupant[1][1], cOccupant[2][1]);
    printf("======================\n");
    printf("|  %c  |  %c  |  %c  |\n", cOccupant[0][2], cOccupant[1][2], cOccupant[2][2]);
    printf("======================\n");

}

//deletes a number from the set.
void delete(int* arr, int target)
{
    short jump = 0;
    for(int i=0; i < TOTALCELLS; i++)
    {
        if(arr[i] == target)
        {
            jump++;
        }
        else if(jump)
        {
            arr[i-jump] = arr[i];
        }
    }
}

//adds an element to the set at the end (empty cells are marked with negative numbers)
void insert(int* arr, int target)
{
    for(int i=0; i<TOTALCELLS; i++)
    {
        if(arr[i] < 0)
        {
            arr[i] = target;
        }
    }
}

//Turns a number into an (x, y) coordinate (FROM THE TOP LEFT, THINK 2D ARRAYS)
void toCoordinates(int single, int* x, int* y)
{
    *y = (single % ROWS) + 1;
    *x = (single / ROWS) + 1;
}

//Turns an (x, y) pair into a single number
int toSingle(int x, int y)
{
    return((x-1)*ROWS+(y-1));
}

//Checks if an element is in the set.
int inSet(int single, int size, int arr[])
{
    int found = 0;
    for(int i=0; i<size; i++)
    {
        if(arr[i] = single)
        {
            found = 1;
        }
    }

    return found;
}


// MAIN FUNCTIONS---------------------------------------------------------------------------------------------------------------------------------

//    (DEVNOTE - Lance: All functions are defaulted to void, please assume they are not yet fully interpreted - 03/04/26)

/*
  <function description + params>
*/
void Remove()
{



}

/*
  <function description + params>
*/
void Replace()
{



}

/*
  <function description + params>
*/
void Expand(int single, gameState game)
{
    
    // (a, b) = pos
    // u, d, k, r ∈ M
    // u = (a − 1, b)
    // d = (a + 1, b)
    // k = (a, b − 1)
    // r = (a, b + 1)
    // Remove(pos)
    // (go) → Replace(u)
    // (¬go) → Replace(d)
    // Replace(k)
    // Replace(r)
    
    int a, b;
    int u, k, d, r;

    toCoordinates(single, &a, &b);

    //Bounds checks
    if(a-1 > 0)
    {
        u = toSingle(a-1, b);
    }
    else
    {
        u = -1;
    }

    if(a+1 < ROWS+1)
    {
        d = toSingle(a-1, b);
    }
    else
    {
        d = -1;
    }

    if(b-1 > 0)
    {
        k = toSingle(a, b-1);
    }
    else
    {
        k = -1;
    }

    if(b+1 < COLUMNS+1)
    {
        r = toSingle(a, b+1);
    }
    else
    {
        u = -1;
    }

    Remove(single);

    if(game.go)
    {
        Replace(u);
    }
    else
    {
        Replace(d);
    }
    Replace(k);
    Replace(r);
}

/*
  <function description + params>
*/
void Update(int single, gameState game)
{
    // good = false
    // (pos̸∈ S) → (S = S ∪ {pos} ∧ good = ¬good)
    // (¬good ∧ pos ∈ S ∧ pos̸∈ T ) → (T = T ∪ {pos} ∧ Expand(pos))
    
    game.good = 0;
    if(!inSet(single, TOTALCELLS, game.S))
    {
        game.good = !game.good;
        insert(game.S, single);
    }

    if(!game.good && inSet(single, TOTALCELLS, game.S) && !inSet(single, TOTALCELLS, game.T))
    {
        insert(game.T, single);
        Expand(game.T, game);
    }
}

/*
  <function description + params>
*/
void NextPlayerMove(int single, gameState game)
{

  // (¬over ∧ start ∧ go) → (R = R ∪ {pos} ∧ S = S ∪ {pos} ∧ good = true)
  // (¬over ∧ start ∧ ¬go) → (B = B ∪ {pos} ∧ S = S ∪ {pos} ∧ good = true)
  // (¬over ∧ ¬start ∧ (go ∧ pos ∈ R ∨ ¬go ∧ pos ∈ B)) → (Update(pos) ∧ good = true)
  // (start ∧ |R| = 1 ∧ |B| = 1) → start = false
  // (¬over ∧ good) → (good = ¬good ∧ go = ¬go ∧ val = val + 1)

  if (!game.over && game.start == 1 && game.go == 1)
  {
    insert(game.R, single); 
    insert(game.S, single);

    game.good = 1;
  }
  else if (!game.over && game.start == 1 && game.go == 0)
  {
    insert(game.B, single); 
    insert(game.S, single);

    game.good = 1;
  }
  else if (!game.over && !game.start && ((game.go == 1 && inSet(single, TOTALCELLS, game.R)) || (!game.go && inSet(single, TOTALCELLS, game.B))))
  {
    Update(single, game);
    game.good = 1;
  }

  if (game.start && R[] == 1 && B[] == 1)
    game.start = 0;

  if (!game.over && game.good == 0)
  {
    game.good = !game.good;
    game.go == !game.go;
    game.val++;
  }

}

/*
  <function description + params>
*/
void GameOver(gameState game)
{

  // result ∈ {“R wins”, “B wins”, “draw”}
  // (over ∧ |R| > |B|) → result = “R wins”
  // (over ∧ |R| < |B|) → result = “B wins”
  // (over ∧ |R| = |B|) → result = “draw”

    if (game.over == 1 && game.R[] > game.B[])
        printf("\nR wins!\n");
    else if (game.over == 1 && game.R[] < game.B[])
        printf("\nB wins!\n");
    else if (game.over && game.R[] == game.B[])
        printf("\ndraw\n");

}


// MAIN--------------------------------------------------------------------------------------------------------------------------------------

int main()
{

  int nChoice;

  gameState game = {.R = {-1}, .S = {-1}, .B = {-1}, .T = {-1}};
  game.good, game.found, game.val = 0;
  game.go, game.start = 1;

  // Begin actual code executions below.

    // Begin the game flow

    printf("\n\n[ Welcome to the Game! ]\n\n");

    

    do
    {



        if (game.over == 1)
            GameOver(game);

    } while (game.over != 1);



  return 0;
}

/**
 * This is to certify that this project is our own work, based on our personal
 * efforts in studying and applying the concepts learned. We have constructed the
 * functions and their respective algorithms and corresponding code by ourselves.
 * The program was run, tested, and debugged by our own efforts. We further certify
 * that we have not copied in part or whole or otherwise plagiarized the work of other
 * students and/or persons, nor did we employ the use of AI in any part of the deliverable.
 
   Borlasa, Sebastian O.
   Sanico, Lance Matthew G.
   Toledo, Nyle M.

 */
