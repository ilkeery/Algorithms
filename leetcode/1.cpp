class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string result = "";
        int len_1 = word1.length();
        int len_2 = word2.length();
        if(len_1>len_2)
        {
            for(int i=0; i<len_2; i++)
            {
                result.append(1,word1[i]);
                result.append(1,word2[i]);
            }
            for(int i=len_2; i<len_1; i++)
            {
                result.append(1, word1[i]);
            }
        }
        else
        {
            for(int i=0; i<len_1; i++)
            {
                result.append(1,word1[i]);
                result.append(1,word2[i]);
            }
            for(int i=len_1; i<len_2; i++)
            {
                result.append(1, word2[i]);
            }
        }
    return result;    
    }
};