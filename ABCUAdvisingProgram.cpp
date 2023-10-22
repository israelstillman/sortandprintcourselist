//============================================================================
// Name        : ABCUAdvising.cpp
// Author      : Israel Stillman
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Define a structure to hold course information
struct Course {
	string courseNumber;
	string courseTitle;
	string prerequisites;
	string tempString;
};

// Function to load course data from a CSV file into a map
void loadFile(unordered_map<string, Course>& courseData, const string& filePath) {
	// Attempt to open the input file
	ifstream inputFile(filePath);
	if (!inputFile.is_open()) {
		cerr << "Error opening the file." << endl;
		return;
	}

	string line;
	while (getline(inputFile, line)) {
		stringstream inputString(line);

		string courseNumber, courseTitle, prerequisites;
		getline(inputString, courseNumber, ',');
		getline(inputString, courseTitle, ',');
		getline(inputString, prerequisites);

		// Removing potential byte order mark (BOM) from courseNumber
		if (courseNumber.size() >= 3 && courseNumber[0] == '\xEF' && courseNumber[1] == '\xBB' && courseNumber[2] == '\xBF') {
			courseNumber.erase(0, 3);
		}

		// Removing double quotes from courseNumber and prerequisites
		courseNumber.erase(remove(courseNumber.begin(), courseNumber.end(), '\"'), courseNumber.end());
		prerequisites.erase(remove(prerequisites.begin(), prerequisites.end(), '\"'), prerequisites.end());

		Course c;
		c.courseNumber = courseNumber;
		c.courseTitle = courseTitle;
		c.prerequisites = prerequisites;

		// Adding the course to the courseData map
		courseData[courseNumber] = c;
	}
}

// Function to print the list of courses
void printCourseList(const unordered_map<string, Course>& courseData) {
	cout << "Course List: " << endl;
	for (const auto& entry : courseData) {
		cout << "Course Number: " << entry.second.courseNumber << endl;
		cout << "Course Title: " << entry.second.courseTitle << endl;
		cout << "Prerequisites: " << entry.second.prerequisites << endl;
		cout << "---------------------------" << endl;
	}
}

// Function to print details of a specific course
void printSpecificCourse(const unordered_map<string, Course>& courseData) {
	string courseNumber;
	cout << "Enter the course number: ";
	cin.ignore();
	getline(cin, courseNumber);

	courseNumber = courseNumber;

	// Convert course number to uppercase for case-insensitive search
	transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

	auto it = courseData.find(courseNumber);
	if (it != courseData.end()) {
		const Course& course = it->second;
		cout << "Course Number: " << course.courseNumber << endl;
		cout << "Course Title: " << course.courseTitle << endl;
		cout << "Prerequisites: " << course.prerequisites << endl;
	}
	else {
		cout << "Course not found." << endl;
	}
}


int main() {
	int inputOption = 0;
	unordered_map<string, Course> courseData;

	cout << "Welcome to the ABCU Advising Program" << endl;

	while (inputOption != 4) {
		cout << "Please make a selection from the menu below: " << endl;
		cout << "1: Load Data Structure" << endl;
		cout << "2: Print Course List" << endl;
		cout << "3: Print Course" << endl;
		cout << "4: Exit" << endl;
		cout << " " << endl;
		cin >> inputOption;

		switch (inputOption) {
		case 1:
		{
			loadFile(courseData, "ABCUAdvisingProgramInput.csv");
			cout << "Data loaded successfully!" << endl;
			break;
		}
		case 2:
			printCourseList(courseData);
			break;
		case 3:
			printSpecificCourse(courseData);
			break;
		case 4:
			cout << "Exiting the program." << endl;
			return 0;
		default:
			cout << "Invalid input. Please select a valid option." << endl;
			break;
		}

		if (cin.fail()) {
			cout << "Invalid input. Please enter a valid option." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	return 0;
}
