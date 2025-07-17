
#include <iostream>
#include <conio.h>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <random>
#include <windows.h>
#include <fstream>

using namespace std;

//Global variables:
int playerX;
int playerY;
int ghostX;
int ghostY;
int ghost2X, ghost2Y;
int Map;
const int rows = 15, cols = 31;
bool gameOver = false;
bool won = false, loss = false;
char direction = ' ';
int score = 0;
bool noDots = false;

//color codes:
const int RED = 12;
const int PINK = 13;
const int GREEN = 10;
const int YELLOW = 14;
const int BLUE = 9;
const int WHITE = 15;

void map(char grid[rows][cols],int &score);
void playerMovement(char grid[rows][cols]);
void ghostMovement(char grid[rows][cols]);
void ghost2Movement(char grid[rows][cols]);
void checkLoss(char grid[rows][cols]);
bool checkWin(char grid[rows][cols], bool noDots);
void setColor(int color);


int main() {
	char grid[rows][cols];

    //Game menu:
    setColor(BLUE);
    cout << "\t\t\t    ______ " << "  " << " ______ " << "  " << " _____  " << "  " << " __     __  " << "  " << " ______ " << "  " << " _     _ " << endl;
    cout << "\t\t\t   |  __  |" << "  " << "|  __  |" << "  " << "/  ___  " << "  " << "|  \\   /  | " << "  " << "|  __  |" << "  " << "|  \\  | |" << endl;
    cout << "\t\t\t   | |__| |" << "  " << "| |__| |" << "  " << "| |     " << "  " << "|    \\/   | " << "  " << "| |__| |" << "  " << "| | \\ | |" << endl;
    cout << "\t\t\t   |   ___|" << "  " << "|  __  |" << "  " << "| |     " << "  " << "|  |   |  | " << "  " << "|  __  |" << "  " << "| |  \\| |" << endl;
    cout << "\t\t\t   |  |    " << "  " << "| |  | |" << "  " << "| |____ " << "  " << "|  |   |  | " << "  " << "| |  | |" << "  " << "| |   \\ |" << endl;
    cout << "\t\t\t   |__|    " << "  " << "|_|  |_|" << "  " << "  ____/ " << "  " << "|__|   |__| " << "  " << "|_|  |_|" << "  " << "|_|   |_|" << endl;

    cout << "\n\n\t\t\t\t\t\t  Welcome to PACMAN!";
    this_thread::sleep_for(chrono::milliseconds(1100));
    system("cls");
    
    setColor(YELLOW);
    cout << "\n\n\t\t\t\t\t\t  INSTRUCTIONS:" << endl;
    cout << "\t\t\t\t  -> Use W A S D to move." << endl;
    cout << "\t\t\t\t  -> Score increments on collecting points (dots on map)." << endl;
    cout << "\t\t\t\t  -> If touched to either ghost, game ends." << endl;
    cout << "\t\t\t\t  -> If collected all points, You'll win the game." << endl << endl;
    setColor(RED);
    cout << "\t\t\t\t\t  Select map Easy or Advanced" << endl;
    cout << "\t\t\t\t         Enter 1 for map 1, 2 for map 2: ";
    cin >> Map;
    //Managing positions of player and ghosts based on inputs:
    if (Map == 1) {
        playerX = 11;
        playerY = 15;
        ghostX = 1;
        ghostY = 23;
        ghost2X = 13, ghost2Y = 7;
    }
    else if (Map == 2) {
        playerX = 13;
        playerY = 15;
        ghostX = 1;
        ghostY = 23;
        ghost2X = 13, ghost2Y = 7;
    }


    //main game logic:
	while (!gameOver) {
		map(grid, score);

        ghostMovement(grid);
        ghost2Movement(grid);
        playerMovement(grid);

        checkWin(grid, noDots);
        if (checkWin(grid, noDots)) {
            won = true;
            gameOver = true;
            break;
        }
		checkLoss(grid);
        if (gameOver) {
            loss = true;
            break;
        }
		//to slow down each iteration:
		this_thread::sleep_for(chrono::milliseconds(90));
	}
    //To show map after game ends:
	map(grid, score);

    //To display won or lost message on screen:
    if (won) {
        setColor(YELLOW);
        cout << "\n\t\t\t  You Won!" << endl;
    }
    else if (loss) {
        setColor(RED);
        cout << "\n\t\t\t  You lost!" << endl;
    }

    //File handling to store score of player:
    ofstream outputFile("score.txt", ios::app);

    if (outputFile.is_open()) {
        outputFile << "Score: " << score << endl;
        outputFile.close();
    }
    
    //Reset color to whte
    setColor(WHITE);
	return 0;
}



