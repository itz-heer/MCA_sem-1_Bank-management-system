#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>



using namespace std;

// ANSI color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string BOLD = "\033[1m";
const string UNDERLINE = "\033[4m";


struct Manager {
    string fullName;
    string dob;
    string gender;
    string address;
    string phoneNumber;
    string email;
    string password;
};

map<string, Manager> managers; // Store manager accounts

// Structure to represent the Employee's account and information

struct Employee {
    string name;
    string gender;
    string dob;
    string phoneNumber;
    string email;
    string address;
    string username;
    string password;
};

map<string, Employee> employees; // Map to store employees


// Structure to represent the user's account and information
struct User {
    string fullName;
    string address;
    string phoneNumber;
    string dob;
    string education;
    string job;
    string accountType;
    string password;
    int accountNumber;
    double balance;
    vector<string> transactions;
    vector<string> notifications; //  field for notifications

};



map<string, User> users;  // Map to store user accounts

struct LoanRequest {
    string username;
    double amount;
    double duration; // In years
    double interestRate;
    string loanType;
    string status; // "Pending", "Approved", "Rejected"
};

vector<LoanRequest> loanRequests; // Store loan requests

// Function prototypes
void mainMenu();
void adminMenu();
void createManager();
void managerMenu();
void saveEmployees();
void deleteEmployee();
void downloadEmployeeDetails();
void searchEmployeeDetails();
void loadEmployees();
void createEmployee();
void viewAllEmployees();
void viewAllManagers();
void employeeMenu();
void userMenu(string username);
void createUser();
void deleteUser();
void viewAllUsers();
void depositMoney();
void withdrawMoney();
void userLogin();
void viewBalance(string username);
void viewLastTransactions(string username);
void transferMoney(string username);
void downloadStatement(string username);
void viewUserInformation() ;
void downloadUserInformation();
void loanDepartment(string username);
void viewNotifications(string username);
void approveLoanRequests();
void saveUsers();
void loadUsers();
void loadManagers();
void saveManagers();
void printHeader(const string &title, const string &color = CYAN);
void printMenuOption(const string &option, int number);

// Main function
int main() {
    loadUsers();      // Load user data
    loadManagers();// Load manager data
    loadEmployees();
    mainMenu();       // Launch the main menu
    saveUsers();      // Save user data
    saveManagers(); // Save manager data
    saveEmployees();
    return 0;
}





void printHeader(const string &title, const string &color) {
    const int consoleWidth = 80; // Adjust this value to match your console width
    int padding = (consoleWidth - title.length()) / 2;

    cout << color;
    cout << string(consoleWidth, '-') << "\n"; // Top border
    cout << string(padding, ' ') << BOLD << title << RESET << "\n"; // Centered title
    cout << string(consoleWidth, '-') << RESET << "\n"; // Bottom border
}

// Print a menu option with a consistent style
void printMenuOption(const string &option, int number) {
    cout << YELLOW << number << ". " << RESET << option << "\n";
}
// Main menu
void mainMenu() {
    int choice;
    do {
        printHeader("WELCOME TO BANK MANAGEMENT SYSTEM", GREEN);
        printMenuOption("Admin Login", 1); // Shift others down by 1
        printMenuOption("Manager Login", 2);
        printMenuOption("Employee Login", 3);
        printMenuOption("User Login", 4);
        printMenuOption("Exit", 5);
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                managerMenu();
                break;
            case 3:
                employeeMenu();
                break;
            case 4:
                userLogin();
                break;
            case 5:
                cout << GREEN << "Exiting system. Goodbye!\n" << RESET;
                break;
            default:
                cout << RED << "Invalid option. Try again.\n" << RESET;
        }
    } while (choice != 5);
}

void adminMenu() {
    string adminPassword = "superadmin123"; // Example password
    string password;

    printHeader("ADMIN LOGIN", RED);
    cout << "Enter Admin password:";
    cin >> password;

    if (password != adminPassword) {
        cout << RED << "Invalid password. Returning to main menu.\n" << RESET;
        return;
    }

    int choice;
    do {
        printHeader("ADMIN MENU", CYAN);
        printMenuOption("Create Manager", 1);
        printMenuOption("View All Managers", 2);
        printMenuOption("Logout", 3);
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createManager();
                break;
            case 2:
                viewAllManagers();
                break;
            case 3:
                cout << GREEN << "Logging out...\n" << RESET;
                break;
            default:
                cout << RED << "Invalid option. Try again.\n" << RESET;
        }
    } while (choice != 3);
}

bool isValidEmail(const string &email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);

    return atPos != string::npos && dotPos != string::npos && dotPos > atPos + 1 && dotPos < email.length() - 1;
}

