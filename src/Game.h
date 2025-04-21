#include <string>

class Game
{
public: 
    Game();
    ~Game() = default;

    void Reset();
    void InitializeFrame();
    void ProcessThrow(std::string throwValue);
    void NextFrame();

    bool GameRunning() const;
    bool AcceptThrows() const;

    unsigned int GetTotalScore() const;
    unsigned int GetCurrentFrameNumber() const;
    unsigned int GetCurrentFrameScore() const;

private:
    static const unsigned int MAX_FRAMES;
    static const unsigned int MAX_THROWS_PER_FRAME;
    static const unsigned int MAX_PINS_PER_FRAME;
    unsigned int BonusTracker;
    unsigned int TotalScore;
    unsigned int CurrentFrameIndex;
    unsigned int CurrentFrameScore;
    unsigned int ThrowCountWithinFrame;
    bool AcceptThrowsTracker;
};
