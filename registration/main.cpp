#include <iostream>
#include <fstream>
#include <functional>
#include <string>

using namespace std;

string hashPassword(const string &password) {
    return to_string(hash<string>{}(password));
}

class Person {
protected:
    char email[50];
    char password[50];

public:
    Person() {}
};

class Registration : public Person {
public:
    void registerUser() {
        fstream logindata("logindata.txt", ios::out | ios::app);
        if (!logindata.is_open()) {
            cout << "ERROR OPENING THE FILE !!\n";
            return;
        }
        cout << "ENTER YOUR EMAIL: ";
        cin.ignore(); 
        cin.getline(email, 50);
        cout << "ENTER YOUR PASSWORD: ";
        cin.getline(password, 50);
        string hashedPassword = hashPassword(password);
        logindata << email << "\n";
        logindata << hashedPassword << "\n";
        logindata.close();
        cout << "Registration successful!" << endl;
    }

    void loginUser() {
        char email[50], password[50];
        string temp_email, temp_password;

        cout << "ENTER YOUR EMAIL: ";
        cin.ignore(); 
        cin.getline(email, 50);
        cout << "ENTER YOUR PASSWORD: ";
        cin.getline(password, 50);

        string hashedPassword = hashPassword(password);

        ifstream file("logindata.txt");
        bool found = false;
        if (file.is_open()) {
            while (getline(file, temp_email) && getline(file, temp_password)) {
                if (temp_email == email && temp_password == hashedPassword) {
                    found = true;
                    break;
                }
            }
            file.close();
        } else {
            cout << "Unable to open file for reading!" << endl;
            return;
        }

        if (found) {
            cout << "Login successful!" << endl;
        } else {
            cout << "Invalid email or password!" << endl;
        }
    }
};

int main() {
    Registration reg;
    int choice;

    do {
        cout << "================ Registration System ======================\n";
        cout << "\t\t1. Create an account\n";
        cout << "===========================================================\n";
        cout << "\t\t2. Login\n";
        cout << "===========================================================\n";
        cout << "\t\t3. Exit\n";
        cout << "===========================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                reg.registerUser();
                break;
            case 2:
                reg.loginUser();
                break;
            case 3:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
