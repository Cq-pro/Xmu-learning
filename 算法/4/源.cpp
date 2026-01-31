#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
    int time; // 完成任务所需时间
    int deadline; // 截止时间
    int penalty; // 误时惩罚
};

bool compareTasks(const Task& task1, const Task& task2) {
    return task1.deadline < task2.deadline;
}

int minPenalty(vector<Task>& tasks) {
    sort(tasks.begin(), tasks.end(), compareTasks); // 按照截止时间从小到大排序

    int currentTime = 0;
    int totalPenalty = 0;

    for (int i = 0; i < tasks.size(); ++i) {
        currentTime += tasks[i].time; // 完成当前任务
        totalPenalty += max(0, currentTime - tasks[i].deadline) * tasks[i].penalty; // 计算当前任务的误时惩罚
    }

    return totalPenalty;
}

int main() {
    int n;
    cin >> n;

    vector<Task> tasks(n);
    for (int i = 0; i < n; ++i) {
        int time, deadline, penalty;
        cin >> time >> deadline >> penalty;
        tasks[i] = { time, deadline, penalty };
    }

    cout << minPenalty(tasks) << endl;

    return 0;
}
