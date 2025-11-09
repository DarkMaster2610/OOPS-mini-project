#include <iostream>
using namespace std;

// -------------------- CLASS : Classroom --------------------
class Classroom {
private:
    string className;
    string subject;
    int students;
    int rows, cols;
    int roomNo;

public:
    Classroom() {
        className = "";
        subject = "";
        students = 0;
        rows = 0;
        cols = 0;
        roomNo = 0;
    }

    void inputDetails() {
        cout << "\nEnter Room No: ";
        cin >> roomNo;
        cout << "Enter Class Name: ";
        cin >> className;
        cout << "Enter Subject: ";
        cin >> subject;
        cout << "Enter Room Rows: ";
        cin >> rows;
        cout << "Enter Room Columns: ";
        cin >> cols;
    }

    int getCapacity() const {
        return rows * cols;
    }

    string getClassName() const { return className; }
    string getSubject() const { return subject; }
    int getRoomNo() const { return roomNo; }

    void displaySeating(int startRoll, int remaining) const {
        cout << "\n--- Room " << roomNo << " | Class: " << className 
             << " | Subject: " << subject << " ---\n";
        cout << "-------------------------------------------\n";
        int totalSeats = rows * cols;

        char rowLetter = 'A';
        int seatCount = 1;
        int rollNo = startRoll;

        for (int i = 0; i < rows && remaining > 0; i++) {
            for (int j = 0; j < cols && remaining > 0; j++) {
                cout << rowLetter << j + 1 << "(" << rollNo << ")\t";
                rollNo++;
                seatCount++;
                remaining--;
            }
            rowLetter++;
            cout << endl;
        }
    }
};

// -------------------- CLASS : ExamHall --------------------
class ExamHall {
private:
    Classroom rooms[10]; // up to 10 rooms
    int roomCount;
    int totalStudents;
    string className;
    string subject;

public:
    ExamHall() {
        roomCount = 0;
        totalStudents = 0;
        className = "";
        subject = "";
    }

    void addRoom() {
        if (roomCount >= 10) {
            cout << "Room limit reached!\n";
            return;
        }
        rooms[roomCount].inputDetails();
        roomCount++;
    }

    void inputClassDetails() {
        cout << "\nEnter Class Name: ";
        cin >> className;
        cout << "Enter Subject: ";
        cin >> subject;
        cout << "Enter Total Number of Students: ";
        cin >> totalStudents;
    }

    void allotSeats() {
        if (roomCount == 0 || totalStudents == 0) {
            cout << "\nAlert! Add rooms and students first!\n";
            return;
        }

        cout << "\n===== SEATING ARRANGEMENT =====\n";
        int remaining = totalStudents;
        int rollNo = 1;

        for (int i = 0; i < roomCount && remaining > 0; i++) {
            int capacity = rooms[i].getCapacity();
            int allotNow = (remaining > capacity) ? capacity : remaining;
            rooms[i].displaySeating(rollNo, allotNow);
            rollNo += allotNow;
            remaining -= allotNow;
        }

        if (remaining > 0)
            cout << "\n Still " << remaining << " students without seats!\n";
        else
            cout << "\n All students allotted successfully!\n";
    }
};

// -------------------- MAIN FUNCTION --------------------
int main() {
    ExamHall exam;
    int choice;

    cout << "===== EXAM SEATING ARRANGEMENT GENERATOR =====\n";

    do {
        cout << "\n1. Add Room";
        cout << "\n2. Enter Class & Students";
        cout << "\n3. Allot Seats";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                exam.addRoom();
                break;
            case 2:
                exam.inputClassDetails();
                break;
            case 3:
                exam.allotSeats();
                break;
            case 4:
                cout << "Exiting... All the best for your exams!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
