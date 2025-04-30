#include "Game.h"
#include "Frame.h"
#include "BonusEvaluator.h"

#include <iostream>

namespace
{
    constexpr unsigned int MAX_FRAMES = 10;
}

using namespace std;

Game::Game()
    : FrameInstance(std::make_unique<Frame>())
    , BonusEvaluatorInstance(std::make_unique<BonusEvaluator>())
    , TotalScore(0)
    , CurrentFrameIndex(0)
{

}

Game::~Game()
{
}

void Game::Reset()
{
    FrameInstance.reset(new Frame());
    BonusEvaluatorInstance.reset(new BonusEvaluator());
    TotalScore = 0;
    CurrentFrameIndex = 0;
}

bool Game::GameRunning() const
{
    return (CurrentFrameIndex < MAX_FRAMES);
}

void Game::InitializeFrame()
{
    ++CurrentFrameIndex;
    cout << "Frame " << CurrentFrameIndex << endl;
    FrameInstance->Reset();
    FrameInstance->StartFrame();
    if (CurrentFrameIndex == MAX_FRAMES)
    {
        FrameInstance->SetAsLastFrame();
    }
}

void Game::ProcessFrame()
{

    while (FrameInstance->NextThrowNeeded())
    {
        char bowlingThrow{'q'};
        cout << "Enter the throw : " << endl;
        cin >> bowlingThrow;
        if (bowlingThrow == 'q')
        {
            exit(1);
        }
        
        try
        {
            ProcessThrow(bowlingThrow);
        }
        catch (invalid_argument& e)
        {
            cout << e.what() << endl;
        }
    }
    BonusEvaluatorInstance->AllotBonusForFrame(FrameInstance.get());
    TotalScore += (FrameInstance->GetFrameScore() + BonusEvaluatorInstance->GetBonusValue());
    BonusEvaluatorInstance->ClearBonus();
}

void Game::ProcessThrow(char throwValue)
{
    unsigned int currentThrowScore = 0;
    switch (throwValue)
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
        break;

    default:
        throw invalid_argument("Input is not from valid list of arguments. Please try again.");
        break;
    }

    try
    {
        FrameInstance->ProcessThrow(currentThrowScore);
    }
    catch (out_of_range& e) 
    {
        cout << e.what() << endl;
    }
    BonusEvaluatorInstance->AwardBonusIfApplicable(currentThrowScore, FrameInstance.get());
}

unsigned int Game::GetTotalScore() const
{
    return TotalScore;
}

unsigned int Game::GetCurrentFrameNumber() const
{
    return CurrentFrameIndex;
}

unsigned int Game::GetCurrentFrameScore() const
{
    return FrameInstance->GetFrameScore();
}