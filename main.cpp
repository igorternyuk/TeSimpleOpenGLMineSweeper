#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "painter.h"
#include "game.h"
#include <sstream>

Game game;
int winID;

void display()
{
    Painter p;
    glClear(GL_COLOR_BUFFER_BIT);
    game.draw();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
     if(state == GLUT_UP)
     {
         switch(button)
         {
            case GLUT_RIGHT_BUTTON:
                game.markCell(x / Painter::CELL_WIDTH, y / Painter::CELL_HEIGHT);
                break;
            case GLUT_LEFT_BUTTON:
                game.openCell(x / Painter::CELL_WIDTH, y / Painter::CELL_HEIGHT);
                break;
         }
         glutPostRedisplay();
     }
}

void myKeyboardFunction(unsigned char key, int, int)
{
    switch(key)
    {
        case 'n':
            game.newGame();
            glutPostRedisplay();
            break;
        case 'q':
            glutDestroyWindow(winID);
            exit(0);
            break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Painter::CELL_WIDTH * Game::WIDTH, Painter::CELL_HEIGHT * Game::HEIGHT + 50);
    glutInitWindowPosition((1366 - Painter::CELL_WIDTH * Game::WIDTH) / 2,
                           (768 - (Painter::CELL_HEIGHT * Game::HEIGHT + 50)) / 2);
    winID = glutCreateWindow("TeMineSweeper");
    glClearColor(0.8f, 0.8f, 0.8f, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Painter::CELL_WIDTH  * Game::WIDTH, Painter::CELL_HEIGHT * Game::HEIGHT + 50, 0, -1.0, +1.0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(myKeyboardFunction);
    glutMainLoop();
    return 0;
}
