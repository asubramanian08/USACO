/*USACO FEB11 Problem 'cowlpha' Analysis by Michael Cohen

This is a simple dynamic programming problem. The idea is to compute and store, for all i <= U, j <= L, 
and symbols k, the number of strings containing i uppercase letters and j lowercase letters that end on 
the symbol k. For each i and j, this can be computed using the values for smaller i and j by looping over 
each final valid pair of symbols and adding the number of possibilities ending on these pairs to the 
appropriate positions. For instance, if Ab is a valid string, the number of strings containing 5 uppercase 
and 6 lowercase letters ending on Ab is equal to the number of strings containing 5 uppercase and 5 
lowercase letters and ending on A; this value is added the the value for 5 uppercase and 6 lowercase 
ending on b. Evaluating this recurrence in this way takes time O(ULP). A short implementation of this 
solution is: */
#include <fstream>
using namespace std;
int U, L, P;
int first[200], second[200];
int sentence[251][251][52];
int main()
{
    ifstream inp("cowlpha.in");
    ofstream outp("cowlpha.out");
    inp >> U >> L >> P;
    for (int i = 0; i < P; i++)
    {
        char pair[3];
        inp >> pair;
        first[i] = ('A' <= pair[0] && pair[0] <= 'Z' ? pair[0] - 'A' : pair[0] - 'a' + 26);
        second[i] = ('A' <= pair[1] && pair[1] <= 'Z' ? pair[1] - 'A' : pair[1] - 'a' + 26);
    }
    for (int i = 0; i < 26; i++)
        sentence[1][0][i]++;
    for (int i = 26; i < 52; i++)
        sentence[0][1][i]++;
    for (int i = 0; i <= U; i++)
        for (int j = 0; j <= L; j++)
        {
            if ((i + j) <= 1)
                continue;
            for (int k = 0; k < P; k++)
            {
                if (second[k] < 26 && i > 0)
                    sentence[i][j][second[k]] = (sentence[i][j][second[k]] +
                                                 sentence[i - 1][j][first[k]]) %
                                                97654321;
                else if (second[k] >= 26 && j > 0)
                    sentence[i][j][second[k]] = (sentence[i][j][second[k]] + sentence[i][j - 1][first[k]]) % 97654321;
            }
        }
    int answer = 0;
    for (int i = 0; i < 52; i++)
        answer = (answer + sentence[U][L][i]) % 97654321;
    outp << answer << endl;
    return 0;
}