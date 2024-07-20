#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// ��ӡ��ǰ֡״̬
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

// LRU ҳ���û��㷨
void LRU(const vector<int>& pages, int frameCount) {
    vector<int> frames(frameCount, -1);
    unordered_map<int, int> lastUsed;
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

        if (!found) { // ȱҳ
            pageFaults++;
            bool emptyFrame = false;
            for (int j = 0; j < frames.size(); ++j) {
                if (frames[j] == -1) {
                    frames[j] = page;
                    emptyFrame = true;
                    break;
                }
            }
            if (!emptyFrame) {
                pageReplacements++;
                int lruPage = pages.size(), replaceIndex = -1;
                for (int j = 0; j < frames.size(); j++) {
                    if (lastUsed[frames[j]] < lruPage) {
                        lruPage = lastUsed[frames[j]];
                        replaceIndex = j;
                    }
                }
                frames[replaceIndex] = page;
            }
        }
        lastUsed[page] = i;
        printFrames(frames);
    }

    cout << "LRU: Page Faults: " << pageFaults << ", Page Replacements: " << pageReplacements
        << ", Page Fault Rate: " << (double)pageFaults / pages.size() << endl;
}

int main() {
    vector<int> pages = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1 };
    int frameCount = 3;

    cout << "\nLRU Algorithm:" << endl;
    LRU(pages, frameCount);

    return 0;
}