void createManager() {
    string username, fullName, dob, gender, address, phoneNumber, email, password;

    printHeader("CREATE MANAGER", CYAN);

    // Username validation
    do {
        cout << "Enter a username for the Manager (alphanumeric only): ";
        cin >> username;
        if (managers.count(username)) {
            cout << RED << "Username already exists. Please choose another.\n" << RESET;
            username.clear();
        } else if (username.empty() || !all_of(username.begin(), username.end(), [](char c) { return isalnum(c); })) {
            cout << RED << "Invalid username. Use alphanumeric characters only.\n" << RESET;
            username.clear();
        }
    } while (username.empty());

    // Full Name validation
    do {
        cout << "Enter full name (letters only): ";
        cin.ignore();
        getline(cin, fullName);
        if (fullName.empty() || !all_of(fullName.begin(), fullName.end(), [](char c) { return isalpha(c) || isspace(c); })) {
            cout << RED << "Invalid full name. Use letters and spaces only.\n" << RESET;
            fullName.clear();
        }
    } while (fullName.empty());

    // DOB validation
    do {
        cout << "Enter date of birth (DD/MM/YYYY): ";
        cin >> dob;
        if (dob.length() != 10 || dob[2] != '/' || dob[5] != '/' ||
            !isdigit(dob[0]) || !isdigit(dob[1]) || !isdigit(dob[3]) || !isdigit(dob[4]) ||
            !isdigit(dob[6]) || !isdigit(dob[7]) || !isdigit(dob[8]) || !isdigit(dob[9])) {
            cout << RED << "Invalid date of birth. Use format DD/MM/YYYY.\n" << RESET;
            dob.clear();
        }
    } while (dob.empty());

    // Gender validation
    do {
        cout << "Enter gender (Male/Female/Other): ";
        cin >> gender;
        if (gender != "Male" && gender != "Female" && gender != "Other") {
            cout << RED << "Invalid gender. Please enter 'Male', 'Female', or 'Other'.\n" << RESET;
            gender.clear();
        }
    } while (gender.empty());

    // Address validation
    do {
        cout << "Enter address: ";
        cin.ignore();
        getline(cin, address);
        if (address.empty()) {
            cout << RED << "Address cannot be empty.\n" << RESET;
        }
    } while (address.empty());

    // Phone Number validation
    do {
        cout << "Enter phone number (10 digits): ";
        cin >> phoneNumber;
        if (phoneNumber.length() != 10 || !all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit)) {
            cout << RED << "Invalid phone number. Must be exactly 10 digits.\n" << RESET;
            phoneNumber.clear();
        }
    } while (phoneNumber.empty());

    // Email validation
    do {
        cout << "Enter email: ";
        cin >> email;
        if (!isValidEmail(email)) {
            cout << RED << "Invalid email format.\n" << RESET;
            email.clear();
        }
    } while (email.empty());

    // Password validation
    do {
        cout << "Enter password (at least 6 characters, including one number): ";
        cin >> password;
        if (password.length() < 6 || none_of(password.begin(), password.end(), ::isdigit)) {
            cout << RED << "Invalid password. It must be at least 6 characters long and include at least one number.\n" << RESET;
            password.clear();
        }
    } while (password.empty());

    // Save the new manager
    managers[username] = {fullName, dob, gender, address, phoneNumber, email, password};
    saveManagers(); // Save managers after creation
    cout << GREEN << "Manager created successfully!\n" << RESET;
}


void viewAllManagers() {
    printHeader("ALL MANAGERS", CYAN);

    if (managers.empty()) {
        cout << RED << "No managers found.\n" << RESET;
        return;
    }

    // Print table header
    cout << setw(15) << left << "Username"
         << setw(25) << "Full Name"
         << setw(15) << "DOB"
         << setw(10) << "Gender"
         << setw(20) << "Phone"
         << setw(30) << "Email"
         << "\n";
    cout << string(115, '-') << "\n";

    // Print details of each manager
    for (const auto &entry : managers) {
        const Manager &m = entry.second;
        cout << setw(15) << left << entry.first
             << setw(25) << m.fullName
             << setw(15) << m.dob
             << setw(10) << m.gender
             << setw(20) << m.phoneNumber
             << setw(30) << m.email
             << "\n";
    }

    cout << string(115, '-') << "\n";
}



