//
// Created by jakub on 12/2/22.
//

// Testcases:
//"abcccdee"
//"abbccedd"
//false

//"abbcd"
//"abcdd"
//true

// sort frequency arrays so that they can be later compared

class Solution {
public:
    bool closeStrings(string word1, string word2) {
        // if words do not have equal length, they cannot be close
        if (word1.size() != word2.size()) return false;

        // initialize two frequency arrays to store the alphabet
        array<int, 26> a1 = {0};
        array<int, 26> a2 = {0};

        // populate frequency arrays with number of occurrences of each letter
        for (char &c: word1) ++a1[c - 'a'];
        for (char &c: word2) ++a2[c - 'a'];

        // check for discrepancies in the type of letters
        // that are present in both strings
        // (a comparison of two sets could be used as an alternative
        for (int i = 0; i < 26; ++i) {
            if (bool(a1[i]) != bool(a2[i])) return false;
        }

        // if the program executed thus far, we know that both words
        // are build of the same letters. Let's look at the letter frequencies.

        // Since Operation 2 enables any existing letter to be swapped
        // with another existing letter within the word
        // it is not relevant which particular distinct letter occurred n-times
        // we can sort frequency arrays to later see if the number of letters
        // occurring with certain frequency match
        sort(a1.begin(), a1.end());
        sort(a2.begin(), a2.end());

        // check if both collections of sorted letter frequencies are equal
        return a1 == a2;
    }
};