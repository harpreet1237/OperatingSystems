#include<bits/stdc++.h>
using namespace std;

class Process{
private:
    string name;
    float arrivalTime;
    float totalExecutionTime;
    float executionLeftTime;
    float ioInterruptTime;
    float ioTime;
    int priority;
    float waitingTime = 0;
    float turnAroundTime;
    float currentTime;
    float finishTime;
    float firstArrivalTime = -1;
    float CPUTime = 0;
public:
    string getName() { return name; }
    void setName(string name) { this->name = name; }

    float getArrivalTime() const { return this->arrivalTime; }
    void setArrivalTime(float at) { this->arrivalTime = at; if(firstArrivalTime == -1)this->firstArrivalTime = at;}

    float getExecutionLeftTime() const { return this->executionLeftTime; }
    void setExecutionLeftTime(float et) { this->executionLeftTime = et;this->totalExecutionTime = et; }

    float getIoInterruptTime() { return this->ioInterruptTime; }
    void setIoInterruptTime(float iit) { this->ioInterruptTime = iit; }
	
    float getfirstArrivalTime() const {return this->firstArrivalTime;}
    float getIoTime() { return this->ioTime; }
    void setIoTime(float it) { this->ioTime = it; }

    int getPriority() const { return this->priority; }
    void setPriority(int p) { this->priority = p; }

    float getWaitingTime() { return this->waitingTime; }
    void setWaitingTime(float wt) { this->waitingTime = wt; }

    float getTurnAroundTime() { return this->turnAroundTime; }
    void setTurnAroundTime(float tat) { this->turnAroundTime = tat - firstArrivalTime; }

    float getCPUTime() { return this->CPUTime;}
    void setCPUTime(float cpuTime) {this->CPUTime = cpuTime;}

    void subtractExecutionTime(float timeStep){
        this->executionLeftTime = this->executionLeftTime - timeStep;
    }

    void shiftIoInterruptTime(){this->ioInterruptTime  = this->ioInterruptTime + this->ioTime;}

    void display(){
        cout << this->name << "                " << this->turnAroundTime << "                " << this->waitingTime << endl;
    }
};

struct CompareByExecutionTime {
    bool operator()(const Process& process1, const Process& process2) const {
        if (process1.getExecutionLeftTime() < process2.getExecutionLeftTime())
        return true;
    else if (process1.getExecutionLeftTime() > process2.getExecutionLeftTime())
        return false;

    // If arrivalTime is the same, compare by priority
    return process1.getPriority() < process2.getPriority();
    }
};

struct CompareByArrivalTime {
    bool operator()(const Process& process1, const Process& process2) const {
        if (process1.getArrivalTime() < process2.getArrivalTime())
        return true;
    else if (process1.getArrivalTime() > process2.getArrivalTime())
        return false;

    // If arrivalTime is the same, compare by priority
    return process1.getPriority() < process2.getPriority();
    }
};

vector<Process> takeInput(){
    string filename;
    cout << "Enter fileName : " << endl;
    cin >> filename;

    vector<Process> processes;
    //Take input
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return std::vector<Process>();
    }
    string line;

    while (std::getline(file, line)) {
        Process process;
        std::istringstream iss(line);
        string processName;
        float processArrivalTime,processExecutionTime,processIoInterruptTime,processIoTime;
        int processPriority;
        iss >> processName >> processArrivalTime >> processExecutionTime >> processIoInterruptTime >> processIoTime >> processPriority;

        process.setName(processName);
        process.setArrivalTime(processArrivalTime);
        process.setIoInterruptTime(processIoInterruptTime);
        process.setIoTime(processIoTime);
        process.setPriority(processPriority);
        process.setExecutionLeftTime(processExecutionTime);
        processes.push_back(process);
    }

    for(int i = 1;i < processes.size();i++){
        processes[i].setArrivalTime(processes[i].getArrivalTime() + processes[i-1].getArrivalTime());
    }//relative time

    file.close();
    return processes;
 
}

void displayProcessInfo(vector<Process>& processes,string nameAlgorithm){
    cout << "Process Information for the algorithm : " << nameAlgorithm << endl;
    cout << "ProcesName\tProcessTurnAroundTime\tProcessWaitingTime\n";
    float averageTurnAroundTime = 0;
    float standardDeviation = 0;
    float averageWaitingTime = 0;

    for(auto process:processes){
        averageTurnAroundTime += process.getTurnAroundTime();
        averageWaitingTime += process.getWaitingTime();
        process.display();
    }
    averageTurnAroundTime /= (processes.size());

    for(auto process:processes){
        standardDeviation += (averageTurnAroundTime - process.getTurnAroundTime())*(averageTurnAroundTime - process.getTurnAroundTime());
    }
    standardDeviation = sqrt(standardDeviation);

    
    cout << "The average time for processes to complete was : " << averageTurnAroundTime << endl;
    cout << "The standard deviation for the average process completion time was : " << standardDeviation << endl;

}

