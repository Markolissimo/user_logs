#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> SplitDate(string s, char sep)
{
    //vector<string> month = ('January', 'February', 'March', 'April', 'May', 'June',
    //        'July', 'August', 'September', 'October', 'November', 'December');
    vector<string> v;
    string temp = "";
    for (size_t i = 0; i < s.length(); ++i)
    {
        if (s[i] == sep)
        {
            v.push_back(temp);
            temp = "";
        }
        else
        {
            temp.push_back(s[i]);
        }
    }
    v.push_back(temp);
    return v;
}

class Log
{
protected:
    string Name;
    string Email;
    string Department;
    string Position;
    string Project;
    string Task;
    /*Structed Date
    struct Date
    {
        int year;
        int month;
        int day;
    };
    */
    vector<string> Date;
    int Logged_hours;

public:
    Log(vector<string> person)
    {
        Name = person[0];
        Email = person[1];
        Department = person[2];
        Position = person[3];
        Project = person[4];
        Task = person[5];
        Date = SplitDate(person[6], '-');
        Logged_hours = stoi(person[7]);
    }

    string get_Name()
    {
        return Name;
    }

    string get_Email()
    {
        return Email;
    }

    string get_Department()
    {
        return Department;
    }

    string get_Position()
    {
        return Position;
    }

    string get_Project()
    {
        return Project;
    }

    string get_Task()
    {
        return Task;
    }

    vector<string> get_Date()
    {
        return Date;
    }

    int get_Logged_hours()
    {
        return Logged_hours;
    }


    void ShowLog()
    {   
        cout << Name << " | " << Email << " | " << Department
            << " | " << Position << " | " << Project << " | " << Task << " | " 
            << Date[0] << "-" << Date[1]
            << "-" << Date[2] << " | " << to_string(Logged_hours) << endl; 
    }
};