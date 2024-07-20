#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Process {
    char name;  // ��������
    int arrival_time;  // ����ʱ��
    int burst_time;  // ����ʱ��
    int completion_time;  // ���ʱ��
    int turnaround_time;  // ��תʱ��
    double weighted_turnaround_time;  // ��Ȩ��תʱ��
};

// �����ʱ�����
void calculateTimes(std::vector<Process>& processes) {
    int current_time = 0;
    for (auto& p : processes) {
        current_time = std::max(current_time, p.arrival_time);
        p.completion_time = current_time + p.burst_time;
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.weighted_turnaround_time = (double)p.turnaround_time / p.burst_time;
        current_time += p.burst_time;
    }
}

// ��ʾ���
void displayResults(const std::vector<Process>& processes) {
    int total_turnaround_time = 0;
    double total_weighted_turnaround_time = 0.0;
    std::cout << "����\t����ʱ��\t����ʱ��\t���ʱ��\t��תʱ��\t��Ȩ��תʱ��\n";
    for (const auto& p : processes) {
        std::cout << p.name << "\t"
            << p.arrival_time << "\t\t"
            << p.burst_time << "\t\t"
            << p.completion_time << "\t\t"
            << p.turnaround_time << "\t\t"
            << std::fixed << std::setprecision(2) << p.weighted_turnaround_time << "\n";
        total_turnaround_time += p.turnaround_time;
        total_weighted_turnaround_time += p.weighted_turnaround_time;
    }
    std::cout << "ƽ����תʱ��: " << (double)total_turnaround_time / processes.size() << "\n";
    std::cout << "ƽ����Ȩ��תʱ��: " << total_weighted_turnaround_time / processes.size() << "\n";
}

// �����ȷ�������㷨
void fcfs(std::vector<Process> processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
        });
    calculateTimes(processes);
    std::cout << "�����ȷ������:\n";
    displayResults(processes);
}

// �����ҵ���ȵ����㷨
void sjf(std::vector<Process> processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
        });
    int current_time = 0;
    std::vector<Process> ready_queue;
    std::vector<Process> result;
    while (!processes.empty() || !ready_queue.empty()) {
        while (!processes.empty() && processes.front().arrival_time <= current_time) {
            ready_queue.push_back(processes.front());
            processes.erase(processes.begin());
        }
        if (!ready_queue.empty()) {
            std::sort(ready_queue.begin(), ready_queue.end(), [](const Process& a, const Process& b) {
                return a.burst_time < b.burst_time;
                });
            auto next_process = ready_queue.front();
            ready_queue.erase(ready_queue.begin());
            next_process.completion_time = current_time + next_process.burst_time;
            next_process.turnaround_time = next_process.completion_time - next_process.arrival_time;
            next_process.weighted_turnaround_time = (double)next_process.turnaround_time / next_process.burst_time;
            current_time += next_process.burst_time;
            result.push_back(next_process);
        }
        else {
            current_time = processes.front().arrival_time;
        }
    }
    std::cout << "�����ҵ���ȵ���:\n";
    displayResults(result);
}

int main() {
    std::vector<Process> processes = {
        {'A', 0, 4},
        {'B', 1, 3},
        {'C', 2, 5},
        {'D', 3, 2},
        {'E', 4, 4}
    };

    fcfs(processes);
    std::cout << "\n";
    sjf(processes);

    return 0;
}
