#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept> 

using namespace std;


struct Date {
    int day;
    int month;
    int year;

    Date() {
        day = 1; month = 1; year = 2025;
    }
};


class Expense {
public:
    string description;
    double amount;
    string category;
    Date expenseDate; 

    Expense() {
        description = "";
        amount = 0.0;
        category = "Uncategorized";
    }

    void set_data() {
        cout << "  Enter description: ";
        cin.ignore();
        getline(cin, description);

        cout << "  Enter amount (Rs.): ";
        cin >> amount;
        
        if (amount < 0) {
            throw std::runtime_error("Amount cannot be negative.");
        }

        cout << "  Enter date (dd mm yyyy): ";
        cin >> expenseDate.day >> expenseDate.month >> expenseDate.year;
        
        cout << "  Enter category (e.g., Food, Travel): ";
        cin >> category;
    }

    void save_to_file(ofstream &fileStream) {
        if (fileStream.is_open()) {
            fileStream << "--- Expense ---" << "\n";
            fileStream << "Description: " << description << "\n";
            fileStream << "Amount: Rs." << amount << "\n";
            fileStream << "Date: " << expenseDate.day << "/"
                       << expenseDate.month << "/" << expenseDate.year << "\n";
            fileStream << "Category: " << category << "\n";
            fileStream << "----------------------\n";
        }
    }
};


int main() {
    cout << "--- My C++ Expense Tracker ---\n\n";

    const int MAX_EXPENSES = 100;
    Expense my_expenses[MAX_EXPENSES];
    int expense_count = 0; 

    char choice;

    do {
        if (expense_count < MAX_EXPENSES) {
            cout << "\n--- Adding Expense #" << (expense_count + 1) << " ---\n";

            try {
                my_expenses[expense_count].set_data();
                expense_count++; 
            }
            catch (const std::runtime_error& e) {
                cout << "  *** ERROR: " << e.what() << " ***\n";
                cout << "  Please try again for this expense.\n";
            }
        } else {
            cout << "You have reached the maximum number of expenses.\n";
            break;
        }

        cout << "\nDo you want to add another expense? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "\nFinished adding expenses. You entered " << expense_count << " item(s).\n";

    if (expense_count > 0) {
        string filename;
        cout << "\nEnter a name for your output file (e.g., expenses.txt): ";
        cin >> filename;

        ofstream myfile(filename);

        if (!myfile.is_open()) {
            cerr << "Error: Could not open the file " << filename << " for writing.\n";
            return 1;
        }

        cout << "Saving expenses to " << filename << "...\n";

        myfile << "--- MY EXPENSE REPORT ---\n";
        myfile << "Total Items: " << expense_count << "\n";
        myfile << "----------------------------\n";

        for (int i = 0; i < expense_count; i++) {
            my_expenses[i].save_to_file(myfile);
        }
        
        myfile.close();
        cout << "Successfully saved all expenses!\n";

    } else {
        cout << "No expenses were entered, so no file was saved.\n";
    }

    cout << "\nProgram finished.\n";
    return 0;
}
