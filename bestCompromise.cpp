#include <iostream>
#include <cstdio>

// "I Wrote This" by Alex Lancaster (6706998)

void Solve() {
    int peopleCount, beliefsCount;
    std::cin >> peopleCount >> beliefsCount;
    
    int beliefsTotal[beliefsCount] = {0};

    char* beliefCurr = new char[beliefsCount + 1];
    beliefCurr[beliefsCount] = '\0';
    for (int i = 0; i < peopleCount; ++i) {
	std::cin >> beliefCurr;
	for (int j = 0; j < beliefsCount; ++j) {
	    if (beliefCurr[j] == '1') { ++beliefsTotal[j]; }
	}
    }


    // the greedy approach is to have the most agreements for each character by itself.
    // note that no characters affect another character.
    // that is why the whole string has the minimum hamming distances
    // exactly when each character has the least hamming distances.
    
    int majority = (peopleCount + 1) / 2;

    char* compString = new char[beliefsCount + 1];
    compString[beliefsCount] = '\0';
    for (int j = 0; j < beliefsCount; ++j) {
        compString[j] = (beliefsTotal[j] >= majority)?('1'):('0');
    }

    std::cout << compString << std::endl;
    
    delete[] compString;
    delete[] beliefCurr;
}

int main(int argc, char** argv) {
    int testCount;
    std::cin >> testCount;

    for (int i = 0; i < testCount; ++i) {
        Solve();
    }

    return 0;
}