// Manager functions
void managerMenu() {
    string username, password;

    printHeader("MANAGER LOGIN", BLUE);
    cout << "Enter username: ";
    cin >> username;

    if (!managers.count(username)) {
        cout << RED << "Manager not found. Returning to main menu.\n" << RESET;
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    if (managers[username].password != password) {
        cout << RED << "Invalid password. Returning to main menu.\n" << RESET;
        return;
    }

    cout << GREEN << "Login successful! Welcome, " << managers[username].fullName << ".\n" << RESET;

    int choice;
    do {
        printHeader("MANAGER MENU", CYAN);

        printMenuOption("Add Employee", 1);
        printMenuOption("View All Employees", 2);
        printMenuOption("Search Employee Details", 3); // New option
        printMenuOption("Download Employee Details", 4); // New option
        printMenuOption("Delete Employee", 5);
        printMenuOption("Approve Loan Requests", 6); // New option
        printMenuOption("Logout", 7);
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createEmployee();
                break;
            case 2:
                viewAllEmployees();
                break;
            case 3:
                searchEmployeeDetails(); // Call the new function
                break;
            case 4:
                downloadEmployeeDetails(); // Call the new function
                break;
            case 5:
                deleteEmployee();
                break;
            case 6:
                approveLoanRequests();

            case 7:
                cout << GREEN << "Logging out...\n" << RESET;
                break;
            default:
                cout << RED << "Invalid option. Try again.\n" << RESET;
        }
    } while (choice != 7);
}


void createEmployee() {
    string username, name, gender, dob, phoneNumber, email, address, password;

    printHeader("CREATE EMPLOYEE", CYAN);

    // Username validation
    do {
        cout << "Enter a username for the Employee (alphanumeric only): ";
        cin >> username;
        if (employees.count(username)) {
            cout << RED << "Username already exists. Please choose another.\n" << RESET;
            username.clear();
        } else if (username.empty() || !all_of(username.begin(), username.end(), [](char c) { return isalnum(c); })) {
            cout << RED << "Invalid username. Use alphanumeric characters only.\n" << RESET;
            username.clear();
        }
    } while (username.empty());

    // Full Name validation
    do {
        cout << "Enter full name (letters only): ";
        cin.ignore();
        getline(cin, name);
        if (name.empty() || !all_of(name.begin(), name.end(), [](char c) { return isalpha(c) || isspace(c); })) {
            cout << RED << "Invalid name. Use letters and spaces only.\n" << RESET;
            name.clear();
        }
    } while (name.empty());

    // Gender validation
    do {
        cout << "Enter gender (Male/Female/Other): ";
        cin >> gender;
        if (gender != "Male" && gender != "Female" && gender != "Other") {
            cout << RED << "Invalid gender. Please enter 'Male', 'Female', or 'Other'.\n" << RESET;
            gender.clear();
        }
    } while (gender.empty());

    // DOB validation
    do {
        cout << "Enter date of birth (DD/MM/YYYY): ";
        cin >> dob;
        if (dob.length() != 10 || dob[2] != '/' || dob[5] != '/' ||
            !isdigit(dob[0]) || !isdigit(dob[1]) || !isdigit(dob[3]) || !isdigit(dob[4]) ||
            !isdigit(dob[6]) || !isdigit(dob[7]) || !isdigit(dob[8]) || !isdigit(dob[9])) {
            cout << RED << "Invalid date of birth. Use format DD/MM/YYYY.\n" << RESET;
            dob.clear();
        }
    } while (dob.empty());

    // Phone number validation
    do {
        cout << "Enter phone number (10 digits): ";
        cin >> phoneNumber;
        if (phoneNumber.length() != 10 || !all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit)) {
            cout << RED << "Invalid phone number. Must be exactly 10 digits.\n" << RESET;
            phoneNumber.clear();
        }
    } while (phoneNumber.empty());

    // Email validation
    do {
        cout << "Enter email: ";
        cin >> email;
        if (!isValidEmail(email)) {
            cout << RED << "Invalid email format.\n" << RESET;
            email.clear();
        }
    } while (email.empty());

    // Address validation
    do {
        cout << "Enter address: ";
        cin.ignore();
        getline(cin, address);
        if (address.empty()) {
            cout << RED << "Address cannot be empty.\n" << RESET;
        }
    } while (address.empty());

    // Password validation
    do {
        cout << "Enter password (at least 6 characters, including one number): ";
        cin >> password;
        if (password.length() < 6 || none_of(password.begin(), password.end(), ::isdigit)) {
            cout << RED << "Invalid password. It must be at least 6 characters long and include at least one number.\n" << RESET;
            password.clear();
        }
    } while (password.empty());

    // Save the new employee
    employees[username] = {name, gender, dob, phoneNumber, email, address, username, password};
    saveEmployees(); // Save employees after creation
    cout << GREEN << "Employee created successfully!\n" << RESET;
}

void searchEmployeeDetails() {
    string username;

    printHeader("SEARCH EMPLOYEE DETAILS", CYAN);
    cout << "Enter the username of the employee to search: ";
    cin >> username;

    // Check if the employee exists
    if (!employees.count(username)) {
        cout << RED << "Employee not found.\n" << RESET;
        return;
    }

    // Display employee details
    const Employee &e = employees[username];
    cout << GREEN << "Employee Details:\n" << RESET;
    cout << "Name: " << e.name << "\n";
    cout << "Gender: " << e.gender << "\n";
    cout << "Date of Birth: " << e.dob << "\n";
    cout << "Phone Number: " << e.phoneNumber << "\n";
    cout << "Email: " << e.email << "\n";
    cout << "Address: " << e.address << "\n";
}



