/*USACO JAN14 Problem 'slowdown' Analysis by Nathan Pinsker

In this problem, we are given N times at which Bessie slows down, and want to find the time required for 
Bessie to travel one kilometer. If we somehow had the order in which these events occurred, this problem 
would be much easier: for the first event, we can easily calculate the time and distance at which it 
occurs: the time (in seconds) is equal to the distance in meters from the start. For all subsequent events, 
we know either the time OR the distance at which they occur. We can calculate the other one of these 
values based on the information we have for the event immediately before it. Once we have the distance and 
time at which the last event occurs, we can easily calculate the time required for Bessie to finish out 
the race.

This suggests that we should try to find which order the events occur in. One way to do this is to actually 
run the event. We iterate over all N events, find which one occurs at the earliest time, run the clock 
until that event actually occurs, and repeat, until all events have occurred. While this is a correct 
solution, it is a bit too slow;

the runtime of this is O(N ^ 2), which is not quite fast enough here.By far, the slowest part is actually 
checking all of the N events and seeing which one is first.If we could speed this up, then we should be 
able to solve the problem.The crucial insight to solve this is to note that events that occur at specific 
times, and events that occur at specific distances, actually have orderings of their own.For example, the 
event "D 10" will *always *occur before the event "D 15", no matter what other events might exist along 
the track.Similarly, the event "T 8" will always come after "T 5", no matter what.This means that to check 
which event is coming up first, we only have to find the two events(one of each type) that the lowest 
numbers !Motivated by this, we separate the events with Ds and the events with Ts into two lists, and sort 
them both by the time or distance at which they occur.At each time step, we check the beginning of both 
lists, and figure out which of our two candidate events occurs first.As before, we run the clock until 
that event occurs, remove the event from its list, and repeat.Now, instead of checking up to N events at 
each time step, we have to check at most two !This reduces the runtime to O(N log N)(due to the need to 
sort), which is a huge improvement and is fast enough to score full points. Kalki Seksaria's code is below. 
(He uses priority queues instead of sorted lists, but the details are very similar.)*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int N;
priority_queue<int, vector<int>, greater<int>> timeEvents;
priority_queue<int, vector<int>, greater<int>> distanceEvents;
double currentD;
double currentT;
int speedValue; // 1/speed
int main()
{
    ifstream in("slowdown.in");
    ofstream out("slowdown.out");
    in >> N;
    for (int i = 0; i < N; i++)
    {
        char c;
        int x;
        in >> c >> x;
        if (c == 'T')
            timeEvents.push(x);
        else
            distanceEvents.push(x);
    }
    distanceEvents.push(1000);
    currentT = currentD = 0.0;
    speedValue = 1;
    while (!timeEvents.empty() || !distanceEvents.empty())
    {
        bool isNextTime = false;
        if (distanceEvents.empty())
            isNextTime = true;
        else if (!distanceEvents.empty() && !timeEvents.empty())
            if (timeEvents.top() < (currentT + (distanceEvents.top() -
                                                currentD) *
                                                   speedValue))
                isNextTime = true;
        if (isNextTime)
        {
            currentD += (timeEvents.top() - currentT) / (speedValue + 0.0);
            currentT = timeEvents.top();
            timeEvents.pop();
        }
        else
        {
            currentT += (distanceEvents.top() - currentD) * speedValue;
            currentD = distanceEvents.top();
            distanceEvents.pop();
        }
        speedValue++;
    }
    int currentTime = (int)currentT;
    double fraction = currentT - currentTime;
    if (fraction < 0.5)
        out << currentTime << "\n";
    else
        out << currentTime + 1 << "\n";
    out.close();
}
