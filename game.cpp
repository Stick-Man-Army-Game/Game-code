#include <windows.h>
#include <gl\glut.h>
#include <iostream>
#include <math.h>
using namespace std;
int c = 0;
float E = 475 / 7;
int xman, yman, xmanfirst, ymanfirst, xman_org, yman_org;
int turn = 0; // represents which player's turn
int clickTime = 2; //he can click 2 times
//
char BoardMem[7][7] = { //Board memory 
	'G', '0', '0', '0', '0', '0', 'B', //the bottom most row of the board
	'0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0',
	'B', '0', '0', '0', '0', '0', 'G', }; //top row of the board

/*void drawStrokeText(char*string,int x,int y,int z)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y+8,z);
	  glScalef(0.09f,-0.08f,z);
  
	  for (c=string; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
}
void print(void)
{ 
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
 
	glColor3f(0,1,0);
	drawStrokeText("Osama Hosam's OpenGL Tutorials",500,500,-2.0f);
	glutSwapBuffers(); 
}
*/

	void stickman(float xtranslation, float ytranslation, float g, float b)
{
	glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix
	glLoadIdentity();

	glTranslatef(-34.0 + xtranslation*5.7, -34.0 + ytranslation*5.7, -60.0f);

	glColor3f(0.0, g, b);
	glBegin(GL_POLYGON);
	glVertex3f((4.0 + 25)*0.5, (6.5 + 25)*0.5, -1.0);
	glVertex3f((6.0 + 25)*0.5, (6.5 + 25)*0.5, -1.0);
	glVertex3f((6.0 + 25)*0.5, (8.5 + 25)*0.5, -1.0);
	glVertex3f((4.0 + 25)*0.5, (8.5 + 25)*0.5, -1.0);
	glEnd();
	glFlush();

	glColor3f(0.0, g, b);
	glBegin(GL_LINES);
	glVertex3f((5.0 + 25)*0.5, (6.5 + 25)*0.5, -1.0);
	glVertex3f((5.0 + 25)*0.5, (3.0 + 25)*0.5, -1.0);
	glVertex3f((3.5 + 25)*0.5, (5.1 + 25)*0.5, -1.0);
	glVertex3f((6.5 + 25)*0.5, (5.1 + 25)*0.5, -1.0);
	glVertex3f((5.0 + 25)*0.5, (3.0 + 25)*0.5, -1.0);
	glVertex3f((3.5 + 25)*0.5, (1.0 + 25)*0.5, -1.0);
	glVertex3f((5.0 + 25)*0.5, (3.0 + 25)*0.5, -1.0);
	glVertex3f((6.5 + 25)*0.5, (1.0 + 25)*0.5, -1.0);
	glEnd();
	glFlush();
	
}