void deleteEmployee() {
    string username;

    printHeader("DELETE EMPLOYEE", CYAN);
    cout << "Enter the username of the employee to delete: ";
    cin >> username;

    // Check if the employee exists
    if (!employees.count(username)) {
        cout << RED << "Employee not found.\n" << RESET;
        return;
    }

    // Confirm deletion
    cout << YELLOW << "Are you sure you want to delete employee " << username << "? (yes/no): " << RESET;
    string confirmation;
    cin >> confirmation;
    if (confirmation != "yes") {
        cout << GREEN << "Employee deletion cancelled.\n" << RESET;
        return;
    }

    // Remove employee
    employees.erase(username);
    saveEmployees(); // Save updated data to file
    cout << GREEN << "Employee " << username << " deleted successfully.\n" << RESET;
}



void downloadEmployeeDetails() {
    string username;

    printHeader("DOWNLOAD EMPLOYEE DETAILS", CYAN);
    cout << "Enter the username of the employee to download details: ";
    cin >> username;

    // Check if the employee exists
    if (!employees.count(username)) {
        cout << RED << "Employee not found.\n" << RESET;
        return;
    }

    string filename = username + "_details.txt";
    ofstream file(filename);

    if (!file) {
        cout << RED << "Failed to create file.\n" << RESET;
        return;
    }

    const Employee &e = employees[username];
    file << "Employee Details:\n";
    file << "Name: " << e.name << "\n";
    file << "Gender: " << e.gender << "\n";
    file << "Date of Birth: " << e.dob << "\n";
    file << "Phone Number: " << e.phoneNumber << "\n";
    file << "Email: " << e.email << "\n";
    file << "Address: " << e.address << "\n";

    file.close();
    cout << GREEN << "Employee details downloaded successfully as '" << filename << "'.\n" << RESET;
}

void viewAllEmployees() {
    printHeader("ALL EMPLOYEES", CYAN);

    if (employees.empty()) {
        cout << RED << "No employees found.\n" << RESET;
        return;
    }

    // Print table header
    cout << setw(15) << left << "Username"
         << setw(25) << "Name"
         << setw(15) << "DOB"
         << setw(10) << "Gender"
         << setw(20) << "Phone"
         << setw(30) << "Email"
         << "\n";
    cout << string(115, '-') << "\n";

    // Print details of each employee
    for (const auto &entry : employees) {
        const Employee &e = entry.second;
        cout << setw(15) << left << entry.first
             << setw(25) << e.name
             << setw(15) << e.dob
             << setw(10) << e.gender
             << setw(20) << e.phoneNumber
             << setw(30) << e.email
             << "\n";
    }

    cout << string(115, '-') << "\n";
}


// View user information by username
void viewUserInformation() {
    string username;

    printHeader("VIEW USER INFORMATION", CYAN);
    cout << "Enter username to view information: ";
    cin >> username;

    if (users.count(username) == 0) {
        cout << RED << "User not found.\n" << RESET;
        return;
    }

    // Display user information
    const User &user = users[username];
    cout << "User Information for: " << username << "\n";
    cout << "Full Name: " << user.fullName << "\n";
    cout << "Address: " << user.address << "\n";
    cout << "Phone Number: " << user.phoneNumber << "\n";
    cout << "Date of Birth: " << user.dob << "\n";
    cout << "Education: " << user.education << "\n";
    cout << "Job: " << user.job << "\n";
    cout << "Account Type: " << user.accountType << "\n";
    cout << "Account Number: " << user.accountNumber << "\n";
    cout << "Balance: " << fixed << setprecision(2) << user.balance << "\n";

    // Show recent transactions
    cout << "Recent Transactions: \n";
    if (user.transactions.empty()) {
        cout << "No transactions available.\n";
    } else {
        for (const auto &transaction : user.transactions) {
            cout << transaction << "\n";
        }
    }
}

// Download user information by username
void downloadUserInformation() {
    string username;

    printHeader("DOWNLOAD USER INFORMATION", CYAN);
    cout << "Enter username to download information: ";
    cin >> username;

    if (users.count(username) == 0) {
        cout << RED << "User not found.\n" << RESET;
        return;
    }

    string filename = username + "_information.txt";
    ofstream file(filename);

    if (!file) {
        cout << RED << "Failed to create file.\n" << RESET;
        return;
    }

    const User &user = users[username];
    file << "User Information for: " << username << "\n";
    file << "Full Name: " << user.fullName << "\n";
    file << "Address: " << user.address << "\n";
    file << "Phone Number: " << user.phoneNumber << "\n";
    file << "Date of Birth: " << user.dob << "\n";
    file << "Education: " << user.education << "\n";
    file << "Job: " << user.job << "\n";
    file << "Account Type: " << user.accountType << "\n";
    file << "Account Number: " << user.accountNumber << "\n";
    file << "Balance: " << fixed << setprecision(2) << user.balance << "\n";

    // Write recent transactions to file
    file << "Recent Transactions: \n";
    if (user.transactions.empty()) {
        file << "No transactions available.\n";
    } else {
        for (const auto &transaction : user.transactions) {
            file << transaction << "\n";
        }
    }

    file.close();
    cout << GREEN << "User information downloaded successfully as '" << filename << "'.\n" << RESET;
}


