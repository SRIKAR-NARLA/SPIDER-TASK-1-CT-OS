#include <iostream>
#include <vector>
using namespace std;

int main() {
    int number_of_processes, number_of_resources;
    cout << "Enter the number of processes: ";
    cin >> number_of_processes;
    cout << "Enter the number of resources: ";
    cin >> number_of_resources;

    vector<int> available(number_of_resources);
    cout << "Enter the available instances of each resource: ";
    for (int i = 0; i < number_of_resources; ++i) {
        cin >> available[i];
    }

    vector<vector<int> > allocation(number_of_processes, vector<int>(number_of_resources));
    for (int i = 0; i < number_of_processes; ++i) {
        for (int j = 0; j < number_of_resources; ++j) {
            cout << "Enter the number of instances of resource " << j + 1 << " allocated to process " << i + 1 << ": ";
            cin >> allocation[i][j];
        }
    }

    vector<vector<int> > max_need(number_of_processes, vector<int>(number_of_resources));
    for (int i = 0; i < number_of_processes; ++i) {
        for (int j = 0; j < number_of_resources; ++j) {
            cout << "Enter the maximum need of instances of resource " << j + 1 << " for process " << i + 1 << ": ";
            cin >> max_need[i][j];
        }
    }

	// To find the remaining number of instances of each resource required
    vector<vector<int> > required(number_of_processes, vector<int>(number_of_resources));
    for (int i = 0; i < number_of_processes; ++i) {
        for (int j = 0; j < number_of_resources; ++j) {
            required[i][j] = max_need[i][j] - allocation[i][j];
        }
    }

	// To compute the safe order by comparing the remaining and available, once a process is done, all the resources used by it will be added to the available 
    vector<int> isDone(number_of_processes, 0), order(number_of_processes, 0);
    int index = 0;

    for (int i = 0; i < number_of_processes; i++) {
        for (int j = 0; j < number_of_processes; j++) {
            if (isDone[j] == 0) {
                int flag = 0;
                for (int k = 0; k < number_of_resources; k++) {
                    if (required[j][k] > available[k]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    order[index++] = j + 1;
                    for (int l = 0; l < number_of_resources; l++) {
                        available[l] += allocation[j][l];
                    }
                    isDone[j] = 1;
                }
            }
        }
    }

    cout << "The safe sequence is:" << endl;
    for (int i = 0; i < number_of_processes; i++) {
        if (order[i] == 0) {
        	if(i==0)
        		cout<<"Deadlock at the "<<i+1<<"st step";
        	else if(i==1)
        		cout<<"Deadlock at the "<<i+1<<"nd step";
        	else if(i==2)
        		cout<<"Deadlock at the "<<i+1<<"rd step";
        	else
        		cout<<"Deadlock at the "<<i+1<<"th step";
            break;
        }
        cout << "P" << order[i] << " ";
    }

    return 0;
}

