#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Process { //struct to create a process
    int processID;
    int arrivalTime;
    int burstDuration;
    int priority;
};
void FCFS(std::vector<Process>& processes) {// first come first serve method
    float totalTurnaroundTime = 0; // datea needed for calcs
    float totalWaitingTime = 0;
    int currentTime = 0;

    for (const auto& process : processes) { // for every process in the processes vector
        totalTurnaroundTime += (currentTime + process.burstDuration - process.arrivalTime);// calc total urnaround
        totalWaitingTime += (currentTime - process.arrivalTime); // cal wait time
        currentTime += process.burstDuration; //update time
    }

    float avgTurnaroundTime = totalTurnaroundTime / processes.size();// calculate values for output
    float avgWaitingTime = totalWaitingTime / processes.size();
    float throughput = processes.size() / static_cast<float>(currentTime);

    std::cout << "--- FCFS ---" << std::endl; // print output
    std::cout << "Average Turnaround Time: " << avgTurnaroundTime << std::endl;
    std::cout << "Average Waiting Time: " << avgWaitingTime << std::endl;
    std::cout << "Throughput: " << throughput << std::endl;
    std::cout << std::endl;
}

void SJF(std::vector<Process>& processes) {//shortest job first method
    float totalTurnaroundTime = 0;
    float totalWaitingTime = 0;
    int currentTime = 0;

    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.burstDuration < b.burstDuration;
    });// sort processes shortest to longest

    for (const auto& process : processes) { //calculate values for every process
        totalTurnaroundTime += (currentTime + process.burstDuration - process.arrivalTime);
        totalWaitingTime += (currentTime - process.arrivalTime);
        currentTime += process.burstDuration;
    }

    float avgTurnaroundTime = totalTurnaroundTime / processes.size(); // calc values for outpt
    float avgWaitingTime = totalWaitingTime / processes.size();
    float throughput = processes.size() / static_cast<float>(currentTime);

    std::cout << "--- SJF ---" << std::endl; // print output
    std::cout << "Average Turnaround Time: " << avgTurnaroundTime << std::endl;
    std::cout << "Average Waiting Time: " << avgWaitingTime << std::endl;
    std::cout << "Throughput: " << throughput << std::endl;
    std::cout << std::endl;
}

void PriorityScheduling(std::vector<Process>& processes) {// priority algorithm
    float totalTurnaroundTime = 0;
    float totalWaitingTime = 0;
    int currentTime = 0;

    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority < b.priority;
    });// sort processes by priority

    for (const auto& process : processes) { //calculate values based off of sorted processes
        totalTurnaroundTime += (currentTime + process.burstDuration - process.arrivalTime);
        totalWaitingTime += (currentTime - process.arrivalTime);
        currentTime += process.burstDuration;
    }
//calc values for output
    float avgTurnaroundTime = totalTurnaroundTime / processes.size();
    float avgWaitingTime = totalWaitingTime / processes.size();
    float throughput = processes.size() / static_cast<float>(currentTime);

    std::cout << "--- Priority ---" << std::endl;//print output
    std::cout << "Average Turnaround Time: " << avgTurnaroundTime << std::endl;
    std::cout << "Average Waiting Time: " << avgWaitingTime << std::endl;
    std::cout << "Throughput: " << throughput << std::endl;
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) { // if a file is not passed show how to
        std::cerr << "Usage: " << argv[0] << " <input_filename>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file.\n";
        return 1;
    }// if file cannot open send error

    std::vector<Process> processes; // vector to fill with processes
    std::string line;

    while (std::getline(inputFile, line)) { // create processes and place in vector
        std::stringstream ss(line);
        std::string item;
        std::vector<int> items;

        while (std::getline(ss, item, ',')) {
            items.push_back(std::stoi(item));
        }

        if (items.size() == 4) {
            processes.push_back({ items[0], items[1], items[2], items[3] });
        }
    }

    inputFile.close();

    if (processes.empty()) { // if ifle is empty error
        std::cerr << "No valid data in the file.\n";
        return 1;
    }


    FCFS(processes); // call fcfs

    std::vector<Process> sjfProcesses = processes; // make a copy so sorted prccesses doesnt effect other algorithms
    SJF(sjfProcesses); // call sjf

    std::vector<Process> priorityProcesses = processes; // make copy again
    PriorityScheduling(priorityProcesses); // call prior

    return 0;
}
