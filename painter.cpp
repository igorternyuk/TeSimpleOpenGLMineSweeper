#include "painter.h"
#include <cstring>
#include <cmath>

Painter::Painter()
{}

void Painter::drawClosedCell(int x, int y)
{
    glColor3f(0, 99.f/255, 230.f/255);
    glBegin(GL_QUADS);
        glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT);
        glVertex2f((x + 1) * CELL_WIDTH, y * CELL_HEIGHT);
        glVertex2f((x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT);
        glVertex2f(x * CELL_WIDTH, (y + 1) * CELL_HEIGHT);
    glEnd();
    drawFrame(x, y);
}

void Painter::drawOpenedCell(int x, int y, int numMines)
{
    drawBackground(x, y);
    if(numMines > 0)
    {
        switch(numMines)
        {
            case 1:
                glColor3f(0.f, 0.f, 1.f);
                break;
            case 2:
                glColor3f(0.f, 0.5f, 0.08f);
                break;
            case 3:
                glColor3f(1.f, 0.f, 0.f);
                break;
            case 4:
                glColor3f(0.f, 0.7f, 0.f);
                break;
            case 5:
                glColor3f(0.5f, 0.4f, 0.f);
                break;
            case 6:
                glColor3f(0.f, 0.8f, 0.5f);
                break;
            case 7:
                glColor3f(0.5f, 0.f, 0.35f);
                break;
            case 8:
                glColor3f(0.3f, 0.3f, 0.3f);
                break;
        }
        glRasterPos2f((x + 0.33) * CELL_WIDTH, (y + 0.75) * CELL_HEIGHT);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0' + numMines);
    }
    drawFrame(x, y);
}

void Painter::drawFlaggedCell(int x, int y)
{
    //Фон
    drawClosedCell(x, y);
    drawFlag(x, y);
}

void Painter::drawQuestionedCell(int x, int y)
{
    drawClosedCell(x, y);
    glColor3f(1.0f, 0.f, 0.f);
    glRasterPos2f((x + 0.33) * CELL_WIDTH, (y + 0.75) * CELL_HEIGHT);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '?');
}

void Painter::drawMinedCell(int x, int y, bool isExplosion)
{
    drawBackground(x, y);
    if(isExplosion)
        glColor3f(1.f, 0.f, 0.f);
    else
        glColor3f(0.f, 0.f, 0.f);
    drawPolygon(x, y, 18, 10.0f);
    glBegin(GL_TRIANGLES);
    for(int i{0}; i < 8; ++i)
    {
        glVertex2f((x + 0.5) * CELL_WIDTH + 8.f * cos(2 * M_PI * (i - 0.4) / 8),
                   (y + 0.5) * CELL_HEIGHT + 8.f * sin(2 * M_PI * (i - 0.4) / 8));
        glVertex2f((x + 0.5) * CELL_WIDTH + 15.f * cos(2 * M_PI * i / 8),
                   (y + 0.5) * CELL_HEIGHT + 15.f * sin(2 * M_PI * i / 8));
        glVertex2f((x + 0.5) * CELL_WIDTH + 8.f * cos(2 * M_PI * (i + 0.4) / 8),
                   (y + 0.5) * CELL_HEIGHT + 8.f * sin(2 * M_PI * (i + 0.4) / 8));
    }
    glEnd();
    drawFrame(x, y);
}

void Painter::drawText(const char *word, int x_, int y_, float step, int red, int green, int blue)
{
    glColor3f(red / 255.f, green / 255.f, blue / 255.f);
    for(int i{0}; i < std::strlen(word); ++i)
    {
        glRasterPos2f(x_ + i * step, y_);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)word[i]);
    }
}

void Painter::drawBackground(int x, int y)
{
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT);
    glVertex2f((x + 1) * CELL_WIDTH, y * CELL_HEIGHT);
    glVertex2f((x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT);
    glVertex2f(x * CELL_WIDTH, (y + 1) * CELL_HEIGHT);
    glEnd();
}

void Painter::drawFrame(int x, int y)
{
    glBegin(GL_LINES);
        glColor3f(171.f / 255, 191.f / 255, 201.f / 255);
        glVertex2f(x * CELL_WIDTH + 1, y * CELL_HEIGHT + 1);
        glVertex2f((x + 1) * CELL_WIDTH - 1, y * CELL_HEIGHT + 1);
        glVertex2f(x * CELL_WIDTH + 1, y * CELL_HEIGHT + 1);
        glVertex2f(x * CELL_WIDTH + 1, (y + 1) * CELL_HEIGHT - 1);
        glColor3f(13.f / 255, 72.f / 255, 104.f / 255);
        glVertex2f((x + 1) * CELL_WIDTH - 1, (y + 1) * CELL_HEIGHT - 1);
        glVertex2f((x + 1) * CELL_WIDTH - 1, y * CELL_HEIGHT + 1);
        glVertex2f((x + 1) * CELL_WIDTH - 1, (y + 1) * CELL_HEIGHT - 1);
        glVertex2f(x * CELL_WIDTH - 1, (y + 1) * CELL_HEIGHT - 1);
    glEnd();
}

void Painter::drawPolygon(int x, int y, int numVertex, float radius)
{
    glBegin(GL_POLYGON);
    for(int i = 0; i < numVertex; ++i)
    {
        glVertex2f((x + 0.5) * CELL_WIDTH + radius * cos(2 * M_PI * i / numVertex),
                   (y + 0.5) * CELL_HEIGHT + radius * sin(2 * M_PI * i / numVertex));
    }
    glEnd();
}

void Painter::drawFlag(int x, int y)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    //Палка
    glBegin(GL_QUADS);
    glVertex2f((x + 0.2) * CELL_WIDTH, (y + 0.1) * CELL_HEIGHT);
    glVertex2f((x + 0.25) * CELL_WIDTH, (y + 0.1) * CELL_HEIGHT);
    glVertex2f((x + 0.25) * CELL_WIDTH, (y + 0.9) * CELL_HEIGHT);
    glVertex2f((x + 0.2) * CELL_WIDTH, (y + 0.9) * CELL_HEIGHT);
    glEnd();
    glColor3f(1.0f, 0.f, 0.f);
    //Флажок
    glBegin(GL_TRIANGLES);
    glVertex2f((x + 0.25) * CELL_WIDTH, (y + 0.15) * CELL_HEIGHT);
    glVertex2f((x + 0.85) * CELL_WIDTH, (y + 0.65) * CELL_HEIGHT);
    glVertex2f((x + 0.25) * CELL_WIDTH, (y + 0.65) * CELL_HEIGHT);

    glVertex2f((x + 0.25) * CELL_WIDTH, (y + 0.15) * CELL_HEIGHT);
    glVertex2f((x + 0.85) * CELL_WIDTH, (y + 0.15) * CELL_HEIGHT);
    glVertex2f((x + 0.55) * CELL_WIDTH, (y + 0.4) * CELL_HEIGHT);
    glEnd();
}
