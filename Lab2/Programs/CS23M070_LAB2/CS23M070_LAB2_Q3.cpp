#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, k, sum, max_sum;

    cin >> n >> k; // Inputing n and k
    vector<int> v(n);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i]; // Inputing n elements
    }
    sum = 0;
    for (int i = 0; i < k; i++) // sum of first k elements
    {
        sum += v[i];
    }
    max_sum = sum;
    for (int i = 1; i + k - 1 < n; i++)
    {
        sum = sum - v[i - 1] + v[i + k - 1]; // sum of k elements starting from i
        if (sum > max_sum)
        {
            max_sum = sum;
        }
    }
    cout << max_sum;
}