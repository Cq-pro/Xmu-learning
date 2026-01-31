#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5  // 假设最多有5个进程
#define MAX_RESOURCES 3  // 假设最多有3种资源

// 定义资源向量、需求矩阵、分配矩阵、和可用资源向量
int R[MAX_RESOURCES];                 // 资源总量
int A[MAX_PROCESSES][MAX_RESOURCES];   // 资源分配矩阵
int C[MAX_PROCESSES][MAX_RESOURCES];   // 最大需求矩阵
int N[MAX_PROCESSES][MAX_RESOURCES];   // 需求矩阵 = C - A
int V[MAX_RESOURCES];                  // 可用资源向量
int num_processes, num_resources;      // 进程数和资源种类数

void initialize() {
    printf("输入进程数量和资源种类数（空格分隔）: ");
    scanf("%d %d", &num_processes, &num_resources);

    printf("输入每种资源的总量: ");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &R[i]);
        V[i] = R[i];  // 初始化可用资源等于总量
    }

    printf("输入每个进程的最大需求矩阵 C:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &C[i][j]);
            A[i][j] = 0;                   // 初始分配为 0
            N[i][j] = C[i][j];              // 初始化需求矩阵 N
        }
    }
}

bool request_resources(int process_id, int request[]) {
    // 检查请求是否合法
    for (int i = 0; i < num_resources; i++) {
        if (request[i] > N[process_id][i]) {
            printf("进程%d 申请的资源超过了其最大需求。\n", process_id);
            return false;
        }
        if (request[i] > V[i]) {
            printf("进程%d 需要等待资源。\n", process_id);
            return false;
        }
    }

    // 试探性分配资源
    for (int i = 0; i < num_resources; i++) {
        V[i] -= request[i];
        A[process_id][i] += request[i];
        N[process_id][i] -= request[i];
    }

    // 检查系统安全性
    if (is_safe()) {
        printf("资源分配成功！\n");
        return true;
    } else {
        // 恢复资源分配
        for (int i = 0; i < num_resources; i++) {
            V[i] += request[i];
            A[process_id][i] -= request[i];
            N[process_id][i] += request[i];
        }
        printf("分配会导致不安全状态，已恢复原状态。\n");
        return false;
    }
}

bool is_safe() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safe_sequence[MAX_PROCESSES];
    int count = 0;

    for (int i = 0; i < num_resources; i++)
        work[i] = V[i];

    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < num_resources; j++) {
                    if (N[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < num_resources; j++)
                        work[j] += A[i][j];
                    safe_sequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("系统处于不安全状态！\n");
            return false;
        }
    }

    printf("系统处于安全状态，安全序列为：");
    for (int i = 0; i < num_processes; i++)
        printf("P%d ", safe_sequence[i]);
    printf("\n");
    return true;
}

int main() {
    initialize();
    while (true) {
        int process_id;
        int request[MAX_RESOURCES];

        printf("\n输入进程ID和申请资源数量: ");
        scanf("%d", &process_id);
        for (int i = 0; i < num_resources; i++)
            scanf("%d", &request[i]);

        if (request_resources(process_id, request)) {
            printf("当前资源分配矩阵 A:\n");
            for (int i = 0; i < num_processes; i++) {
                for (int j = 0; j < num_resources; j++) {
                    printf("%d ", A[i][j]);
                }
                printf("\n");
            }

            printf("当前可用资源向量 V: ");
            for (int i = 0; i < num_resources; i++)
                printf("%d ", V[i]);
            printf("\n");
        }

        printf("按空格键继续下一次资源申请...\n");
        while (getchar() != ' ');  // 等待空格输入
    }
    return 0;
}