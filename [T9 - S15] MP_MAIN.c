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



// DEFINITIONS-------------------------------------------------------------------------------------------------------------------------------

// sys_variables
typedef struct game
{
  int R[8], B[8], S[8], T[8], V[8];
  short good, go , start, over, found;
  int val;
} gameState;


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
void Expand()
{



}

/*
  <function description + params>
*/
void Update()
{



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
