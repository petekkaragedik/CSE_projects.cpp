//Petek Karagedik 34042
#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    int task_id;
    int priority;
    std::string location;
    std::string category;

    Task(int id, int prio, std::string loc = "", std::string cat = "")
        : task_id(id), priority(prio), location(loc), category(cat) {}
};

#endif 