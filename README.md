# 🎓 Course Registration System  
**Team:** Ice Breakers  
**Project Topic:** Course Registration System

---

## 📘 Project Overview

Course Registration System is a C++ console-based application that allows students to register and manage their course enrollments easily. The system uses a menu-driven interface and stores all data persistently using file handling.

---

## 🚀 Features

### 👨‍🎓 Student Management
- **Add Student:** Register students using a unique ID and name.
- **Delete Student:** Remove students from the system.
- **Search Student:** Find a student using name or ID.
- **View Registered Courses:** Display the list of courses a student is enrolled in.

### 📚 Course Management
- **Add Course:** Add new courses with course code, name, total seats, and available seats.
- **Delete Course:** Remove a course using the course code.
- **View All Courses:** Display all courses with current seat availability.
- **Search Course:** Search by course code or name.

### ✅ Course Registration
- **Register to Course:** Enroll a student into a course (if seats are available).
- **Drop from Course:** Allow students to drop a course.
- **Prevent Duplicates:** Ensures students cannot register twice for the same course.
- **Seat Limit Handling:** Prevents overbooking of courses.

### 🧾 Sorting & Export
- **Sort Students:** Alphabetically by name.
- **Sort Courses:** Alphabetically by course name.
- **Export Data:** Save all registrations to a `registrations.csv` file.

### 💾 Data Handling
- **Persistent Storage:**  
  - Students → `students.txt`  
  - Courses → `courses.txt`  
  - Registrations → `registrations.csv`
- **Input Validation:**  
  - Non-empty fields
  - - Valid course code format  
  - No duplicate student ID or course code  
  - Valid seat numbers

---

## 📋 Usage

1. **Compile** the program in any C++ IDE (VS Code, Code::Blocks, etc.).
2. **Run** the executable.
3. Use the interactive menu to:
   - Add/Delete Students or Courses
   - Register/Drop Courses
   - Sort or Search Data
   - Export registrations to CSV
4. Data is automatically saved in text files and updated after each operation.
  
