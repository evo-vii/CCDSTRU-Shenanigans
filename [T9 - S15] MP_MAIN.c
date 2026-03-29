/******************************************************************************
 *  Description     : This program is an interpretation of the logical messages from
                      the specifications of the CCDSTRU Machine Project.
 *  Author/s        : Borlasa, Sebastian O.
                      Sanico, Lance Matthew G.
 *                    Toledo, Nyle M.
 *  Section         : S15
 *  Last Modified   : 03/29/2026
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

// FUNCTION PROTOTYPES------------------------------------------------------------------------------------------------------------------

void delete(int* arr, int target);
void insert(int* arr, int target);
void printarray(int* arr, int size);
void toCoordinates(int single, int* x, int* y);
int toSingle(int x, int y);
int inSet(int single, int size, int arr[]);
int cardinality(int arr[], int n);
void displayGrid(gameState* game);

void Remove(int single, gameState* game);
void Replace(int single, gameState* game);
void Expand(int single, gameState* game);
void Update(int single, gameState* game);
void NextPlayerMove(int single, gameState* game);
void GameOver(gameState* game);

//Helper functions

/** 
  The function delete() deletes a number from the set.

  @param arr - Array elements to be counted.
  @param target - The value to be checked against an array element.
*/
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
            arr[i] = -1;
        }
    }
}

/** 
  The function insert() adds an element to the set
  at the end, with empty cells marked with negative
  numbers.

  @param arr - Array elements to be counted.
  @param target - The value to be checked against an array element.
*/
void insert(int* arr, int target)
{
    bool placed = 0;
    for(int i=0; i<TOTALCELLS && !placed; i++)
    {
        if(arr[i] < 0)
        {
            arr[i] = target;
            placed = 1;
        }
    }
}

/** 
  The function printarray() prints the array elements
  via loops.

  @param arr - Array elements to be counted.
  @param size - Array Size
*/
void printarray(int* arr, int size)
{
    for(int i=0; i<TOTALCELLS; i++)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
}

/** 
  The function toCoordinates() transforms a number into
  two coordinate values.

  @param single - A position in the grid
  @param x - The Abscissa/X-Coordinate
  @param y - The Ordinate/Y-Coordinate
*/
void toCoordinates(int single, int* x, int* y)
{
    *x = (single % ROWS) + 1;
    *y = (single / ROWS) + 1;
}

/** 
  The function toSingle() transforms two coordinate values
  into a single integer.

  @param x - The Abscissa/X-Coordinate
  @param y - The Ordinate/Y-Coordinate
*/
int toSingle(int x, int y)
{
    return((y-1)*ROWS+(x-1));
}

/** 
  The function inSet() checks a certain array element
  if it is present in the set. Specifically, it checks
  the presences of the grid's position in a set.

  @param arr - Array elements to be counted.
  @param size - Array Size
  @param single - A position in the grid
*/
int inSet(int single, int size, int arr[])
{
    int found = 0;
    for(int i=0; i<size; i++)
    {
        
        if(arr[i] == single)
        {
            found = 1;
        }
    }

    return found;
}

/** 
  The function cardinality() returns cardinality by counting
  non-negative elements.

  @param arr - Array elements to be counted.
  @param n - Array Size
*/
int cardinality(int arr[], int n)
{
    int count = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] >= 0)
        {
            count++;
        }
    }

    return count;
}

