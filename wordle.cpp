#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
// bool hasFloating(const string& word, const string& floating);
void fillWord (int idx, string curr, const string& in, int floatCount[26], int floatRemaining, const set<string>& dict, set<string>& results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    int floatCount[26] = {0};
    for (char c : floating) floatCount[c - 'a']++;
    string curr = in;
    fillWord(0, curr, in, floatCount, floating.size(), dict, results);
    return results; 
}

// Define any helper functions here

void fillWord (int idx, string curr, const string& in, int floatCount[26], int floatRemaining, const set<string>& dict, set<string>& results) {
    // base case
    if (idx == (int)curr.size()) {
        if (floatRemaining == 0 && dict.find(curr) != dict.end()) results.insert(curr);
        return;
    }

    // fixed letter
    if (in[idx] != '-') {
        curr[idx] = in[idx];
        
        fillWord(idx+1, curr, in, floatCount, floatRemaining, dict, results);
        return;
    }

    int blanks = 0;
    for (int i = idx+1; i < (int)curr.size(); i++) {
      if (curr[i] == '-') blanks++;
    }

    int totalSlots = blanks + 1; // include current blank;

    for (char c = 'a'; c <= 'z'; c++) {
      if (floatRemaining == totalSlots && floatCount[c -'a'] == 0) continue;

        curr[idx] = c;

        int newCount[26];

        for (int i = 0; i < 26; i++) newCount[i] = floatCount[i];

        int newRemain = floatRemaining;
        if (newCount[c - 'a'] > 0) {
            newCount[c - 'a']--;
            newRemain--;
        }
        // remaining floating > remaing blanks AFTER placing c
        if (newRemain <= blanks) {
          fillWord(idx + 1, curr, in, newCount, newRemain, dict, results);
        }
    }
}