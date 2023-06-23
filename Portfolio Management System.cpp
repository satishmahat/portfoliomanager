#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <sstream>
#include <shellapi.h>
#define true 1
using namespace std;

struct Stock {
    string name;
    int shares;
    double price;
};
string password;
void getpassword() {
    cout << "Enter New Password: ";
    ofstream passfile("password.txt");
    cin >> password;
    passfile << password;
    cout << "PASSWORD CHANGED SUCCESSFULLY";

    Sleep(1000);
    passfile.close();
    system("cls");
}
void loadpass() {
    ifstream inpass("password.txt");
    inpass >> password;
    inpass.close();
}

void addStock(Stock portfolio[], int & numStocks) {
    cout << "----------------------------";
    cout << "\n\t**ADD STOCKS**\n";
    cout << "----------------------------\n";
    while (true) {
        cout << "Enter the name of the stock (in capital letters): ";
        cin >> portfolio[numStocks].name;
        cout << "Enter the number of shares: ";
        cin >> portfolio[numStocks].shares;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        cout << "Enter the price per share: ";
        cin >> portfolio[numStocks].price;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        numStocks++;
        char exitVariable1, lcase1;
        cout << "Do you want add more? (Y/N).";
        cin >> exitVariable1;
        lcase1 = tolower(exitVariable1);
        if (lcase1 == 'n') {
            system("cls");
            break;
        } else if (lcase1 == 'y') {
            continue;
        } else {
            system("cls");
            break;
        }
    }
}
void viewPortfolio(Stock portfolio[], int numStocks) {
    double grandtotal;
    cout << "---------------------------------";
    cout << "\n\t**YOUR PORTFOLIO**\n";
    cout << "---------------------------------\n\n\n\n";
    cout << "Name\tShares\tPricePerShare\tTotal" << endl;
    cout << "----------------------------------------\n";
    for (int i = 0; i < numStocks; i++) {
        double total = portfolio[i].shares * portfolio[i].price;
        cout << portfolio[i].name << "\t" << portfolio[i].shares << "\t" << portfolio[i].price << "\t\t" << total << endl;
        grandtotal = grandtotal + total;
    }
    cout << "----------------------------------------\n";
    cout << "\t\tGrand Total: " << setprecision(30) << grandtotal;
}

void portmain();
void deleteStock(Stock portfolio[], int & numStocks) {
    while (true) {
        stockdel: string stockName;
        cout << "\n\nEnter the name of the stock to delete (E for mainmenu): ";
        cin >> stockName;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        if (stockName == "E") {
            system("cls");
            portmain();
        }
        int index = -1;
        for (int i = 0; i < numStocks; i++) {
            if (portfolio[i].name == stockName) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            cout << "Stock not found!";
            continue;
        }
        for (int i = index; i < numStocks - 1; i++) {
            portfolio[i] = portfolio[i + 1];
        }
        numStocks--;
        char exitVariable1,
        lcase1;
        cout << "Do you want DELETE more? (Y/N).";
        cin >> exitVariable1;
        lcase1 = tolower(exitVariable1);
        if (lcase1 == 'n') {
            system("cls");
            break;
        } else if (lcase1 == 'y') {
            continue;
        } else {
            system("cls");
            break;
        }
    }
}

void updateStock(Stock portfolio[], int numStocks) {
    while (true) {
        string stockName;
        cout << "\n\nEnter the name of the stock to update (E for mainmenu): ";
        cin >> stockName;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        if (stockName == "E") {
            system("cls");
            portmain();
        }
        int index = -1;
        for (int i = 0; i < numStocks; i++) {
            if (portfolio[i].name == stockName) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            cout << "Stock not found." << endl;
            continue;
        }
        cout << "Enter the new number of shares: ";
        cin >> portfolio[index].shares;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        cout << "Enter the new price per share: ";
        cin >> portfolio[index].price;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        char exitVariable1, lcase1;
        cout << "Do you want UPDATE more? (Y/N).";
        cin >> exitVariable1;
        lcase1 = tolower(exitVariable1);
        if (lcase1 == 'n') {
            system("cls");
            break;
        } else if (lcase1 == 'y') {
            continue;
        } else {
            system("cls");
            break;
        }
    }
}

