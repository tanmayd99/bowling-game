#pragma once

#include <string>
#include <memory>

class Frame;
class BonusEvaluator;

class Game
{
public:
    Game();
    ~Game();

    void Reset();
    void InitializeFrame();
    void ProcessFrame();

    bool GameRunning() const;

    unsigned int GetTotalScore() const;
    unsigned int GetCurrentFrameNumber() const;
    unsigned int GetCurrentFrameScore() const;

private:
    void ProcessThrow(char throwValue);

    std::unique_ptr<Frame> FrameInstance;
    std::unique_ptr<BonusEvaluator> BonusEvaluatorInstance;
    unsigned int TotalScore;
    unsigned int CurrentFrameIndex;
};
