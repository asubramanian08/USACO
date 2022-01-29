#include <iostream>
using namespace std;

int main(void)
{
    int tests, len;
    cin >> tests;
    for (int test = 0; test < tests; test++)
    {
        cin >> len;
        len += 2;
        long long *arr = new long long[len];
        for (int i = 1; i < len - 1; i++)
            cin >> arr[i];
        arr[0] = arr[len - 1] = 0;
        long long change = 0, curr;
        bool works = true;
        for (int i = 2; i < len - 1 && works; i++)
            if (arr[i - 1] < arr[i])
            {
                curr = arr[i] - arr[i - 1];
                if ((arr[i] -= curr) < 0)
                    works = false;
                if ((arr[i + 1] -= curr) < 0)
                    works = false;
                change += curr * 2;
            }
            else if (arr[i - 1] > arr[i])
            {
                change += (arr[i - 1] - arr[i]) * (i - 1);
                works = i % 2 == 1;
            }
        if (works)
            cout << change << endl;
        else
            cout << -1 << endl;
        delete[] arr;
    }
    return 0;
}