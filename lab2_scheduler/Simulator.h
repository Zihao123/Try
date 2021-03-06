#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include "Process.h"
#include "Event.h"
#include "utility.h"
#include "scheduler.h"
using namespace std;

// some constant
#define CREATED_TO_READY 1
#define READY_TO_RUNNG 2
#define RUNNG_TO_BLOCK 3
#define BLOCK_TO_READY 4
#define RUNNG_TO_READY 5
#define DONE 0


class Simulator {
    public:
        // Member
        int current_AT;
        int current_TC;
        int current_CB;
        int current_IO;
        int line_counter;
        priority_queue<Event, vector<Event>, EventBigger> event_queue; 
        vector<Process> process_list;
        vector<int> randval;
        vector<Process*> ready_queue;
        vector<Process*> expired_queue;
        int total_rand;
        int ofs;
        int event_count;
        bool verbose;
        Scheduler* sched;
        string sched_type;
        int quantum = 10000;
        int io_flag; // whether it can get in I/O, only one can be in I/O, like semophore
        int last_io_busy;
        int sim_time;
        int io_sum;
        int priority_num;
        double cpu_util;
        double io_util;
        double avg_TT;
        double avg_CW;
        double throughput;

        // Constructor
        Simulator(const char* randomfilename);

        // Method
        int myrandom(int burst);
        void Init_Process(const char* filename);
        void put_event(int _curr_time, int _PID, int _exec_time, string _oldstate, string _newstate);
        int Init_Scheduler(string& schedname, const bool& _verbose);// 1 means successfully initialize the scheduler.
        void handle_event(Event& event);
        void run_action();
        void run_all();
        void print_summary();
        void gather_info();
};

#endif