class Solution
{
public:
    vector<bool> kidsWithCandies(vector<int> &candies, int extraCandies)
    {
        int n = candies.size();
        vector<bool> candiesBool(n);
        fill(candiesBool.begin(), candiesBool.end(), false);

        int max = greatestNumber(candies, n);
        for (int i = 0; i < n; i++)
        {
            if (extraCandies + candies[i] >= max)
            {
                candiesBool[i] = true;
            }
        }
        return candiesBool;
    }

    int greatestNumber(vector<int> &candies, int size)
    {
        int max = candies[0];
        for (int i = 0; i < size; i++)
        {
            if (candies[i] > max)
            {
                max = candies[i];
            }
        }
        return max;
    }
};