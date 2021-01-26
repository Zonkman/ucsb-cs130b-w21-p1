#include <iostream>
#include <vector>
#include <queue>

// "I Wrote This" by Alex Lancaster (6706998)

void Solve() {
    int soldierCount; std::cin >> soldierCount;
    int enemyPairCount; std::cin >> enemyPairCount;

    std::vector<int> adjacency[soldierCount];

    for (int i = 0; i < enemyPairCount; ++i) {
        int enemyA, enemyB;
	std::cin >> enemyA >> enemyB;
	--enemyA; --enemyB;
	adjacency[enemyA].push_back(enemyB);
	adjacency[enemyB].push_back(enemyA);
    }

    // there are always at most two groups (that i call red and blue, and denote by color).
    // why?
    // because every solider has at most three enemies!
    // assume every solider has the maximum of three enemies.
    // at least two enemies of a solider would always be the same color.
    // if the soldier is the other color, then only one enemy will be the same color as the soldier.
    // this is the property we want to have for each group.

    // so we put each soldier in the red group at first.
    // they keep track of how many enemies are red.
    // if 2 or 3 enemies are red, this soldier turns blue.
    // if 0 or 1 enemies are red, this solider turns red.
    // repeat until the property is satisfied for all soldiers.
    
    // this process will eventually stop after O(n) group swaps.
    // why?
    // let every edge defining the enemy relationship have the "same" state 
    // if the two vertices are the same group. 
    // at first, every edge is in the "same" state.
    // every time a solider swaps group, at least two "same" edges stop being "same".
    // but at most one edge that wasn't "same" can become "same".
    // so the total number of "same" edges decreases.
    // there are only 3n/2 edges.

    // special: if everyone remains red, there is only one group. don't print the blue group.
    
    bool red[soldierCount];
    bool isInQueue[soldierCount];
    for (int i = 0; i < soldierCount; ++i) {
        red[i] = true; isInQueue[i] = true;
    }
    bool noChanges = true;
    
    std::queue<int> dirty;
    for (int i = 0; i < soldierCount; ++i) { dirty.push(i); }

    while (!dirty.empty()) {
        int curr = dirty.front(); dirty.pop();
        isInQueue[curr] = false;
        int enemiesSameCount = 0;

        for (int i = 0; i < adjacency[curr].size(); ++i) {
            int enemy = adjacency[curr][i];
            if (red[enemy] == red[curr]) { ++enemiesSameCount; }
        }

        bool thisChanged = false;

        if (enemiesSameCount >= 2) {
            if (red[curr]) { thisChanged = true; }
            red[curr] = !red[curr];
        }

        if (thisChanged) {
            noChanges = false;
            for (int i = 0; i < adjacency[curr].size(); ++i) {
                int enemy = adjacency[curr][i];
                if (!isInQueue[enemy]) {
                    dirty.push(enemy);
                    isInQueue[enemy] = true;
                }
            }
        }
    }

    if (noChanges) {
        std::cout << "1" << std::endl;
	for (int i = 0; i < soldierCount; ++i) { 
	    std::cout << i; 
            if (i != soldierCount - 1) { std::cout << " "; }
	}
	std::cout << std::endl;
	return;
    }

    std::cout << "2" << std::endl;
    std::vector<int> redPrintStore;
    std::vector<int> bluePrintStore;
    for (int i = 0; i < soldierCount; ++i) {
        if (red[i]) { redPrintStore.push_back(i+1); }
	else { bluePrintStore.push_back(i+1); }
    } 
     
    for (int i = 0; i < redPrintStore.size(); ++i) {
        std::cout << redPrintStore[i];
	if (i != redPrintStore.size() - 1) {std::cout << " "; }
    }
    std::cout << std::endl;

    for (int i = 0; i < bluePrintStore.size(); ++i) {
        std::cout << bluePrintStore[i];
	if (i != bluePrintStore.size() - 1) {std::cout << " "; }
    }
    std::cout << std::endl;
    
}

int main(int argc, char** argv) {
    
    //std::ifstream in("test.txt");
    //std::streambuf* cinbuf = std::cin.rdbuf();
    //std::cin.rdbuf(in.rdbuf());

    Solve();

    //std::cin.rdbuf(cinbuf);

    return 0;
}
