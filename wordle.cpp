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
//using namespace std;




// Add prototypes of helper functions here
void recursive_helper(const std::string& in, const std::string& floating, int position, std::string& curr, std::set<std::string>& allStrings);
bool containsAllChars(const std::string& curr, const std::string& floating);
void findEnglishWords(const std::set<std::string>& gibberish, const std::set<std::string>& dict, std::set<std::string>& english_set);
bool doesContainWord(const std::set<std::string>& container, const std::string& containee);
bool doesContainLetter(const std::string& container, char& containee);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> english_set;
    std::set<std::string> gibberish_set;
    std::string startword(in.length(), ' '); // start with a blank word
    recursive_helper(in, floating, 0, startword, gibberish_set);
    // Filter gibberish to english
    findEnglishWords(gibberish_set, dict, english_set);
    return english_set;
}


// Define any helper functions here
//
// All permutations of strings with the given letters
void recursive_helper(const std::string& in, const std::string& floating, int position, std::string& curr, std::set<std::string>& allStrings) {
    if (unsigned(position) == in.length()) {
        // Word is full check if it has floating chars
        if (containsAllChars(curr, floating)) {
            // Add it to possible strings
            allStrings.insert(curr);
        }
        return;
    }
   
    if (in[position] != '-') {// Its a fixed element, set it accordingly
        curr[position] = in[position];
        recursive_helper(in, floating, position += 1, curr, allStrings);
    }
    else {// Try every letter
        for (char letter = 'a'; letter <= 'z'; letter++) {
            curr[position] = letter;
            recursive_helper(in, floating, position + 1, curr, allStrings);
        }
    }
}


// See if the word contains all the floating chars
bool containsAllChars(const std::string& curr, const std::string& floating) {
    // Iterate through all characters in the floating string
    for (char ch : floating) {
        // Check if character is present in curr
        //if (!doesContainLetter(curr, ch)) {
        if (curr.find(ch) == std::string::npos){
            // If it's not present, return false
            return false;
        }
    }
    // True if all characters are present
    return true;
}


// Filter down to english words only
void findEnglishWords(const std::set<std::string>& gibberish, const std::set<std::string>& dict, std::set<std::string>& english_set) {
    for (const std::string& word : gibberish) {
        //if (doesContainWord(dict, word)) {
        if (dict.count(word) > 0){
            english_set.insert(word);
        }
    }
}


// bool doesContainWord(const std::set<std::string>& container,const std::string& containee){
//     for (const std::string& word : container){
//         if (word == containee){
//             return true;
//         }
//     }
//     return false;
// }


// bool doesContainLetter(const std::string& container, char& containee){
//     for (const char& letter : container){
//         if (letter == containee){
//             return true;
//         }
//     }
//     return false;
// }