void map(char grid[rows][cols], int &score) {
	system("cls");
    //Shows score on left side:
    cout << "\t\t\t\t\t\t\t\t\t\t\t SCORE: " << score << endl;


    // Map 1:
	if (Map == 1) {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (i == 0 || i == 14 || j == 0 || j == 30)
                {
                    grid[i][j] = '#';
                }
                else if (i == 5 && j < 20 && j > 10)
                {
                    grid[i][j] = '#';
                }
                else if (i == 9 && j < 20 && j > 10)
                {
                    grid[i][j] = '#';
                }
                else if (j == 11 && i < 9 && i > 5)
                {
                    grid[i][j] = '#';
                }
                else if (j == 19 && i < 9 && i > 5)
                {
                    grid[i][j] = '#';
                }
                else if (i == 6 && j < 19 && j > 11)
                {
                    grid[i][j] = ' ';
                }
                else if (i == 7 && j < 19 && j > 11)
                {
                    grid[i][j] = ' ';
                }
                else if (i == 8 && j < 19 && j > 11)
                {
                    grid[i][j] = ' ';
                }
                else if (j == 5 && i < 6 && i > 0)
                {
                    grid[i][j] = '#';
                }
                else if (j == 5 && i < 14 && i > 8)
                {
                    grid[i][j] = '#';
                }
                else if (j == 25 && i < 6 && i > 0)
                {
                    grid[i][j] = '#';
                }
                else if (j == 25 && i < 14 && i > 8)
                {
                    grid[i][j] = '#';
                }
                else if (i == 2 && j < 20 && j > 10)
                {
                    grid[i][j] = '#';
                }
                else if (i == 12 && j < 20 && j > 10)
                {
                    grid[i][j] = '#';
                }
                else if (i == 13 && j == 11)
                {
                    grid[i][j] = '#';
                }
                else if (i == 13 && j == 19)
                {
                    grid[i][j] = '#';
                }
                else if (i == 1 && j == 11)
                {
                    grid[i][j] = '#';
                }
                else if (i == 1 && j == 19)
                {
                    grid[i][j] = '#';
                }
                else if (i == 13 && j > 11 && j < 19)
                {
                    grid[i][j] = ' ';
                }
                else if (i == 1 && j > 11 && j < 19)
                {
                    grid[i][j] = ' ';
                }
                else if (i == playerX && j == playerY) {
                    grid[i][j] = 'O';
                }
                else if (i == ghostX && j == ghostY) {

                    grid[i][j] = '>';
                }
                else if (i == ghost2X && j == ghost2Y) {
                    grid[i][j] = '<';
                }
                //To prevent map, printing dots on spaced area:
                else if (grid[i][j] == ' ') {
                    continue;
                }

                else
                {
                    grid[i][j] = '.';
                }
            }
        }
	}

    // Map 2:
	else if (Map == 2) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
               
                if (i == 0 || i == 14) {
                    grid[i][j] = '#';
                }
                else if (j == 0 || j == 30) {
                    grid[i][j] = '#';
                }
                else if (i == 5 && j < 3 && j > 0) {
                    grid[i][j] = '#';
                }
                else if (i == 9 && j < 3 && j > 0) {
                    grid[i][j] = '#';
                }
                else if (i == 2 && j < 5 && j > 1) {
                    grid[i][j] = '#';
                }
                else if (i == 3 && j == 2) {
                    grid[i][j] = '#';
                }
                else if (j == 6 && i < 7 && i > 0) {
                    grid[i][j] = '#';
                }
                else if (i == 4 && j < 7 && j > 3) {
                    grid[i][j] = '#';
                }
                else if (i == 6 && j < 9 && j > 5) {
                    grid[i][j] = '#';
                }
                else if (i == 7 && j < 5 && j > 1) {
                    grid[i][j] = '#';
                }
                else if (i == 10 && j < 7 && j > 3) {
                    grid[i][j] = '#';
                }
                else if (i == 2 && j < 11 && j > 7) {
                    grid[i][j] = '#';
                }
                else if (i == 8 && j < 11 && j > 5) {
                    grid[i][j] = '#';
                }
                else if (j == 4 && i < 10 && i > 3) {
                    grid[i][j] = '#';
                }
                else if (j == 8 && i < 7 && i > 1) {
                    grid[i][j] = '#';
                }
                else if (j == 6 && i < 14 && i > 11) {
                    grid[i][j] = '#';
                }
                else if (j == 8 && i < 13 && i > 7) {
                    grid[i][j] = '#';
                }
                else if (j == 10 && i < 7 && i > 3) {
                    grid[i][j] = '#';
                }
                else if (j == 10 && i < 11 && i > 7) {
                    grid[i][j] = '#';
                }
                else if (j == 15 && i < 5 && i > 1) {
                    grid[i][j] = '#';
                }
                else if (j == 15 && i < 13 && i > 7) {
                    grid[i][j] = '#';
                }
                else if (j == 12 && i < 9 && i > 5) {
                    grid[i][j] = '#';
                }
                else if (j == 18 && i < 9 && i > 5) {
                    grid[i][j] = '#';
                }
                else if (j == 17 && i < 7 && i > 3) {
                    grid[i][j] = '#';
                }
                else if (j == 20 && i < 7 && i > 3) {
                    grid[i][j] = '#';
                }
                else if (j == 20 && i < 11 && i > 7) {
                    grid[i][j] = '#';
                }
                else if (j == 20 && i < 14 && i > 11) {
                    grid[i][j] = '#';
                }
                else if (j == 22 && i < 4 && i > 1) {
                    grid[i][j] = '#';
                }
                else if (j == 22 && i < 7 && i > 4) {
                    grid[i][j] = '#';
                }
                else if (j == 22 && i < 13 && i > 7) {
                    grid[i][j] = '#';
                }
                else if (j == 24 && i < 5 && i > 0) {
                    grid[i][j] = '#';
                }
                else if (j == 24 && i < 14 && i > 11) {
                    grid[i][j] = '#';
                }
                else if (j == 26 && i < 11 && i > 3) {
                    grid[i][j] = '#';
                }
                else if (j == 28 && i < 13 && i > 10) {
                    grid[i][j] = '#';
                }
                else if (i == 10 && j < 14 && j > 9) {
                    grid[i][j] = '#';
                }
                else if (i == 12 && j < 11 && j > 7) {
                    grid[i][j] = '#';
                }
                else if (i == 4 && j < 14 && j > 9) {
                    grid[i][j] = '#';
                }
                else if (i == 6 && j < 15 && j > 11) {
                    grid[i][j] = '#';
                }
                else if (i == 6 && j < 19 && j > 15) {
                    grid[i][j] = '#';
                }
                else if (i == 8 && j < 19 && j > 11) {
                    grid[i][j] = '#';
                }
                else if (i == 2 && j < 19 && j > 11) {
                    grid[i][j] = '#';
                }
                else if (i == 12 && j < 19 && j > 11) {
                    grid[i][j] = '#';
                }
                else if (i == 10 && j < 21 && j > 16) {
                    grid[i][j] = '#';
                }
                else if (i == 4 && j < 21 && j > 16) {
                    grid[i][j] = '#';
                }
                else if (i == 2 && j < 23 && j > 19) {
                    grid[i][j] = '#';
                }
                else if (i == 12 && j < 23 && j > 19) {
                    grid[i][j] = '#';
                }
                else if (i == 6 && j < 25 && j > 21) {
                    grid[i][j] = '#';
                }
                else if (i == 8 && j < 25 && j > 21) {
                    grid[i][j] = '#';
                }
                else if (i == 4 && j < 27 && j > 23) {
                    grid[i][j] = '#';
                }
                else if (i == 10 && j < 27 && j > 23) {
                    grid[i][j] = '#';
                }
                else if (i == 5 && j < 30 && j > 27) {
                    grid[i][j] = '#';
                }
                else if (i == 9 && j < 30 && j > 27) {
                    grid[i][j] = '#';
                }
                else if (i == 7 && j < 29 && j > 25) {
                    grid[i][j] = '#';
                }
                else if (i == 12 && j < 29 && j > 25) {
                    grid[i][j] = '#';
                }
                else if (i == playerX && j == playerY) {                    
                    grid[i][j] = 'O';
                }
                else if (i == ghostX && j == ghostY) {
                    
                    grid[i][j] = '>';
                }
                else if (i == ghost2X && j == ghost2Y) {
                    grid[i][j] = '<';
                }
                //To prevent map, printing dots on spaced area:
                else if (grid[i][j] == ' ') {
                    continue;
                }

                else {
                    grid[i][j] = '.';
                }
            }
        }
	}

	

	//Printing map and setting colors:
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '#') {
                setColor(BLUE);
            }
            else if (grid[i][j] == 'O') {
                setColor(YELLOW);
            }
            else if (grid[i][j] == '>' || grid[i][j] == '<') {
                setColor(RED);
            }
            else {
                setColor(WHITE);
            }

			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
    //Reset color:
    setColor(WHITE);

}


