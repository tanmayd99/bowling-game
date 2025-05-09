#include "Game.h"
#include "Frame.h"
#include "BonusEvaluator.h"

#include <iostream>
#include <regex>

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
        std::string bowlingThrow;
        cout << "Enter the throw : ";
        cin >> bowlingThrow;
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

void Game::ProcessThrow(std::string throwValue)
{
    unsigned int currentThrowScore = 0;
    std::regex regexp("^[0-9]*$");
    if (std::regex_match(throwValue, regexp))
    {

        currentThrowScore = std::stoi(throwValue);
        if (currentThrowScore > 10)
        {
            throw invalid_argument("Input is not from valid list of arguments. Please try again.");
        }
    }
    else
    {
        throw invalid_argument("Input is not from valid list of arguments. Please try again.");
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