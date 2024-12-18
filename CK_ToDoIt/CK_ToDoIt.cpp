#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <windows.h>

using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::string;
using std::vector;

int Choice;


// PRIORITY LEVELS
// 1 = Very Low
// 2 = Low
// 3 = Medium
// 4 = High
// 5 = Very High
// 6 = Urgent
// 7 = Immediate

// STATUS LEVELS
// 1 = Not Started
// 2 = Started
// 3 = In Progress
// 4 = Almost Done
// 5 = Completed

struct Task {
	string TaskName;
	string TaskDescription;
	string TaskDate;
	string TaskTime;
	int TaskPriority;
	int TaskStatus;
};

vector<Task> TaskList;

bool CreateTask();
bool EditTask();
bool DeleteTask();

string GetCurrentDate();
string GetCurrentTimeStamp();

void PrintTasksWithIndex();
void PrintStatusHelp();
void PrintPriorityHelp();
void PrintCurrentTask();
void PrintAllTasks();

int main() {
	do {
		cout << "----------          MENU          ----------" << endl;

		cout << "1) Create Task" << endl;
		cout << "2) Edit Task" << endl;
		cout << "3) Delete Task" << endl;
		cout << "4) View All Tasks" << endl;
		cout << "5) View Specific Task by Name" << endl;
		cout << "6) View Specific Task by Date" << endl;
		cout << "7) View Specific Task by Priority" << endl;
		cout << "8) Exit" << endl;
		cout << "--------------------------------------------" << endl;

		cout << "Your Input: ";
		cin >> Choice;
        cout << endl << endl;

		switch (Choice) {
			case 1: {
				if (CreateTask()) {
                    cout << "Task created Successfully..." << endl << endl;
                    Sleep(1500);
                    PrintCurrentTask();
				} else {
                    cout << "Something went wrong. Please try again." << endl << endl;
				}
				break;
			}
            case 2: {
                if (TaskList.empty()) {
                    cout << "No Tasks available." << endl << endl;
                }
                else {
                    EditTask();
                }
            }
            case 3: {
                if (TaskList.empty()) {
                    cout << "No Tasks available." << endl << endl;
                }
                else {
                    if (DeleteTask()) {
                        cout << "Task deleted Successfully..." << endl << endl;
						Sleep(1500);
                    }
                    else {
                        cout << "Something went wrong. Please try again." << endl << endl;
                    }
                }
            }
            case 4: {
				if (TaskList.empty()) {
					cout << "No Tasks available." << endl << endl;
				} else {
					PrintAllTasks();
				}
				break;
            }
		}

	} while (Choice != 8);
}

