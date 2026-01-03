/*
File: virtual_function.cpp
Date: 2026-01-03 16:08

Problem: Virtual Functions
Link: https://www.hackerrank.com/challenges/virtual-functions/problem

Problem Statement:
This problem requires the implementation of three classes: Person, Professor, and Student.
- `Person`: An abstract base class with virtual functions `getdata` and `putdata`.
- `Professor`: Inherits from Person, tracks publications, and generates a unique ID starting from 1.
- `Student`: Inherits from Person, tracks marks in 6 subjects, calculates the sum, and generates a unique ID starting from 1.

The program creates N objects (either Professor or Student) based on user input, reads their specific data, and then displays it using the polymorphic interface of the base class.

-------------------------------------------------
Current/Optimized Approach
- Idea: Use Runtime Polymorphism. We define a common interface in `Person` and override the behavior in `Professor` and `Student`.
- Algorithm:
  1. Define `Person` with pure virtual functions.
  2. Implement `Professor` and `Student` with static members to handle auto-incrementing IDs.
  3. In `main`, use a container of `Person*` to store derived objects uniformly.
  4. Iterate through the container to call `putdata()` dynamically.
- Time complexity: O(N) - We process N objects linearly.
- Space complexity: O(N) - Storing N objects in memory.

💡 Key Pattern:
- Polymorphism (Virtual Functions)
- Inheritance
- Static Class Members (for ID generation)

ℹ️ Keywords:
- virtual, override, static, inheritance, abstract class

🗒️ Notes
- Added a virtual destructor to the base class `Person`. This is crucial when deleting derived objects via a base class pointer to prevent undefined behavior and memory leaks.
- Replaced the Variable Length Array (VLA) `Person* per[n]` with `std::vector<Person*>` for standard C++ compliance.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @brief Abstract base class Person
 */
class Person
{
public:
    string name;
    int age;

    // Virtual destructor is essential for a polymorphic base class
    virtual ~Person() {}

    // Pure virtual functions
    virtual void getdata() = 0;
    virtual void putdata() = 0;
};

/**
 * @brief Derived class Professor
 * Tracks publications and unique sequential ID.
 */
class Professor : public Person
{
public:
    int publications;
    int id;
    static int cur_id; // Static variable to track current ID counter

    Professor()
    {
        id = cur_id++;
    }

    void getdata() override
    {
        cin >> name >> age >> publications;
    }

    void putdata() override
    {
        cout << name << " " << age << " " << publications << " " << id << endl;
    }
};

// Initialize static member for Professor
int Professor::cur_id = 1;

/**
 * @brief Derived class Student
 * Tracks marks and unique sequential ID.
 */
class Student : public Person
{
public:
    vector<int> marks;
    int id;
    static int cur_id; // Static variable to track current ID counter

    Student()
    {
        id = cur_id++;
        marks.resize(6);
    }

    void getdata() override
    {
        cin >> name >> age;
        for (int i = 0; i < 6; i++)
        {
            cin >> marks[i];
        }
    }

    void putdata() override
    {
        int sum = 0;
        for (int m : marks)
            sum += m;
        cout << name << " " << age << " " << sum << " " << id << endl;
    }
};

// Initialize static member for Student
int Student::cur_id = 1;

int main()
{
    int n, type;
    cin >> n; // Read number of objects

    // Use vector instead of VLA (Person* per[n]) for standard C++ compliance
    vector<Person *> per(n);

    // Read data and create objects
    for (int i = 0; i < n; i++)
    {
        cin >> type;

        // Create Professor (1) or Student (2)
        if (type == 1)
        {
            per[i] = new Professor();
        }
        else
        {
            per[i] = new Student();
        }

        per[i]->getdata();
    }

    // Output data using polymorphism
    for (int i = 0; i < n; i++)
    {
        per[i]->putdata();
    }

    // Cleanup memory (Good practice)
    for (int i = 0; i < n; i++)
    {
        delete per[i];
    }

    return 0;
}