void playerMovement(char grid[rows][cols]) {

	if (_kbhit()) {
		// Update direction based on key pressed
		direction = _getch();
	}
        //Move player based on key pressed:
		switch (direction) {
		case 'w':
			if (grid[playerX - 1][playerY] != '#') {
                //for score:
                if (grid[playerX - 1][playerY] == '.')
                    score++;
                //movement:
				playerX--;	
                // Leave a space in the opposite direction of movement:
				grid[playerX + 1][playerY] = ' ';
			}	
			break;
		case 's':
			if (grid[playerX + 1][playerY] != '#') {
                //for score:
                if (grid[playerX + 1][playerY] == '.')
                    score++;
                //movement:
				playerX++;
                // Leave a space in the opposite direction of movement:
				grid[playerX - 1][playerY] = ' ';
			}
			break;
		case 'a':
			if (grid[playerX][playerY - 1] != '#') {
                //for score:
                if (grid[playerX][playerY - 1] == '.')
                    score++;
                //movement:
				playerY--;
                // Leave a space in the opposite direction of movement:
				grid[playerX][playerY + 1] = ' ';
			}
			break;
		case 'd':
			if (grid[playerX][playerY + 1] != '#') {
                //for score:
                if (grid[playerX][playerY + 1] == '.')
                    score++;
                //movement:
				playerY++;
                // Leave a space in the opposite direction of movement:
				grid[playerX][playerY - 1] = ' ';
			}
			break;
		}	

}

