
/*
 Aadiba Haque
 Rec 06
 Models how NYU Tandon CS Lab instructors keep up with grades.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Section {
    friend ostream& operator<<(ostream& os, const Section& section);
public:
    Section(const string& name, const string& day, unsigned time) :
        name(name), timeSlot(day,time){}
    Section(const Section& rhs) : name(rhs.name), timeSlot(rhs.timeSlot) {
        for (size_t i = 0; i < rhs.vectorOfRecords.size(); ++i) {
            vectorOfRecords.emplace_back(new StudentRecord(
                *rhs.vectorOfRecords[i]));
        } 
        
    }
    class TimeSlot {    
        friend ostream& operator<<(ostream& os, const TimeSlot& timeSlot) {
            os << "Time slot: [Day: " + timeSlot.day + ", Start time: ";
            if (timeSlot.time == 0) {
                os << 12 << "am], ";
            } else if (timeSlot.time <= 12) {
                os << timeSlot.time << "am], ";
            } else {
                os << timeSlot.time - 12 << "pm], ";
            }
            return os;
        }
    public:
        TimeSlot(const string& day, unsigned time) : day(day), time(time) {}
    private:
        string day;
        unsigned time;
    };
    class StudentRecord {
        friend ostream& operator<<(ostream& os,
            const StudentRecord& studentRecord) {
            os << studentRecord.name + ", Grades: ";
            for (size_t i = 0; i < studentRecord.studentGrades.size(); ++i) {
                os << studentRecord.studentGrades[i] << ' ';
            }
            os << endl;
            return os;
        } 
    public:
        StudentRecord(const string& studentName) : name(studentName) {}
        string getName() const { return name; }
        void addGrade(int week, int grade) {
            studentGrades[week-1] = grade;
        }
    private:
        string name;
        vector<int> studentGrades{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
    };
    void addGrades(const string& studentName, int grade, int week) {
        for (size_t i = 0; i < vectorOfRecords.size(); ++i) {
            if (studentName == vectorOfRecords[i]->getName()) {
                vectorOfRecords[i]->addGrade(week, grade);
            }
        }
    }
    void addStudent(const string& studentName) {
        vectorOfRecords.push_back(new StudentRecord(studentName));
    }
    ~Section() {
        cout << "Section " + name << " is being deleted" << endl;
        for (size_t i = 0; i < vectorOfRecords.size(); ++i) {
            cout << "Deleting " << vectorOfRecords[i]->getName() << endl;
            delete vectorOfRecords[i];
        }
    }
    void reset(Section section) {
        for (size_t i = 0; i < section.vectorOfRecords.size(); ++i) {
            cout << "Deleting " << section.vectorOfRecords[i]->getName()
                << endl;
            delete vectorOfRecords[i];
            vectorOfRecords[i] = nullptr;
        }
        vectorOfRecords.clear();
    }
    
private:
    string name;
    TimeSlot timeSlot;
    vector<StudentRecord*> vectorOfRecords;
};


class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& labWorker);
public:
    LabWorker(const string& name) : name(name) {}
    void addSection(Section& section) {
        sectionPtr = &section;
    }
    void addGrade(const string& studentName, int grade, int week) {
        if (sectionPtr) {
            sectionPtr->addGrades(studentName, grade, week);
        }
    }
private:
    Section* sectionPtr = nullptr;
    string name;
};






// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");  
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
        << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
        << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main

ostream& operator<<(ostream& os, const LabWorker& labWorker)
{
    if (labWorker.sectionPtr) {
        os << labWorker.name + " has " << *labWorker.sectionPtr;
    } else {
        os << labWorker.name + " does not have a section";
    }
    return os;
}

ostream& operator<<(ostream& os, const Section& section)
{
    os << "Section: " << section.name + ", " << section.timeSlot 
        << "Students:";
    if (section.vectorOfRecords.size() != 0) {
        os << endl;
        for (int i = 0; i < section.vectorOfRecords.size(); ++i) {
            os << "Name: " << *section.vectorOfRecords[i];
        }
    } else {
        os << " None";
    }
    return os;
 }