void fcfs(vector<Process> processes){

    priority_queue<Process,vector<Process>, CompareByArrivalTime> processQueue;
    float currentTime = 0;

    vector<Process>processesFinal;
    for(auto process:processes){
        processQueue.push(process);
    }

    while(!processQueue.empty()){
    
        Process currentProcesss = processQueue.top();
        processQueue.pop();
        if(currentTime > currentProcesss.getArrivalTime()){
            currentProcesss.setWaitingTime(currentProcesss.getWaitingTime() + (currentTime - currentProcesss.getArrivalTime()));
        }
        else {
            currentTime = currentProcesss.getArrivalTime();
        }
        
        currentTime += min(currentProcesss.getExecutionLeftTime(), currentProcesss.getIoInterruptTime());
        currentProcesss.subtractExecutionTime(min(currentProcesss.getExecutionLeftTime(),currentProcesss.getIoInterruptTime()));

        if(currentProcesss.getExecutionLeftTime() == 0){
            currentProcesss.setTurnAroundTime(currentTime);
            processesFinal.push_back(currentProcesss);
        }
        else{
            currentProcesss.setArrivalTime(currentTime + currentProcesss.getIoTime());
            currentTime += currentProcesss.getIoTime();
            processQueue.push(currentProcesss);
        }
    }

    //End of Algorithm
    displayProcessInfo(processesFinal,"FCFS");
}


void sjf(vector<Process> processes){

    vector<Process>processesFinal;
    priority_queue<Process,vector<Process>,CompareByExecutionTime> processQueue;

    float currentTime = 0;

        
    displayProcessInfo(processesFinal,"Shortest Job First");
}


vector<Process> transfer(priority_queue<Process,vector<Process>, CompareByArrivalTime> & processQueue){
    vector<Process>temp;

    while(!processQueue.empty()){
        temp.push_back(processQueue.top());
        processQueue.pop();
    }
    return temp;
}

void roundRobin(vector<Process> processes,float timeslice = 1.0){

    vector<Process>processesFinal;

    vector<Process>processQueueVector;
    processQueueVector = processes;
    priority_queue<Process,vector<Process>, CompareByArrivalTime> processQueue;
    float currentTime = 0;

    for(auto process:processes){
        processQueue.push(process);
    }

    processQueueVector.clear();
    while(!processQueue.empty()){processQueueVector.push_back(processQueue.top());processQueue.pop();}

    for(int i=0;i<processQueueVector.size();i++)cout << processQueueVector[i].getArrivalTime() << endl;
    while(!processQueueVector.empty()){
        
        for(auto currentProcess:processQueueVector){
            if(currentTime >= currentProcess.getArrivalTime()){
                currentProcess.setWaitingTime(currentTime - currentProcess.getArrivalTime());
            }
            else{
                currentTime = currentProcess.getArrivalTime();
            }

            float timeAvailable = min(currentProcess.getExecutionLeftTime(),currentProcess.getCPUTime());

            if(timeAvailable <= timeslice){
                currentProcess.subtractExecutionTime(timeAvailable);
                currentTime += timeAvailable;

                if(currentProcess.getExecutionLeftTime() == 0){
                    currentProcess.setTurnAroundTime(currentTime);
                    if(currentProcess.getName() == "P1"){
                    	cout << currentProcess.getfirstArrivalTime() << " " << currentTime << endl;
                    }
                    processesFinal.push_back(currentProcess);
                }
                else{
                    currentProcess.setCPUTime(currentProcess.getIoInterruptTime());
                    currentProcess.setArrivalTime(currentTime + currentProcess.getIoTime());
                    processQueue.push(currentProcess);
                }
            }
            else{
                currentProcess.subtractExecutionTime(timeslice);
                currentProcess.setCPUTime(currentProcess.getCPUTime() - timeslice);
                currentTime += timeslice;
                currentProcess.setArrivalTime(currentTime);
                processQueue.push(currentProcess);
            }
        }

        processQueueVector.clear();
        while(!processQueue.empty()){processQueueVector.push_back(processQueue.top());processQueue.pop();}

    }
    
    displayProcessInfo(processesFinal,"Round-Robin");
}


int main(){
    cout <<setprecision(4)<<fixed;
    vector<Process> processes ;
    processes = takeInput();    //take input from file

    // Implement FCFS first;
    fcfs(processes);

    // Implement SJF 
    sjf(processes);

    // Implement RoundRobin both 1.0 and 2.0 
    cout << " RoundRobin (timeslice 1.0)\n"; 
    roundRobin(processes,1.0f);
    cout << " RoundRobin (timeslice 2.0)\n"; 
    roundRobin(processes,2.0f);

    return 0;
}
