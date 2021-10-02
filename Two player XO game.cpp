//Ahmed Gamal Anany
//20172532
// A two player XO game


#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>



int matrix[3][3]; 
int playerturn; 
int result; 
bool gameover; 

struct Move {
	int row, col;
	Move() {
		row = -1;
		col = -1;
	}
};

struct WinPosition {
	int x1, y1;
	WinPosition() {
		x1 = y1 = -1;
	}
};

WinPosition winPosition;

void initgame()
{
	playerturn = 1;
	winPosition.x1 = winPosition.y1 = -1;
	for (int i = 0; i <= 2; i++)
		for (int j = 0; j <= 2; j++)
			matrix[i][j] = 0;
}

bool isMovesLeft(int board[3][3])
{
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (board[i][j] == 0)
				return true;
	return false;
}

int evaluate()
{
	for (int row = 0; row < 3; row++)
	{
		if (matrix[row][0] == matrix[row][1] && matrix[row][1] == matrix[row][2])
		{
			if (matrix[row][0] == 1) {
				winPosition.x1 = row;
				return 10;
			}
			else if (matrix[row][0] == 2) {
				winPosition.x1 = row;
				return -10;
			}
		}
	}

	for (int col = 0; col < 3; col++)
	{
		if (matrix[0][col] == matrix[1][col] && matrix[1][col] == matrix[2][col])
		{
			if (matrix[0][col] == 1) {
				winPosition.y1 = col;
				return 10;
			}
			else if (matrix[0][col] == 2) {
				winPosition.y1 = col;
				return -10;
			}
		}
	}

	if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2])
	{
		if (matrix[0][0] == 1) {
			winPosition.x1 = winPosition.y1 = 0;
			return 10;
		}
		else if (matrix[0][0] == 2) {
			winPosition.x1 = winPosition.y1 = 0;
			return -10;
		}
	}

	if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0])
	{
		if (matrix[0][2] == 1) {
			winPosition.x1 = winPosition.y1 = 1;
			return 10;
		}
		else if (matrix[0][2] == 2) {
			winPosition.x1 = winPosition.y1 = 1;
			return -10;
		}
	}
	return 0;
}






void KeyPress(unsigned char key, int x, int y)
{
	switch (key){
	case 'y':
		if (gameover == true)
		{
			gameover = false;
			initgame();
		}
		break;
	case 'n':
		if (gameover == true)
			exit(0);
		break;

	case 'q':
		exit(0);
	}
}


void click(int button, int state, int x, int y)
{
	if (gameover == false && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (playerturn == 1)
		{
			if (matrix[(y - 50) / 100][x / 100] == 0)
			{
				matrix[(y - 50) / 100][x / 100] = 1;
			
					playerturn = 2;
			}
		}
		else
		{
			if (matrix[(y - 50) / 100][x / 100] == 0)
			{
				matrix[(y - 50) / 100][x / 100] = 2;
				playerturn = 1;
			}
		}
	}
}


void drawString(void * font, char *s, float x, float y)
{
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(font, s[i]);
}


void drawlines()
{
	glBegin(GL_LINES);
	glColor3f(0, 0, 0.8);
	//2 vertical lines
	glVertex2f(100, 50);
	glVertex2f(100, 350);
	glVertex2f(200, 350);
	glVertex2f(200, 50);
	//2 horizontal lines
	glColor3f(0, 0.7, 0);
	glVertex2f(0, 150);
	glVertex2f(300, 150);
	glVertex2f(0, 250);
	glVertex2f(300, 250);
	glEnd();
}

void drawxo()

{
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			if (matrix[i][j] == 1) 
			{
				glBegin(GL_LINES);
				glLineWidth((GLfloat)5);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 - 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 - 25);
				glEnd();
			}
			else if (matrix[i][j] == 2) 
			{
				
				glBegin(GL_LINE_LOOP);
			
				{
					glVertex2f(50 + j * 100 - 25, 100 + i * 100 - 25);
					glVertex2f(50 + j * 100 + 25, 100 + i * 100 + 25);
					glVertex2f(50 + j * 100 - 25, 100 + i * 100 + 25);
				glEnd();
			}
		}
	}
}





void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 0);


		drawString(GLUT_BITMAP_HELVETICA_18, "2 Player Game", 100, 400);

	if (playerturn == 1)
		drawString(GLUT_BITMAP_HELVETICA_18, "Player 1's turn", 100, 30);
	else {
	
	
			drawString(GLUT_BITMAP_HELVETICA_18, "Player 2's turn", 100, 30);
	}

	drawlines();
	drawxo();

	if (evaluate() != 0)
	{
		if (winPosition.x1 == winPosition.y1) {
			if (winPosition.x1 == 0)
				drawWinningLine(50, 100, 250, 300);
			else
				drawWinningLine(250, 100, 50, 300);
		}
		else {
			if (winPosition.x1 == -1)
				drawWinningLine(100 * winPosition.y1 + 50, 100, 100 * winPosition.y1 + 50, 300);
			else
				drawWinningLine(50, 100 * winPosition.x1 + 100, 250, 100 * winPosition.x1 + 100);
		}

		if (playerturn == 1)
		{
			gameover = true;
			result = 2; 
		}
		else
		{
			gameover = true;
			result = 1; 
		}
	}
	else if (isMovesLeft(matrix) == false)
	{
		gameover = true;
	
	}

	if (gameover == true)
	{

		glColor3f(0.9, 0, 0);
		drawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);

		//if (result == 0)
		//	drawString(GLUT_BITMAP_HELVETICA_18, "Its a draw", 110, 185);

		if (result == 1)
			drawString(GLUT_BITMAP_HELVETICA_18, "Player 1 wins", 95, 185);

		if (result == 2) {
				drawString(GLUT_BITMAP_HELVETICA_18, "Player 2 wins", 95, 185);
		}

		drawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue (y/n)", 40, 210);
	}

	glutSwapBuffers();
}


void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv)
{
	initgame();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(300, 450);
	glutCreateWindow("X0");


	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(KeyPress);
	glutMouseFunc(click);
	glutIdleFunc(display);
	glutMainLoop();
}
