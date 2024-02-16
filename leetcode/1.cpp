class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string result = "";
        int len_1 = word1.length(); // n
        int len_2 = word2.length(); // n 
        if(len_1>len_2) //1
        {
            for(int i=0; i<len_2; i++) //n
            {
                result += word1[i]; // 1*n
                result += word2[i]; // 1*n
                
            }
            for(int i=len_2; i<len_1; i++) // n or 1?
            {
                result += word1[i]; // 1*n
            }
        }
        else
        {
            for(int i=0; i<len_1; i++) //n
            {
                result += word1[i]; // 1*n
                result += word2[i]; // 1*n
            }
            for(int i=len_1; i<len_2; i++) //n
            {
                result += word2[i]; // 1*n
            }
        }
    return result; // Time complexity: O(n), space complexity: O(n)
    }
};
