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


// FUNCTIONS---------------------------------------------------------------------------------------------------------------------------------

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
void NextPlayerMove(int pos)
{

  // (¬over ∧ start ∧ go) → (R = R ∪ {pos} ∧ S = S ∪ {pos} ∧ good = true)
  // (¬over ∧ start ∧ ¬go) → (B = B ∪ {pos} ∧ S = S ∪ {pos} ∧ good = true)
  // (¬over ∧ ¬start ∧ (go ∧ pos ∈ R ∨ ¬go ∧ pos ∈ B)) → (Update(pos) ∧ good = true)
  // (start ∧ |R| = 1 ∧ |B| = 1) → start = false
  // (¬over ∧ good) → (good = ¬good ∧ go = ¬go ∧ val = val + 1)

  

}

/*
  <function description + params>
*/
void GameOver()
{

  // result ∈ {“R wins”, “B wins”, “draw”}
  // (over ∧ |R| > |B|) → result = “R wins”
  // (over ∧ |R| < |B|) → result = “B wins”
  // (over ∧ |R| = |B|) → result = “draw”



}


// MAIN--------------------------------------------------------------------------------------------------------------------------------------

int main()
{

  printf("\n\n[ Welcome to the Game! ]\n\n");
  gameState game = {.R = {-1}, .S = {-1}, .B = {-1}, .T = {-1}};
  game.good, game.found, game.val = 0;
  game.go, game.start = 1;

  // Begin actual code executions below.




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
