#include "ladder.h"
using namespace std;

int main() {
    // Load dictionary
    set<string> word_list;
    load_words(word_list, "words.txt");

    // Possibly run some tests
    // verify_word_ladder();

    cout << "Enter start word: ";
    string start;
    cin >> start;
    cout << "Enter end word: ";
    string end;
    cin >> end;

    // Generate ladder
    vector<string> ladder = generate_word_ladder(start, end, word_list);

    // Print
    cout << "Word ladder: ";
    print_word_ladder(ladder);

    return 0;
}
