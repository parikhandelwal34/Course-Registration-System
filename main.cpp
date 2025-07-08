#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
  
class student{
public:
    string name;
    string studentID;
    vector<string>registeredCourse;

    student(string id, string n){
        studentID = id;
        name = n; 
    } 

    void registerCourses(string courseCode){
      registeredCourse.push_back(courseCode);
    }

    void dropCourses(string courseCode){
      auto it = find(registeredCourse.begin(), registeredCourse.end(), courseCode);
        if (it != registeredCourse.end()) {
            registeredCourse.erase(it);
        }
    }

    bool isRegistered(string courseCode){
      for(string c : registeredCourse){
        if(c == courseCode){
          return true;
        }
      }
      return false;
    }

    void viewRegisteredCourses(){
      cout<<"course registered by : "<<name<<endl;
      for(string c : registeredCourse){
        cout<<c<<endl;
      }
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class course{
public:
   string courseName;
   int totalseats;
   int availableSeats;
   string courseCode;

   course(string code, string name, int total,int seats){
       courseName = name;
       courseCode = code;
       totalseats = total;
       availableSeats = seats;
   }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<student> students;
vector<course> courses;


student* findStudent(string id) {
    for (auto& s : students) {
        if (s.studentID == id) return &s;
    }
    return nullptr;
}

course* findCourse(string code) {
    for (auto& c : courses) {
        if (c.courseCode == code) return &c;
    }
    return nullptr;
}


void saveStudents() {
    ofstream out("student.txt");
    for (auto& s : students) {
        out << s.studentID << "," << s.name;
        for (auto& c : s.registeredCourse) {
            out << "," << c;
        }
        out << endl;
    }
    out.close();
}

void loadStudents() {
    students.clear();
    ifstream in("student.txt");
    string line;
    while (getline(in, line)) {
        vector<string> tokens;
        string temp = "";
        for (char ch : line) {
            if (ch == ',') {
                tokens.push_back(temp);
                temp = "";
            } else {
                temp += ch;
            }
        }
        tokens.push_back(temp);
        if (tokens.size() >= 2) {
            student s(tokens[0], tokens[1]);
            for (size_t i = 2; i < tokens.size(); ++i) {
                s.registerCourses(tokens[i]);
            }
            students.push_back(s);
        }
    }
    in.close();
}

void saveCourses() {
    ofstream out("course.txt");
    for (auto& c : courses) {
        out << c.courseCode << "," << c.courseName << "," << c.totalseats << "," << c.availableSeats << endl;
    }
    out.close();
}

void loadCourses() {
    courses.clear();
    ifstream in("course.txt");
    string code, name;
    int total, avail;
    char comma;
    while (getline(in, code, ',')) {
        getline(in, name, ',');
        in >> total >> comma >> avail;
        in.ignore();
        courses.push_back(course(code, name, total, avail));
    }
    in.close();
}


//////////////////////////////////////////////////////////////////////////////////////////////////
void addStudent(){
    string id,n,course;
    cout<<"Enter student ID : ";
    cin>>id;

    cout<<"Enter student name : ";
    cin>>n;

    if (id.empty() || n.empty() || id.find(' ') != string::npos || n.find(' ') != string::npos) {
        cout << "\n Invalid input. ID and name cannot be empty or contain spaces.\n";
        return;
    }
    if (findStudent(id)) {
        cout << "\n Student ID already exists.\n";
        return;
    }

    student s(id, n);
    students.push_back(s);
    saveStudents();

    
    cout<<"Student added successfully";
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void addCourse(){
    string code,name;
    int total,seats;

    cout<<"Enter course code : ";
    cin>>code;

    cin.ignore();

    cout<<"Enter course name : ";
    getline(cin,name);

    cout<<"Enter total seats : ";
    cin>>total;

    cout<<"Enter seats remaining : ";
    cin>>seats;

    if (code.empty() || name.empty() || seats < 0 || total < 0) {
        cout << "\n Invalid input. Fields cannot be empty or negative.\n";
        return;
    }
    for (char ch : code) {
        if (!isupper(ch) && !isdigit(ch)) {
            cout << "\n Course code must contain only uppercase letters and digits.\n";
            return;
        }
    }
    if (findCourse(code)) {
        cout << "\n Course already exists.\n";
        return;
    }

    course c(code, name, total, seats);
    courses.push_back(c);
    saveCourses();
    cout<<"Course added succesfully";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deleteStudent(){
    string requiredID;
    cout<<"Enter id to delete :";
    cin>>requiredID;
    ifstream in("student.txt");
    ofstream out("temp.txt");
    
    string id,fullline; // fullline store all data of student in string 
     bool found=false;

     while(getline(in,fullline)){
      size_t commaPos = fullline.find(',');
      id = fullline.substr(0, commaPos);

      if(id != requiredID){
        out<<fullline<<endl;
      }else{
        found = true;
      }
     }

     in.close();
     out.close();

     remove("student.txt");
     rename("temp.txt","student.txt");

     if(found){
        cout<<"student deleted"<<endl;
     }else{
        cout<<"student ID not found"<<endl;
     }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deleteCourse(){
  string targetCode;
  cout << "Enter course code to delete: ";
  cin >> targetCode;
    ifstream in("course.txt");
    ofstream out("temp.txt");

    string code,name;
    int total,seats;

    while(in >> code){
        getline(in,name,',');
        in>>total>>seats;
        if(code != targetCode){
            out<< code <<","<< name <<","<< total <<","<< seats <<endl;
        }
    }

      in.close();
      out.close();
      remove("course.txt");
      rename("temp.txt","course.txt");
      cout<<"Course deleted"<<endl;
        
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void viewAllCourses(){
  ifstream in("course.txt");
  string name,code;
  int total ,seats;

  cout<<"All Courses list"<<endl;

  while(in >> code){
    getline(in, name ,',');
    in>>total>>seats;
    cout<< code <<","<< name <<","<< total <<","<< seats<<endl;
  }
  in.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void registerStudentToCourse() {
    string id, code;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter course code: ";
    cin >> code;
    student* s = findStudent(id);
    course* c = findCourse(code);
    if (!s || !c) {
        cout << "Invalid student ID or course code.\n";
        return;
    }
    if (s->isRegistered(code)) {
        cout << "Already registered.\n";
        return;
    }
    if (c->availableSeats <= 0) {
        cout << "No seats available.\n";
        return;
    }
    s->registerCourses(code);
    c->availableSeats--;
    saveStudents();
    saveCourses();
    cout << "Registration successful.\n";
}

void dropStudentFromCourse() {
    string id, code;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter course code: ";
    cin >> code;
    student* s = findStudent(id);
    course* c = findCourse(code);
    if (!s || !c) {
        cout << "Invalid student ID or course code.\n";
        return;
    }
    if (!s->isRegistered(code)) {
        cout << "Student not registered in this course.\n";
        return;
    }
    s->dropCourses(code);
    c->availableSeats++;
    saveStudents();
    saveCourses();
    cout << "Dropped successfully.\n";
}

void searchStudent() {
    string key;
    cout << "Enter student name or ID to search: ";
    cin >> key;
    bool found = false;
    for (auto& s : students) {
        if (s.studentID == key || s.name == key) {
            cout << "Found: " << s.studentID << " - " << s.name << endl;
            s.viewRegisteredCourses();
            found = true;
        }
    }
    if (!found) cout << "No matching student found.\n";
}

void searchCourse() {
    string key;
    cout << "Enter course name or code to search: ";
    cin.ignore();
    getline(cin, key);
    bool found = false;
    for (auto& c : courses) {
        if (c.courseCode == key || c.courseName == key) {
            cout << "Found: " << c.courseCode << " - " << c.courseName
                 << " | Total: " << c.totalseats
                 << " | Available: " << c.availableSeats << endl;
            found = true;
        }
    }
    if (!found) cout << "No matching course found.\n";
}


void sortStudentsByName() {
    sort(students.begin(), students.end(), [](student& a, student& b) {
        return a.name < b.name;
    });
    cout << "Students sorted by name.\n";
}

void sortCoursesByName() {
    sort(courses.begin(), courses.end(), [](course& a, course& b) {
        return a.courseName < b.courseName;
    });
    cout << "Courses sorted by name.\n";
}


void exportToCSV() {
    ofstream out("registrations.csv");
    out << "StudentID,StudentName,CourseCode\n";
    for (auto& s : students) {
        for (auto& c : s.registeredCourse) {
            out << s.studentID << "," << s.name << "," << c << "\n";
        }
    }
    out.close();
    cout << "Exported to registrations.csv\n";
}

// MENU
void menu() {
    loadStudents();
    loadCourses();
    int choice;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Add Student\n2. Add Course\n3. Delete Student\n4. Delete Course\n";
        cout << "5. View All Courses\n6. Register Student to Course\n7. Drop Student from Course\n";
        cout << "8. Export Registrations to CSV\n";
        cout << "9. Search Student\n10. Search Course\n";
        cout << "11. Sort Students\n12. Sort Courses\n";
        cout << "13. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: addCourse(); break;
            case 3: deleteStudent(); break;
            case 4: deleteCourse(); break;
            case 5: viewAllCourses(); break;
            case 6: registerStudentToCourse(); break;
            case 7: dropStudentFromCourse(); break;
            case 8: exportToCSV(); break;
            case 9: searchStudent(); break;
            case 10: searchCourse(); break;
            case 11: sortStudentsByName(); break;
            case 12: sortCoursesByName(); break;
            case 13: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 13);
}

int main() {
    menu();
    return 0;
}
