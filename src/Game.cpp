#include "Game.h"

#include <iostream>

const unsigned int Game::MAX_FRAMES = 10;
const unsigned int Game::MAX_THROWS_PER_FRAME = 2;
const unsigned int Game::MAX_PINS_PER_FRAME = 10;

Game::Game()
    : TotalScore(0)
    , CurrentFrameIndex(0)
    , CurrentFrameScore(0)
    , ThrowCountWithinFrame(0)
    , AcceptThrowsTracker(true)
{

}

void Game::Reset()
{
    TotalScore = 0;
    CurrentFrameIndex = 0;
    CurrentFrameScore = 0;
    ThrowCountWithinFrame = 0;
    AcceptThrowsTracker = true;
}

bool Game::GameRunning() const
{
    return (CurrentFrameIndex < MAX_FRAMES);
}

void Game::InitializeFrame()
{
    std::cout << "Frame " << GetCurrentFrameNumber() << std::endl;
    CurrentFrameScore = 0;
    ThrowCountWithinFrame = 0;
    AcceptThrowsTracker = true;
}

void Game::ProcessThrow(std::string throwValue)
{
    ++ThrowCountWithinFrame;

    unsigned int currentThrowScore = 0;
    switch(throwValue[0])
    {
    case '0':
        break;

    case '1':
        currentThrowScore = 1;
        break;

    case '2':
        currentThrowScore = 2;
        break;

    case '3':
        currentThrowScore = 3;
        break;

    case '4':
        currentThrowScore = 4;
        break;

    case '5':
        currentThrowScore = 5;
        break;

    case '6':
        currentThrowScore = 6;
        break;

    case '7':
        currentThrowScore = 7;
        break;

    case '8':
        currentThrowScore = 8;
        break;

    case '9':
        currentThrowScore = 9;
        break;

    case 'x':
        currentThrowScore = 10;
        AcceptThrowsTracker = false;
        break;

    default :
        break;
    }

    if((currentThrowScore + CurrentFrameScore) > MAX_PINS_PER_FRAME )
    {
        if(ThrowCountWithinFrame == MAX_THROWS_PER_FRAME)
        {
            if(!((CurrentFrameIndex == 9) && (CurrentFrameScore == MAX_FRAMES)))
            {
                std::cout << "Bad Throw: Throw exeeds maximum PINs available to knock down. Awarding Zero score for the current thow" << std::endl;
                currentThrowScore = 0;
            }
        }
    }

    CurrentFrameScore += currentThrowScore;

    bool allotBonusScore = false;
    bool allotBonusThrow = false;
    if(BonusTracker > 0)
    {
        allotBonusScore = true;
        --BonusTracker;
    }

    if((ThrowCountWithinFrame >= MAX_THROWS_PER_FRAME))
    {
        AcceptThrowsTracker = false;
        if((CurrentFrameScore == MAX_PINS_PER_FRAME ) && (ThrowCountWithinFrame == MAX_THROWS_PER_FRAME))
        {
            if(CurrentFrameIndex == 9)
            {
                allotBonusThrow = true;
            }
            else
            {
                ++BonusTracker;
            }
        }
    }
    else if(throwValue == "x")
    {
        if((CurrentFrameIndex == 9) && (ThrowCountWithinFrame < MAX_THROWS_PER_FRAME))
        {
            allotBonusThrow = true;
        }
        else
        {
            BonusTracker += 2;
        }
    }

    if(allotBonusThrow)
    {
        AcceptThrowsTracker = true;
        allotBonusThrow = false;
    }

    if(allotBonusScore)
    {
        TotalScore += currentThrowScore;
    }

    if(AcceptThrowsTracker == false)
    {
        TotalScore += CurrentFrameScore;
    }
}

bool Game::AcceptThrows() const
{
    return AcceptThrowsTracker;
}

void Game::NextFrame()
{
    ++CurrentFrameIndex;
}

unsigned int Game::GetTotalScore() const
{
    return TotalScore;
}

unsigned int Game::GetCurrentFrameNumber() const
{
    return (CurrentFrameIndex + 1);
}

unsigned int Game::GetCurrentFrameScore() const
{
    return CurrentFrameScore;
}
