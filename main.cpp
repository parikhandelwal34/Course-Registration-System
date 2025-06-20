#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class student{
public:
    string name;
    string studentID;
    string registeredCourse;

    student(string id, string n, string course){
        studentID = id;
        name = n;
        registeredCourse = course;
    } 
};

///////////////////////////////////////////////////////////////////////////////////////////

class course{
public:
   string courseName;
   int totalseats;
   int seatsRemaining;
   string courseCode;

   course(string code, string name, int total,int seats){
       courseName = name;
       courseCode = code;
       totalseats = seats;
       seatsRemaining = total;
   }
};
///////////////////////////////////////////////////////////////////////////////

void addStudent(){
    string id,n,course;
    cin.ignore();
    cout<<"Enter your name : ";
    getline(cin,n);

    cout<<"Enter your ID : ";
    cin>>id;

    cout<<"Enter your course : ";
    cin>>course;

     ofstream out("student.txt",ios::app);
      out<< n << "," << id << "," << course <<endl;
      out.close();
     
     
    cout<<"Student added successfully";
}
/////////////////////////////////////////////////////////////////////////////////

void addCourse(){
    string code,name;
    int total,seats;
    
    cin.ignore();
    cout<<"Enter course name : ";
    getline(cin,name);

    cout<<"Enter course code : ";
    cin>>code;

    cout<<"Enter total seats : ";
    cin>>seats;

    cout<<"Enter seats remaining : ";
    cin>>total;

    ofstream out("course.txt",ios::app);
     out<< name << "," << code << "," << seats << "," << total <<endl;
    out.close();

    cout<<"Course added succesfully";
}

////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////

void deleteCourse(){
  string targetCode;
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

////////////////////////////////////////////////////////////////////////////////////////////////////


void viewAllCourses(){
  ifstream in("course.txt");
  string name,code;
  int total ,seats;

  cout<<"All Courses list"<<endl;

  while(in >> code){
    getline(in, name ,',');
    in>>total>>seats;
    cout<< code <<","<< name <<","<< total <<","<< seats;
  }
  in.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////
int main(){
  int choice;
    while(true){
      cout<<"COURSE REGISTRATION SYSTEM"<<endl;
      cout<<"1. Add Student"<<endl;
      cout<<"2. Add Course"<<endl;
      cout<<"3. Delete Student"<<endl;
      cout<<"4. Delete Course"<<endl;
      cout<<"5. View AllCourse"<<endl;
      cout<<"6. Exit"<<endl;
      cout<<"Enter your choice(1-6)";

      cin>>choice;


     if(choice == 1){
      addStudent();
     } else if(choice == 2){
      addCourse();
     }else if(choice == 3){
      deleteStudent();
     }else if(choice == 4){
      deleteCourse();
     }else if(choice == 5){
      viewAllCourses();
     }else if(choice == 6){
      cout<<"Exiting Program."<<endl;
      break;
     }
     else{
      cout<<"Invalid Choice . Please enter choice between 1-6"<<endl;
     }
    }
     
return 0;
}
