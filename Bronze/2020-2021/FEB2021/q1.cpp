// Doing to stop debug time -> submit once
// Start: 7:22
// Think: 7:29
// Write: 8:03 3/10 -> fixed (didn't make dist negative)
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

#define cycleLen 12

int main(void)
{
    //preperation
    string years[] = {"Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat"};
    map<string, int> cowBirth;
    cowBirth["Bessie"] = 0;
    int numLines, refYear, cycle, dist, refCycle;
    string name, word;
    bool is_before;

    //reading and doing
    cin >> numLines;
    for (int i = 0; i < numLines; i++)
    {
        //read
        cin >> name;         //cow name
        cin >> word >> word; //"born in"
        cin >> word;         //next of previous
        is_before = (word == "previous");
        cin >> word; //cycle type
        cycle = find(years, years + cycleLen, word) - years;
        cin >> word >> word; //"year from"
        cin >> word;         //cow from
        refYear = cowBirth[word];

        //find year
        refCycle = refYear % cycleLen;
        if (refCycle < 0)
            refCycle += cycleLen;
        dist = cycle - refCycle;
        if (is_before && dist >= 0)
            dist -= cycleLen;
        if (!is_before && dist <= 0)
            dist += cycleLen;

        //set
        cowBirth[name] = dist + refYear;
    }

    cout << abs(cowBirth["Elsie"]);
    return 0;
}