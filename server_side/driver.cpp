// g++ -o prog driver.cpp generate_student_entries.cpp crypto.cpp mail.cpp -lthemis -lsoter -lPocoFoundation -lPocoNet  -lPocoNetSSL -lPocoUtil && ./prog
#include<bits/stdc++.h>
#include"crypto.cpp"
#include"generate_student_entries.cpp"
#include"mail.cpp"

using namespace std;

student st;
crypto cr;
mail ml;

string csv_file = "input.csv";
string enc_file_with_mail = "encrypted_mail.txt";
string enc_file_with_id = "encrypted_id.txt";


void sub_menu_add(){
    cout << "******** Create New Result entry ********" << endl;
    cout << "1. Add Student"<< endl;
    cout << "0. Main Menu" << endl;
    cout << "Enter choice: ";
    string c; cin >> c;
    if(c == "1"){
        st.random_student();
        st.display_student();

        cout << "1. Save" << endl; 
        cout << "2. Cancel" << endl;
        cout << "Enter: ";
        string ch;
        cin >> ch;
        if(ch == "1"){
            st.write_in_csv(csv_file);
            cout << "Saved.\n\n\n" << endl;
        }
        sub_menu_add();
    }else{
        return;
    }
}

void sub_menu_encrypt(){
    ifstream fin(csv_file);
    ofstream fout_mail(enc_file_with_mail);
    ofstream fout_id(enc_file_with_id);
    string line;
    cout << "Enter Password for encryption: ";
    string pass; cin >> pass;
    while(getline(fin, line)){
        vector<string> val;
        string cur = "";
        for(int i = 0; i < line.size(); i++){
            if(line[i] == ','){
                val.push_back(cur);
                cur = "";
            }else{
                cur += line[i];
            }
        }
        string email = val[0];
        string id = val[3];
        string enc = cr.encrypt(pass, line);

        fout_mail << email << " " << enc << endl;
        fout_id << id << " " << enc << endl;
    }
    cout << "Encryption done.\n\n\n" << endl;
}

void sub_menu_mail(){
    string email, pass, rcv_email, res, line;
    cout << "Enter sender email Adrress: "; cin >> email;
    cout << "Enter sender password: "; cin >> password;
    ifstream fin(enc_file_with_mail);
    ml.set_sender_email(email);
    ml.set_subject("Result");
    ml.set_sender_password(pass);
    ml.start_session();
    while(getline(fin, line)){
        stringstream ss(line);
        ss >> rcv_email;
        ss >> res;
        
        ml.set_recipient(rcv_email);
        ml.set_content(res);
        ml.send();
    }

    ml.stop_session();
    cout << "All results sent successfully\n\n\n" << endl;

}

void sub_menu_server(){

}

void main_menu(){
    cout << "******** Main Menu ********" << endl;
    string ch;
    cout << "1. Create New Result Entry" << endl;
    cout << "2. Encrypt Strored Result" << endl;
    cout << "3. Send Result to Students" << endl;
    cout << "4. Start Server" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter: ";
    cin >> ch;
    
    if(ch == "1") sub_menu_add();
    else if(ch == "2") sub_menu_encrypt();
    else if(ch == "3") sub_menu_mail();
    else if(ch == "4") sub_menu_server();
    else return;
    main_menu();
}


int main(){
    main_menu();
}
