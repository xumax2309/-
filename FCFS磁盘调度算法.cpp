#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void fcfs(const vector<int>& requests, int start) {
    int total_distance = 0;
    int current_position = start;
    vector<int> access_sequence;

    for (int request : requests) {
        int distance = abs(request - current_position);
        total_distance += distance;
        access_sequence.push_back(request);
        current_position = request;
    }

    double average_distance = static_cast<double>(total_distance) / requests.size();

    cout << "FCFS磁道访问顺序: ";
    for (int track : access_sequence) {
        cout << track << " ";
    }
    cout << endl;

    cout << "FCFS总寻道长度: " << total_distance << endl;
    cout << "FCFS平均寻道长度: " << average_distance << endl;
}

int main() {
    vector<int> requests = { 55, 58, 39, 18, 90, 160, 150, 38, 184 };
    int start = 100;

    fcfs(requests, start);

    return 0;
}
