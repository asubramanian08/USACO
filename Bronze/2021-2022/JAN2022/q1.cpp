#include <iostream>
using namespace std;

#define SIDE 3
#define LET 26

int main(void)
{
    char org[SIDE][SIDE];
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
            cin >> org[i][j];
    char guess[SIDE][SIDE];
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
            cin >> guess[i][j];
    int orgColorCt[LET], guessColorCt[LET];
    for (int i = 0; i < LET; i++)
        orgColorCt[i] = guessColorCt[i] = 0;
    int correct = 0, misplaced = 0;
    for (int i = 0; i < SIDE; i++)
        for (int j = 0; j < SIDE; j++)
            if (org[i][j] == guess[i][j])
                correct++;
            else
            {
                orgColorCt[org[i][j] - 'A']++;
                guessColorCt[guess[i][j] - 'A']++;
            }
    for (int i = 0; i < LET; i++)
        misplaced += min(orgColorCt[i], guessColorCt[i]);
    cout << correct << endl
         << misplaced << endl;
}