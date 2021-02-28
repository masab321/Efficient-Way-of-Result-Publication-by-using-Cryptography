/**
    author: masab hasnain
    time: 22:9:23
    date: 2:1:2021

**/


/* CSV file format for result entries:
 * email, program, name, id, enrollment, batch, semester, course_code, grade, course_code,credit, grade..
 */


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

class crs{
public:
    string cr_code;
    int cr_credit;
    double cr_grade;
    crs(string course_name, int course_credit, double course_grade){
        cr_code = course_name;
        cr_credit = course_credit; 
        cr_grade = course_grade;
    }
};


class student{
private:
    vector<crs> course;
    int batch, course_counter ;
    string email, program, name, id, enrollment, semester;

public:
    student(){
        program = "B.Sc in Computer Science and Engineering";
        enrollment = "summer 2017";
        semester = enrollment;
    }



    string random_course_code(){
        vector<string> course_code = {"cse221", "cse112", "cse312", "cse415", "ged122", "mat122", "mat211", "mat111", "ged123"};
        return course_code[rand() % int(course_code.size())];
    }

    double random_grade(){
        return double(rand() % 2 + 2) + (double(rand() % 100) + 3) / 100.0; 
    }

    int random_credit(){
        vector<int> cr = {3, 3, 1, 3};
        return cr[rand() % 4];
    }

    void random_student(){
        cout << "Enter email: ";
        cin >> email;

        cout << "Enter name: ";
        ws(cin);
        getline(cin, name);

        cout << "Enter student ID: ";
        cin >> id;

        batch = 47;
        int n = rand() % 2 + 3;
        for(int i = 0; i < n; i++){
            course.push_back(crs(random_course_code(),random_credit(), random_grade()));
        }
        
    }


    void display_student(){
        cout << "********Student Details**********" << endl;
        cout << "Email: " << email << endl;
        cout << "Program: " << program << endl;
        cout << "Name: " << name << endl;
        cout << "Student ID: " << id << endl;
        cout << "Enrollment: " << enrollment << endl;
        cout << "Batch: " << batch << endl;
        cout << "Semester: " << semester << endl;

        cout << "Course code   Grade" << endl;
        cout << "___________________" << endl;

        for(auto i: course){
            cout << i.cr_code << "        " << i.cr_credit << "       " << i.cr_grade << endl;
        }
    }

    void write_in_csv(string file_name){
        ofstream fout(file_name, ios_base::app);
        fout << email << ", " << program << ", " << name << ", " << id << ", " << enrollment << ", ";
        fout << batch << ", " << semester << ", ";
        for (auto i : course){
            fout << i.cr_code << ", " << i.cr_credit << ", " << i.cr_grade << ", ";
        }
        fout << endl;
    }
};

/*
 int main(){
    
     vector<student> st;
     srand(time(0));
     while(true){
         cout << " **** MENU ****" << endl;
         int op;
         cout << "1. Add Real Student" << endl;
         cout << "2. Random Student" << endl;
         cout << "3. Main Menu" << endl;
         cout << "4. Exit" << endl;
         cout << "Enter : " << endl;
         cin >> op;
         if(op == 1){
             student cur = student();
             cur.display_student();

             int ok = 0;
             cout << "1. Write in csv file" << endl; 
             cout << "2. Main Menu" << endl;
             cout << "Enter : ";
             cin >> ok;

             if(ok == 1){
                 st.push_back(cur);
                 cur.write_in_csv("raw_data.txt");
             }
         }else if(op == 2){
             student cur = student();
             cur.random_student();
             cur.display_student();

             int ok = 0;
             cout << "1. Write in csv file" << endl; 
             cout << "2. Main Menu" << endl;
             cout << "Enter : ";
             cin >> ok;

             if(ok == 1){
                 st.push_back(cur);
                 cur.write_in_csv("raw_data.txt");
             }
         }else if(op == 4) break;

     }
 }
 */













