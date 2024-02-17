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
// Less memory usage
class Solution
{
public:
    vector<bool> kidsWithCandies(vector<int> &candies, int extraCandies)
    {
        int num_kids = candies.size();
        std::vector<bool> b_hasGreatest(num_kids);
        int max_num_candies = *max_element(candies.begin(), candies.end());

        for (int iter = 0; iter < num_kids; iter++)
        {
            if (max_num_candies <= candies[iter] + extraCandies)
            {
                b_hasGreatest[iter] = true;
            }
            else
            {
                b_hasGreatest[iter] = false;
            }
        }
        return b_hasGreatest;
    }
};