bool isBoardFull(){
	int i, j;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++) {
			if (BoardMem[i][j] == '0')
				return false;
		}
	}
	return true;
}
char isWinnerDecided() {
	int i, j, countG = 0, countB = 0;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++) {
			if (BoardMem[i][j] == 'G')
				countG++;
			else if (BoardMem[i][j] == 'B')
				countB++;
		}
	}
	if (countB == 0)
		return 'G';
	else if (countG == 0)
		return 'B';
	else
		return '-1';
}
char winner(){
	int i, j, countG = 0, countB = 0;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++) {
			if (BoardMem[i][j] == 'G')
				countG++;
			else if (BoardMem[i][j] == 'B')
				countB++;
		}
	}
	
		if (countB>countG)
	{
		return 'B';
	}
	else if (countB < countG)
	{
		return 'G';
	}
	else
		return '-1';

}
bool checkValidPosFirst(int xcoor, int ycoor, int turn){
	char ch;
	//Assuming we are starting with Green (G)
	//if the turn=0 then it will check against 'G' else it will check against 'B' 
	if (turn == 0)
		ch = 'G';
	else
		ch = 'B';
	if (BoardMem[xcoor][ycoor] == ch) //&& (BoardMem[xcoor][ycoor] != '0' ) )
		return true;
	else
		return false;
}
int checkValidPosSecond(int xcoor, int ycoor, int turn){
	char ch;
	if (turn == 0){
		ch = 'G';
	}
	else {
		ch = 'B';
	}
	if ((BoardMem[xcoor][ycoor] == 'G') || (BoardMem[xcoor][ycoor] == 'B'))
		return -1;
	else if ((abs(xcoor - xmanfirst) > 2) || (abs(ycoor - ymanfirst) > 2))
		return -1;
	else{

		if (abs(xcoor - xmanfirst) >= 2 || abs(ycoor - ymanfirst) >= 2)
			return 1;

		else if ((abs(xcoor - xmanfirst) == 1 || abs(ycoor - ymanfirst) == 1))
			return 2; // 2 indicates we have to replicate

		/*else
			return 1; // 1 indicates we have to transfer*/
	}
}
void replaceOpponent(int xcoor, int ycoor, int turn){
	char ch;
	if (turn == 0){
		ch = 'G';
		if ((xcoor - 1) >= 0 && (ycoor + 1) <= 6)
		if (BoardMem[xcoor - 1][ycoor + 1] == 'B')
			BoardMem[xcoor - 1][ycoor + 1] = 'G';
		if ((ycoor + 1) <= 6)
		if (BoardMem[xcoor][ycoor + 1] == 'B')
			BoardMem[xcoor][ycoor + 1] = 'G';
		if ((xcoor + 1) <= 6 && (ycoor + 1) <= 6)
		if (BoardMem[xcoor + 1][ycoor + 1] == 'B')
			BoardMem[xcoor + 1][ycoor + 1] = 'G';
		if ((xcoor + 1) <= 6)
		if (BoardMem[xcoor + 1][ycoor] == 'B')
			BoardMem[xcoor + 1][ycoor] = 'G';
		if ((xcoor + 1) <= 6 && (ycoor - 1) >= 0)
		if (BoardMem[xcoor + 1][ycoor - 1] == 'B')
			BoardMem[xcoor + 1][ycoor - 1] = 'G';
		if ((ycoor - 1) >= 0)
		if (BoardMem[xcoor][ycoor - 1] == 'B')
			BoardMem[xcoor][ycoor - 1] = 'G';
		if ((xcoor - 1) >= 0 && (ycoor - 1) >= 0)
		if (BoardMem[xcoor - 1][ycoor - 1] == 'B')
			BoardMem[xcoor - 1][ycoor - 1] = 'G';
		if ((xcoor - 1) >= 0)
		if (BoardMem[xcoor - 1][ycoor] == 'B')
			BoardMem[xcoor - 1][ycoor] = 'G';
	}
	else{
		ch = 'B';
		if ((xcoor - 1) >= 0 && (ycoor + 1) <= 6)
		if (BoardMem[xcoor - 1][ycoor + 1] == 'G')
			BoardMem[xcoor - 1][ycoor + 1] = 'B';
		if ((ycoor + 1) <= 6)
		if (BoardMem[xcoor][ycoor + 1] == 'G')
			BoardMem[xcoor][ycoor + 1] = 'B';
		if ((xcoor + 1) <= 6 && (ycoor + 1) <= 6)
		if (BoardMem[xcoor + 1][ycoor + 1] == 'G')
			BoardMem[xcoor + 1][ycoor + 1] = 'B';
		if ((xcoor + 1) <= 6)
		if (BoardMem[xcoor + 1][ycoor] == 'G')
			BoardMem[xcoor + 1][ycoor] = 'B';
		if ((xcoor + 1) <= 6 && (ycoor - 1) >= 0)
		if (BoardMem[xcoor + 1][ycoor - 1] == 'G')
			BoardMem[xcoor + 1][ycoor - 1] = 'B';
		if ((ycoor - 1) >= 0)
		if (BoardMem[xcoor][ycoor - 1] == 'G')
			BoardMem[xcoor][ycoor - 1] = 'B';
		if ((xcoor - 1) >= 0 && (ycoor - 1) >= 0)
		if (BoardMem[xcoor - 1][ycoor - 1] == 'G')
			BoardMem[xcoor - 1][ycoor - 1] = 'B';
		if ((xcoor - 1) >= 0)
		if (BoardMem[xcoor - 1][ycoor] == 'G')
			BoardMem[xcoor - 1][ycoor] = 'B';
	}
}