// Employee login and menu
void employeeMenu() {
    string username, password;

    printHeader("EMPLOYEE LOGIN", CYAN);
    cout << "Enter username: ";
    cin >> username;

    // Check if the employee exists
    if (!employees.count(username)) {
        cout << RED << "Employee not found. Returning to main menu.\n" << RESET;
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Validate password
    if (employees[username].password != password) {
        cout << RED << "Invalid password. Returning to main menu.\n" << RESET;
        return;
    }

    cout << GREEN << "Login successful! Welcome, " << employees[username].name << ".\n" << RESET;

    int choice;
    do {
        printHeader("EMPLOYEE MENU", CYAN);
        printMenuOption("Deposit Money", 1);
        printMenuOption("Withdraw Money", 2);
        printMenuOption("Create User", 3);
        printMenuOption("Delete User", 4);
        printMenuOption("View All Users", 5);
        printMenuOption("View User Information", 6);
        printMenuOption("Download User Information", 7);
        printMenuOption("Logout", 8);
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                depositMoney();
                break;
            case 2:
                withdrawMoney();
                break;
            case 3:
                createUser();
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                viewAllUsers();
                break;
            case 6:
                viewUserInformation();
                break;
            case 7:
                downloadUserInformation();
                break;
            case 8:
                cout << GREEN << "Logging out...\n" << RESET;
                break;
            default:
                cout << RED << "Invalid option. Try again.\n" << RESET;
        }
    } while (choice != 8);
}


// User login and menu
void userLogin() {
    string username, password;

    printHeader("USER LOGIN", YELLOW);
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.count(username) && users[username].password == password) {
        cout << GREEN << "Login successful!\n" << RESET;
        userMenu(username);
    } else {
        cout << RED << "Invalid username or password.\n" << RESET;
    }
}

void userMenu(string username) {
    int choice;
    do {
        printHeader("USER MENU", CYAN);
        cout << "Account Number: " << users[username].accountNumber << "\n";
        printMenuOption("View Balance", 1);
        printMenuOption("View Last Transactions", 2);
        printMenuOption("Transfer Money", 3);
        printMenuOption("Loan Department", 4);
        printMenuOption("Download Statement", 5);
        printMenuOption("View Notifications", 6); // New option
        printMenuOption("Logout", 7);
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewBalance(username);
                break;
            case 2:
                viewLastTransactions(username);
                break;
            case 3:
                transferMoney(username);
                break;
            case 4:
                loanDepartment(username);
                break;
            case 5:
                downloadStatement(username); // Call new function
                break;
            case 6:
                viewNotifications(username);
                break;
            case 7:
                cout << GREEN << "Logging out...\n" << RESET;
                break;
            default:
                cout << RED << "Invalid option. Try again.\n" << RESET;
        }
    } while (choice != 7);
}
// Helper function to check if input contains only letters and spaces
bool isAlphaOnly(const string &input) {
    for (char c : input) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

// Function to validate full name (should only contain letters and spaces)
bool isValidFullName(const string &fullName) {
    return !fullName.empty() && isAlphaOnly(fullName);
}

// Function to validate address (should only contain letters and spaces)
bool isValidAddress(const string &address) {
    return !address.empty() && isAlphaOnly(address);
}

bool isValidPhoneNumber(const std::string& phoneNumber) {
    return phoneNumber.length() == 10 && std::all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit);
}


// Function to validate job (should only contain letters and spaces)
bool isValidJob(const string &job) {
    return !job.empty() && isAlphaOnly(job);
}

// Function to validate education (letters and spaces only)
bool isValidEducation(const string& education) {
    return education.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") == string::npos;
}

