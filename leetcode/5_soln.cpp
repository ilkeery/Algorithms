// slower but more educative
class Solution
{
public:
    string reverseVowels(string s)
    {
        vector<char> vowels = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};
        vector<int> indices;
        vector<char> reverseVowels;

        // Vokalleri bul ve ters çevrilen vokalleri sakla
        for (int i = 0; i < s.length(); ++i)
        {
            if (find(vowels.begin(), vowels.end(), s[i]) != vowels.end())
            {
                indices.push_back(i);
                reverseVowels.push_back(s[i]);
            }
        }

        // Vokalleri ters çevir
        reverse(reverseVowels.begin(), reverseVowels.end());

        // Vokalleri string içinde yer değiştir
        for (int i = 0; i < indices.size(); ++i)
        {
            s[indices[i]] = reverseVowels[i];
        }

        return s;
    }
};


// faster
class Solution
{
public:
    string reverseVowels(string s)
    {
        vector<char> vowels;
        int counter = 0;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (
                s[i] == 'a' ||
                s[i] == 'e' ||
                s[i] == 'i' ||
                s[i] == 'o' ||
                s[i] == 'u' ||
                s[i] == 'A' ||
                s[i] == 'E' ||
                s[i] == 'I' ||
                s[i] == 'O' ||
                s[i] == 'U')
            {
                vowels.push_back(s[i]);
                s[i] = '_';
            }
        }

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '_')
            {
                s[i] = vowels[counter];
                counter++;
            }
        }
        return s;
    }
};