bool CreateTask() {
    try {
        Task NewTask;

        cout << "Enter Task Name: ";
        cin.ignore(); // Ignoriere den verbleibenden Zeilenumbruch
        std::getline(cin, NewTask.TaskName);

        while (true) {
            bool nameExists = false;
            for (const auto& task : TaskList) {
                if (task.TaskName == NewTask.TaskName) {
                    nameExists = true;
                    break;
                }
            }
            if (nameExists) {
                cerr << "Error: Task Name already exists. Enter a different Task Name: ";
                std::getline(cin, NewTask.TaskName);
            }
            else {
                break;
            }
        }

        cout << "Enter Task Description: ";
        std::getline(cin, NewTask.TaskDescription);

        // Get Current Date
        NewTask.TaskDate =  "Date of Creation: " + GetCurrentDate();

        // Get Current Timestamp
        NewTask.TaskTime = "Timestamp of Creation: " + GetCurrentTimeStamp();

        cout << "H for Help" << endl;
        cout << "Enter Task Priority: ";
        string priorityInput;
        cin >> priorityInput;
        while (true) {
            if (priorityInput == "H") {
                PrintPriorityHelp();
                cout << "Enter Task Priority: ";
                cin >> priorityInput;
            }
            else {
                NewTask.TaskPriority = std::stoi(priorityInput);
                if (NewTask.TaskPriority < 1 || NewTask.TaskPriority > 7) {
                    cerr << "Error: Priority must be between 1 and 7. Enter Task Priority: ";
                    cin >> priorityInput;
                }
                else {
                    break;
                }
            }
        }

        cout << "H for Help" << endl;
        cout << "Enter Task Status: ";
        string statusInput;
        cin >> statusInput;
        while (true) {
            if (statusInput == "H") {
                PrintStatusHelp();
                cout << "Enter Task Status: ";
                cin >> statusInput;
            }
            else {
                NewTask.TaskStatus = std::stoi(statusInput);
                if (NewTask.TaskStatus < 1 || NewTask.TaskStatus > 5) {
                    cerr << "Error: Status must be between 1 and 5. Enter Task Status: ";
                    cin >> statusInput;
                }
                else {
                    break;
                }
            }
        }

        TaskList.push_back(NewTask);
        return true;

    }
    catch (std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
}

bool EditTask() {
    int TaskNumber, EditChoice;
    string NewPriority, NewStatus;

    try {

        cout << "----------          EDIT TASK          ----------" << endl;
        PrintTasksWithIndex();

        cout << "Enter the number of the Task you want to edit: ";
        cin >> TaskNumber;

        while (true) {
            if (TaskNumber < 0 || TaskNumber >= TaskList.size()) {
                cerr << "Error: Task Number does not exist." << endl;
                cout << "Enter the number of the Task you want to edit: ";
                cin >> TaskNumber;
            }
            else {
                break;
            }
        }

        // Choose what to edit
		cout << "Choose what to edit: " << endl;
		cout << "1) Task Name" << endl;
		cout << "2) Task Description" << endl;
        cout << "3) Task Priority" << endl;
		cout << "4) Task Status" << endl;
		cout << "5) Return to Menu" << endl;

		cout << "Your Input: ";
		cin >> EditChoice;

        switch (EditChoice) {
            case 1: {
				cout << "Enter new Task Name: ";
				cin.ignore();
				std::getline(cin, TaskList[TaskNumber].TaskName);

				// TODO: Check if Task Name already exists
				// TODO: Check if Task Name is empty
				// TODO: Change Task Name in this Task

				break;
            }
            case 2: {
				cout << "Enter new Task Description: ";
				cin.ignore();
				std::getline(cin, TaskList[TaskNumber].TaskDescription);
				break;
            }
            case 3: {
				cout << "Enter new Task Priority: ";
				cin >> NewPriority;
                if (NewStatus == "H") {
                    PrintStatusHelp();
                    cout << "Enter Task Status: ";
                    cin >> NewStatus;
                }
                else {
                    while (true) {
                        TaskList[TaskNumber].TaskPriority = std::stoi(NewPriority);
                        if (TaskList[TaskNumber].TaskPriority < 1 || TaskList[TaskNumber].TaskPriority > 7) {
                            cerr << "Error: Priority must be between 1 and 7. Enter Task Priority: ";
                            cin >> NewPriority;
                        }
                        else {
                            break;
                        }
                    }
                }
            }
            case 4: {
				cout << "Enter H for Help" << endl;
				cout << "Enter new Task Status: ";
                cin >> NewStatus;
                if (NewStatus == "H") {
                    PrintStatusHelp();
                    cout << "Enter Task Status: ";
                    cin >> NewStatus;
                }
                else {
                    while (true) {
                        TaskList[TaskNumber].TaskStatus = std::stoi(NewStatus);
                        if (TaskList[TaskNumber].TaskStatus < 1 || TaskList[TaskNumber].TaskStatus > 5) {
                            cerr << "Error: Status must be between 1 and 5. Enter Task Status: ";
                            cin >> NewStatus;
                        }
                        else {
                            break;
                        }
                    }
                }
            }
            case 5: {
                break;
            }
        }

    }
    catch (std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
}

bool DeleteTask() {
    int TaskNumber;

    try {
        PrintTasksWithIndex();

		cout << "Enter the number of the Task you want to delete: ";
		cin >> TaskNumber;
        while (true) {
            if (TaskNumber < 0 || TaskNumber >= TaskList.size()) {
                cerr << "Error: Task Number does not exist." << endl;
                cout << "Enter the number of the Task you want to delete: ";
                cin >> TaskNumber;
			}
            else {
                break;
            }
        }

		TaskList.erase(TaskList.begin() + TaskNumber);
		return true;

    } catch (std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
}

string GetCurrentDate() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    int year = 1900 + ltm.tm_year;
    int month = 1 + ltm.tm_mon;
    int day = ltm.tm_mday;

    string monthString = std::to_string(month);
    string dayString = std::to_string(day);

    if (month < 10) {
        monthString = "0" + monthString;
    }
    if (day < 10) {
        dayString = "0" + dayString;
    }

	return std::to_string(year) + "." + monthString + "." + dayString;
}

string GetCurrentTimeStamp() {
    time_t now = time(0);
    tm ltm;
	localtime_s(&ltm, &now);

    int hour = ltm.tm_hour;
    int minute = ltm.tm_min;
    int second = ltm.tm_sec;

    string hourString = std::to_string(hour);
    string minuteString = std::to_string(minute);
    string secondString = std::to_string(second);

    if (hour < 10) {
        hourString = "0" + hourString;
    }
    if (minute < 10) {
        minuteString = "0" + minuteString;
    }
    if (second < 10) {
        secondString = "0" + secondString;
    }
    return hourString + ":" + minuteString + ":" + secondString;
}

void PrintTasksWithIndex() {
    for (int i = 0; i < TaskList.size(); i++) {
        cout << "(" << i << ") " << TaskList[i].TaskName << endl;
    }
}

void PrintStatusHelp() {
	cout << "----------          STATUS LEVELS          ----------" << endl;
	cout << "1 = Not Started" << endl;
	cout << "2 = Started" << endl;
	cout << "3 = In Progress" << endl;
	cout << "4 = Almost Done" << endl;
	cout << "5 = Completed" << endl << endl;
}

void PrintPriorityHelp() {
	cout << "----------          PRIORITY LEVELS          ----------" << endl;
	cout << "1 = Very Low" << endl;
	cout << "2 = Low" << endl;
	cout << "3 = Medium" << endl;
	cout << "4 = High" << endl;
	cout << "5 = Very High" << endl;
	cout << "6 = Urgent" << endl;
	cout << "7 = Immediate" << endl << endl;
}

void PrintCurrentTask() {
	cout << "----------          CURRENT TASK          ----------" << endl;
	cout << "Task Name: " << TaskList.back().TaskName << endl;
	cout << "Task Description: " << TaskList.back().TaskDescription << endl;
	cout << "Task Date: " << TaskList.back().TaskDate << endl;
	cout << "Task Time: " << TaskList.back().TaskTime << endl;
	cout << "Task Priority: " << TaskList.back().TaskPriority << endl;
	cout << "Task Status: " << TaskList.back().TaskStatus << endl;
	cout << "----------------------------------------------------" << endl << endl;
}

void PrintAllTasks() {
    cout << "----------          ALL TASKS          ----------" << endl;
    for (const auto& task : TaskList) {
        cout << "Task Name: " << task.TaskName << endl;
        cout << "Task Description: " << task.TaskDescription << endl;
        cout << "Task Date: " << task.TaskDate << endl;
        cout << "Task Time: " << task.TaskTime << endl;
        cout << "Task Priority: " << task.TaskPriority << endl;
        cout << "Task Status: " << task.TaskStatus << endl;
        cout << "----------------------------------------------------" << endl;
    }
    cout << "----------------------------------------------------" << endl << endl;
}