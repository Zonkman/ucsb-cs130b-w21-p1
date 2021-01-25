#include <iostream>
#include <vector>

// "I Wrote This" by Alex Lancaster (6706998)

class Box {
    public:
        int marbles;
	int childCount;
	int targetSubTotal;
	int currentSubTotal;
	std::vector<int> children;
    private:
};

// get some extra data for my solution.
// the extra data is how many marbles are supposed to be in a subtree,
// and how many are in it now.
// O(n)
void CountAndSetTargets(Box& b, Box* boxList) {
    b.targetSubTotal = 1;
    b.currentSubTotal = b.marbles;

    for (int j = 0; j < b.children.size(); ++j) {
        Box& c = boxList[b.children[j]];
	CountAndSetTargets(c, boxList);
        b.targetSubTotal += c.targetSubTotal;
	b.currentSubTotal += c.currentSubTotal;
    }
}

//O(n)
void MoveUp(Box& curr, Box& parent, Box* boxList, int& moveCounter) {
    for (int i = 0; i < curr.children.size(); ++i) {
        Box& child = boxList[curr.children[i]];
	MoveUp(child, curr, boxList, moveCounter);
    }

    int excess = curr.currentSubTotal - curr.targetSubTotal;
    if (excess > 0) {
        curr.marbles -= excess; // these never become negative
	curr.currentSubTotal -= excess;
	parent.marbles += excess;
	moveCounter += excess;
    }
}

//O(n)
void MoveDown(Box& curr, Box* boxList, int& moveCounter) {
    for (int i = 0; i < curr.children.size(); ++i) {
        Box& child = boxList[curr.children[i]];
	int wanted = child.targetSubTotal - child.currentSubTotal;
	if (wanted > 0) {
	    curr.marbles -= wanted; // these never become negative
	    child.marbles += wanted;
	    child.currentSubTotal += wanted;
	    moveCounter += wanted;
	}

	MoveDown(child, boxList, moveCounter);
    }

}

//O(n)!!!
void Redistribute(Box* boxList, int& root, int& moveCounter) {
    Box& b = boxList[root];

    //all the excess marbles move to the root
    for (int i = 0; i < b.children.size(); ++i) {
        Box& child = boxList[b.children[i]];
        MoveUp(child, b, boxList, moveCounter);
    }

    MoveDown(b, boxList, moveCounter);
}

bool Solve() {
    int boxCount; std::cin >> boxCount;
    if (boxCount == 0) { return true; }

    int nothing;
    Box boxList[boxCount];
    bool notRootList[boxCount] = {false};
    for (int i = 0; i < boxCount; ++i) {
        boxList[i] = Box();
	Box& b = boxList[i];
	std::cin >> nothing; // burn vertex number. we don't need it.
	std::cin >> b.marbles;
	std::cin >> b.childCount;
	for (int j = 0; j < b.childCount; ++j) {
	    int childIdx; std::cin >> childIdx;
	    b.children.push_back(childIdx - 1);
	    notRootList[childIdx] = true; // child cannot be the root.
	}
    }

    int root = -1;
    for (int i = 0; i < boxCount; ++i) {
        if (!notRootList[i]) { root = i; break; }
    }

    CountAndSetTargets(boxList[root], boxList);

    int moveCounter = 0;
    Redistribute(boxList, root, moveCounter);

    std::cout << moveCounter << std::endl;

    return false;
}

int main(int argc, char** argv) {
    
    //std::ifstream in("test.txt");
    //std::streambuf* cinbuf = std::cin.rdbuf();
    //std::cin.rdbuf(in.rdbuf());

    for (int i = 0; i < 10; ++i) {
        bool end = Solve();
	if (end) { break; }
    }

    //std::cin.rdbuf(cinbuf);

    return 0;
}