void ghostMovement(char grid[rows][cols]) {
	srand(time(0));
	int randomNumber = rand() % 8 + 1; // generates random num between 1 to 8
	char currentContent = grid[ghostX][ghostY];

    //Move ghost based on random number generated:
	switch (randomNumber) {
		case 1:
		case 6:
			if (grid[ghostX - 1][ghostY] != '#') {	
                //To prevent ghost from leaving dots:
				if (grid[ghostX - 1][ghostY] != '.') {
					grid[ghostX][ghostY] = ' ';
				}
                //To prevent ghost from colliding with other ghost:
                if (grid[ghostX - 1][ghostY] != '<')
				ghostX--; //For movement:
			}
			break;

		case 2:
		case 5:
			if (grid[ghostX + 1][ghostY] != '#') {
                //To prevent ghost from leaving dots:
				if (grid[ghostX + 1][ghostY] != '.') {
					grid[ghostX][ghostY] = ' ';
				}
                //To prevent ghost from colliding with other ghost:
                if (grid[ghostX + 1][ghostY] != '<')
				ghostX++; //For movement:
			}
			break;

		case 3:
		case 8:
			if (grid[ghostX][ghostY - 1] != '#') {
                //To prevent ghost from leaving dots:
				if (grid[ghostX][ghostY - 1] != '.') {
					grid[ghostX][ghostY] = ' ';
				}
                 if (grid[ghostX][ghostY - 1] != '<')
				ghostY--; //For movement:
			}
			break;

		case 4:
		case 7:
			if (grid[ghostX][ghostY + 1] != '#') {
                //To prevent ghost from leaving dots:
				if (grid[ghostX][ghostY + 1] != '.') {
					grid[ghostX][ghostY] = ' ';
				}
                //To prevent ghost from colliding with other ghost:
                if (grid[ghostX][ghostY + 1] != '<')
				ghostY++; //For movement:
			}
			break;
	}
	grid[ghostX][ghostY] = currentContent;

}



