// Doing to stop debug time -> submit once
// Start: 4:43
// Think: 4:44
// Write: 4:55
#include <iostream>
#include <string>
using namespace std;

#define ALPHA_SIZE 26

int main(void)
{
    //read
    string let;
    cin >> let;
    string heard;
    cin >> heard;

    //find letter conversion
    int letters[ALPHA_SIZE];
    for (int i = 0; i < ALPHA_SIZE; i++)
        letters[let[i] - 'a'] = i;

    //find words
    int words = 1;
    for (int i = 1; i < heard.size(); i++)
        if (letters[heard[i] - 'a'] <= letters[heard[i - 1] - 'a'])
            words++;

    //print
    cout << words << '\n';
    return 0;
}