void coordinate(int button, int state, int x, int y) {
	//check whether the board is full or not
	bool BoardFull = isBoardFull();
	if (BoardFull){
		cout << "\n The Board is full";
		cout << "\nWinner is " << winner();
		
		//try to exit somehow
	}
	else //the board is not full and there is a need for check for winner if any
	{
		char winnerDecided = isWinnerDecided();
		if ((winnerDecided == 'G') || (winnerDecided == 'B')) { // winner is decided
			cout << "\nWinner is " << winner();
			if ( winner()=='G')
			{
		stickman(7,7,1.0,0);
		stickman(-1,7,1.0,0);
			stickman(7,-0.5,1.0,0);
			stickman(-1,-0.5,1.0,0);
			}
	else if (winner()=='B')
	{
		stickman(7,7,0,1.0);
		stickman(7,-0.5,0,1.0);
		stickman(-1,7,0,1.0);
		stickman(-1,-0.5,0,1.0);
		}
			//try to exit somehow
		}
		else { // The Game should go on as usual
			//cout << "\nEntering the Game should go on as usual";
			if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
				//cout << "\nEntering the left button click up";
				if (turn == 0 && clickTime == 2)
					cout << "\n\t***Player G turn***\n";
				else if (turn == 1 && clickTime == 2)
					cout << "\n\t***Player B turn***\n";
				//cout << "\nMouse Button Clicked";
				if (x > 140 && x < (140 + E))
					xman = 0;
				else if (x >(140 + E) && x < (140 + 2 * E))
					xman = 1;
				else if (x >(140 + 2 * E) && x < (140 + 3 * E))
					xman = 2;
				else if (x >(140 + 3 * E) && x < (140 + 4 * E))
					xman = 3;
				else if (x >(140 + 4 * E) && x < (140 + 5 * E))
					xman = 4;
				else if (x >(140 + 5 * E) && x < (140 + 6 * E))
					xman = 5;
				else if (x >(140 + 6 * E) && x < (140 + 7 * E))
					xman = 6;
				if (y>(560 - E) && y < (560))
					yman = 0;
				else if (y >(560 - 2 * E) && y < (560 - E))
					yman = 1;
				else if (y >(560 - 3 * E) && y < (560 - 2 * E))
					yman = 2;
				else if (y >(560 - 4 * E) && y < (560 - 3 * E))
					yman = 3;
				else if (y >(560 - 5 * E) && y < (560 - 4 * E))
					yman = 4;
				else if (y >(560 - 6 * E) && y < (560 - 5 * E))
					yman = 5;
				else if (y >(560 - 7 * E) && y < (560 - 6 * E))
					yman = 6;
				//swapping to map board and the matrix
				xman_org = xman;
				yman_org = yman;
				//cout << "\n-----Swapping----";
				int temp = yman;
				yman = xman;
				xman = temp;
				if (clickTime == 2){
					//cout << "\nEntering clickTime == 2";
					//If the returned xman and yman represents his own player then that point is locked 
					//else cout not a valid point click again (create a function that will do check from the global matrix, pass turn, xman and yman so it will check against the turn value)
					//cout << "\nCoordinates getting into checkValidPosFirst " << xman << "\t" << yman;
					//cout << "\nTurn of player " << turn;
					bool firstClick = checkValidPosFirst(xman, yman, turn);
					//cout << "\nFirst Click " << firstClick;
					if (!firstClick)
					{
						cout << "\nClick on a valid position of player " << turn;
						//print("\nClick on a valid position of player ");
					}
					else if (firstClick){
						//cout << "\nValid First move";
						//cout << "\nFirst click of player " << turn << " gives " << xman << " and " << yman;
						//cout << "\nProceed for the next move";
						xmanfirst = xman; // storing the first move so that we can decide what to do in next step
						ymanfirst = yman;
						clickTime--;
						cout << "\n\nThe current display of the Board Matrix after first click\n\n";
						int i, j;
						for (i = 6; i >= 0; i--) {
							for (j = 0; j <= 6; j++) {
								cout << BoardMem[i][j] << "\t";
							}
							cout << "\n";
						}
					}
				}
				else if (clickTime == 1) {
					//cout << "\nEntering clickTime == 1";
					//cout << "\nCoordinates getting into checkValidPosSecond " << xman << "\t" << yman;
					int secondClick = checkValidPosSecond(xman, yman, turn); // this i have taken int as we have to decide whether we have to just move or replicate it
					if (secondClick == -1)
						cout << "\n\t!!!Enter a valid second position!!!";
					else if (secondClick == 1){
						//cout << "\nValid Second move";
						//cout << "\nSecond click of player " << turn << " gives " << xman << " and " << yman;
						clickTime--;
						if (turn == 0){
							BoardMem[xmanfirst][ymanfirst] = '0';
							BoardMem[xman][yman] = 'G';
						}
						else if (turn == 1) {
							BoardMem[xmanfirst][ymanfirst] = '0';
							BoardMem[xman][yman] = 'B';
						}
						replaceOpponent(xman, yman, turn);
						cout << "\n\nThe display of the Board Matrix after second click\n\n";
						int i, j;
						for (i = 6; i >= 0; i--) {
							for (j = 0; j <= 6; j++) {
								cout << BoardMem[i][j] << "\t";
							}
							cout << "\n";
						}
						//After the 2nd click of the player the turn should be that of another player
						if (turn == 0)
							turn = 1;
						else turn = 0;
						clickTime = 2;
						if (turn)
							cout << "\n\n\t---Player turn changed to Blue ---\n";
						else
							cout << "\n\n\t---Player turn changed to Green ---\n";
					}
					else if (secondClick == 2) {
						//cout << "\nValid Second move";
						//cout << "\nSecond click of player " << turn << "gives " << xman << "and " << yman;
						clickTime--;
						if (turn == 0){
							BoardMem[xman][yman] = 'G';
						}
						else if (turn == 1) {
							BoardMem[xman][yman] = 'B';
						}
						replaceOpponent(xman, yman, turn);
						cout << "\n\nThe display of the Board Matrix after second click\n\n";
						int i, j;
						for (i = 6; i >= 0; i--) {
							for (j = 0; j <= 6; j++) {
								cout << BoardMem[i][j] << "\t";
							}
							cout << "\n";
						}
						//After the 2nd click of the player the turn should be that of another player
						if (turn == 0)
							turn = 1;
						else turn = 0;
						clickTime = 2;
						if (turn)
							cout << "\n\n\t---Player turn changed to Blue ---\n";
						else
							cout << "\n\n\t---Player turn changed to Green ---\n";
					}
				} //end of clickTime == 1
			}//Closing the if of left click
		}// Closing of Game should go on
	}//closing of board is not full
}//closing of coordinate