/** 
  The function DisplayGrid() presents the game grid's current
  state.

  @param game - The central structure covering the game's variables.
*/
void displayGrid(gameState* game)
{

    char cOccupant[ROWS][COLUMNS];
    int single;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++)
        {
            single = toSingle(i+1, j+1);
            if(inSet(single, TOTALCELLS, game->R))
            {
                cOccupant[i][j] = 'R'; 
            }
            else if(inSet(single, TOTALCELLS, game->B))
            {
                cOccupant[i][j] = 'B';
            }
            else
            {
                cOccupant[i][j] = '-';
            }
        }

    printf("\nGAME GRID SHOWING STATUS OF PLAYERS R & B\n\n");

    printf("======================\n");
    printf("|  %c  |  %c  |  %c  |\n", cOccupant[0][0], cOccupant[1][0], cOccupant[2][0]);
    printf("======================\n");
    printf("|  %c  |  %c  |  %c  |\n", cOccupant[0][1], cOccupant[1][1], cOccupant[2][1]);
    printf("======================\n");
    printf("|  %c  |  %c  |  %c  |\n", cOccupant[0][2], cOccupant[1][2], cOccupant[2][2]);
    printf("======================\n");
    printf("\nLEGEND: 'R' - P1, 'B' - P2, '-' - EMPTY, 'S' - EXPANSION, 'T' - EXPANDED\n\n");

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++)
        {
            single = toSingle(i+1, j+1);
            if(inSet(single, TOTALCELLS, game->S))
            {
                cOccupant[i][j] = 'S';
            }
            else if(inSet(single, TOTALCELLS, game->T))
            {
                cOccupant[i][j] = 'T';
            }
            else
            {
                cOccupant[i][j] = '-';
            }
        }

    printf("\nGAME GRID SHOWING STATUS OF S & T\n\n");

    printf("======================\n");
    printf("|  %c  |  %c  |  %c  |\n", cOccupant[0][0], cOccupant[1][0], cOccupant[2][0]);
    printf("======================\n");
    printf("|  %c  |  %c  |  %c  |\n", cOccupant[0][1], cOccupant[1][1], cOccupant[2][1]);
    printf("======================\n");
    printf("|  %c  |  %c  |  %c  |\n", cOccupant[0][2], cOccupant[1][2], cOccupant[2][2]);
    printf("======================\n");
    printf("\nLEGEND: '-' - EMPTY, 'S' - EXPANSION, 'T' - EXPANDED\n\n");
}
// MAIN FUNCTIONS---------------------------------------------------------------------------------------------------------------------------------

/** 
  The function Remove() removes an instance of the player in the
  grid.

  @param single - The intended position/coordinate of a player.
  @param game - The central structure covering the game's variables.
*/
void Remove(int single, gameState* game)
{
    if(game->go)
    {
        delete(game->R, single);
    }
    else
    {
        delete(game->B, single);
    }

    delete(game->S, single);
    delete(game->T, single);

}

/** 
  The function Replace() replaces territory within the grid.

  @param single - The intended position/coordinate of a player.
  @param game - The central structure covering the game's variables.
*/
void Replace(int single, gameState* game)
{
    game->found = 0;
    if(game->go && inSet(single, TOTALCELLS, game->B))
    {
        game->found = 1;
        delete(game->B, single);
    }
    else if(game->go && inSet(single, TOTALCELLS, game->R))
    {
        game->found = 1;
    }
    else if(game->go && !inSet(single, TOTALCELLS, game->R))
    {
        insert(game->R, single);
    }

    if(!game->go && inSet(single, TOTALCELLS, game->R))
    {
        game->found = 1;
        delete(game->R, single);
    }
    else if(!game->go && inSet(single, TOTALCELLS, game->B))
    {
        game->found = 1;
    }
    else if(!game->go && !inSet(single, TOTALCELLS, game->B))
    {
        insert(game->B, single);
    }

    if(game->found && !inSet(single, TOTALCELLS, game->S))
    {
        insert(game->S, single);
        game->found = 0;
    }
    else if(game->found && inSet(single, TOTALCELLS, game->S) && !inSet(single, TOTALCELLS, game->T))
    {
        insert(game->T, single);
        Expand(single, game);
    }
}

/** 
  The function Expand() sets up the territory for expansion for the
  players.

  @param single - The intended position/coordinate of a player.
  @param game - The central structure covering the game's variables.
*/
void Expand(int single, gameState* game)
{
    
    int a, b;
    int u, k, d, r;

    toCoordinates(single, &a, &b);

    printf("\nExpanding: %d and %d from %d\n", a, b, single);

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
        d = toSingle(a+1, b);
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

    Remove(single, game);

    if(game->go)
    {
        if(u != -1)
        {
           printf("Expanding left: %d and %d from %d\n", a, b, single);
           Replace(u, game); 
        }
    }
    else
    {
        if(d != -1)
        {
           printf("Expanding right: %d and %d from %d\n", a, b, single);
           Replace(d, game); 
        }
    }

    if(k != -1)
    {
        printf("Expanding high: %d and %d from %d\n", a, b, single);
        Replace(k, game); 
    }
    if(r != -1)
    {
        printf("Expanding low: %d and %d from %d\n", a, b, single);
        Replace(r, game); 
    }
}

