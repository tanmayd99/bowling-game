#include <iostream>
#include "src/Game.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Welcome to the Bowling Arena !!" << endl;
    cout << "Valid Throw format : 0-9 , x - strike , q - quit , any other key - foul (zero score for the throw)" << endl;
    cout << "Get Ready....." << endl;

    string playAgain {"y"};
    string bowlingThrow {"r"};
    Game* gameInstance = new Game();

    while(playAgain == "y")
    {
        gameInstance->Reset();
        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        while(gameInstance->GameRunning())
        {
            gameInstance->InitializeFrame();
            while(gameInstance->AcceptThrows())
            {
                cout<< "Enter the throw : "<< endl;
                cin >> bowlingThrow;
                if(bowlingThrow == "q")
                {
                    exit(1);
                }
                gameInstance->ProcessThrow(bowlingThrow);
            }
            cout << "Score for Frame " << gameInstance->GetCurrentFrameNumber() << " is " << gameInstance->GetCurrentFrameScore() << endl;
            cout << "Cumulative Score : " << gameInstance->GetTotalScore() << endl;
            cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            gameInstance->NextFrame();
        }
        cout << "Total Score for the game: " << gameInstance->GetTotalScore() << endl;
        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;


        cout << "Play Again [y/n]: " ;
        do
        {
            cin >> playAgain;
            if(playAgain != "y" && playAgain != "n")
            {
                cout << "Invalid i/p. Enter Again : ";
            }
        }while(playAgain != "y" && playAgain != "n");
    }

    delete gameInstance;
    return 0;
}

