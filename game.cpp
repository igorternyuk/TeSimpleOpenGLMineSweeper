#include "game.h"
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>

Game::Game(int numMines):
    _numMines(numMines >= WIDTH * HEIGHT ? WIDTH * HEIGHT : numMines)
{
    clearField();
    resetTime();
    //_startTime = clock();
}

void Game::draw() const
{
    for(int y{0}; y < HEIGHT; ++y)
    {
        for(int x{0}; x < WIDTH; ++x)
        {
            switch(_field[y][x].state)
            {
                case CLOSED:
                    Painter::drawClosedCell(x, y);
                    break;
                case OPENED:
                    if(_field[y][x].isMined)
                    {
                        if(x == _explosionX && y == _explosionY)
                            Painter::drawMinedCell(x,y, true);
                        else
                            Painter::drawMinedCell(x,y, false);
                    }
                    else
                        Painter::drawOpenedCell(x, y, coutMinesAround(x, y));
                    break;
                case FLAGGED:
                    Painter::drawFlaggedCell(x, y);
                    break;
                case QUESTIONED:
                    Painter::drawQuestionedCell(x,y);
                    break;
            }
        }
    }
    drawScore();
    drawGameStatus();
    displayTime();
}

void Game::openCell(int x, int y)
{
    if(_gameState == PLAY)
    {
        if(_field[y][x].state == CLOSED)
        {
            _field[y][x].state = OPENED;
            if(_field[y][x].isMined)
            {
                _gameState = DEFEAT;
                _explosionX = x;
                _explosionY = y;
                for(int y{0}; y < HEIGHT; ++y)
                {
                    for(int x{0}; x < WIDTH; ++x)
                    {
                        if(_field[y][x].isMined && _field[y][x].state != FLAGGED)
                            _field[y][x].state = OPENED;
                    }
                }
                return;
            }
        }
        if(isWin())
        {
            _gameState = VICTORY;
            return;
        }
        if(_isFirstMove)
        {
            setMines();
            _isFirstMove = false;
        }
        //Если вокруг ячейки нет мин то рекурсивно открываем соседние ячейки
        if(coutMinesAround(x, y) == 0)
        {
            for(int dx{-1}; dx < 2; ++dx)
            {
                for(int dy{-1}; dy < 2; ++dy)
                {
                    int neighbourX = x + dx;
                    int neighbourY = y + dy;
                    if(neighbourX < 0 || neighbourX >= WIDTH ||
                       neighbourY < 0 || neighbourY >= HEIGHT ||
                       (neighbourX == x && neighbourY == y))
                        continue;
                    if(_field[neighbourY][neighbourX].state == CLOSED)
                        openCell(neighbourX, neighbourY);
                }
            }
        }
    }
}

void Game::newGame()
{
    _gameState = PLAY;
    _numFlags = 0;
    _isFirstMove = true;
    _explosionX = -1;
    _explosionY = -1;
    clearField();
    resetTime();
}

void Game::markCell(int x, int y)
{
    if(_gameState == PLAY)
    {
        switch(_field[y][x].state)
        {
            case OPENED:
                break;
            case CLOSED:
                if(_numFlags < _numMines)
                {
                    _field[y][x].state = FLAGGED;
                    ++_numFlags;
                }
            break;
            case FLAGGED:
                _field[y][x].state = QUESTIONED;
                --_numFlags;
            break;
            case QUESTIONED:
                _field[y][x].state = CLOSED;
            break;
        }
        if(isWin())
        {
            _gameState = VICTORY;
        }
    }
}

int Game::coutMinesAround(int x, int y) const
{
    int result = 0;
    for(int dx{-1}; dx < 2; ++dx)
    {
        for(int dy{-1}; dy < 2; ++dy)
        {
            int neighbourX = x + dx;
            int neighbourY = y + dy;
            if(neighbourX < 0 || neighbourX >= WIDTH ||
               neighbourY < 0 || neighbourY >= HEIGHT ||
               (neighbourX == x && neighbourY == y))
                continue;
            if(_field[neighbourY][neighbourX].isMined)
                ++result;
        }
    }
    return result;
}

void Game::clearField()
{
    for(int y{0}; y < HEIGHT; ++y)
    {
        for(int x{0}; x < WIDTH; ++x)
        {
            _field[y][x].state = CLOSED;
            _field[y][x].isMined = false;
        }
    }
}

void Game::setMines()
{
    srand(time(0));
    for(int i{0}; i < _numMines; ++i)
    {
        int x,y;
        do
        {
            x = rand() % WIDTH;
            y = rand() % HEIGHT;
        }
        while(_field[y][x].isMined || _field[y][x].state != CLOSED);
        _field[y][x].isMined = true;
    }
}

void Game::resetTime()
{
    _startTime = time(0);
    _diffTime = 0;
}

bool Game::isWin() const
{
    for(int y{0}; y < HEIGHT;++y)
        for(int x{0}; x < WIDTH; ++x)
            if(_field[y][x].state == CLOSED)
                return false;
    return true;
}

void Game::drawScore() const
{
    Painter::drawFlag(0, 16);
    std::stringstream ss;
    ss << _numFlags << "/" << _numMines;
    Painter::drawText(ss.str().c_str(), 40, 670, 15, 0, 127, 14);
}

void Game::drawGameStatus() const
{
    switch(_gameState)
    {
        case VICTORY:
            Painter::drawText("YOU WON!", 120, 670, 15, 0, 127, 37);
            break;
        case DEFEAT:
            Painter::drawText("YOU LOST!", 120, 670, 15, 127, 0, 0);
            break;
        case PLAY:
            Painter::drawText("PLAY", 120, 670, 15, 0, 0, 210);
            break;
    }
}

void Game::displayTime() const
{

    if(_gameState == PLAY)
    {
        _diffTime = time(0) - _startTime;
    }
    int hour = _diffTime / 3600;
    int min = (_diffTime % 3600) / 60;
    int sec = (_diffTime % 3600) % 60;
    std::stringstream ss;
    ss << hour << ":" << min << ":" << sec << std::endl;
    Painter::drawText(ss.str().c_str(),260, 670, 13, 0, 127, 0);
    glutPostRedisplay();
}
