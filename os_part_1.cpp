#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Process {
	public:
    int pid;                        // Process ID
    int arrivalTime;                // Arrival Time
    int burstTime;                  // Burst Time
    int completionTime;             // Completion Time
    int turnAroundTime;             // Turnaround Time
    int waitingTime;                // Waiting Time
};

// To arrange the process based on arrival Time, if the arrival times are same, we arrange them based on their id
bool compareProcesses(const Process& a, const Process& b) {
    if (a.arrivalTime != b.arrivalTime)
        return a.arrivalTime < b.arrivalTime;
    return a.pid < b.pid;
}

//completion time =  completion time of the previous process + burst time of that process
void findCompletionTime(vector<Process>&vec){
	vec[0].completionTime=vec[0].burstTime+vec[0].arrivalTime;
	int i;
	for(i=1;i<vec.size();i++){
		vec[i].completionTime=vec[i-1].completionTime+vec[i].burstTime;
	}
}

// Turn around time is the total time the p
void findTurnAroundTime(vector<Process>&vec){
	int i;
	for(i=0;i<vec.size();i++){
		vec[i].turnAroundTime=vec[i].completionTime-vec[i].arrivalTime;
	}
}

// Waiting time is the amount of time the process stays in the ready quque before its implememtation is begun
void findWaitingTime(vector<Process>&vec){
	int i;
	for(i=0;i<vec.size();i++){
		vec[i].waitingTime=vec[i].turnAroundTime-vec[i].burstTime;
	}
}

void printProcesses(const vector<Process>&processes) {
	int i;
    for (i=0;i<processes.size();i++) {
        cout << "PID: " << processes[i].pid
             << ", Arrival Time: " << processes[i].arrivalTime
             << ", Burst Time: " << processes[i].burstTime 
             << ", Completion Time: " << processes[i].completionTime 
             << ", Turn Around Time: " << processes[i].turnAroundTime 
             << ", Waiting Time: " << processes[i].waitingTime << endl;
    }
}

int main(){
	int number_of_process;
	cout<<"Enter the number of processes"<<endl;
	cin>>number_of_process;
	vector<Process>processes(number_of_process);
	int i;
	for(i=0;i<number_of_process;i++){
		processes[i].pid=i+1;
		cout<<"Enter the arrival Time"<<endl;
		cin>>processes[i].arrivalTime;
		cout<<"Enter the burst Time"<<endl;
		cin>>processes[i].burstTime;
	}
	
	sort(processes.begin(), processes.end(), compareProcesses);
	findCompletionTime(processes);
	findTurnAroundTime(processes);
	findWaitingTime(processes);
    
    printProcesses(processes);
}


