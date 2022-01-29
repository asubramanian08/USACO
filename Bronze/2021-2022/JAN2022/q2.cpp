#include <iostream>
#include <algorithm>
using namespace std;

#define SIDES 4
#define MIN_FACE 1
#define MAX_FACE 10

int beats(int *A, int *B)
{
    int wins = 0, total = SIDES * SIDES;
    for (int i = 0; i < SIDES; i++)
        for (int j = 0; j < SIDES; j++)
        {
            wins += A[i] > B[j];
            total -= A[i] == B[j];
        }
    return wins * 2 - total;
}

int main(void)
{
    int tests, *A = new int[SIDES], *B = new int[SIDES], *C = new int[SIDES];
    cin >> tests;
    for (int test = 0; test < tests; test++)
    {
        for (int i = 0; i < SIDES; i++)
            cin >> A[i];
        for (int i = 0; i < SIDES; i++)
            cin >> B[i];
        int outcome = beats(A, B);
        bool ans = false;
        if (outcome == 0) // tie
            ans = true;
        if (outcome < 0)
            swap(A, B);
        for (C[0] = MIN_FACE; C[0] <= MAX_FACE && !ans; C[0]++)
            for (C[1] = MIN_FACE; C[1] <= MAX_FACE && !ans; C[1]++)
                for (C[2] = MIN_FACE; C[2] <= MAX_FACE && !ans; C[2]++)
                    for (C[3] = MIN_FACE; C[3] <= MAX_FACE && !ans; C[3]++)
                        if (beats(C, A) > 0 && beats(B, C) > 0)
                            ans = true;
        if (ans && outcome != 0)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}