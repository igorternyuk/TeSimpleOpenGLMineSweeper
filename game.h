#ifndef GAME_H
#define GAME_H
#include "painter.h"
#include <time.h>

class Game
{
public:
    enum {WIDTH = 16, HEIGHT = 16};
    enum CellState{CLOSED, OPENED, FLAGGED, QUESTIONED};
    enum GameState{PLAY, VICTORY, DEFEAT};
    explicit Game(int numMines = 40);
    void openCell(int x, int y);
    void markCell(int x, int y);
    void newGame();
    void draw() const;
    inline int getNumFlags() const { return _numFlags; }
private:
    struct Cell
    {
        CellState state;
        bool isMined;
    };

    int _numFlags{0};
    bool _isFirstMove {true};
    int _explosionX{-1}, _explosionY{-1};
    GameState _gameState {PLAY};
    int _numMines;
    Cell _field[WIDTH][HEIGHT];
    mutable time_t _startTime, _diffTime;
    int coutMinesAround(int x, int y) const;
    void clearField();
    void setMines();
    void resetTime();
    bool isWin() const;
    void drawScore() const;
    void drawGameStatus() const;
    void displayTime() const;
};

#endif // GAME_H