void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4)
{
	// c alternates color of square
	if (c == 0)
	{
		if(turn == 0) glColor3f(0, 0.4, 0); //green
		else if(turn == 1) glColor3f(0.1,0.3,0.44); //blue
		c = 1;
	}
	else
	{
		glColor3f(0, 0, 0);
		c = 0;
	}
	// Draw Square
	glBegin(GL_POLYGON);
	glVertex3f(x1*0.08, y1*0.08, -4.0);
	glVertex3f(x2*0.08, y2*0.08, -4.0);
	glVertex3f(x3*0.08, y3*0.08, -4.0);
	glVertex3f(x4*0.08, y4*0.08, -4.0);
	glEnd();

}
void board()
{
	glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-25.0f, -25.0f, -60.0f);
	int x, y;
	c = 0; //so that mouse click does not swap colors of squares
	for (x = 25; x <= 475; x += 75)
	{
		for (y = 25; y <= 475; y += 75)
		{
			drawSquare(x, y + 75, x + 75, y + 75, x + 75, y, x, y);
		}
	}
	// Process all OpenGL routines as quickly as possible
	for (int i = 0; i <= 6; i++){
		for (int j = 0; j <= 6; j++){
			if (BoardMem[i][j] != '0'){
				char color = BoardMem[i][j];
				if (color == 'G')
				{
					stickman(j, i, 1.0, 0.0);
				}
				else
				{
					stickman(j, i, 0.0, 1.0);
				}
			}
		}
	}
	char win = isWinnerDecided();
	if (win=='B')
	{
		
		    stickman(7,7,0,1.0);
	    	stickman(7,-0.5,0,1.0);
		    stickman(-1,7,0,1.0);
		    stickman(-1,-0.5,0,1.0);
	}
	else if (win == 'G')
	{		
			stickman(7,7,1.0,0);
		    stickman(-1,7,1.0,0);
			stickman(7,-0.5,1.0,0);
			stickman(-1,-0.5,1.0,0);
	}
}


void reshape(int width, int height) { // GLsizei for non-negative integer
	// aspect ratio of the new window:
	if (height == 0 || width == 0) return; // To prevent divide by 0
	glMatrixMode(GL_PROJECTION); // Projection matrix operated on
	glLoadIdentity();
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	gluPerspective(45.0f, aspect, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW); // Projection matrix operated on
	glViewport(0, 0, width, height);// Set the viewport to cover the new window
	// Perspective projection parameters - fovy, aspect, zNear and zFar
}
void TimerFunc(int extra)
{
	glutPostRedisplay();
	glutTimerFunc(1000, TimerFunc, 0);
}
int main(int agrc, char ** argv)
{
	glutInit(&agrc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("War of Stick Men");
	glutMouseFunc(coordinate);
	// for setting the transformation (here it is 2D)
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glutDisplayFunc(board);
	glutReshapeFunc(reshape);
	glutTimerFunc(2000, TimerFunc, 0);
	glutMainLoop();
	return 0;
}
