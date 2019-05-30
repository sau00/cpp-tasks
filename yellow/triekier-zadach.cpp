#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus
{
    NEW,         // новая
    IN_PROGRESS, // в разработке
    TESTING,     // на тестировании
    DONE         // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

TasksInfo operator+(TasksInfo lhs, TasksInfo rhs)
{
    TasksInfo res;
    vector<TaskStatus> ts{TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE};

    for (auto &tt : ts)
    {
        res[tt] = lhs[tt] + rhs[tt];
    }

    return res;
}

class TeamTasks
{
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const
    {
        return tasks.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person)
    {
        tasks[person][TaskStatus::NEW]++;
    }

    int GetTaskCount(const string &person, const int &task_count) const
    {
        TasksInfo the_tasks = GetPersonTasksInfo(person);
        int counter = 0;
        for (auto &v : ts) {
            counter += the_tasks[v];
        }

        if (counter < task_count) {
            return counter;
        }

        return task_count;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count)
    {
        // Массив с исходными таскаи, от которого мы можем только отнимать
        TasksInfo initial_tasks = tasks[person];
        TasksInfo modified_tasks;
        TasksInfo untouched_tasks;
        task_count = GetTaskCount(person, task_count);

        for (auto &tt : ts)
        {
            if (tt != TaskStatus::DONE) {
                for (int i = 0; i < tasks[person][tt]; ++i) {
                    if (task_count > 0) {
                        initial_tasks[tt]--;
                        modified_tasks[get_next_task_status(tt)]++;
                        task_count--;
                    }
                }
            }
        }

        for (auto &&tt : ts) {
            if (initial_tasks[tt] > 0 && tt != TaskStatus::DONE) {
                untouched_tasks[tt] = initial_tasks[tt];
            }
        }

        tasks[person] = modified_tasks + initial_tasks;

        return make_tuple(modified_tasks, untouched_tasks);
    }

private:
    map<string, TasksInfo> tasks;
    vector<TaskStatus> ts{TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE};

    TaskStatus get_next_task_status(TaskStatus c)
    {
        if (c == TaskStatus::NEW) {
            return TaskStatus::IN_PROGRESS;
        }

        if (c == TaskStatus::IN_PROGRESS) {
            return TaskStatus::TESTING;
        }

        return TaskStatus::DONE;
    }
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info)
{
    cout << tasks_info[TaskStatus::NEW] << " new tasks"
         << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
         << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
         << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main()
{
    TeamTasks tasks;
    for (int i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Alice");
    }
    cout << "Alice tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    for (int i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Alice");
    }
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    // cout << "Updated Alice's tasks: ";
    // PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    // PrintTasksInfo(updated_tasks);
    // cout << "Untouched Alice's tasks: ";
    // PrintTasksInfo(untouched_tasks);

    // tie(updated_tasks, untouched_tasks) =
    //     tasks.PerformPersonTasks("Ivan", 2);
    // cout << "Updated Ivan's tasks: ";
    // PrintTasksInfo(updated_tasks);
    // cout << "Untouched Ivan's tasks: ";
    // PrintTasksInfo(untouched_tasks);

    return 0;
}