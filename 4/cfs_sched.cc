//
//  cfs_sched.cc
//  Program04
//
//  Copyright © 2018 Ye Wang and Faustine Yiu All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "llrb_multimap.h"

void errorHandle(int argc, char *argv[], std::ifstream& File, int& FLAG) {
    if (argc != 2) {
        // handling errors caused by number of arguments
        std::cerr << "Usage: ./cfs_sched <task_file.dat>" << std::endl;
        FLAG = 1;
        return;
    }
    File.open(argv[1]);
    // handling errors caused by wrong file name or size number
    if (!File) {
        std::cerr << "Error: cannot open file " << argv[1] << std::endl;
        FLAG = 1;
        return;
    }
}

class Task {
    // set every task as an object
 private:
    char identifier;
    int startTime;
    int duration;
    int vruntime = 0;
    int rruntime = 0;

 public:
    Task(char id, int stime, int dur) {
        // constructor, only be called in loadVector
        identifier = id;
        startTime = stime;
        duration = dur;
    }

    int getDuration() {return duration;}
    char getID() {return identifier;}
    int getStarttime() {return startTime;}
    int getVrt() {return vruntime;}
    int getRrt() {return rruntime;}

    void setVruntime(int i) {vruntime = i;}
    // i is min_vruntime
    void increVruntime() {vruntime++;}
    // vrt will increase by one after each run
    void increRruntime() {rruntime++;}
    // rrt will increase by one after each run
};

class Scheduler {
// schedule object, store current task, tick, #task, min_vt
 private:
    int min_vruntime = 0;
    // set to 0 in the very beginning
    int ticks = 0;
    int numberTasks = 0;
    Task* currentTask = nullptr;
 public:
    int getminvt() {return min_vruntime;}
    int gettick() {return ticks;}
    Task* getCurTask() {return currentTask;}
    int getNumTask() {return numberTasks;}

    void setMinvt(int i) {
    // i = next schedulable task's vt
        min_vruntime = i;
    }
    void setCurTask(Task* newTask) {currentTask = newTask;}

    void increTask() {numberTasks++;}
    void increTick() {ticks++;}
    void increNumTask() {numberTasks++;}
    void decreNumTask() {numberTasks--;}
};

bool taskLess(Task *a, Task *b) {
    /*
     bool operator< rule:
     1st Priority: starting time
     2nd Priority: ID character
     */
    if (a->getStarttime() < b->getStarttime()) {
        return true;
    } else if (a->getStarttime() == b->getStarttime()
               && a->getID() < b->getID()) {
        return true;
    }
    return false;
}

void loadTask(std::vector<Task*> &taskVect, std::ifstream& File) {
    // load the file, sort the vector
    char name;
    int st, lt;

    std::string input;
    while (getline(File, input)) {
        std::stringstream line;
        line << input;
        line >> name >> st >> lt;
        Task* n = new Task(name, st, lt);
        taskVect.push_back(n);
    }
    std::sort(taskVect.begin(), taskVect.end(), taskLess);
}

bool isComplete(Task* n) {
    // if task is completed
    if (n->getDuration() == n->getRrt())
        return true;
    return false;
}

void removeVector(std::vector<Task*> &vect, char n) {
    // if launched, remove from the vector
    for (int i = 0; i < static_cast<int>(vect.size()); i++) {
        if (vect[i]->getID() == n) {
            vect.erase(vect.begin()+i);
            return;
        }
    }
}

void CFSloop(std::vector<Task*> &taskVect) {
    Scheduler CFSschedule;
    LLRB_multimap<int, Task*> scheduleMap;

    std::vector<char> idVect;
    /*
     launched task's ID will be stored in this vector,
     it will be easy to remove from the taskVect afterwards
     */
    int comFLAG = 0;  // test task is completed or not
    int vecSize = static_cast<int>(taskVect.size());

    // main loop starts here
    while (taskVect.size() != 0 || scheduleMap.Size() != 0
           || comFLAG != vecSize) {
    /*
     loop keep running if:
     1. there are tasks need to be launched
     2. timeline is not empty
     3. there are incompleted tasks
     */
        for (auto i : taskVect) {
        // are there any tasks should be launched at current tick
            if (i->getStarttime() == CFSschedule.gettick()) {
                idVect.push_back(i->getID());
                // store the ID
                i->setVruntime(CFSschedule.getminvt());
                // task's vt = min_vt
                scheduleMap.Insert(i->getVrt(), i);
                // add to the timeline
                CFSschedule.increTask();
            }
        }
        for (auto i : idVect) {
            // remove if launched
            removeVector(taskVect, i);
        }

        Task* curTask = CFSschedule.getCurTask();
        /*
         if need to change the task, if does,
         add back to the timeline, then there
         will be nocurrent task
         */
        if (curTask && curTask->getVrt() > CFSschedule.getminvt()) {
            scheduleMap.Insert(curTask->getVrt(), curTask);
            CFSschedule.setCurTask(nullptr);
        }

        curTask = CFSschedule.getCurTask();
        /*
         find the current task, if it doesn't have it
         and there are task in the timeline, get the
         task with the smallest vt
         */
        if (!curTask && scheduleMap.Size() > 0) {
            CFSschedule.setCurTask(scheduleMap.Get(scheduleMap.Min()));
            scheduleMap.Remove(scheduleMap.Min());
            if (scheduleMap.Size() > 0) {
            /*
             check after remove, are there any tasks
             left in the timeline. If there is, set min_vt to
             the vt of that next task.
             */
                CFSschedule.setMinvt(scheduleMap.Min());
            }
        }

        if (CFSschedule.getCurTask()) {
        // run the same task as in the last loop
            CFSschedule.getCurTask()->increVruntime();
            CFSschedule.getCurTask()->increRruntime();
        }

        // print the scheduling status
        std::cout <<  CFSschedule.gettick() << " ["
        << CFSschedule.getNumTask() << "]: ";

        if (CFSschedule.getNumTask() == 0) {
        // no tasks are running
            std::cout << "_";
        } else {
            std::cout << CFSschedule.getCurTask()->getID();
            if (isComplete(CFSschedule.getCurTask())) {
                // check if completed
                comFLAG++;
                // completed task ++
                std::cout << "*";
                CFSschedule.setCurTask(nullptr);
                // there will be no current task
                CFSschedule.decreNumTask();
                // number of task decreases by 1
            }
        }
        std::cout << std::endl;
        CFSschedule.increTick();
        // tick++
    }
}

int main(int argc, char *argv[]) {
    int FLAG = 0;
    std::ifstream datFile;
    errorHandle(argc, argv, datFile, FLAG);
    if (FLAG == 1) {
        // if there is an error, no need to proceed
        return 1;
    }
    std::vector<Task*> taskVect;
    loadTask(taskVect, datFile);
    // store the input to a vector
    datFile.close();

    CFSloop(taskVect);

    return 0;
}
