#include "ladder.h"
using namespace std;

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    cout << "Enter start word: ";
    string start;
    cin >> start;
    cout << "Enter end word: ";
    string end;
    cin >> end;

    vector<string> ladder = generate_word_ladder(start, end, word_list);

    print_word_ladder(ladder);

    return 0;
}