// Manager functions
void createUser() {
    string username, password, fullName, address, phoneNumber, dob, education, job, accountType;
    double initialDeposit;

    printHeader("CREATE USER ACCOUNT", CYAN);
    cout << "Enter a username (alphanumeric only): ";
    cin >> username;

    cout << "Enter full name (letters only): ";
    cin.ignore(); // To clear any leftover newline character
    getline(cin, fullName);
    if (!isValidFullName(fullName)) {
        cout << RED <<  "Full name can only contain letters and spaces.\n";
        return;
    }

    cout << "Enter address (letters only): ";
    getline(cin, address);
    if (!isValidAddress(address)) {
        cout << RED << "Address can only contain letters and spaces.\n";
        return;
    }

    // Phone number validation
    do {
        cout << "Enter phone number (10 digits): ";
        getline(cin, phoneNumber);

        if (!isValidPhoneNumber(phoneNumber)) {
            cout << RED << "Phone number must be exactly 10 digits.\n";
            phoneNumber.clear(); // Clear the invalid input
        }
    } while (phoneNumber.empty());

    // Date of birth validation
    do {
        cout << "Enter date of birth (DD/MM/YYYY): ";
        getline(cin, dob);

        if (dob.length() != 10 || dob[2] != '/' || dob[5] != '/' ||
            !isdigit(dob[0]) || !isdigit(dob[1]) || !isdigit(dob[3]) || !isdigit(dob[4]) ||
            !isdigit(dob[6]) || !isdigit(dob[7]) || !isdigit(dob[8]) || !isdigit(dob[9])) {
            cout << RED << "Invalid date format. Use DD/MM/YYYY.\n";
            dob.clear();
        }
    } while (dob.empty());

    // Education validation
    cout << "Enter education (letters only): ";
    cin.ignore(); // Clear the input buffer before using getline
    getline(cin, education);

    if (!isValidEducation(education)) {
        cout << "Education can only contain letters and spaces.\n";
        return;
    }

    cout << "Enter job (letters only): ";
    getline(cin, job);
    if (!isValidFullName(job)) {
        cout << "Job can only contain letters and spaces.\n";
        return;
    }

    // Account type validation
    cout << "Enter account type (Saving/Current): ";
    cin >> accountType;
    if (accountType != "Saving" && accountType != "Current") {
        cout << "Invalid account type. Please choose either 'Saving' or 'Current'.\n";
        return;
    }

    // Password validation
    cout << "Enter a password (at least 6 characters and one number): ";
    cin >> password;
    if (password.length() < 6) {
        cout << "Password must be at least 6 characters long.\n";
        return;
    }

    // Initial deposit validation
    cout << "Enter initial deposit (minimum 500): ";
    cin >> initialDeposit;
    if (initialDeposit < 500) {
        cout << "Deposit must be at least 500.\n";
        return;
    }



    int accountNumber = 1001 + users.size();
    users[username] = {fullName, address, phoneNumber, dob, education, job, accountType, password, accountNumber, initialDeposit, {}};
    users[username].transactions.push_back("Account created with deposit: " + to_string(initialDeposit));

    cout << "\033[1;32mUser account created successfully! Account Number: " << accountNumber << ".\n\033[0m";
}

void deleteUser() {
    string username;

    printHeader("DELETE USER ACCOUNT", CYAN);
    cout << "Enter username to delete: ";
    cin >> username;

    if (!users.count(username)) {
        cout << RED << "User not found.\n" << RESET;
        return;
    }

    users.erase(username);
    cout << GREEN << "User account deleted successfully.\n" << RESET;
}

void viewAllUsers() {
    printHeader("ALL USERS", CYAN);

    if (users.empty()) {
        cout << RED << "No users found.\n" << RESET;
        return;
    }

    cout << CYAN << setw(15) << left << "Username"
         << setw(20) << "Account Number"
         << setw(15) << "Balance"
         << setw(20) << "Last Transaction" << RESET << "\n";
    cout << "---------------------------------------------------------------\n";

    for (const auto &entry : users) {
        string lastTransaction = entry.second.transactions.empty() ? "No transactions" : entry.second.transactions.back();
        cout << GREEN << setw(15) << left << entry.first
             << setw(20) << entry.second.accountNumber
             << setw(15) << fixed << setprecision(2) << entry.second.balance
             << setw(20) << lastTransaction << RESET << "\n";
    }
}

// Employee functions
void depositMoney() {
    string username;
    double amount;

    printHeader("DEPOSIT MONEY", GREEN);
    cout << "Enter username: ";
    cin >> username;

    if (!users.count(username)) {
        cout << RED << "User not found.\n" << RESET;
        return;
    }

    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount <= 0) {
        cout << RED << "Amount must be greater than zero.\n" << RESET;
        return;
    }

    users[username].balance += amount;
    users[username].transactions.push_back("Deposited: " + to_string(amount));
    cout << GREEN << "Deposit successful! New Balance: " << users[username].balance << ".\n" << RESET;
}

void withdrawMoney() {
    string username;
    double amount;

    printHeader("WITHDRAW MONEY", GREEN);
    cout << "Enter username: ";
    cin >> username;

    if (!users.count(username)) {
        cout << RED << "User not found.\n" << RESET;
        return;
    }

    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount <= 0) {
        cout << RED << "Amount must be greater than zero.\n" << RESET;
        return;
    }

    if (users[username].balance < amount) {
        cout << RED << "Insufficient balance.\n" << RESET;
        return;
    }

    users[username].balance -= amount;
    users[username].transactions.push_back("Withdrew: " + to_string(amount));
    cout << GREEN << "Withdrawal successful! New Balance: " << users[username].balance << ".\n" << RESET;
}

