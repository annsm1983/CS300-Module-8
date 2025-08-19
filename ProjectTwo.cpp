//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Ann San Miguel
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Define the Course class
class Course {
public:
    std::string courseNumber;
    std::string title;
    std::vector<std::string> prerequisites;

    Course() = default;

    Course(std::string num, std::string t, std::vector<std::string> prereqs)
        : courseNumber(std::move(num)), title(std::move(t)), prerequisites(std::move(prereqs)) {}
};

// Function prototypes
void loadCourses(const std::string& filename, std::vector<Course>& courses);
void printAlphanumericList(const std::vector<Course>& courses);
void printCourseInfo(const std::vector<Course>& courses, const std::string& courseNumber);

int main() {
    std::vector<Course> courses;
    std::string filename;
    int choice = 0;

    while (choice != 9) {
        std::cout << "\nMenu Options:\n";
        std::cout << "1. Load file data\n";
        std::cout << "2. Print alphanumeric list\n";
        std::cout << "3. Print course information\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter the file name: ";
            std::cin >> filename;
            loadCourses(filename, courses);
            break;
        case 2:
            if (courses.empty()) {
                std::cout << "Please load the data first.\n";
            }
            else {
                printAlphanumericList(courses);
            }
            break;
        case 3:
            if (courses.empty()) {
                std::cout << "Please load the data first.\n";
            }
            else {
                std::string courseNum;
                std::cout << "Enter the course number: ";
                std::cin >> courseNum;
                printCourseInfo(courses, courseNum);
            }
            break;
        case 9:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    return 0;
}

// Function to load data from file
void loadCourses(const std::string& filename, std::vector<Course>& courses) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    courses.clear();
    std::string line;
    while (std::getline(file, line)) {
        // Parse the line
        // Example parsing logic (basic)
        // You would need more robust parsing for real-world use
        size_t firstSpace = line.find(' ');
        if (firstSpace == std::string::npos) continue;

        std::string courseNum = line.substr(0, firstSpace);

        size_t secondSpace = line.find(' ', firstSpace + 1);
        if (secondSpace == std::string::npos) secondSpace = line.length();

        std::string title = line.substr(firstSpace + 1, secondSpace - (firstSpace + 1));

        std::vector<std::string> prereqs;
        if (secondSpace != line.length()) {
            std::string prereqStr = line.substr(secondSpace + 1);
            size_t pos = 0;
            std::string token;
            while ((pos = prereqStr.find(' ')) != std::string::npos) {
                token = prereqStr.substr(0, pos);
                prereqs.push_back(token);
                prereqStr.erase(0, pos + 1);
            }
            if (!prereqStr.empty()) {
                prereqs.push_back(prereqStr);
            }
        }

        courses.emplace_back(courseNum, title, prereqs);
    }
    std::cout << "Courses loaded successfully.\n";
}

// Function to sort and print courses
void printAlphanumericList(const std::vector<Course>& courses) {
    std::vector<Course> sortedCourses = courses;
    std::sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    std::cout << "Alphanumeric Course List:\n";
    for (const auto& course : sortedCourses) {
        std::cout << course.courseNumber << ": " << course.title << std::endl;
    }
}

// Function to print details of a specific course
void printCourseInfo(const std::vector<Course>& courses, const std::string& courseNumber) {
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            std::cout << "Course Title: " << course.title << std::endl;
            if (!course.prerequisites.empty()) {
                std::cout << "Prerequisites: ";
                for (const auto& prereq : course.prerequisites) {
                    std::cout << prereq << " ";
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "No prerequisites.\n";
            }
            return;
        }
    }
    std::cout << "Course not found.\n";
}