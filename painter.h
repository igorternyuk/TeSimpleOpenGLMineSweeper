#ifndef PAINTER_H
#define PAINTER_H

#include <GL/gl.h>
#include <GL/glut.h>

class Painter
{
public:
    Painter();
    enum {CELL_WIDTH = 40, CELL_HEIGHT = 40};
    static void drawClosedCell(int x, int y);
    static void drawOpenedCell(int x, int y, int numMines);
    static void drawFlaggedCell(int x, int y);
    static void drawQuestionedCell(int x, int y);
    static void drawMinedCell(int x, int y, bool isExplosion);
    static void drawText(const char *word, int x_, int y_, float step,
                         int red, int green, int blue);
    static void drawFlag(int x, int y);
private:
    static void drawBackground(int x, int y);
    static void drawFrame(int x, int y);
    static void drawPolygon(int x, int y, int numVertex, float radius);


};

#endif // PAINTER_H
