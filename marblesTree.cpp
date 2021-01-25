#include <iostream>
#include <vector>
#include <queue>

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

// move the cheapest marbles "up" to the parent of this node.
// the queue order always finds the lower cost marbles first.
// O(n)
void Leech(Box& b, Box* boxList, int& moveCounter) {
    int marblesToErase = b.currentSubTotal - b.targetSubTotal;
    std::queue<Box*> boxQueue;
    std::queue<int> costQueue;
    boxQueue.push(&b);
    costQueue.push(1);

    while (!boxQueue.empty()) {
        Box& c = (*(boxQueue.front())); boxQueue.pop();
	int cost = costQueue.front(); costQueue.pop();

        if (c.marbles > c.targetSubTotal) {
	    int toRemove = c.marbles - c.targetSubTotal;
            c.marbles -= toRemove;
	    moveCounter += toRemove*cost;
	    marblesToErase -= toRemove;
	    if (marblesToErase < 0) {
	        c.marbles += -marblesToErase;
		moveCounter -= -marblesToErase*cost;
		marblesToErase = 0;
	    }
	    if (marblesToErase == 0) {
	        break;
	    }
        }

        for (int i = 0; i < c.children.size(); ++i) {
            boxQueue.push(&boxList[c.children[i]]);
            costQueue.push(cost + 1);
        }
    }
}

// O(n^2). Maybe there is a way to do better.
void Redistribute(Box& b, Box* boxList, int& moveCounter) {
    std::vector<int> underfunded;
    std::vector<int> overfunded;

    //find out which subtrees have too few or too many marbles.
    for (int i = 0; i < b.children.size(); ++i) {
        Box& c = boxList[b.children[i]];
        if (c.targetSubTotal < c.currentSubTotal) { overfunded.push_back(i); }
        else if (c.targetSubTotal > c.currentSubTotal) { underfunded.push_back(i); }
    }

    // somehow, find the cheapest marbles and "bring them to this root."
    for (int i = 0; i < overfunded.size(); ++i) {
        Leech(boxList[b.children[overfunded[i]]], boxList, moveCounter);
    }

    // "place them into" the trees that are below their target.
    for (int i = 0; i < underfunded.size(); ++i) {
        Box& c = boxList[b.children[underfunded[i]]];
	int add = c.targetSubTotal - c.currentSubTotal;
	moveCounter += add;
        c.marbles += add;
	c.currentSubTotal = c.targetSubTotal;
    }

    // b.marbles = 1; 

    for (int i = 0; i < b.children.size(); ++i) {
	CountAndSetTargets(boxList[b.children[i]], boxList);
        Redistribute(boxList[b.children[i]], boxList, moveCounter);
    }
}

bool Solve() {
    int boxCount; std::cin >> boxCount;
    if (boxCount == 0) { return true; }

    int nothing;
    Box boxList[boxCount];
    for (int i = 0; i < boxCount; ++i) {
        boxList[i] = Box();
	Box& b = boxList[i];
	std::cin >> nothing; // burn vertex number. we don't need it.
	std::cin >> b.marbles;
	std::cin >> b.childCount;
	for (int j = 0; j < b.childCount; ++j) {
	    int childIdx; std::cin >> childIdx;
	    b.children.push_back(childIdx - 1);
	}
    }

    CountAndSetTargets(boxList[0], boxList);

    /*
    std::cout << "----------TEST A---------" << std::endl;

    for (int i = 0; i < boxCount; ++i) {
        std::cout << "Box #" << i << std::endl;
	std::cout << "\t Should have " << boxList[i].targetSubTotal << " marbles in its subtree;" << std::endl;
	std::cout << "\t Right now there are " << boxList[i].currentSubTotal << "." << std::endl;
    }

    std::cout << "----------------------" << std::endl;
    */

    int moveCounter = 0;
    Redistribute(boxList[0], boxList, moveCounter);

    std::cout << moveCounter << std::endl;

    return false;
}

int main(int argc, char** argv) {
    
    //std::ifstream in("test.txt");
    //std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    //std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    for (int i = 0; i < 10; ++i) {
        bool end = Solve();
	if (end) { break; }
    }

    //std::cin.rdbuf(cinbuf);

    return 0;
}
