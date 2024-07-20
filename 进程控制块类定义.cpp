#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Process {
public:
    string name;
    int arrival_time;
    int service_time;
    int finish_time;
    int turnaround_time;
    double weighted_turnaround_time;

    Process(string n, int a, int s) : name(n), arrival_time(a), service_time(s), finish_time(0), turnaround_time(0), weighted_turnaround_time(0.0) {}

    void calculate_times(int current_time) {
        finish_time = current_time;
        turnaround_time = finish_time - arrival_time;
        weighted_turnaround_time = (double)turnaround_time / service_time;
    }
};

void print_results(vector<Process>& processes) {
    double total_turnaround_time = 0.0;
    double total_weighted_turnaround_time = 0.0;

    cout << "进程\t到达时间\t服务时间\t完成时间\t周转时间\t带权周转时间" << endl;
    for (const auto& process : processes) {
        cout << process.name << "\t" << process.arrival_time << "\t\t" << process.service_time << "\t\t"
            << process.finish_time << "\t\t" << process.turnaround_time << "\t\t"
            << fixed << setprecision(2) << process.weighted_turnaround_time << endl;
        total_turnaround_time += process.turnaround_time;
        total_weighted_turnaround_time += process.weighted_turnaround_time;
    }

    cout << "平均周转时间: " << total_turnaround_time / processes.size() << endl;
    cout << "平均带权周转时间: " << total_weighted_turnaround_time / processes.size() << endl;
}

void fcfs(vector<Process> processes) {
    int current_time = 0;

    for (auto& process : processes) {
        if (current_time < process.arrival_time) {
            current_time = process.arrival_time;
        }
        current_time += process.service_time;
        process.calculate_times(current_time);
    }

    cout << "\n先来先服务(FCFS)调度:" << endl;
    print_results(processes);
}

void sjf(vector<Process> processes) {
    int current_time = 0;
    vector<Process> completed;

    while (!processes.empty()) {
        auto it = min_element(processes.begin(), processes.end(), [&](Process& a, Process& b) {
            return a.service_time < b.service_time && a.arrival_time <= current_time;
            });

        if (it == processes.end()) {
            current_time++;
            continue;
        }

        current_time = max(current_time, it->arrival_time) + it->service_time;
        it->calculate_times(current_time);
        completed.push_back(*it);
        processes.erase(it);
    }

    cout << "\n最短作业优先(SJF)调度:" << endl;
    print_results(completed);
}

int main() {
    vector<Process> processes = {
        Process("A", 0, 4),
        Process("B", 1, 3),
        Process("C", 2, 5),
        Process("D", 3, 2),
        Process("E", 4, 4)
    };

    fcfs(processes);
    sjf(processes);

    return 0;
}