void ghost2Movement(char grid[rows][cols]) {
    srand(time(0));
    int randomNumber = rand() % 8 + 1; // generates random num between 1 to 8
    char currentContent = grid[ghost2X][ghost2Y];

    switch (randomNumber) {
    case 1:
    case 5:
        if (grid[ghost2X - 1][ghost2Y] != '#') {
            //To prevent ghost from leaving dots:
                if (grid[ghost2X - 1][ghost2Y] != '.') {
                    grid[ghost2X][ghost2Y] = ' ';
                }
                //To prevent ghost from colliding with other ghost:
            if (grid[ghost2X - 1][ghost2Y] != '>')
            ghost2X--; //For movement:
        }
        break;

    case 2:
    case 6:
        if (grid[ghost2X + 1][ghost2Y] != '#') {
            //To prevent ghost from leaving dots:
            if (grid[ghost2X + 1][ghost2Y] != '.') {
                grid[ghost2X][ghost2Y] = ' ';
            }
            //To prevent ghost from colliding with other ghost:
            if (grid[ghost2X + 1][ghost2Y] != '>')
            ghost2X++; //For movement:
        }
        break;

    case 3:
    case 8:
        if (grid[ghost2X][ghost2Y - 1] != '#') {
            //To prevent ghost from leaving dots:
            if (grid[ghost2X][ghost2Y - 1] != '.') {
                grid[ghost2X][ghost2Y] = ' ';
            }
            //To prevent ghost from colliding with other ghost:
            if (grid[ghost2X][ghost2Y - 1] != '>')
            ghost2Y--; //For movement:
        }
        break;

    case 4:
    case 7:
        if (grid[ghost2X][ghost2Y + 1] != '#') {
            //To prevent ghost from leaving dots:
            if (grid[ghost2X][ghost2Y + 1] != '.') {
                grid[ghost2X][ghost2Y] = ' ';
            }
            //To prevent ghost from colliding with other ghost:
            if (grid[ghost2X][ghost2Y + 1] != '>')
            ghost2Y++;//For movement:
        }
        break;
    }

    grid[ghost2X][ghost2Y] = currentContent;
}



void checkLoss(char grid[rows][cols]) {
    //If mainPlayer collides with any ghost, game ends.
	if (grid[playerX][playerY] == grid[ghostX][ghostY] || grid[playerX][playerY] == grid[ghost2X][ghost2Y]) {
		gameOver = true;
	}
	else {
		gameOver = false;
	}
}

bool checkWin(char grid[rows][cols], bool noDots) {
    //Function to check if all dots collected, player wins!
    noDots = true;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '.') {
                noDots = false;
                break;
            }
        }
        //We dont need to check further because there is atleast 1 dot present on map:
        if (!noDots)
            break;
    }
    return noDots;
}

void setColor(int color) {
    // This functions sets colors with different color codes mentioned at top:
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (color == 14) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    }
    else {
        SetConsoleTextAttribute(hConsole, color);
    }
}