// User functions
void viewBalance(string username) {
    printHeader("VIEW BALANCE", CYAN);
    cout << "Current Balance: " << GREEN << fixed << setprecision(2) << users[username].balance << RESET << "\n";
}

void viewLastTransactions(string username) {
    printHeader("LAST TRANSACTIONS", CYAN);

    if (users[username].transactions.empty()) {
        cout << RED << "No transactions found.\n" << RESET;
        return;
    }

    for (const auto &transaction : users[username].transactions) {
        cout << GREEN << transaction << RESET << "\n";
    }
}

void transferMoney(string username) {
    string recipient;
    double amount;

    printHeader("TRANSFER MONEY", CYAN);
    cout << "Enter recipient username: ";
    cin >> recipient;

    if (!users.count(recipient)) {
        cout << RED << "Recipient not found.\n" << RESET;
        return;
    }

    cout << "Enter amount to transfer: ";. 
    cin >> amount;

    if (amount <= 0 || amount > users[username].balance) {
        cout << RED << "Invalid amount. Check your balance.\n" << RESET;
        return;
    }

    users[username].balance -= amount;
    users[recipient].balance += amount;

    users[username].transactions.push_back("Transferred " + to_string(amount) + " to " + recipient);
    users[recipient].transactions.push_back("Received " + to_string(amount) + " from " + username);

    cout << GREEN << "Transfer successful! New Balance: " << users[username].balance << ".\n" << RESET;
}

void loanDepartment(string username) {
    printHeader("LOAN DEPARTMENT", CYAN);

    int loanType;
    double loanAmount, durationInYears, interestRate;
    string loanTypeName;

    printHeader("AVAILABLE LOAN TYPES", CYAN);
    cout << "1. Home Loan (7% annual interest)\n";
    cout << "2. Education Loan (5% annual interest)\n";
    cout << "3. Personal Loan (10% annual interest)\n";
    cout << "Choose the loan type: ";
    cin >> loanType;

    switch (loanType) {
        case 1:
            interestRate = 7.0;
            loanTypeName = "Home Loan";
            break;
        case 2:
            interestRate = 5.0;
            loanTypeName = "Education Loan";
            break;
        case 3:
            interestRate = 10.0;
            loanTypeName = "Personal Loan";
            break;
        default:
            cout << RED << "Invalid loan type. Returning to User Menu.\n" << RESET;
            return;
    }

    cout << "Enter loan amount: ";
    cin >> loanAmount;

    if (loanAmount <= 0) {
        cout << RED << "Loan amount must be positive.\n" << RESET;
        return;
    }

    cout << "Enter loan duration (in years): ";
    cin >> durationInYears;

    if (durationInYears <= 0) {
        cout << RED << "Duration must be positive.\n" << RESET;
        return;
    }

    // Store loan request
    loanRequests.push_back({username, loanAmount, durationInYears, interestRate, loanTypeName, "Pending"});
    cout << GREEN << "Loan request submitted successfully. Awaiting manager approval.\n" << RESET;
}
void viewNotifications(string username) {
    printHeader("NOTIFICATIONS", CYAN);

    if (users[username].notifications.empty()) {
        cout << YELLOW << "No notifications available.\n" << RESET;
        return;
    }

    for (const auto &notification : users[username].notifications) {
        cout << GREEN << "- " << notification << RESET << "\n";
    }

    // Clear notifications after viewing
    users[username].notifications.clear();
}

void approveLoanRequests() {
    printHeader("APPROVE LOAN REQUESTS", CYAN);

    if (loanRequests.empty()) {
        cout << RED << "No loan requests pending.\n" << RESET;
        return;
    }

    for (auto &request : loanRequests) {
        if (request.status != "Pending") continue; // Skip already processed requests

        cout << "Loan Request for User: " << request.username << "\n";
        cout << "Loan Type: " << request.loanType << "\n";
        cout << "Loan Amount: " << fixed << setprecision(2) << request.amount << "\n";
        cout << "Duration: " << request.duration << " years\n";
        cout << "Interest Rate: " << request.interestRate << "% per annum\n";
        cout << YELLOW << "Approve or Reject this request? (approve/reject): " << RESET;

        string decision;
        cin >> decision;

        if (decision == "approve") {
            request.status = "Approved";
            users[request.username].balance += request.amount; // Add loan amount to user's balance
            users[request.username].transactions.push_back("Loan approved: " + request.loanType + " of " + to_string(request.amount));
            users[request.username].notifications.push_back("Your loan request has been approved!");
            cout << GREEN << "Loan approved successfully!\n" << RESET;
        } else if (decision == "reject") {
            request.status = "Rejected";
            users[request.username].notifications.push_back("Your loan request has been rejected.");
            cout << RED << "Loan rejected.\n" << RESET;
        } else {
            cout << YELLOW << "Invalid input. Skipping this request.\n" << RESET;
        }
    }
}

