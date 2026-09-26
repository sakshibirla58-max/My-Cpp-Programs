//***********************************-----------:-:-:-:-:-:-:-:-: Student Management System :-:-:-:-:-:-:-:-:------------**************************************************

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<iomanip>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
};

void saveToFile(vector<Student> &students);

void addStudent(vector<Student> &students) {
    Student s;

    cout << "Enter Student ID: ";
    cin >> s.id;

    if(s.id <= 0) {
        cout << "Invalid Student ID!" << endl;
        return;
    }

    for(int i = 0; i < students.size(); i++) {
        if(students[i].id == s.id) {
            cout << "Student ID already exists!" << endl;
            return;
        }
    }

    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, s.name);

    cout << "Enter Student Age: ";
    cin >> s.age;

    if(s.age <= 0) {
        cout << "Invalid age!" << endl;
        return;
    }

    students.push_back(s);
    saveToFile(students);

    cout << "Student added successfully!" << endl;
}

void displayStudent(const vector<Student> &students) {
    if(students.empty()) {
        cout << "No students found!" << endl;
        return;
    }

    cout << left
         << setw(6) << "ID"
         << setw(17) << "Name"
         << "Age" << endl;

    cout << "------------------------------------------" << endl;

    for(int i = 0; i < students.size(); i++) {
        cout << left
             << setw(6) << students[i].id
             << setw(17) << students[i].name
             << students[i].age << endl;
    }
}

void searchStudent(const vector<Student> &students) {
    int id;

    cout << "Enter Student ID to search: ";
    cin >> id;

    if(id <= 0) {
        cout << "Invalid Student ID!" << endl;
        return;
    }

    bool found = false;

    for(int i = 0; i < students.size(); i++) {
        if(students[i].id == id) {
            found = true;

            cout << "Student Found!" << endl;
            cout << "ID: " << students[i].id << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Age: " << students[i].age << endl;
        }
    }

    if(found == false) {
        cout << "Student Not Found!" << endl;
    }
}

void updateStudent(vector<Student> &students) {
    int id;

    cout << "Enter Student ID to update: ";
    cin >> id;

    if(id <= 0) {
        cout << "Invalid Student ID!" << endl;
        return;
    }

    bool found = false;

    for(int i = 0; i < students.size(); i++) {
        if(students[i].id == id) {
            found = true;

            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, students[i].name);

            cout << "Enter New Age: ";
            cin >> students[i].age;

            if(students[i].age <= 0) {
                cout << "Invalid age!" << endl;
                return;
            }

            cout << "Student updated successfully!" << endl;

            saveToFile(students);
        }
    }

    if(found == false) {
        cout << "Student Not Found!" << endl;
    }
}

void deleteStudent(vector<Student> &students) {
    int id;
    bool found = false;

    cout << "Enter Student ID to delete: ";
    cin >> id;

    if(id <= 0) {
        cout << "Invalid Student ID!" << endl;
        return;
    }

    for(int i = 0; i < students.size(); i++) {
        if(students[i].id == id) {
            found = true;

            students.erase(students.begin() + i);

            cout << "Student deleted successfully!" << endl;

            saveToFile(students);

            break;
        }
    }

    if(found == false) {
        cout << "Student Not Found!" << endl;
    }
}

void saveToFile(vector<Student> &students) {
    ofstream file("students.txt");

    if(!file) {
        cout << "Unable to save students!" << endl;
        return;
    }
    file << left
         << setw(6) << "ID"
         << setw(17) << "Name"
         << "Age" << endl;

    file << "------------------------------------------" << endl;

    for(int i = 0; i < students.size(); i++) {
        file << students[i].id << "   "
             << students[i].name << "   "
             << students[i].age << endl;
    }

    file.close();
}

void loadFromFile(vector<Student> &students) {
    ifstream file("students.txt");

    if(!file) {
        return;
    }

    Student s;
    string line;

    // Skip heading
    getline(file, line);

    // Skip separator line
    getline(file, line);

    while(getline(file, line)) {

        if(line.empty()) {
            continue;
        }

        // Read ID
        size_t pos1 = line.find(' ');
        if(pos1 == string::npos) {
            continue;
        }

        s.id = stoi(line.substr(0, pos1));

        // Remove spaces before name
        size_t nameStart = line.find_first_not_of(' ', pos1);

        // Find spaces before age
        size_t ageStart = line.find_last_of(' ');

        if(nameStart == string::npos || ageStart == string::npos) {
            continue;
        }

        s.name = line.substr(nameStart, ageStart - nameStart);

        // Remove extra spaces from name
        while(!s.name.empty() && s.name.back() == ' ') {
            s.name.pop_back();
        }

        s.age = stoi(line.substr(ageStart + 1));

        students.push_back(s);
    }

    file.close();
}
void sortStudents(vector<Student> &students) {
    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.id < b.id;
    });
}

int main() {

    vector<Student> students;

    loadFromFile(students);

    int choice;

    while(true) {

        cout << "\n------ Student Management System ------\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort Students\n";
        cout << "7. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                addStudent(students);
                break;

            case 2:
                displayStudent(students);
                break;

            case 3:
                searchStudent(students);
                break;

            case 4:
                updateStudent(students);
                break;

            case 5:
                deleteStudent(students);
                break;

            case 6:
                sortStudents(students);
                saveToFile(students);
                cout << "Students sorted successfully!" << endl;
                break;

            case 7:
                cout << "Exiting...";
                return 0;

            default:
                cout << "Invalid choice";
        }
    }
}