/** 
  The function Update() sets game status to 0 and checks for the positions
  for S and T.

  @param single - The intended position/coordinate of a player.
  @param game - The central structure covering the game's variables.
*/
void Update(int single, gameState* game)
{
    
    game->good = 0;
    if(!inSet(single, TOTALCELLS, game->S))
    {
        game->good = !game->good;
        insert(game->S, single);
    }

    else if(!game->good && inSet(single, TOTALCELLS, game->S) && !inSet(single, TOTALCELLS, game->T))
    {
        insert(game->T, single);
        Expand(single, game);
    }
}

/** 
  The function NextPlayerMove() is an iterative function looping for every
  instance each player is given a chance to move.

  @param single - The intended position/coordinate of a player.
  @param game - The central structure covering the game's variables.
*/
void NextPlayerMove(int single, gameState* game)
{

  if (!game->over && game->start && game->go)
  {
    //(R = R ∪ {pos} ∧ S = S ∪ {pos}
    insert(game->R, single); 
    insert(game->S, single);
    
    // ∧ good = true
    game->good = 1;
  }
  
  // (¬over ∧ start ∧ ¬go) 
  else if (!game->over && game->start && !game->go)
  {
    //(B = B ∪ {pos} ∧ S = S ∪ {pos}
    insert(game->B, single); 
    insert(game->S, single);

    //S ∪ {pos}
    game->good = 1;
  }
  else if (!game->over && !game->start && ((game->go && inSet(single, TOTALCELLS, game->R)) || (!game->go && inSet(single, TOTALCELLS, game->B))))
  {
    Update(single, game);
    game->good = 1;
  }
  else
  {
    printf("That's not the right move...");
  }

  if (game->start && cardinality(game->R, TOTALCELLS) == 1 && cardinality(game->B, TOTALCELLS) == 1)
    game->start = 0;

  if (!game->over && game->good == 1)
  {
    game->good = !game->good;
    game->go = !game->go;
    game->val++;
  }

  int R = cardinality(game->R, TOTALCELLS);
  int B = cardinality(game->B, TOTALCELLS);
  int F = TOTALCELLS - R - B;
  game->over = (F == 3 || game->val > 20 || (!game->start && ((R && !B) || (!R && B))));
}

/** 
  The function GameOver() sets the conditions for the game to end.

  @param game - The central structure covering the game's variables.
*/
void GameOver(gameState* game)
{

    if (game->over == 1 && cardinality(game->R, TOTALCELLS) > cardinality(game->B, TOTALCELLS))
        printf("\nR wins!\n");
    else if (game->over == 1 && cardinality(game->R, TOTALCELLS) < cardinality(game->B, TOTALCELLS))
        printf("\nB wins!\n");
    else if (game->over && cardinality(game->R, TOTALCELLS) == cardinality(game->B, TOTALCELLS))
        printf("\ndraw\n");

}

// MAIN--------------------------------------------------------------------------------------------------------------------------------------

int main()
{

  int x, y;

  gameState game = {.R = {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
                    .S = {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
                    .B = {-1, -1, -1, -1, -1, -1, -1, -1, -1}, 
                    .T = {-1, -1, -1, -1, -1, -1, -1, -1, -1}};
  game.good = 0, game.found = 0, game.val = 0;
  game.go = 1, game.start = 1;

  // Begin actual code executions below.

    // Begin the game flow

    printf("\n\n[ Welcome to the Game! ]\n\n");

    do
    {
        // Displays grid for every instance of a player's turn.
        displayGrid(&game);
        
        printf("MOVE #%d\n", game.val);

        do
        {
            printf("Your turn, player %d! Type a an X coordinate (eg., 1 1, starts from top left at 1 1):", 2 - game.go);
            scanf("%d", &x); // scanf("%d %d%*c", &x, &y);

            if (x > 3 || x < 1)
                printf("\nOut of Bounds! Your range is from (1, 1) to (3, 3) only!\n");

        } while (x > 3 || x < 1); // Guards options to prevent potentially buggy inputs.

        do
        {
            printf("Your turn, player %d! Type a Y coordinate (eg., 1 1, starts from top left at 1 1):", 2 - game.go);
            scanf("%d", &y);

            if (x > 3 || x < 1)
                printf("\nOut of Bounds! Your range is from (1, 1) to (3, 3) only!\n");

        } while (x > 3 || x < 1);

        NextPlayerMove(toSingle(x, y), &game);

        if (game.over == 1) // Game over condition
            GameOver(&game);

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
