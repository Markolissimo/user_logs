#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Logged_person.h"
using namespace std;

// reading_from_file_module___________________________________________________________________reading_from_file_module

int main()
{
    
    ifstream csvfile;
    vector<Log> logged_people;

    // opening the file
    csvfile.open("user_logs.csv");
    if(!csvfile.is_open())
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }

    // reading_from_file_to_vector_with_Logged_users_____________________reading_from_file_to_vector_with_Logged_users
    string line;
    vector<vector<string>> parsedCSV;
    vector<string> keys;

    // getting keys
    getline(csvfile, line);
    stringstream s (line);
    while(getline (s, line, ';'))
        keys.push_back(line);

    // line_by_line_reading_to_vector
    while(getline (csvfile, line))
    {
        string val;
        vector<string> row;
        stringstream s (line);
        while(getline (s, val, ';'))
            row.push_back(val);  
        logged_people.push_back(Log(row));
    }
    csvfile.close();

// changing_format_of_logs_for_output_______________________________________________changing_format_of_logs_for_output
    multimap<string, vector<string>> general_properties_of_logs;
    multimap<string, vector<string>>::iterator it = general_properties_of_logs.begin();
    string current_user_month = "";
    for (size_t i = 0; i < logged_people.size(); i++)
    {
        vector<string> month = {"January", "February", "March", "April", "May", "June",
                "July", "August", "September", "October", "November", "December"};
        vector<string> month_year_hours = {
                month.at(stoi(logged_people.at(i).get_Date().at(1)) - 1),
                logged_people.at(i).get_Date().at(0),
                to_string(logged_people.at(i).get_Logged_hours())
                };
        string name = logged_people.at(i).get_Name();
        if(general_properties_of_logs.count(name) == 0)
        {   
            general_properties_of_logs.insert(make_pair(logged_people.at(i).get_Name(), month_year_hours));
            current_user_month = month_year_hours.at(0);
            it = general_properties_of_logs.find(logged_people.at(i).get_Name());
        }
        else if (general_properties_of_logs.count(logged_people.at(i).get_Name()) > 0)
        {
            if(month.at(stoi(logged_people.at(i).get_Date().at(1)) - 1) == current_user_month)
            {
                int first_add = stoi(it->second.at(2));
                int sum_of_hours = first_add + logged_people.at(i).get_Logged_hours();
                it->second.at(2) = to_string(sum_of_hours);
            }
            else
            {
                general_properties_of_logs.insert(make_pair(logged_people.at(i).get_Name(), month_year_hours));
                current_user_month = month_year_hours.at(0);
                it = general_properties_of_logs.find(logged_people.at(i).get_Name());
            }   
        }
    }

    // output of edited logs 
    cout << keys[0] << ';' << keys[keys.size() - 2] << ';' << keys[keys.size() - 1] <<endl;
    for(auto elem : general_properties_of_logs)
    {
        cout << elem.first << ';' << elem.second.at(0) << ' '
            << elem.second.at(1) << ';' << elem.second.at(2) << endl;
    }
}
