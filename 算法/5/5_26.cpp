/*#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 任务调度函数
int task_scheduling(vector<int>& tasks, int machines) {
    // 将任务按时间从大到小排序
    sort(tasks.rbegin(), tasks.rend());

    // 初始化一个最小堆，表示每台机器的当前任务时间总和
    priority_queue<int, vector<int>, greater<int>> min_heap;

    // 初始时每台机器的总任务时间为0
    for (int i = 0; i < machines; ++i) {
        min_heap.push(0);
    }

    // 分配任务
    for (int task : tasks) {
        // 取出当前总任务时间最短的机器
        int min_time = min_heap.top();
        min_heap.pop();
        // 将任务时间加到该机器的总任务时间上
        min_time += task;
        // 将更新后的总时间放回堆中
        min_heap.push(min_time);
    }

    // 堆中的最大值即为最早完成时间
    int result = 0;
    while (!min_heap.empty()) {
        result = max(result, min_heap.top());
        min_heap.pop();
    }

    return result;
}

int main() {
    // 读取输入
    int n, m;
    cin >> n >> m;
    vector<int> tasks(n);
    for (int i = 0; i < n; ++i) {
        cin >> tasks[i];
    }

    // 计算最早完成时间
    int result = task_scheduling(tasks, m);
    cout << result << endl;

    return 0;
}*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int best_time = INT_MAX; // 初始化最佳完成时间为无穷大
vector<int> best_schedule; // 初始化最佳调度方案为空列表

// 回溯函数
void backtrack(vector<int>& schedule, int next_task, vector<int>& machine_times, int n, int k, vector<int>& times) {
    if (next_task == n) { // 如果所有任务都已经分配完成
        int current_max_time = *max_element(machine_times.begin(), machine_times.end());
        if (current_max_time < best_time) { // 剪枝：如果当前机器已经超过了最小完成时间，则跳过
            best_time = current_max_time; // 更新最佳完成时间
            best_schedule = schedule; // 更新最佳调度方案
        }
        return;
    }

    for (int machine = 0; machine < k; ++machine) { // 遍历每台机器
        if (machine_times[machine] + times[next_task] >= best_time) { // 剪枝：如果当前机器已经超过了最小完成时间，则跳过该机器
            continue;
        }
        if (machine > 0 && machine_times[machine] == machine_times[machine - 1]) { // 剪枝：如果两台机器在分配同一个任务之后具有相同的完成时间，则跳过
            continue;
        }
        schedule[next_task] = machine; // 将下一个任务分配给当前机器
        machine_times[machine] += times[next_task]; // 更新当前机器的完成时间
        if (*max_element(machine_times.begin(), machine_times.end()) < best_time) { // 剪枝：如果当前机器已经超过了最小完成时间，则跳过
            backtrack(schedule, next_task + 1, machine_times, n, k, times); // 递归进行下一个任务的分配
        }
        machine_times[machine] -= times[next_task]; // 回溯：撤销当前任务的分配
    }
}

pair<int, vector<int>> schedule_tasks(int n, int k, vector<int>& times) {
    best_time = INT_MAX; // 初始化最佳完成时间为无穷大
    best_schedule.clear(); // 清空最佳调度方案

    vector<int> initial_schedule(n, 0); // 初始化任务分配方案
    vector<int> initial_machine_times(k, 0); // 初始化机器完成时间列表
    sort(times.begin(), times.end(), greater<int>()); // 对任务的完成时间进行排序，从大到小
    backtrack(initial_schedule, 0, initial_machine_times, n, k, times); // 调用回溯函数开始搜索最佳调度方案

    return { best_time, best_schedule }; // 返回最佳完成时间和调度方案
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> times(n);
    for (int i = 0; i < n; ++i) {
        cin >> times[i];
    }

    auto result = schedule_tasks(n, k, times);
    cout <<result.first << endl;
    return 0;
}
