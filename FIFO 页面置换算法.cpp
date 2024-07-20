#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// ´òÓ¡µ±Ç°Ö¡×´Ì¬
void printFrames(const vector<int>& frames) {
    for (int frame : frames) {
        if (frame == -1) {
            cout << " ";
        }
        else {
            cout << frame;
        }
        cout << " ";
    }
    cout << endl;
}

// FIFO Ò³ÃæÖÃ»»Ëã·¨
void FIFO(const vector<int>& pages, int frameCount) {
    vector<int> frames(frameCount, -1);
    queue<int> fifoQueue;
    int pageFaults = 0;
    int pageReplacements = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        bool found = false;
        for (int j = 0; j < frames.size(); ++j) {
            if (frames[j] == page) {
                found = true;
                break;
            }
        }

        if (!found) { // È±Ò³
            pageFaults++;
            bool emptyFrame = false;
            for (int j = 0; j < frames.size(); ++j) {
                if (frames[j] == -1) {
                    frames[j] = page;
                    fifoQueue.push(page);
                    emptyFrame = true;
                    break;
                }
            }
            if (!emptyFrame) {
                pageReplacements++;
                int toReplace = fifoQueue.front();
                fifoQueue.pop();
                for (int j = 0; j < frames.size(); ++j) {
                    if (frames[j] == toReplace) {
                        frames[j] = page;
                        break;
                    }
                }
                fifoQueue.push(page);
            }
        }
        printFrames(frames);
    }

    cout << "FIFO: Page Faults: " << pageFaults << ", Page Replacements: " << pageReplacements
        << ", Page Fault Rate: " << (double)pageFaults / pages.size() << endl;
}

int main() {
    vector<int> pages = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1 };
    int frameCount = 3;

    cout << "\nFIFO Algorithm:" << endl;
    FIFO(pages, frameCount);

    return 0;
}
