#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void sstf(const vector<int>& requests, int start) {
    int total_distance = 0;
    int current_position = start;
    vector<int> access_sequence;
    vector<int> pending_requests = requests;

    while (!pending_requests.empty()) {
        auto closest_request = min_element(pending_requests.begin(), pending_requests.end(),
            [current_position](int a, int b) {
                return abs(a - current_position) < abs(b - current_position);
            });
        int distance = abs(*closest_request - current_position);
        total_distance += distance;
        access_sequence.push_back(*closest_request);
        current_position = *closest_request;
        pending_requests.erase(closest_request);
    }

    double average_distance = static_cast<double>(total_distance) / requests.size();

    cout << "SSTF磁道访问顺序: ";
    for (int track : access_sequence) {
        cout << track << " ";
    }
    cout << endl;

    cout << "SSTF总寻道长度: " << total_distance << endl;
    cout << "SSTF平均寻道长度: " << average_distance << endl;
}

int main() {
    vector<int> requests = { 55, 58, 39, 18, 90, 160, 150, 38, 184 };
    int start = 100;

    sstf(requests, start);

    return 0;
}