// Function to download transaction statement
void downloadStatement(string username) {
    string filename = username + "_statement.txt";
    ofstream file(filename);

    if (!file) {
        cout << RED << "Failed to create statement file.\n" << RESET;
        return;
    }

    file << "Transaction Statement for User: " << username << "\n";
    file << "Account Number: " << users[username].accountNumber << "\n";
    file << "Current Balance: " << fixed << setprecision(2) << users[username].balance << "\n";
    file << "--------------------------------------------------------\n";
    file << setw(30) << left << "Transaction Details" << "\n";
    file << "--------------------------------------------------------\n";

    if (users[username].transactions.empty()) {
        file << "No transactions available.\n";
    } else {
        for (const auto &transaction : users[username].transactions) {
            file << transaction << "\n";
        }
    }

    file.close();

    cout << GREEN << "Transaction statement downloaded successfully as '" << filename << "'.\n" << RESET;
}



// Save users to file
void saveUsers() {
    ofstream file("users.txt");

    if (!file) {
        cout << RED << "Failed to save users.\n" << RESET;
        return;
    }

    for (const auto &entry : users) {
        file << entry.first << " "
             << entry.second.password << " "
             << entry.second.accountNumber << " "
             << entry.second.balance << " "
             << entry.second.transactions.size() << " ";
        for (const auto &transaction : entry.second.transactions) {
            file << transaction << " ";
        }
        file << "\n";
    }

    file.close();
}

// Load users from file
void loadUsers() {
    ifstream file("users.txt");

    if (!file) {
        cout << RED << "No previous data found. Starting fresh.\n" << RESET;
        return;
    }

    users.clear();
    string username, password, fullName, address, phoneNumber, dob, education, job, accountType, transaction;
    int accountNumber, transactionCount;
    double balance;

    while (file >> username >> password >> accountNumber >> balance >> fullName >> address >> phoneNumber >> dob >> education >> job >> accountType >> transactionCount) {
        // Reading multi-word inputs for full name, address, education, and job
        string fullNameLine, addressLine, educationLine, jobLine;
        cin.ignore();  // To clear any leftover newline characters
        getline(file, fullNameLine);  // Read full name
        getline(file, addressLine);   // Read address
        getline(file, educationLine); // Read education
        getline(file, jobLine);       // Read job

        // Add the user to the map
        users[username] = {
            fullNameLine, addressLine, phoneNumber, dob, educationLine, jobLine, accountType,
            password, accountNumber, balance, {}
        };

        // Read all transactions for the user
        for (int i = 0; i < transactionCount; ++i) {
            getline(file, transaction);
            users[username].transactions.push_back(transaction);
        }
    }

    file.close();
}
void saveManagers() {
    ofstream file("managers.txt");

    if (!file) {
        cout << RED << "Failed to save managers.\n" << RESET;
        return;
    }

    for (const auto &entry : managers) {
        const Manager &m = entry.second;
        file << entry.first << " " // Username
             << m.password << " "  // Password
             << m.fullName << " "  // Full Name
             << m.dob << " "       // Date of Birth
             << m.gender << " "    // Gender
             << m.address << " "   // Address
             << m.phoneNumber << " " // Phone Number
             << m.email << "\n";   // Email
    }

    file.close();
}

void loadManagers() {
    ifstream file("managers.txt");

    if (!file) {
        cout << YELLOW << "No previous manager data found. Starting fresh.\n" << RESET;
        return;
    }

    managers.clear();
    string username, password, fullName, dob, gender, address, phoneNumber, email;

    while (file >> username >> password >> fullName >> dob >> gender >> address >> phoneNumber >> email) {
        managers[username] = {fullName, dob, gender, address, phoneNumber, email, password};
    }

    file.close();
}

void saveEmployees() {
    ofstream file("employees.txt");

    if (!file) {
        cout << RED << "Failed to save employees.\n" << RESET;
        return;
    }

    for (const auto &entry : employees) {
        const Employee &e = entry.second;
        file << e.username << " "
             << e.password << " "
             << e.name << " "
             << e.gender << " "
             << e.dob << " "
             << e.phoneNumber << " "
             << e.email << " "
             << e.address << "\n";
    }

    file.close();
}

void loadEmployees() {
    ifstream file("employees.txt");

    if (!file) {
        cout << YELLOW << "No previous employee data found. Starting fresh.\n" << RESET;
        return;
    }

    employees.clear();
    string username, password, name, gender, dob, phoneNumber, email, address;

    while (file >> username >> password >> name >> gender >> dob >> phoneNumber >> email >> address) {
        employees[username] = {name, gender, dob, phoneNumber, email, address, username, password};
    }

    file.close();
}

