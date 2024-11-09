#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

// Structure for storing account information
typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    char account_number[MAX_LEN];
    double balance;
} Account;

// Function prototypes
void signup();
void login();
void open_account(Account *account);
void deposit_money(Account *account);
void withdraw_money(Account *account);
void display_account(const Account *account);
void save_account_to_file(const Account *account);
int read_account_from_file(const char *username, Account *account);

// Main function
int main() {
    int choice;
    printf("Welcome to the Bank Management System!\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1. Signup\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                login();
                break;
            case 3:
                printf("Thank you for using the Bank Management System!\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

// Signup function
void signup() {
    Account account;
    FILE *file = fopen("accounts.txt", "a");
    if (!file) {
        printf("Error opening file for saving accounts.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", account.username);
    printf("Enter password: ");
    scanf("%s", account.password);
    printf("Enter account number: ");
    scanf("%s", account.account_number);
    account.balance = 0.0;

    fprintf(file, "%s %s %s %.2f\n", account.username, account.password, account.account_number, account.balance);
    fclose(file);

    printf("Signup successful! You can now login.\n");
}

// Login function
void login() {
    char username[MAX_LEN];
    char password[MAX_LEN];
    Account account;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (read_account_from_file(username, &account) && strcmp(account.password, password) == 0) {
        printf("Login successful!\n");

        int choice;
        do {
            printf("\n--- ACCOUNT MENU ---\n");
            printf("1. Open Account\n");
            printf("2. Deposit Money\n");
            printf("3. Withdraw Money\n");
            printf("4. Display Account\n");
            printf("5. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    open_account(&account);
                    break;
                case 2:
                    deposit_money(&account);
                    break;
                case 3:
                    withdraw_money(&account);
                    break;
                case 4:
                    display_account(&account);
                    break;
                case 5:
                    save_account_to_file(&account);
                    printf("Logged out successfully.\n");
                    break;
                default:
                    printf("Invalid choice, please try again.\n");
            }
        } while (choice != 5);
    } else {
        printf("Invalid username or password.\n");
    }
}

// Function to open a new account
void open_account(Account *account) {
    printf("Enter new account number: ");
    scanf("%s", account->account_number);
    account->balance = 0.0;
    printf("Account opened successfully!\n");
}

// Function to deposit money
void deposit_money(Account *account) {
    double amount;
    printf("Enter deposit amount: ");
    scanf("%lf", &amount);
    account->balance += amount;
    printf("Deposit successful! New balance: %.2f\n", account->balance);
}

// Function to withdraw money
void withdraw_money(Account *account) {
    double amount;
    printf("Enter withdrawal amount: ");
    scanf("%lf", &amount);

    if (amount > account->balance) {
        printf("Insufficient balance.\n");
    } else {
        account->balance -= amount;
        printf("Withdrawal successful! New balance: %.2f\n", account->balance);
    }
}

// Function to display account information
void display_account(const Account *account) {
    printf("\n--- ACCOUNT DETAILS ---\n");
    printf("Account Number: %s\n", account->account_number);
    printf("Username: %s\n", account->username);
    printf("Balance: %.2f\n", account->balance);
    printf("-----------------------\n");
}

// Function to save account to file
void save_account_to_file(const Account *account) {
    FILE *file = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) {
        printf("Error opening file for saving.\n");
        return;
    }

    Account temp;
    int found = 0;

    // Read each account and rewrite to temp file with updates
    while (fscanf(file, "%s %s %s %lf\n", temp.username, temp.password, temp.account_number, &temp.balance) != EOF) {
        if (strcmp(temp.username, account->username) == 0) {
            fprintf(tempFile, "%s %s %s %.2f\n", account->username, account->password, account->account_number, account->balance);
            found = 1;
        } else {
            fprintf(tempFile, "%s %s %s %.2f\n", temp.username, temp.password, temp.account_number, temp.balance);
        }
    }

    if (!found) {
        fprintf(tempFile, "%s %s %s %.2f\n", account->username, account->password, account->account_number, account->balance);
    }

    fclose(file);
    fclose(tempFile);

    // Replace old file with new file
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}

// Function to read account from file
int read_account_from_file(const char *username, Account *account) {
    FILE *file = fopen("accounts.txt", "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return 0;
    }

    while (fscanf(file, "%s %s %s %lf\n", account->username, account->password, account->account_number, &account->balance) != EOF) {
        if (strcmp(account->username, username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
