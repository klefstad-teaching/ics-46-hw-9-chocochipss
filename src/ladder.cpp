#include "ladder.h"
#include <unordered_map>
#include <unordered_set>
using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " for start = \"" 
         << word1 << "\", end = \"" << word2 << "\"" << endl;
}


bool edit_distance_within(const std::string &s1, const std::string &s2, int d)
{
  
    if (std::abs((int)s1.size() - (int)s2.size()) > d) return false;

    if (s1.size() == s2.size()) {
        int mismatchCount = 0;
        for (int i = 0; i < (int)s1.size(); i++) {
            if (s1[i] != s2[i]) {
                mismatchCount++;
                if (mismatchCount > d) return false;
            }
        }
     
        return true;
    }

    const std::string &shorter = (s1.size() < s2.size()) ? s1 : s2;
    const std::string &longer  = (s1.size() < s2.size()) ? s2 : s1;

    int i = 0, j = 0, mismatch = 0;
    while (i < (int)shorter.size() && j < (int)longer.size()) {
        if (shorter[i] != longer[j]) {
            mismatch++;
            if (mismatch > d) return false;
            j++;
        } else {
            i++;
            j++;
        }
    }

    mismatch += (longer.size() - j);

    return (mismatch <= d);
}




bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string &begin_word,
                                    const string &end_word,
                                    const set<string> &word_list)
{

    if (begin_word == end_word) {
        return {};
    }
    if (word_list.find(end_word) == word_list.end()) {
        return {};
    }


    unordered_map<int, vector<string>> length_map;
    for (auto &w : word_list) {
        length_map[w.size()].push_back(w);
    }


    queue<vector<string>> q;
    q.push({begin_word});

    unordered_set<string> visited;
    visited.insert(begin_word); 

    while (!q.empty()) {
        auto ladder = q.front();
        q.pop();
        const string &last = ladder.back();
        int L = last.size();

        vector<string> candidates;
        if (length_map.find(L) != length_map.end()) {
            candidates.insert(candidates.end(),
                              length_map[L].begin(),
                              length_map[L].end());
        }
        if (length_map.find(L+1) != length_map.end()) {
            candidates.insert(candidates.end(),
                              length_map[L+1].begin(),
                              length_map[L+1].end());
        }
        if (L > 0 && length_map.find(L-1) != length_map.end()) {
            candidates.insert(candidates.end(),
                              length_map[L-1].begin(),
                              length_map[L-1].end());
        }

        for (auto &w : candidates) {
            if (!visited.count(w) && is_adjacent(last, w)) {
                visited.insert(w);
                auto new_ladder = ladder;
                new_ladder.push_back(w);

                if (w == end_word) {
                    return new_ladder;
                }
                q.push(new_ladder);
            }
        }
    }

    return {};
}



void load_words(set<string> & word_list, const string& file_name) {
    ifstream fin(file_name);
    if (!fin.is_open()) {
        cerr << "Cannot open " << file_name << endl;
        return; 
    }
    string word;
    while (fin >> word) {
        word_list.insert(word);
    }
    fin.close();
}


void print_word_ladder(const vector<string> &ladder)
{
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
        return;
    }


    cout << "Word ladder found:";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << " " << ladder[i];
    }
    cout << " \n";  
}



void verify_word_ladder() {
   
    set<string> word_list;
    load_words(word_list, "words.txt");

    {
        auto ladder = generate_word_ladder("cat", "dog", word_list);
        cout << "cat -> dog: ";
        print_word_ladder(ladder);
    }

}

