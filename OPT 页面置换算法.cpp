#include <iostream>
#include <vector>
#include <unordered_map>
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

// OPT Ò³ÃæÖÃ»»Ëã·¨
void OPT(const vector<int>& pages, int frameCount) {
    vector<int> frames(frameCount, -1);
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
                    emptyFrame = true;
                    break;
                }
            }
            if (!emptyFrame) {
                pageReplacements++;
                unordered_map<int, int> futureUses;
                for (int j = 0; j < frames.size(); j++) {
                    futureUses[frames[j]] = pages.size();
                }
                for (int j = i + 1; j < pages.size(); j++) {
                    if (futureUses.find(pages[j]) != futureUses.end() && futureUses[pages[j]] == pages.size()) {
                        futureUses[pages[j]] = j;
                    }
                }
                int farthest = -1, replaceIndex = -1;
                for (int j = 0; j < frames.size(); j++) {
                    if (futureUses[frames[j]] > farthest) {
                        farthest = futureUses[frames[j]];
                        replaceIndex = j;
                    }
                }
                frames[replaceIndex] = page;
            }
        }
        printFrames(frames);
    }

    cout << "OPT: Page Faults: " << pageFaults << ", Page Replacements: " << pageReplacements
        << ", Page Fault Rate: " << (double)pageFaults / pages.size() << endl;
}

int main() {
    vector<int> pages = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1 };
    int frameCount = 3;

    cout << "OPT Algorithm:" << endl;
    OPT(pages, frameCount);

    return 0;
}