void saveData(Stock portfolio[], int numStocks) {
    ofstream outFile("portfolio.txt");
    for (int i = 0; i < numStocks; i++) {
        outFile << portfolio[i].name << endl;
        outFile << portfolio[i].shares << endl;
        outFile << portfolio[i].price << endl;
    }
    outFile.close();
}

void Export(Stock portfolio[], int numStocks) {
    ofstream outFile("portfolioexport.csv");
    for (int i = 0; i < numStocks; i++) {
        outFile << "Stock Name, No. of Shares, Price" << endl;
        outFile << portfolio[i].name << "," << portfolio[i].shares << "," << portfolio[i].price << endl;
    }
    outFile.close();
}

void loadData(Stock portfolio[], int & numStocks) {
    ifstream inFile("portfolio.txt");
    if (!inFile) {
        cout << "File not found!" << endl;
        return;
    }
    while (!inFile.eof()) {
        inFile >> portfolio[numStocks].name;
        inFile >> portfolio[numStocks].shares;
        inFile >> portfolio[numStocks].price;
        numStocks++;
    }
    numStocks--;
    inFile.close();
}
void portmain();
void startTrading() {
    int brkn;
    string burl;
    ostringstream tempurl;
    broker:
        cout << "Enter broker number (0 to exit): ";
    cin >> brkn;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input!" << endl;
    }
    if (brkn == 0) {
        system("cls");
        portmain();
    } else if (brkn < 1 || brkn > 59) {
        cout << "Invalid Broker Number!" << endl;
        goto broker;
    } else {
        tempurl << "https://tms" << brkn << ".nepsetms.com.np/";
        burl = tempurl.str();
        ShellExecute(NULL, "open", burl.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    system("cls");
}

void portmain() {
    Stock portfolio[100];
    int numStocks = 0;
    loadData(portfolio, numStocks);
    int choice;
    do {
        cout << endl << endl;
        cout << "------------------------------------";
        cout << "\n!!!**** PORTFOLIO MANAGER ****!!!" << endl;
        cout << "------------------------------------" << endl;
        cout << "1. Add Stock" << endl;
        cout << "2. View Portfolio" << endl;
        cout << "3. Delete Stock" << endl;
        cout << "4. Update Stock" << endl;
        cout << "5. Change Password" << endl;
        cout << "6. Start Trading" << endl;
        cout << "7. Save And Exit" << endl;
        cout << "8. Export Data as CSV" << endl;
        cout << "----------****************----------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            system("cls");
            continue;
        }
        system("cls");

        switch (choice) {
        case 1:
            addStock(portfolio, numStocks);
            break;
        case 2:
            viewPortfolio(portfolio, numStocks);
            while (true) {
                int ret;
                cout << "\n\n\nPress 1 to return to mainmenu. ";
                cin >> ret;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input!" << endl;
                    continue;
                }
                if (ret != 1) {
                    cout << "\nInvalid Input!";
                    continue;
                }
                if (ret == 1) {
                    system("cls");
                    break;
                }
            }
            break;
        case 3:
            viewPortfolio(portfolio, numStocks);
            deleteStock(portfolio, numStocks);
            break;
        case 4:
            viewPortfolio(portfolio, numStocks);
            updateStock(portfolio, numStocks);
            break;
        case 5:
            getpassword();
            break;
        case 6:
            startTrading();
            break;
        case 7:
            saveData(portfolio, numStocks);
            break;
        case 8:
            Export(portfolio, numStocks);
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 7);
}

int main() {
    system("color E5");
    loadpass();
    string inpass;
    cout << "\n\n----WELCOME TO PORTFOLIO MANAGER-----";
    cout << "\n\nPASSWORD: ";
    cin >> inpass;
    if (inpass == password) {
        cout << "\nACCESS GRANTED";
        Sleep(100);
        cout << ".";
        Sleep(100);
        cout << ".";
        Sleep(100);
        cout << ".";
        Sleep(100);
        cout << ".";
        Sleep(500);
        system("cls");
        portmain();
    } else {
        cout << "\n..ACCESS DENIED..";
        Sleep(1000);
    }

    return 0;
}
