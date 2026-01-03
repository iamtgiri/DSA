/*
File: virtual_function.cpp
Date: 2026-01-03 16:08

Problem: Virtual Functions
Link: https://www.hackerrank.com/challenges/virtual-functions/problem

Problem Statement:

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: 
- Time complexity: 
- Space complexity: 
- Limitations: 

Current/Optimized Approachs
- Idea: 
- Approach: 
- Algorithm: 
- Time complexity: 
- Space complexity: 

💡 Key Pattern:
- 

ℹ️ Keywords: 
- 

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
-------------------------------------------------
*/

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Base class Person with virtual functions
 * @param name Name of the person
 * @param age Age of the person
 * @function getdata Pure virtual function to get data
 * @function putdata Pure virtual function to put data
 */
class Person {
public:
    string name;
    int age;

    virtual void getdata() = 0;
    virtual void putdata() = 0;
};

/**
 * @brief Derived class Professor from Person
 * @param publications Number of publications
 * @param id Unique ID for each Professor
 * @param cur_id Static variable to keep track of current ID
 * @fn getdata Override to get Professor data
 * @fn putdata Override to put Professor data
 */
class Professor : public Person {
public:
    int publications; ///< Number of research publications
    int id; // Unique ID for each Professor
    static int cur_id; // Static variable to track current ID

    // Constructor to initialize ID
    Professor() {
        id = cur_id++;
    }

    // Read professor data
    void getdata() override {
        cin >> name >> age >> publications;
    }

    // Print professor data
    void putdata() override {
        cout << name << " " << age << " " << publications << " " << id << endl;
    }
};

// Initialize static member
int Professor::cur_id = 1;


/**
 * @brief Derived class Student from Person
 * @param marks Vector of marks in 6 subjects
 * @param id Unique ID for each Student
 * @param cur_id Static variable to keep track of current ID
 * @function getdata Override to get Student data
 * @function putdata Override to put Student data
 */
class Student : public Person {
public:
    vector<int> marks;
    int id;
    static int cur_id; // Static variable to track current ID

    // Constructor to initialize ID and resize marks vector
    Student() {
        id = cur_id++;
        marks.resize(6);
    }

    // Read student data
    void getdata() override {
        cin >> name >> age;
        for (int i = 0; i < 6; i++) {
            cin >> marks[i];
        }
    }

    // Calculate sum of marks and print student data
    void putdata() override {
        int sum = 0;
        for (int m : marks) sum += m;
        cout << name << " " << age << " " << sum << " " << id << endl;
    }
};

// Initialize static member
int Student::cur_id = 1;

int main() {
    int n;
    cin >> n;

    // Create an array of Person pointers
    Person* per[n];

    // Read data and create objects
    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;

        // Create Professor or Student based on type
        if (type == 1) {
            per[i] = new Professor();
        } else {
            per[i] = new Student();
        }
        per[i]->getdata();
    }

    // Output data
    for (int i = 0; i < n; i++) {
        per[i]->putdata();
    }

    return 0;
}
