#include "ladder.h"

using namespace std;

/**
 * @brief Print an error message (or handle invalid input).
 *        You could also just do cerr << msg and exit(1), 
 *        or throw an exception, depending on your teacher's specs.
 */
void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " for start = \"" 
         << word1 << "\", end = \"" << word2 << "\"" << endl;
    // Possibly exit or throw
    // exit(1); 
}

/**
 * @brief Return true if str1 and str2 differ by 
 *        at most 'd' "edit operations" (insertion, deletion, substitution).
 *        For Homework 9, 'd' will always be 1 if you just want a yes/no check 
 *        that they differ by exactly 1 operation.
 *
 *        A simplified approach is:
 *        1) If abs(len1 - len2) > 1 => return false
 *        2) If lengths differ by 1, check if you can insert or remove 1 char
 *        3) If lengths are same, check if exactly 1 char differs
 */
bool edit_distance_within(const std::string& s1, const std::string& s2, int d) {
    // Quick length check
    int len1 = (int)s1.size();
    int len2 = (int)s2.size();
    if (abs(len1 - len2) > d) {
        return false; 
    }

    // CASE 1: Same length => check if exactly 1 substitution
    if (len1 == len2) {
        int diffCount = 0;
        for (int i = 0; i < len1; i++) {
            if (s1[i] != s2[i]) {
                diffCount++;
                if (diffCount > d) return false;
            }
        }
        return (diffCount == d); 
    }

    // CASE 2: length differs by 1 => check insertion/deletion
    // We'll ensure s1 is the shorter (or equal)
    const string& shorter = (len1 < len2) ? s1 : s2;
    const string& longer  = (len1 < len2) ? s2 : s1;

    int i = 0, j = 0;
    int mismatchCount = 0;
    while (i < (int)shorter.size() && j < (int)longer.size()) {
        if (shorter[i] != longer[j]) {
            mismatchCount++;
            if (mismatchCount > d) return false;
            j++; // skip one char in longer
        } else {
            i++;
            j++;
        }
    }
    // If we exit the loop, we might have leftover in "longer" 
    // but it can only be 1 leftover char to still be within distance 1
    // So mismatch is mismatchCount + leftover
    // leftover = (longer.size() - j)
    mismatchCount += (longer.size() - j);

    return (mismatchCount == d);
}

/**
 * @brief Return true if word1 and word2 differ by exactly 1 "edit operation".
 */
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

/**
 * @brief BFS to find the shortest word ladder from begin_word to end_word 
 *        among words in word_list.
 * 
 * Steps:
 *  1. If begin_word == end_word => immediate error or handle edge case
 *  2. Use queue< vector<string> > for BFS 
 *  3. Keep a visited set<string> so we don't re-use words 
 *  4. Return the first ladder that reaches end_word or empty if none
 */
vector<string> generate_word_ladder(const string& begin_word, 
                                    const string& end_word, 
                                    const set<string>& word_list)
{
    // Edge case check
    if (begin_word == end_word) {
        // Possibly do: error(begin_word, end_word, "Start equals end");
        return {}; 
    }

    // BFS data structures
    queue< vector<string> > ladderQueue; 
    ladderQueue.push({ begin_word });

    // visited tracks dictionary words we've used 
    // (we do not require begin_word to be in dictionary).
    set<string> visited; 
    // If begin_word is in dict, we mark it visited; 
    // if it's not in dict, it's effectively "used" as well, so no duplicates.
    if (word_list.find(begin_word) != word_list.end()) {
        visited.insert(begin_word);
    }

    while (!ladderQueue.empty()) {
        vector<string> ladder = ladderQueue.front();
        ladderQueue.pop();
        // The last word in the current ladder
        string last_word = ladder.back();

        // We'll search potential neighbors in word_list
        // Because word_list can be large, you might want a more optimized approach,
        // but naive is okay for moderate data sizes. 
        // Check each dictionary word to see if it's 1 edit away from last_word
        for (auto & w : word_list) {
            if (visited.count(w) == 0) {
                if (is_adjacent(last_word, w)) {
                    // Found a neighbor
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(w);
                    visited.insert(w); // mark it used

                    if (w == end_word) {
                        // Found a solution!
                        return new_ladder;
                    } else {
                        ladderQueue.push(new_ladder);
                    }
                }
            }
        }
    }

    // No ladder found
    return {};
}

/**
 * @brief Load words from a file into a set<string>.
 *        Typically all-lowercase in words.txt, but you might want to 
 *        do `tolower()` conversions if needed.
 */
void load_words(set<string> & word_list, const string& file_name) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        cerr << "Cannot open " << file_name << endl;
        return; // or throw
    }
    string word;
    while (fin >> word) {
        // possibly transform to lowercase
        // for (auto &c : word) c = tolower(c);
        word_list.insert(word);
    }
    fin.close();
}

/**
 * @brief Print out the ladder separated by spaces
 */
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "(No ladder found)" << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i + 1 < ladder.size()) cout << " -> ";
    }
    cout << endl;
}

/**
 * @brief Example test harness to ensure the code works.
 *        Called from ladder_main.cpp or for your convenience.
 */
void verify_word_ladder() {
    // Just an example – only works if you have words.txt in the same folder
    set<string> word_list;
    load_words(word_list, "words.txt");

    // Some basic tests
    {
        auto ladder = generate_word_ladder("cat", "dog", word_list);
        cout << "cat -> dog: ";
        print_word_ladder(ladder);
    }

    // You can put the my_assert() macros or other checks 
    // from the assignment instructions here if you like.
}

