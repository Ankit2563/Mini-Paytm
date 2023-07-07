#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include <stdio.h>
using namespace std;

// **************************************** Money Transfer - Start *******************************************
void transactionSuccessful()
{
    cout << "\n\n";
    cout << "\t\t\t\t\t\t\t#########################################\n";
    cout << "\t\t\t\t\t\t\t#        TRANSACTION SUCCESSFUL         #\n";
    cout << "\t\t\t\t\t\t\t#########################################\n\n\n";
}

string getFileContents(ifstream &File)
{

    string Lines = "";

    if (File)
    {
        while (File.good())
        {
            string TempLine;
            getline(File, TempLine);
            TempLine += "\n";

            Lines += TempLine;
        }
        return Lines;
    }
    else
    {
        return "ERROR File does not exist.";
    }
}

string readLine(string &filename, int n)
{
    ifstream file(filename);
    string output;

    for (int i = 0; i < n; i++)
    {
        getline(file, output);
    }

    getline(file, output);
    file.close();
    return output;
}

class accountDetails
{
public:
    string unAttempt;
    string pwAttempt;
    string upiPin;
    float balance;
    void operator-(float amount)
    {
        balance = balance - amount;
    }

    void operator+(float amount)
    {
        balance = balance + amount;
    }

    accountDetails()
    {
        balance = 0;
    }
};

class UPI
{
public:
    void mainMenu();
    void loginScreen();
    void registerScreen();
    void infoScreen();
    void MenuScreen();
    void BalanceScreen();
    void TransferScreen();
    void TransactionHistory();

    bool createUser(const string username, const string password, const string upi_pin);
    bool authenticateUser(const string usernameAttempt);
    bool authenticatePassword(const string usernameAttempt, const string passwordAttempt);
    bool verifypin();
    bool verifyPinPayment(const string username);
    bool transfer(float amount);
    bool deductAmount(const string username, float amount);
    bool transfer(const string username, float amount);
    bool transfer(const string username1, const string username2, float amount);

protected:
    bool authenticated;
    int no = 1;
    string usName;
public:
    accountDetails *acc = new accountDetails();
    accountDetails * getUserName()
    {
        return acc;
    }
};

void UPI::mainMenu()
{
    int option;

    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t#########################################\n";
        cout << "\t\t\t\t\t\t\t#                 PAYTM                 #\n";
        cout << "\t\t\t\t\t\t\t#########################################\n\n\n";
        cout << "\t\t\t\t\t\t\tPlease choose your option." << endl
             << endl;
        cout << "\t\t\t\t\t\t\t1 : LOGIN" << endl
             << endl;
        cout << "\t\t\t\t\t\t\t2 : REGISTER" << endl
             << endl;
        cout << "\t\t\t\t\t\t\t3 : INFO" << endl
             << endl;
        cout << "\t\t\t\t\t\t\t4 : QUIT" << endl
             << endl;
        cout << "\t\t\t\t\t\t\tOption : ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "\n\t\t\t\t\t\t\tLOGIN INITIALIZED...\n";
            Sleep(500);
            loginScreen();
            return;

        case 2:
            cout << "\n\t\t\t\t\t\t\tREGISTER INITIALIZED...\n";
            Sleep(500);
            registerScreen();
            break;

        case 3:
            cout << "\n\t\t\t\t\t\t\tINFO INITIALIZED...\n";
            Sleep(500);
            infoScreen();
            break;

        case 4:
            cout << "\n\t\t\t\t\t\t\tQUIT INITIALIZED...\n";
            Sleep(500);
            option = 4;
            exit(0);

        default:
            cout << "\n\t\t\t\t\t\t\tINVALID OPTION.\n";
            cout << "\n\t\t\t\t\t\t\tPlease choose an option from 1 to 4.\n";
            Sleep(1000);
            mainMenu();
            break;
        }
    } while (option != 4);
}

void UPI::loginScreen()
{
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t#########################################\n";
    cout << "\t\t\t\t\t\t\t#             Login Screen              #\n";
    cout << "\t\t\t\t\t\t\t#########################################\n\n\n";
    cout << "\t\t\t\t\t\t\tPlease enter your username. " << endl
         << endl
         << "\t\t\t\t\t\t\tUsername : ";
    cin >> usName;
    acc->unAttempt = usName;
    if (authenticateUser(acc->unAttempt))
    {
        cout << "\n\n\t\t\t\t\t\t\tPlease enter your password. " << endl
             << endl
             << "\t\t\t\t\t\t\tPassword : ";
        cin >> acc->pwAttempt;
        if (authenticatePassword(acc->unAttempt, acc->pwAttempt))
        {
            authenticated = true;
            cout << "\n\t\t\t\t\t\t\tLogin Successful!" << endl;
            Sleep(1000);
            return;
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\tWrong password. Please try another password." << endl;
            Sleep(500);
            loginScreen();
        }
    }
    else
    {
        cout << "\n\t\t\t\t\t\t\tUsername does not exist. Please try another username." << endl;
        cout << "\n\n";
        system("PAUSE");
        Sleep(500);
        mainMenu();
    }
}

void UPI::registerScreen()
{
    system("cls");
    string un, pw, upi;
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t#########################################\n";
    cout << "\t\t\t\t\t\t\t#            Register Screen            #\n";
    cout << "\t\t\t\t\t\t\t#########################################\n\n\n";
    cout << "\t\t\t\t\t\t\tPlease enter an unused username. " << endl
         << endl
         << "\t\t\t\t\t\t\tUsername : ";
    cin >> un;
    cout << "\n\n\t\t\t\t\t\t\tPlease enter a password. " << endl
         << endl
         << "\t\t\t\t\t\t\tPassword : ";
    cin >> pw;
    cout << "\n\n\t\t\t\t\t\t\tPlease enter the 6 digit upi pin. " << endl
         << endl
         << "\t\t\t\t\t\t\tUPI pin : ";
    cin >> upi;
    if (upi.find_first_not_of("1234567890.") != string::npos || upi.length() != 6)
    {
        cout << "\n\t\t\t\t\t\t\t--PLEASE ENTER A VALID 6 DIGIT UPI PIN--" << endl;
        system("PAUSE");
        Sleep(1000);
        return registerScreen();
    }
    else
    {
        if (createUser(un, pw, upi))
        {
            cout << "\n\t\t\t\t\t\t\tSUCCESS! User " << un << " created.\n";
            Sleep(1000);
            return;
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\tUsername already taken. Please try another username.\n";
            Sleep(1000);
            registerScreen();
        }
    }
}

void UPI::infoScreen()
{

    system("cls");
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tMade by Ankit Singh / Arshdeep Singh / Anish Kumar" << endl;
    system("PAUSE");
    mainMenu();
}

void UPI::MenuScreen()
{
    system("cls");

    int option;
    while (1)
    {
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t#########################################\n";
        cout << "\t\t\t\t\t\t\t#                 PAYTM                 #\n";
        cout << "\t\t\t\t\t\t\t#########################################\n\n\n";
        cout << "\t\t\t\t\t\t\tEnter : " << endl
             << endl;
        cout << "\t\t\t\t\t\t\t1 : ACCOUNT BALANCE" << endl
             << endl;
        cout << "\t\t\t\t\t\t\t2 : TRANSFER MONEY" << endl
             << endl;
        cout << "\t\t\t\t\t\t\t3 : TRANSACTION HISTORY" << endl
             << endl;
        cout << "\t\t\t\t\t\t\t4 : BACK" << endl
             << endl;
        cout << "\t\t\t\t\t\t\tOption : ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "\n\t\t\t\t\t\t\tGET BALANCE INITIALIZED...\n";
            Sleep(1000);

            BalanceScreen();
            break;

        case 2:
            cout << "\n\t\t\t\t\t\t\tTRANSFER MONEY INITIALIZED...\n";
            Sleep(1000);

            TransferScreen();
            break;

        case 3:
            cout << "\n\t\t\t\t\t\t\tTRANSACTION HISTORY INITIALIZED....\n";
            Sleep(1000);
            TransactionHistory();
            break;

        case 4:
            cout << "\n\t\t\t\t\t\t\tRETURN INITIALIZED...\n";
            Sleep(1000);
            return;

        default:
            cout << "\n\t\t\t\t\t\t\tINVALID OPTION.\n";
            cout << "\n\t\t\t\t\t\t\tPlease choose an option from 1 to 4.\n";
            Sleep(1000);
            MenuScreen();
            break;
        }
    }
}

void UPI::BalanceScreen()
{
    system("cls");
    if (authenticated && verifypin())
    {
        string fileName = "data\\" + acc->unAttempt + ".dat";
        string amt = readLine(fileName, 3);
        float Amt = stof(amt);
        cout << "\n\n\t\t\t\t\t\t\t#############################################\n";
        cout << "\n\t\t\t\t\t\t\tBalance available : RS " << fixed << setprecision(2) << Amt;
        cout << "\n\n";

        system("PAUSE");
        MenuScreen();
    }
}

void UPI::TransactionHistory()
{
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t<---------- TRANSACTION HISTORY ---------->" << endl
         << endl;
    string name = "history\\" + acc->unAttempt + ".dat";
    string line;
    ifstream h_file;
    h_file.open(name);
    if (h_file.good())
    {
        while (h_file.eof() == 0)
        {
            getline(h_file, line);
            cout << "\t\t\t\t\t\t\t" << line << endl
                 << endl;
        }

        getch();
    }
    else
        cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t<----- YOUR TRANSACTION HISTORY IS EMPTY ----->" << endl;
    getch();
    h_file.close();
    MenuScreen();
}

void UPI::TransferScreen()
{
    system("cls");
    if (authenticated)
    {
        string amtInput;
        string toInput;
        float amt;
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t<----- Transfer Money ----->" << endl
             << endl;
        cout << "\n\t\t\t\t\t\t\tPlease Enter the transfer amount (Rs) : ";
        cin >> amtInput;
        getchar();
        cout << "\n";

        cout << "\n\t\t\t\t\t\t\tPlease Enter the transfer recipient : ";
        cin >> toInput;
        getchar();
        cout << "\n";

        if (amtInput.find_first_not_of("1234567890.") != string::npos)
        {
            cout << "\t\t\t\t\t\t\tInvalid input: " << amtInput << endl;
            cout << "\n\n";
            system("PAUSE");
            TransferScreen();
        }

        amt = stof(amtInput);
        if (amt <= 0)
        {
            cout << "\t\t\t\t\t\t\tPlease Enter only positive values.\n";
        }

        if (verifypin())
        {
            if (transfer(acc->unAttempt, toInput, amt))
            {
                cout << "\n\t\t\t\t\t\t\tSuccessfully transferred Rs " << amt << " from your account to " << toInput << ".\n";
                char ch;
                cout << "\n\t\t\t\t\t\t\tEnter any key to continue : ";
                getch();
                Sleep(1000);
                MenuScreen();
            }
            else
            {
                cout << "\n\t\t\t\t\t\t\tPlease check your balance...\n";
                system("PAUSE");
                MenuScreen();
            }
        }
        else
            MenuScreen();
    }
}

bool UPI::transfer(float amount)
{
    float initialBal;
    string fileName = "data\\" + acc->unAttempt + ".dat";
    initialBal = stof(readLine(fileName, 3));

    if (amount > initialBal)
    {
        return false;
    }
    else
    {
        string buffer;
        string accDetails[4];
        ifstream currentFile(fileName);
        string bufferName = "data\\buffer.dat";
        ofstream bufferFile(bufferName);

        for (int i = 0; i < 4; i++)
        {
            getline(currentFile, buffer);
            accDetails[i] = buffer;
        }
        acc->upiPin = accDetails[2];
        acc->balance = initialBal;

        *acc - amount;
        string printBal = to_string(acc->balance);
        accDetails[3] = printBal;

        for (int i = 0; i < 4; i++)
        {
            bufferFile << accDetails[i] + '\n';
        }
        currentFile.close();
        bufferFile.close();
        remove(fileName.c_str());
        rename("data\\buffer.dat", fileName.c_str());

        return true;
    }
}

bool UPI::deductAmount(const string username, float amount)
{
    float initialBal;
    string fileName = "data\\" + username + ".dat";
    initialBal = stof(readLine(fileName, 3));

    if (amount > initialBal)
    {
        return false;
    }
    else
    {
        string buffer;
        string accDetails[4];
        ifstream currentFile(fileName);
        string bufferName = "data\\buffer.dat";
        ofstream bufferFile(bufferName);

        for (int i = 0; i < 4; i++)
        {
            getline(currentFile, buffer);
            accDetails[i] = buffer;
        }
        acc->upiPin = accDetails[2];
        acc->balance = initialBal;

        *acc - amount;
        string printBal = to_string(acc->balance);
        accDetails[3] = printBal;

        for (int i = 0; i < 4; i++)
        {
            bufferFile << accDetails[i] + '\n';
        }
        currentFile.close();
        bufferFile.close();
        remove(fileName.c_str());
        rename("data\\buffer.dat", fileName.c_str());

        return true;
    }
}

bool UPI::transfer(const string username, float amount)
{
    float initialBal;
    string fileName = "data\\" + username + ".dat";
    initialBal = stof(readLine(fileName, 3));

    string buffer;
    string accDetails[4];
    ifstream currentFile(fileName);
    string bufferName = "data\\buffer.dat";
    ofstream bufferFile(bufferName);

    for (int i = 0; i < 4; i++)
    {
        getline(currentFile, buffer);
        accDetails[i] = buffer;
    }
    acc->upiPin = accDetails[2];
    acc->balance = initialBal;

    *acc + amount;
    string printBal = to_string(acc->balance);
    accDetails[3] = printBal;

    for (int i = 0; i < 4; i++)
    {
        bufferFile << accDetails[i] + '\n';
    }

    currentFile.close();
    bufferFile.close();
    remove(fileName.c_str());
    rename("data\\buffer.dat", fileName.c_str());

    return true;
}

bool UPI::transfer(const string from_user, const string to_user, float amount)
{

    string fileName = "data\\" + to_user + ".dat";
    ifstream isFile;
    isFile.open(fileName);
    if (isFile)
    {
        isFile.close();
        if (transfer(amount))
        {
            transfer(to_user, amount);
            string historystr1 = "history\\" + from_user + ".dat";
            ofstream histor1(historystr1, ios::app);
            histor1 << "->"
                    << " TRANSFERRED RS " << amount << " TO " << to_user << endl;
            histor1.close();

            string historystr2 = "history\\" + to_user + ".dat";
            ofstream histor2(historystr2, ios::app);
            histor2 << "->"
                    << " RECEIVED RS " << amount << " FROM " << from_user << endl;
            no++;
            histor2.close();
            return true;
        }
    }
    return false;
}

bool UPI::createUser(const string username, const string password, const string upi_pin)
{
    string fileName = username + ".dat";
    string pathName = "data\\" + fileName;
    string history = "history\\" + fileName;
    if (!ifstream(pathName))
    {
        ofstream file(pathName, ios::out);
        file << username << endl;
        file << password << endl;
        file << upi_pin << endl;
        file << 0 << endl;
        ofstream histo(history);
        histo.close();
        histo << " Your transaction history :--------------->" << endl;

        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool UPI::authenticateUser(const string usernameAttempt)
{
    string fileName = usernameAttempt + ".dat";
    string pathName = "data\\" + fileName;

    if (ifstream(pathName))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool UPI::authenticatePassword(const string usernameAttempt, const string passwordAttempt)
{
    string fileName = usernameAttempt + ".dat";
    string pathName = "data\\" + fileName;
    string password = readLine(pathName, 1);

    if (password == passwordAttempt)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool UPI::verifypin()
{
    string pin;
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t-> PLEASE ENTER YOUR 6 DIGIT UPI PIN NUMBER : ";
    cin >> pin;
    if (pin.find_first_not_of("1234567890") != string::npos || pin.length() != 6)
    {
        cout << "\n\t\t\t\t\t\t\t---------- PLEASE ENTER A VALID UPI PIN -----------" << endl;
        system("PAUSE");
        Sleep(1000);

        return verifypin();
    }
    else
    {
        string fileName = acc->unAttempt + ".dat";
        string pathName = "data\\" + fileName;
        string upiPin = readLine(pathName, 2);
        if (upiPin == pin)
        {
            return true;
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\tWrong upi pin number entered     ";
            return verifypin();
        }
    }
}

bool UPI::verifyPinPayment(const string username)
{
    string pin;
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t-> PLEASE ENTER YOUR 6 DIGIT UPI PIN NUMBER : ";
    cin >> pin;
    if (pin.find_first_not_of("1234567890") != string::npos || pin.length() != 6)
    {
        cout << "\n\t\t\t\t\t\t\t---------- PLEASE ENTER A VALID UPI PIN -----------" << endl;
        system("PAUSE");
        Sleep(1000);

        return verifyPinPayment(username);
    }
    else
    {
        string fileName = username + ".dat";
        string pathName = "data\\" + fileName;
        string upiPin = readLine(pathName, 2);
        if (upiPin == pin)
        {
            return true;
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\tWrong upi pin number entered     ";
            return verifyPinPayment(username);
        }
    }
}
// **************************************** Money Transfer - End *******************************************

// **************************************** Bills and Recharges - Start *******************************************
class Bills_Recharges : public UPI, public accountDetails
{
    string name;
    char phoneNo[10];
    char subscriberID[10];
    char elec_consumerID[10];
    char water_consumerID[10];
    int amount;

public:
    void menu();
    void mobileRecharge();
    void DTHRecharge();
    void electricityBill();
    void waterBill();
    friend void showHistory();
};

void showHistory()
{
    system("cls");
    ifstream in("RechargeHistory.txt");
    string billRechHist;
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t=> Bill and Recharge History <=\n\n";

    int attempts = 1;
    do
    {
        getline(in, billRechHist);
        if (in.eof() == 1 && attempts == 1)
        {
            cout << "\n\t\t\t\t\t\t\t\t* No items found in History *\n\n";
        }
        else
        {
            cout << billRechHist << "\n\n";
        }
        attempts++;
    } while (in.eof() == 0);

    char choice;
    cout << "\t\t\t\t\t\t\t\t-------------------------------\n\n";
    cout << "\t\t\t\t\t\t\t\tEnter any key to return back : ";
    cin >> choice;
    getchar();
}

void Bills_Recharges ::menu()
{
    int choice;

    while (1)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t########## BILLS AND RECHARGES ##########\n\n\n";
        cout << "\t\t\t\t\t\t\t1. Mobile Recharge\n\n";
        cout << "\t\t\t\t\t\t\t2. DTH/Cable TV Recharge\n\n";
        cout << "\t\t\t\t\t\t\t3. Electricity Bill\n\n";
        cout << "\t\t\t\t\t\t\t4. Water Bill\n\n";
        cout << "\t\t\t\t\t\t\t5. Bill and Recharges History\n\n";
        cout << "\t\t\t\t\t\t\t6. Return to Main Menu\n\n";
        cout << "\t\t\t\t\t\t\t-----------------------------------------\n\n";
        cout << "\t\t\t\t\t\t\tYour Choice : ";
        cin >> choice;
        getchar();
        switch (choice)
        {
        case 1:
            mobileRecharge();
            break;
        case 2:
            DTHRecharge();
            break;
        case 3:
            electricityBill();
            break;
        case 4:
            waterBill();
            break;
        case 5:
            showHistory();
            break;
        case 6:
            return;

        default:
            cout << "\t\t\t\t\t\t\tInvalid Choice. Try Again\n";
            break;
        }
    }
}

void Bills_Recharges ::mobileRecharge()
{
    system("cls");
    string mobileOperators[4] = {"Jio Prepaid", "Airtel Prepaid", "VI Prepaid", "BSNL Prepaid"};
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t~~~~~~~~~~ MOBILE RECHARGE ~~~~~~~~~~\n\n\n";
    cout << "\t\t\t\t\t\t\t=> Mobile Operators <=\n\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "\t\t\t\t\t\t\t" << i + 1 << ". " << mobileOperators[i] << "\n\n";
    }
    int choice;
    while (1)
    {
        cout << "\t\t\t\t\t\t\t-----------------------------------------\n\n";
        cout << "\t\t\t\t\t\t\tYour Choice : ";
        cin >> choice;
        getchar();
        if (choice >= 1 && choice <= 4)
        {
            string mobOpr = mobileOperators[choice - 1];
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t~~~~~~~~~~ MOBILE RECHARGE ~~~~~~~~~~\n\n\n";
            cout << "\t\t\t\t\t\t\tEnter : \n";
            cout << "\n\t\t\t\t\t\t\tName : ";
            cin >> name;
            getchar();
            while (2)
            {
                cout << "\n\t\t\t\t\t\t\tMobile No. : ";
                gets(phoneNo);
                if (strlen(phoneNo) == 10 && (phoneNo[0] == '9' || phoneNo[0] == '8' || phoneNo[0] == '7' || phoneNo[0] == '6'))
                {
                    cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                    string AllRecharges[5];
                    string recharge;
                    ifstream in("DataPacks.txt");
                    int i = 0;
                    while (in.eof() == 0 && i <= 4)
                    {
                        getline(in, recharge);
                        AllRecharges[i] = recharge;
                        i++;
                    }
                    cout << "\n\t\t\t\t\t\t\t\t=> Available Recharges <=\n\n";
                    for (int i = 0; i < 5; i++)
                    {
                        cout << "\t\t" << i + 1 << ". " << mobOpr << " | " << AllRecharges[i] << endl
                             << endl;
                    }

                    while (3)
                    {
                        cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                        cout << "\t\t\t\t\t\t\tYour Choice : ";
                        cin >> choice;
                        getchar();

                        if (choice >= 1 && choice <= 5)
                        {
                            char strAmount[4];
                            recharge = AllRecharges[choice - 1];
                            cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                            cout << "\n\t\t\t\t\t\t\t\t=> Selected Recharge Package <=\n\n";
                            cout << "\t\t" << choice << ". " << mobOpr << " | " << recharge << endl
                                 << endl;

                            for (int i = 0; recharge[i] != ' '; i++)
                            {
                                strAmount[i] = recharge[i];
                            }
                            amount = atoi(strAmount);
                            cout << "\n\t\t\t\t\t\t\t#=> Amount to be Paid : " << amount << " <=#\n";
                            float amtToPay = (float)amount;
                            int isPaid = 0;
                            if (verifyPinPayment(name))
                            {
                                deductAmount(name, amtToPay);
                                isPaid = 1;
                            }
                            if (isPaid == 1)
                            {
                                ofstream out("RechargeHistory.txt", ios_base::app);
                                out << "=> [Mobile Recharge] - Phone No : " << phoneNo << " | " << mobOpr << " | " << AllRecharges[choice - 1] << "\n";
                                out.close();
                            }
                            transactionSuccessful();

                            cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                            cout << "\t\t\t\t\t\t\tEnter any key to return back to home : ";
                            char choice2;
                            cin >> choice2;
                            getchar();
                            return;
                        }
                        else
                        {
                            cout << "\t\t\t\t\t\t\tInvalid Choice. Try Again\n";
                        }
                    }
                }
                else
                {
                    cout << "\t\t\t\t\t\t\t* Invalid format for an Indian mobile number. Try Again\n";
                }
            }
        }
        else
        {
            cout << "\t\t\t\t\t\t\tInvalid Choice. Try Again\n";
        }
    }
}

void Bills_Recharges ::DTHRecharge()
{
    system("cls");
    string dthBillers[4] = {"D2H", "Airtel Digital TV", "Dish TV", "Tata Play"};
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t~~~~~~~~~~ DTH/Cable TV RECHARGE ~~~~~~~~~~\n\n\n";
    cout << "\t\t\t\t\t\t\t=> DTH/Cable TV Billers <=\n\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "\t\t\t\t\t\t\t" << i + 1 << ". " << dthBillers[i] << "\n\n";
    }
    int choice;
    while (1)
    {
        cout << "\t\t\t\t\t\t\t-----------------------------------------\n\n";
        cout << "\t\t\t\t\t\t\tYour Choice : ";
        cin >> choice;
        getchar();
        if (choice >= 1 && choice <= 4)
        {
            string dthBiller = dthBillers[choice - 1];
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t~~~~~~~~~~ DTH/Cable TV RECHARGE ~~~~~~~~~~\n\n\n";
            cout << "\t\t\t\t\t\t\tEnter : \n";
            cout << "\n\t\t\t\t\t\t\tName : ";
            cin >> name;
            getchar();
            while (2)
            {
                cout << "\n\t\t\t\t\t\t\tSubscriber ID : ";
                gets(subscriberID);
                if (strlen(subscriberID) == 10)
                {
                    cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                    string allPlans[3];
                    string plan;

                    ifstream in("DataPacks.txt");
                    int i = 0;
                    while (in.eof() == 0)
                    {
                        getline(in, plan);
                        if (plan.find(dthBiller) != string::npos)
                        {
                            allPlans[i] = plan;
                            i++;
                        }
                    }

                    cout << "\n\t\t\t\t\t\t\t   => Available DTH/Cable TV Plans <=\n\n";
                    for (int i = 0; i < 3; i++)
                    {
                        cout << "\t\t\t\t\t\t\t" << i + 1 << ". " << allPlans[i] << endl
                             << endl;
                    }

                    while (3)
                    {
                        cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                        cout << "\t\t\t\t\t\t\tYour Choice : ";
                        cin >> choice;
                        getchar();

                        if (choice >= 1 && choice <= 3)
                        {
                            char strAmount[4];
                            plan = allPlans[choice - 1];
                            cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                            cout << "\n\t\t\t\t\t\t\t   => Selected DTH/Cable TV Plan <=\n\n";
                            cout << "\t\t\t\t\t\t\t" << choice << ". " << plan << endl
                                 << endl;

                            for (int i = 0; plan[i] != ' '; i++)
                            {
                                strAmount[i] = plan[i];
                            }
                            amount = atoi(strAmount);

                            cout << "\n\t\t\t\t\t\t\t#=> Amount to be Paid : " << amount << " <=#\n";
                            float amtToPay = (float)amount;
                            int isPaid = 0;
                            if (verifyPinPayment(name))
                            {
                                deductAmount(name, amtToPay);
                                isPaid = 1;
                            }
                            if (isPaid == 1)
                            {
                                ofstream out("RechargeHistory.txt", ios_base::app);
                                out << "=> [DTH/Cable Recharge] - Sub. Id : " << subscriberID << " | " << allPlans[choice - 1] << "\n";
                                out.close();
                            }

                            transactionSuccessful();

                            cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                            cout << "\t\t\t\t\t\t\tEnter any key to return back to home : ";
                            char choice2;
                            cin >> choice2;
                            getchar();
                            return;
                        }
                        else
                        {
                            cout << "\t\t\t\t\t\t\tInvalid Choice. Try Again\n";
                        }
                    }
                }
                else
                {
                    cout << "\t\t\t\t\t\t\t* Subscriber ID must be of 10 digits. Try Again\n";
                }
            }
        }
        else
        {
            cout << "\t\t\t\t\t\t\tInvalid Choice. Try Again\n";
        }
    }
}

void Bills_Recharges ::electricityBill()
{
    system("cls");
    string electricityBoards[3] = {"Dakshin Haryana Bijli (DHBVN)", "Punjab State Power (PSPCL)", "Uttar Pradesh Power (UPPCL)"};
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t~~~~~~~~~~ Electricity Bill ~~~~~~~~~~\n\n\n";
    cout << "\t\t\t\t\t\t\t=> Electricity Boards <=\n\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "\t\t\t\t\t\t\t" << i + 1 << ". " << electricityBoards[i] << "\n\n";
    }
    int choice;
    while (1)
    {
        cout << "\t\t\t\t\t\t\t-----------------------------------------\n\n";
        cout << "\t\t\t\t\t\t\tYour Choice : ";
        cin >> choice;
        getchar();
        if (choice >= 1 && choice <= 3)
        {
            string elecBrd = electricityBoards[choice - 1];
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t~~~~~~~~~~ Electricity Bill ~~~~~~~~~~\n\n\n";
            cout << "\t\t\t\t\t\t\tEnter : \n";
            cout << "\n\t\t\t\t\t\t\tName : ";
            cin >> name;
            getchar();
            while (2)
            {
                cout << "\n\t\t\t\t\t\t\tConsumer ID : ";
                gets(elec_consumerID);
                if (strlen(elec_consumerID) == 8)
                {
                    cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                    string billDetails[6];
                    string bill;

                    ifstream in("DataPacks.txt");
                    int isBillFound = 0;
                    while (in.eof() == 0)
                    {
                        getline(in, bill);
                        if (bill.find(elec_consumerID) != string::npos && bill.find(elecBrd) != string::npos)
                        {
                            isBillFound = 1;
                            for (int i = 0; i < 6; i++)
                            {
                                billDetails[i] = bill;
                                getline(in, bill);
                            }
                            break;
                        }
                    }
                    if (isBillFound == 1)
                    {
                        cout << "\n\t\t\t\t\t\t\t\t   => Bill Details <=\n\n";
                        for (int i = 0; i < 6; i++)
                        {
                            cout << "\t\t\t\t\t\t\t" << billDetails[i] << endl
                                 << endl;
                        }

                        char strAmount[5];
                        for (int i = 0; billDetails[5][i] != '}'; i++)
                        {
                            if (billDetails[5][i] == '{')
                            {
                                i++;
                                for (int j = 0; billDetails[5][i] != '}'; j++)
                                {
                                    strAmount[j] = billDetails[5][i];
                                    i++;
                                }
                                break;
                            }
                        }

                        amount = atoi(strAmount);

                        cout << "\n\t\t\t\t\t\t\t#=> Amount to be Paid : " << amount << " <=#\n";
                        float amtToPay = (float)amount;
                        int isPaid = 0;
                        if (verifyPinPayment(name))
                        {
                            deductAmount(name, amtToPay);
                            isPaid = 1;
                        }
                        if (isPaid == 1)
                        {
                            ofstream out("RechargeHistory.txt", ios_base::app);
                            out << "=> [Electricity Bill] - Consumer Id : " << elec_consumerID << " | " << billDetails[2] << " | Electricity Board : " << elecBrd << " | Bill Amount Paid : " << amount << "\n";
                            out.close();
                        }

                        transactionSuccessful();

                        cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                        cout << "\t\t\t\t\t\t\tEnter any key to return back to home : ";
                        char choice2;
                        cin >> choice2;
                        getchar();
                        return;
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\t\tConsumer Id : " << elec_consumerID << " is not registered in " << elecBrd << "\n\n";
                    }
                }
                else
                {
                    cout << "\t\t\t\t\t\t\t* Consumer ID must be of 8 digits. Try Again\n";
                }
            }
        }
        else
        {
            cout << "\t\t\t\t\t\t\tInvalid Choice. Try Again\n";
        }
    }
}

void Bills_Recharges ::waterBill()
{
    system("cls");
    string waterBoards[3] = {"Haryana PHED - Water", "Punjab Municipal Corp (PMC)", "Uttar Pradesh Municipal Corp (UPMC)"};
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t~~~~~~~~~~ Water Bill ~~~~~~~~~~\n\n\n";
    cout << "\t\t\t\t\t\t\t=> Water Boards <=\n\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "\t\t\t\t\t\t\t" << i + 1 << ". " << waterBoards[i] << "\n\n";
    }
    int choice;
    while (1)
    {
        cout << "\t\t\t\t\t\t\t-----------------------------------------\n\n";
        cout << "\t\t\t\t\t\t\tYour Choice : ";
        cin >> choice;
        getchar();
        if (choice >= 1 && choice <= 3)
        {
            string waterBrd = waterBoards[choice - 1];
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t~~~~~~~~~~ Water Bill ~~~~~~~~~~\n\n\n";
            cout << "\t\t\t\t\t\t\tEnter : \n";
            cout << "\n\t\t\t\t\t\t\tName : ";
            cin >> name;
            getchar();
            while (2)
            {
                cout << "\n\t\t\t\t\t\t\tConsumer ID : ";
                gets(water_consumerID);
                if (strlen(water_consumerID) == 8)
                {
                    cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                    string billDetails[6];
                    string bill;

                    ifstream in("DataPacks.txt");
                    int isBillFound = 0;
                    while (in.eof() == 0)
                    {
                        getline(in, bill);
                        if (bill.find(water_consumerID) != string::npos && bill.find(waterBrd) != string::npos)
                        {
                            isBillFound = 1;
                            for (int i = 0; i < 6; i++)
                            {
                                billDetails[i] = bill;
                                getline(in, bill);
                            }
                            break;
                        }
                    }
                    if (isBillFound == 1)
                    {
                        cout << "\n\t\t\t\t\t\t\t\t   => Bill Details <=\n\n";
                        for (int i = 0; i < 6; i++)
                        {
                            cout << "\t\t\t\t\t\t\t" << billDetails[i] << endl
                                 << endl;
                        }

                        char strAmount[5];
                        for (int i = 0; billDetails[5][i] != '}'; i++)
                        {
                            if (billDetails[5][i] == '{')
                            {
                                i++;
                                for (int j = 0; billDetails[5][i] != '}'; j++)
                                {
                                    strAmount[j] = billDetails[5][i];
                                    i++;
                                }
                                break;
                            }
                        }

                        amount = atoi(strAmount);

                        cout << "\n\t\t\t\t\t\t\t#=> Amount to be Paid : " << amount << " <=#\n";
                        float amtToPay = (float)amount;
                        int isPaid = 0;
                        if (verifyPinPayment(name))
                        {
                            deductAmount(name, amtToPay);
                            isPaid = 1;
                        }
                        if (isPaid == 1)
                        {
                            ofstream out("RechargeHistory.txt", ios_base::app);
                            out << "=> [Water Bill] - Consumer Id : " << water_consumerID << " | " << billDetails[2] << " | Water Board : " << waterBrd << " | Bill Amount Paid : " << amount << "\n";
                            out.close();
                        }

                        transactionSuccessful();

                        cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                        cout << "\t\t\t\t\t\t\tEnter any key to return back to home : ";
                        char choice2;
                        cin >> choice2;
                        getchar();
                        return;
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\t\tConsumer Id : " << water_consumerID << " is not registered in " << waterBrd << "\n\n";
                    }
                }
                else
                {
                    cout << "\t\t\t\t\t\t\t* Consumer ID must be of 8 digits. Try Again\n";
                }
            }
        }
        else
        {
            cout << "\t\t\t\t\t\t\tInvalid Choice. Try Again\n";
        }
    }
}
// **************************************** Bills and Recharges - End *******************************************

// **************************************** Movie - Start *******************************************
class movie : public UPI
{
public:
    string name;
    int amount;
    int noOfTickets;
    string movieChosen;
    string seatNo;
    string phoneNo;

    movie()
    {
        amount = 0;
        seatNo = "";
        phoneNo = "";
    }

    void input()
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tEnter your details :\n";
        cout << "\n\t\t\t\t\t\t\t\tName : ";
        getline(cin >> ws, name);
        while (1)
        {
            cout << "\n\t\t\t\t\t\t\t\tPhone number : ";
            getline(cin >> ws, phoneNo);
            if (phoneNo.length() != 10)
            {
                cout << "\t\t\t\t\t\t\tPlease enter a valid 10 digit phone number" << endl;
            }
            else
            {
                break;
            }
        }
        cout << "\n\n";
    }

    int checkprice(int i)
    {
        fstream p;
        p.open("price.txt", ios::in);
        string a;
        int b[10];
        int k = 0;
        while (getline(p, a))
        {
            b[k++] = stoi(a);
        }
        p.close();
        return b[i - 1];
    }

    void updateSeats(string s)
    {
        fstream m1, m2;
        string line, newline = "";
        m1.open("newFile.txt", ios::out);
        m2.open("seats.txt", ios::in);
        int k = int(s.at(0)) - 48;
        int i = int(s.at(1)) - 65;
        while (i > 0)
        {
            getline(m2, line);
            m1 << line << endl;
            i--;
        }
        getline(m2, line);
        line.replace(3 * (k - 1), 2, "X ");
        m1 << line << endl;
        while (getline(m2, line))
            m1 << line << endl;
        m1.close();
        m2.close();
        m1.open("newFile.txt", ios::in);
        m2.open("seats.txt", ios::out);
        int j = 1;
        while (m1.eof() == 0)
        {
            getline(m1, line);
            m2 << line;
            if (j != 10)
            {
                m2 << "\n";
            }
            j++;
        }
        m1.close();
        m2.close();
    }

    void book()
    {
        fstream movie;
        int choice;
        cout << "\t\t\t\t\t\t\t\t            Choose your Movie             \n";
        cout << "\t\t\t\t\t\t\t___________________________________________________________\n\n";
        movie.open("movies.txt", ios::in);
        string movies[7];
        int i = 0;
        if (movie.is_open())
        {
            string s;
            while (getline(movie, s))
            {
                movies[i] = s;
                i++;
                cout << "\t\t\t\t\t\t\t" << s << endl
                     << endl;
            }
        }
        movie.close();
        while (1)
        {
            cout << "\n\n\t\t\t\t\t\t\tEnter your choice : ";
            cin >> choice;
            if (choice >= 1 && choice <= 6)
            {
                movieChosen = movies[choice].substr(14, 30);
                cout << "\n\n\t\t\t\t\t\t\tEnter No of Tickets you want to book : ";
                cin >> noOfTickets;
                getchar();
                amount = checkprice(choice) * noOfTickets;
                for (int i = 1; i <= noOfTickets; i++)
                {
                    system("cls");
                    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tEnter the Seat Number for Ticket no. : " << i << "\n\n";
                    movie.open("seats.txt", ios::in);
                    if (movie.is_open())
                    {
                        string mn;
                        for (int j = 0; j < 10; j++)
                        {
                            getline(movie, mn);
                            cout << "\t\t\t\t\t\t\t" << mn << endl;
                        }
                    }
                    cout << "\n\n\t\t\t\t\t\t\tBooked seats are marked with X\n";
                    cout << "\t\t\t\t\t\t\tEnter your choice ----->   ";
                    getline(cin >> ws, seatNo);
                    if (seatNo == "X")
                    {
                        cout << "\t\t\t\t\t\t\tWRONG CHOICE!! ENTER AGAIN\n";
                        book();
                    }
                    updateSeats(seatNo);
                    movie.close();
                }
                cout << "\n\t\t\t\t\t\t\t------> Your payable amount is : Rs " << amount << " <------" << endl;
                float amtToPay = (float)amount;
                if (verifyPinPayment(name))
                {
                    deductAmount(name, amtToPay);
                }
                transactionSuccessful();
                cout << "\n\t\t\t\t\t\t\t-----------------------------------------\n\n";
                cout << "\t\t\t\t\t\t\tEnter any key to return back to home : ";
                char choice2;
                cin >> choice2;
                getchar();
                return;
            }
            else
            {
                cout << "\t\t\t\t\t\t\tInvalid Movie Number. Try Again" << endl;
            }
        }
    }
};
class details : public movie
{
public:
    void add()
    {
        fstream d1;
        d1.open("details.txt", ios::app);
        d1 << "Moive : " << movieChosen << endl;
        d1 << "Name : " << name << endl;
        d1 << "Phone number : " << phoneNo << endl;
        d1 << "Seat number : " << seatNo << endl;
        d1 << "Number of Seats : " << noOfTickets << endl;
        d1 << "Amount paid : " << amount << endl;
        d1 << "----------------------------------" << endl
           << endl;
        d1.close();
    }
    void display()
    {
        system("cls");
        char ch;
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t||  Movie Ticket History  ||\n\n";
        fstream d1;
        string s;
        d1.open("details.txt", ios::in);
        while (d1.eof() == 0)
        {
            getline(d1, s);
            cout << "\t\t\t\t\t\t\t" << s << endl;
        }
        d1.close();
        cout << "\n\t\t\t\t\t\t\tEnter Any key to Return Back : \n\n";
        cin >> ch;
        getchar();
    }
};
// **************************************** Movie - End *******************************************

// **************************************** FLight - Start *******************************************
ofstream out("flight1.txt");
ofstream pnr("flight2.txt");
ofstream MyTick("BookedTick.txt", ios::in | ios::out | ios::app);
class DetailsofPassenger : public UPI
{
private:
    int PinNo;
    string CardHolname;

public:
    char f_name[20];
    char L_name[20];
    char Email[100];
    int age;
    long long contactNo;
    char address[100];
    string gender;
    long long cardNo;
    long long CVVNo;
    char Exdate[100];

    void InputDetail(int i)
    {
        string allpnr;

        system("cls");

        cout << "\n\n\t\tDetails of Person : " << i << endl;
        cout << "\n\t\tEnter Your first Name : ";
        cin >> f_name;
        cout << endl;
        cout << "\t\tEnter Your Last Name : ";
        cin >> L_name;

        cout << endl;
        cout << "\t\tEnter Your Email Id : ";
        cin >> Email;
        cout << endl;

        cout << "\t\tEnter Your age : ";
        cin >> age;
        cout << endl;
        cout << "\t\tEnter Your gender : ";
        cin >> gender;
        cout << endl;
        cout << "\t\tEnter your address : ";
        cin >> address;
        cout << endl;
        cout << "\t\tEnter you Phone Number : ";
        cin >> contactNo;
        cout << endl;

        out << "\t\tPassenger Details\n\n";
        out << "\t\tName : " << f_name << " " << L_name << endl;
        out << "\t\tEmail Id : " << Email << endl;
        out << "\t\tAge : " << age << endl;
        out << "\t\tGender : " << gender << endl;
        out << "\t\tAddress : " << address << endl;
        out << "\t\tPhone Number : " << contactNo << endl;
        pnr << "\t\tPNR Number is : 21" << contactNo << endl;
    }

    void printTicketDetails(int No)
    {
        string st1;
        string st2;
        string st3;

        ifstream in1("flight2.txt");
        ifstream in("flight1.txt");
        system("cls");
        cout << "     \t\t***********************************" << endl;
        cout << "     \t\t*   Your trasaction is succesfull *" << endl;
        cout << "     \t\t***********************************" << endl;

        for (int i = 0; i < No; i++)
        {
            ifstream in3("flight3.txt");
            cout << endl;
            MyTick << endl;
            getline(in1, st2);
            cout << st2 << endl;
            MyTick << st2 << endl;

            for (int j = 8 * i; j < 8 * (i + 1); j++)
            {
                getline(in, st1);
                cout << st1 << endl;
                MyTick << st1 << endl;
            }
            getline(in3, st3);
            cout << "\t" << st3 << endl;
            MyTick << "      \t" << st3 << endl;
            getline(in3, st3);
            cout << "\t   " << st3 << endl;
            MyTick << "\t" << st3 << endl;
            in3.close();
            cout << "\n\t\t************************************************" << endl;
        }
    }
};

class SourceAndDest : public DetailsofPassenger
{
public:
    string sor;
    string dest;
    int date;
    float amount;

public:
    void input1()
    {
        system("cls");
        cout << "    \t\t\t************************************" << endl;
        cout << "    \t\t\t* WELCOME TO TICKET BOOKING SYSTEM *" << endl;
        cout << "    \t\t\t************************************\n\n"
             << endl;
        cout << "\t\tPlease Write Source and destination from the following one :" << endl;
        cout << "\n\t\t*Mumbai   *Delhi   *Kolkata   *Chennai   *Bangalore" << endl;
        cout << "\n\n\t\tEnter the source Address : ";
        cin >> sor;

        if (sor != "Mumbai" && sor != "Delhi" && sor != "Kolkata" && sor != "Chennai" && sor != "Bangalore")
        {
            cout << "\t\tPlease Enter Correct source address" << endl;
            getch();
            return input1();
        }
        cout << endl;
    }
    void input2()
    {
        cout << "\t\tEnter the destination Address : ";
        cin >> dest;
        if (dest != "Mumbai" && dest != "Delhi" && dest != "Kolkata" && dest != "Chennai" && dest != "Bangalore")
        {
            cout << "\t\tPlease Enter Correct destination" << endl;
            getch();
            return input2();
        }
        cout << endl;
    }

    void CountTheNo()
    {
        int No;
        cout << "\n\n\tFor how many person do you want to book the ticket : ";
        cin >> No;
        getchar();
        amount = amount * No;
        if (No <= 10000 && No >= 1)
        {

            for (int i = 1; i <= No; i++)
            {
                InputDetail(i);

                if (i == No)
                {
                    string name = "";
                    for(int i = 0; i < strlen(f_name); i++)
                    {
                        name = name + f_name[i];
                    }
                    if (verifyPinPayment(name))
                    {
                        deductAmount(name, amount);
                    }
                    transactionSuccessful();
                    printTicketDetails(No);
                }
            }
        }

        else
        {
            cout << "\t\tPlease Enter a valid No" << endl;
            getch();
            return CountTheNo();
        }
    }
    // function to select flight
    void showData()
    {

        ofstream sode("flight3.txt");

        system("cls");

        input1();
        input2();
        string str;
        string st;
        string flights[1000];

        ifstream in("AllSourceAndDest.txt");
        int j = 0;
        int choice;
        int t = 0;
        while (in.eof() == 0)
        {
            getline(in, str);
            if (str.find(sor) < str.find(dest))
            {
                if (str.find(sor) != string::npos && str.find(dest) != string::npos)
                {
                    t++;
                    flights[j] = str;
                    j++;
                }
            }
        }
    START:
        system("cls");
        cout << " \t   Airline:\t  Departure:\t      Arrival:\t       Price:\n"
             << endl;

        sode << "\tAirline:\t  Departure:\t    Arrival:\t\t Price:"
             << endl;

        for (int i = 0; i < j; i++)
        {
            cout << "\t" << i + 1 << "." << flights[i] << endl;
        }

        cout << "\n\n\t   Enter Your choice : ";
        cin >> choice;
        int count = 0;
        for (int k = 1; k <= t; k++)
        {
            if (k == choice)
            {
                count++;
                cout << "\n\t  "
                     << "You have chosen : " << endl;
                cout << "\n\t    Airline:\t  Departure:\t\t Arrival:\t    Price:\n"
                     << endl;
                st = flights[choice];
                string amt = st.substr(58, 4);
                amount = stof(amt);
                cout << "\t   " << flights[choice];
                sode << "     " << st << endl;
            }
        }
        if (count == 0)
        {
            cout << "\n\t   Please Enter the valid choice : " << endl;
            getch();
            goto START;
        }
        else
        {
            CountTheNo();
        }

        getch();
    }
};

class CheckStatus : public UPI
{

public:
    string str, s, pnr;

    int ShowMyTicket(string pnr, int &count)
    {
        ifstream Book("BookedTick.txt");
        while (Book.eof() == 0)
        {
            getline(Book, str);

            if (str.find(pnr) != string::npos && str.find("PNR") != string::npos)
            {
                count++;
                for (int i = 0; i < 12; i++)
                {
                    cout << str << endl;
                    getline(Book, str);
                }
            }
        }
        return count;
    }
    void DisplayStatus()
    {
        system("cls");

        cout << "\t\tEnter Your  PNR Number : ";
        cin >> pnr;
        int count = 0;
        ShowMyTicket(pnr, count);

        if (count == 0)
        {
            cout << "\n\t\tPNR does not matched" << endl;
            cout << "\n\t\t Please Enter correct PNR " << endl;
            getch();
            return DisplayStatus();
        }
        else
        {
            cout << "\n\t\t Do u want to check another status(Yes/No) : ";
            cin >> s;
            if (s == "Yes")
            {
                getch();
                return DisplayStatus();
            }
            else
            {

                getch();
            }
        }
    }
};

class CancelMYTicket : public CheckStatus
{
public:
    string can, num, st;

    void RemoveTicket(string num)
    {
        string Rem[1000];

        ifstream in("BookedTick.txt");
        int j = 1;
        int choice;
        int t = 0;
        while (in.eof() == 0)
        {
            t++;
            getline(in, str);

            Rem[j] = str;
            j++;

            if (str.find(num) != string::npos && str.find("PNR") != string::npos)
            {
                for (int k = 0; k < 12; k++)
                {
                    getline(in, str);
                }
            }
        }
        ofstream Again("BookedTick.txt");

        for (int l = 0; l < t; l++)
        {
            Again << Rem[l] << endl;
        }
        Again.close();
    }

    void TicketCancel()
    {
        string strdata;
        system("cls");

        cout << "\t\tEnter Your PNR number : ";
        cin >> num;
        cout << endl;
        int count = 0;

        count = ShowMyTicket(num, count);
        if (count != 0)
        {

                cout << "\n\n\t\tAre you sure to cancel the Ticket(Yes/No)" << endl;
                string s;
                cout << "\t\tWrite Your choice : ";
                cin >> s;
                if (s == "Yes")
                {
                    cout << "\t\tYour Ticket has been successfully cancelled\n\n";

                    RemoveTicket(num);
                }
                else if (s == "No")
                {
                    getch();
                }
                else
                {
                    cout << "\n\t\tYou Entered wrong choice" << endl;
                    cout << "\n\t\tPress Any key to go back  " << endl;
                    getch();
                    return TicketCancel();
                }

        }
        else
        {
            string str;
            cout << "\n\t\tTicket Not found " << endl;
            cout << "\n\t\tDo You wish to continue(Yes/No) : ";
            cin >> str;
            cout << endl;
            if (str == "Yes")
            {
                cout << "\t\tPlease Enter Valid PNR Number" << endl;
                getch();
                return TicketCancel();
            }
        }
    }
};
// **************************************** FLight - End *******************************************

// **************************************** Bus - Start *******************************************
int count01;

class Seats : public UPI
{
protected:
    int seats;

public:
    int CheckSeatAvailabilty(string DepSt, string ArrSt, int nt);
};
int Seats ::CheckSeatAvailabilty(string DepSt, string ArrSt, int nt)
{
    int seats, cntr = 0;
    ifstream SeatAvailbility;
    ofstream seat_update;
    string s1, s2;
    SeatAvailbility.open("seat_available.txt");
    while (SeatAvailbility >> s1 >> s2 >> seats)
    {
        seat_update.open("temp11.txt", ios::app);
        if ((s1 == DepSt) & (s2 == ArrSt))
        {
            seats = seats - nt;
            if (seats < 0)
            {
                cout << "\n\n\n****SORRY! THIS RESERVATION IS NOT POSSIBLE****\n\n\n"
                     << endl;
                return (0);
            }
            seat_update << DepSt << "\t" << ArrSt << "\t" << seats << "\n";
            cntr++;
        }
        else
        {
            seat_update << s1 << "\t" << s2 << "\t" << seats << "\n";
        }
        seat_update.close();
    }
    SeatAvailbility.close();
    if (cntr == 0)
    {
        remove("temp11.txt");
    }
    if (cntr > 0)
    {
        remove("seat_available.txt");
        rename("temp11.txt", "seat_available.txt");
        return (1);
    }
    return 0;
}

class Passenger
{
    string str_City, str_ContactNumber, str_UserName, str_Password;

protected:
    string str_customer_id,  str_name, username01;

public:
    Passenger() {}
    Passenger(string name, string customer_id, string City, string ContactNumber, string Username, string Password);
    int Login();
    void SearchFile_and_Update(int);
    void Deletes(int);
    ~Passenger();
};
Passenger ::~Passenger() {}
Passenger ::Passenger(string name, string customer_id, string City, string ContactNumber, string Username, string Password)
{
    str_name = name;
    str_customer_id = customer_id;
    str_City = City;
    str_ContactNumber = ContactNumber;
    str_UserName = Username;
    str_Password = Password;
    fstream registration;
    registration.open("Passenger.txt", ios::app | ios::out | ios::ate);
    registration << str_customer_id << "\t" << str_name << "\t" << str_City << "\t" << str_ContactNumber << "\t" << str_UserName
                 << "\t" << str_Password << "\n";
    registration.close();
}
void Passenger::Deletes(int log_customerid)
{
    int customer_id;
    string name, city, username, password, cn;
    cout << "\n\nEnter your Customer ID to delete the record :\n\n";
    cin >> str_customer_id;
    fstream deleteF;
    ofstream df;
    deleteF.open("Passenger.txt", ios::in);
    while (deleteF >> customer_id >> name >> city >> cn >> username)
    {
        df.open("temp2.txt", ios ::out | ios ::app);
        if (customer_id != log_customerid)
        {
            df << customer_id << "\t" << name << "\t" << city << "\t"
               << cn << "\t" << username
               << "\n";
        }
        else
        {
            count01++;
        }
        df.close();
    } // end of while
    deleteF.close();
    if (count01 == 0)
    {
        remove("temp2.txt");
        cout << "\n\nRecord not found\n\n";
    }
    if (count01 > 0)
    {
        remove("Passenger.txt");
        rename("temp2.txt", "Passenger.txt");
        cout << "Deleted account successfully!!\n";
    }
} // end of function DeleteRecord
void Passenger ::SearchFile_and_Update(int log_customerid)
{
    count01 = 0;
    string name, city, username, password, cn;
    int customer_id;
    cout << "\n\n--------------------------------------------------------------------------------\n\n";
    cout << "\n\nEnter your Customer ID :\n\n";
    cin >> str_customer_id;
    ifstream PassengerIn;
    ofstream writeFile;
    PassengerIn.open("Passenger.txt");
    while (PassengerIn >> customer_id >> name >> city >> cn >> username)
    {
        writeFile.open("temp1.txt", ios ::app);
        if (customer_id == log_customerid)
        {
            cout << "\n\nRecord found!\n\n";
            cout << "\n\n--------------------------------------------------------------------------------\n\n";
            cout << "\n\nNew Passenger Name:\n\n ";
            cin >> str_name;
            cout << "\n\nNew Passenger City:\n\n "; // address change to city
            cin >> str_City;
        contact:
            cout << "\n\nNew Passenger : Contact No\n\n ";
            getline(cin, str_ContactNumber);
            if (str_ContactNumber.size() > 10 || str_ContactNumber.size() < 10)
            {
                cout << "\n\t\t!!!!Please Enter Valid Contact Number:!!!!" << endl;
                goto contact;
            }
            cout << "\n\nNew Passenger : UserName \n\n ";
            cin >> str_UserName;
            cout << "\n\nNew Passenger : Password\n\n ";
            cin >> str_Password;
            writeFile << customer_id << "\t" << str_name << "\t" << str_City << "\t"
                      << str_ContactNumber << "\t" << str_UserName
                      << "\n";
            count01++;
        }
        else
        {
            writeFile << customer_id << "\t" << name << "\t" << city << "\t"
                      << cn << "\t" << username
                      << "\n";
        }
        writeFile.close();
    } // end of while
    PassengerIn.close();
    if (count01 == 0)
    {
        cout << "\n\nRecord  could not be found!\n\n";
        remove("temp1.txt");
    }
    if (count01 > 0)
    {
        remove("Passenger.txt");
        rename("temp1.txt", "Passenger.txt");
        cout << "MODIFIED SUCCESSFULLY!!\n";
    }
}
int Passenger ::Login()
{
    long long x = 0; // to detect correct username and password for login
    string password01;
    cout << "===================================================================================="
         << "\n\n\t\t\t\t"
         << "LOGIN SCREEN"
         << "\n\n"
         << "Enter your UserName:\n\n";
    cin >> username01;
    ifstream matchup;
    matchup.open("Passenger.txt", ios::in);
    int s1, retype;
    string s2, s3, s4, s5, s6;
    while (matchup >> s1 >> s2 >> s3 >> s4 >> s5)
    {
        if (username01 == s5)
        {
            x++;
            retype = s1;
        }
    }
    matchup.close(); // end of while
    if (x > 0)
    {
        cout << "\n\nLogged in Successfully!!\n\n";
        return retype;
    }
    else
    {
        cout << "\n\nLog in Failed!\n\n";
        return 0;
    }
}

class Reservations : public Passenger, public Seats
{
protected:
    string str_Arrival_St, str_Dep_St;
    int i_No_Tickets, i_Charge;
    double i_total;

public:
    Reservations();
    // to make a reservation
    Reservations(int customer_id, string DeptSt, string ArrivalSt, int NoTickets);
    void SearchFile_and_Update(int);
    // ModifyReservation Function
    void Deletes(int);
    // cancel reservation function
    void Show(int);
    void Show(int, string, string, int, int, int);
    double CalculateFee(double, int);
    ~Reservations();
};
Reservations ::Reservations() {}

// class Payments
class Payments : public Reservations
{
public:
    void Show() const;
    ~Payments();
};
// payments - show
void Payments ::Show() const
{
    fstream payments;
    payments.open("Payments.txt", ios::in);
    string line;
    cout << "\n\n";
    if (!payments.is_open())
    {
        cout << "Unable to open payment records!!" << endl;
    }
    while (!payments.eof())
    {
        getline(payments, line);
        cout << line << endl;
    }
    payments.close();
}
Payments ::~Payments() {}
// Reservations constructor
Reservations ::Reservations(int customer_id, string DeptSt, string ArrivalSt, int NoTickets)
{
    int n;
    Reservations r2;
    str_Dep_St = DeptSt;
    str_Arrival_St = ArrivalSt;
    i_No_Tickets = NoTickets;
    ifstream PaymentsRead;
    PaymentsRead.open("Timetables.txt");
    float ch, ticket;
    string s1, s2, s3, s4;
    int ot = 0;
    while (PaymentsRead >> s1 >> s2 >> ch >> s3 >> s4)
    {
        if ((str_Dep_St == s1) & (str_Arrival_St == s2))
        {
            i_total = CalculateFee(ch, i_No_Tickets);
            ticket = ch;
            ot = 1;
        }
    }
    if (ot != 1)
    {
        cout << "\t\tSorry!! No bus found on your searched route\n"
             << endl;
    }
    else if (ot >= 0)
    {
        char confirmation;
        cout << "\n\nConfirm the Reservation(Y/N): \n\n";
        cin >> confirmation;
        confirmation = tolower(confirmation);
        if (confirmation == 'y')
        {
            fstream Reservations;
            string line;

            n = r2.CheckSeatAvailabilty(DeptSt, ArrivalSt, NoTickets);
            if (n == 1)
            {
                Reservations.open("Reservations.txt", ios ::app | ios ::out | ios ::ate | ios ::in);
                Reservations << customer_id << "\t" << str_Dep_St << "\t" << str_Arrival_St << "\t" << i_No_Tickets
                             << "\t" << i_total << "\n";
                Reservations.close();
                cout << "\n\t\t\t*** RESERVATION IS SUCCESSFUL!! ***\n"
                     << endl;
                r2.Show(customer_id, str_Dep_St, str_Arrival_St, i_No_Tickets, ticket, i_total);
            }
        }
        else
            cout << "\n\n\t\t***Confirmation Denied***\n";
    }
}
// modify Reservation function
void Reservations ::SearchFile_and_Update(int log_customerid)
{
    int new_ticket_no;
    count01 = 0;
    Reservations r1;
    double ch;
    char confirmation;
    ifstream reservationsIn;
    fstream reservationsOut;
    cout << "\n\nConfirm that you want to modify reservation(Y/N): \n\n";
    cin >> confirmation;
    confirmation = tolower(confirmation);
    if (confirmation == 'y')
    {

        Payments P1;
        P1.Show();
        cout << "\n\nEnter your Customer ID:\n\n";
        cin >> str_customer_id;
        cout << "\n\n--------------------------------------------------------------------------------\n\n";
        cout << "\n\nDeparture station\n\n ";
        cin >> str_Dep_St;
        cout << "\n\n Arrival station\n\n ";
        cin >> str_Arrival_St;
        cout << "\n\n-------------------------------------------------\n\n";
        cout << "\n\nEnter New  No. of Tickets\n\n ";
        cin >> i_No_Tickets; // new no of tickets
        fstream PaymentsRead;

        PaymentsRead.open("Timetables.txt", ios ::in);
        string s1, s2, s3, s4, s5, s6, s7, s8;
        while (PaymentsRead >> s1 >> s2 >> ch >> s7 >> s8)
        {
            if ((str_Dep_St == s1) & (str_Arrival_St == s2))
            {
                i_total = CalculateFee(ch, i_No_Tickets);
            }
        }
        reservationsIn.open("Reservations.txt");
        int s10;
        while (reservationsIn >> s10 >> s2 >> s3 >> s4 >> s5)
        {
            reservationsOut.open("temp7.txt", ios ::app);
            if ((s10 == log_customerid) & (s2 == str_Dep_St) & (s3 == str_Arrival_St))
            {
                new_ticket_no = i_No_Tickets - stoi(s4);
                int n = CheckSeatAvailabilty(str_Dep_St, str_Arrival_St, new_ticket_no);
                if (n == 1)
                {
                    reservationsOut << log_customerid << "\t" << str_Dep_St << "\t" << str_Arrival_St << "\t" << i_No_Tickets
                                    << "\t" << i_total << "\n";
                    cout << "\n\t\tRecord found & updated!\n\n";
                    cout << "\n-------------------------------------------------\n";
                    count01++;
                }
            }
            else
            {
                reservationsOut << s10 << "\t" << s2 << "\t" << s3 << "\t" << s4 << "\t" << s5 << "\n";
            }
            reservationsOut.close();
        } // end of while
        if (count01 == 0)
        {
            cout << "\n\n\t\tSorry, Record could not be found!\n\n";
            remove("temp7.txt");
        }
        else if (count01 != 0)
        {
            remove("Reservations.txt");
            rename("temp7.txt", "Reservations.txt");
            r1.Show(log_customerid, str_Dep_St, str_Arrival_St, i_No_Tickets, ch, i_total);
        }
        reservationsOut.close();
    }
    else
    {
        cout << "\n\t\t***Confirmation Denied!!***\n"
             << endl;
    }
}
void Reservations ::Deletes(int log_customerid)
{
    int cntr5 = 0;
    char confirmation;
    int customer_id;
    string dept, arr;
    int nt, tot;
    ifstream ResIn;
    ofstream ResOut;
    cout << "\n\nConfirm to "
         << "Cancel"
         << " the Reservation of your Customer ID (y/n): \n\n";
    cin >> confirmation;
    confirmation = tolower(confirmation);
    if (confirmation == 'y')
    {
        cout << "\n\n--------------------------------------------------------------------------------\n\n";
        cout << "\n\nEnter your Customer ID :\n\n";
        cin >> str_customer_id;
        cout << "\n\nDepature station\n\n ";
        cin >> str_Dep_St;
        cout << "\n\n Arrival station\n\n ";
        cin >> str_Arrival_St;
        cout << "\n\n-------------------------------------------------\n\n";
        ResIn.open("Reservations.txt");
        ResOut.open("temp5.txt", ios ::app);
        while (ResIn >> customer_id >> dept >> arr >> nt >> tot)
        {
            if ((customer_id == log_customerid) & (dept == str_Dep_St) & (arr == str_Arrival_St))
            {
                int n = CheckSeatAvailabilty(str_Dep_St, str_Arrival_St, -nt);
            }
            else
            {
                ResOut << customer_id << "\t" << dept << "\t" << arr << "\t" << nt << "\t" << tot << "\n";
                cntr5++;
            }
        }
        ResOut.close();
        if (cntr5 == 0)
        {
            cout << "\n\nRecord  could not be found!\n\n";
            remove("temp5.txt");
        }
        else if (cntr5 > 0)
        {
            remove("Reservations.txt");
            rename("temp5.txt", "Reservations.txt");
            cout << "\n\n\t\t***Your Reservation Cancelled Successfully!!***\n\n\n";
        }
        ResIn.close();
    }
    else
    {
        cout << "\n\t\t***Confirmation Denied!!***" << endl;
    }
}
void Reservations ::Show(int customer_id, string Dept_St, string Arrival_St, int No_Tickets, int Charge, int total)
{
    string s6, s7, s8, s9, s10;
    string deptime, arrtime;
    fstream time;
    time.open("Timetables.txt");
    while (time >> s6 >> s7 >> s8 >> s9 >> s10)
    {
        if ((s6 == Dept_St) & (s7 == Arrival_St))
        {
            deptime = s9;
            arrtime = s10;
        }
    }
    cout << "\n\n\t**************************************************************\n"
         << "\t\t\t\t      "
         << "INDIAN ROADWAYS"
         << "\n\n"
         << "\t\tCustomer ID :" << customer_id << "\n\n"
         << "\t\tDep. St. : "
         << left << setw(20) << Dept_St << "\t"
         << "Departure Time: " << deptime << "\n\n"
         << "\t\tArrival St. : "
         << left << setw(17) << Arrival_St << "\t"
         << "Arrival Time: " << arrtime << "\n\n"
         << "\t\tNo. of Tickets :" << No_Tickets << "\n\n"
         << "\t\tCharge for one ticket : " << Charge << "\n\n"
         << "\t\t\t---------------------------------\n"
         << "\n\t\t\t\tTotal Fare = " << total << "\n"
         << "\n\t***************************************************************\n";
}
void Reservations ::Show(int log_customerid)
{
    int cntr20 = 0;
    int s1;
    string s2, s3, s4, s5;
    string s6, s7, s8, s9, s10;
    string deptime, arrtime;
    cout << "\n\nEnter your Customer ID:\n\n";
    cin >> str_customer_id;
    cout << "\n\n-----------------------------------------------------------------------------------\n\n";
    cout << "\n\n Depature station\n\n ";
    cin >> str_Dep_St;
    cout << "\n\n Arrival station\n\n ";
    cin >> str_Arrival_St;
    fstream read;
    read.open("Reservations.txt");
    fstream time;
    time.open("Timetables.txt");
    while (time >> s6 >> s7 >> s8 >> s9 >> s10)
    {
        if ((s6 == str_Dep_St) & (s7 == str_Arrival_St))
        {
            deptime = s9;
            arrtime = s10;
        }
    }
    while (read >> s1 >> s2 >> s3 >> s4 >> s5)
    {
        if ((s1 == log_customerid) & (s2 == str_Dep_St) & (s3 == str_Arrival_St))
        {
            cout << "\n\n\t**********************************************************************\n"
                 << "\t\t\t\t    "
                 << "INDIAN ROADWAYS"
                 << "\n\n"
                 << "\t\tCustomer ID :" << s1 << "\n\n"
                 << "\t\tDep. St. : "
                 << left << setw(20) << s2 << "\t"
                 << "Departure Time: " << deptime << "\n\n"
                 << "\t\tArrival St. : "
                 << left << setw(17) << s3 << "\t"
                 << "Arrival Time: " << arrtime << "\n\n"
                 << "\t\tNo. of Tickets :" << s4 << "\n\n"
                 << "\t\t\t---------------------------------\n"
                 << "\n\t\t\t\tTotal Fare = " << s5 << "\n"
                 << "\n\t***********************************************************************\n";
            cntr20++;
        }
    }
    read.close();
    if (cntr20 == 0)
    {
        cout << "\n\n\t\t***Record Not Found!!***" << endl;
    }
}
// Reservations Destructor
Reservations ::~Reservations() {}
// Payments Calculate
double Reservations ::CalculateFee(double fee, int nt)
{
    i_total = nt * fee;
    return i_total;
}

// generates a unique customer_id
string gen_id()
{
    long long x = 190000;
    int count = 1;
    string line;
    /* Creating input filestream */
    ifstream file("Passenger.txt");
    string s1, s2, s3, s4, s5, s6, id;
    while (file >> s1 >> s2 >> s3 >> s4 >> s5 >> s6)
    {
        count++;
    }
    id = to_string(x + count + 1);
    return id;
}

// **************************************** Bus - End *******************************************

class TicketBooking : public UPI
{
public:
    void menu();
    void menuFlight();
    int menuBus();
    void menuMovie();
};

void TicketBooking::menu()
{
    while (1)
    {
        int choice;
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t~~~~~~~~~~ Ticket Booking ~~~~~~~~~~\n\n\n";
        cout << "\t\t\t\t\t\t\t1. Bus Ticket\n\n";
        cout << "\t\t\t\t\t\t\t2. Flight Ticket\n\n";
        cout << "\t\t\t\t\t\t\t3. Movie Ticket\n\n";
        cout << "\t\t\t\t\t\t\t4. Return to Main Menu\n\n";
        cout << "\t\t\t\t\t\t\t-----------------------------------------\n\n";
        cout << "\t\t\t\t\t\t\tYour Choice : ";
        cin >> choice;
        getchar();
        switch (choice)
        {
        case 1:
            menuBus();
            break;
        case 2:
            menuFlight();
            break;
        case 3:
            menuMovie();
            break;
        case 4:
            return;
        default:
            cout << "\t\t\t\t\t\t\tInvalid Choice. Try Again\n";
            break;
        }
    }
}

void TicketBooking::menuFlight()
{
    DetailsofPassenger d;
    SourceAndDest d1;
    CancelMYTicket C;
    CheckStatus C2;
    system("cls");

    cout << "\t*******************************************************************************" << endl;
    cout << "\t*                                                                             *" << endl;
    cout << "\t*                   WELCOME TO AIRLINES BOOKING *                             *" << endl;
    cout << "\t*             __________________________________________                      *" << endl;
    cout << "\t*                                                                             *" << endl;
    cout << "\t*******************************************************************************" << endl;

    cout << "\n \n\t\t\t Please Select one of the options" << endl;
    cout << " \t\t_____________________________________________" << endl;
    cout << "\n\n\t\t\t<1>.Flight Booking" << endl
         << " \t\t\t<2>.Cancel Ticket" << endl
         << "\t\t\t<3>.Check Ticket Status" << endl
         << "\t\t\t<4>.Help" << endl;
    cout << "\t\t\t<5>.Return back to Ticket Booking Menu" << endl;
    cout << "\n\t\t Please enter your choice : ";

    int choice;

    cin >> choice;
    string s;
    switch (choice)
    {
    case 1:
        system("cls");
        cout << "    \t\t\t************************************" << endl;
        cout << "    \t\t\t* WELCOME TO TICKET BOOKING SYSTEM *" << endl;
        cout << "    \t\t\t************************************" << endl;
        //  d1.input();
        d1.showData();
        // d.Payment();

        cout << "\t\tPress any key to go in main Menu back" << endl;
        getch();
        return menu();
        break;
    case 2:
        C.TicketCancel();
        cout << "\n\n\t\tPress any key to go in main Menu back" << endl;
        getch();
        return menu();

        break;
    case 3:
        system("cls");

        cout << "\t\t             TICKET STATUS                 " << endl;
        cout << "\t\t_________________________________________" << endl;

        C2.DisplayStatus();
        cout << "\n\t\tPress any key to go in main Menu back" << endl;
        getch();
        return menu();

    case 4:
        system("cls");

        cout << "\n\n\n\n";
        cout << "\t\t\t\tPlease read the Instruction Carefully" << endl;
        cout << "\t\t\t________________________________________________________\n\n\n\n";
        cout << "The following instructions pertain to medical clearance andfitness nto fly. kindly complete all details of MEDIF (Medical Information Form)while  making your booking. most people with existing medical conditions are able  to fly"
                "on a commercial aircraft without difficulty. however on flight the cabin air is pressurized and precautions are sometimes needed if you have a respiratoryor heart problem.It is recommended that you check any vaccination requirements at least six weeks prior to your departure and carry adequate travel insurance to cover any medical costs incurred abroad. most medical cases are straightforward, but others require  assessment. in some cases, you may be asked to travel with a medical escort or with supplementary oxygen. your fitness to fly is based on internationally accepted criteria, the aim being to ensure that you have a safe."
             << endl;

        cout << "\t\tPress any key to go in main Menu back" << endl;
        getch();
        return menu();
        break;
    case 5:
        break;

    default:
        cout << "\t\t\tYou Entered wrong choice" << endl;
        cout << "\t\t\tPlease press any key to go back" << endl;
        getch();

        return menu();
    }
}

int TicketBooking::menuBus()
{
    int mainchoice, subChoiceOne, nt, choice;
    string name, customer_id, City, Password, UserName, ContactNumber, DepSt, ArrSt;
    try
    {
    mainMenu:
        system("cls");
        cout << "\n\n\t\t\t   "
             << "###### BUS TICKET BOOKING #####"
             << "\n\n";
        cout << "\n\n\t\t\t\t1.Customer\n\n"
             << "\t\t\t\t2.Reservation\n\n"
             << "\t\t\t\t3.Exit\n\n"
             << "Enter your choice :";
        try
        {
            cin >> mainchoice;
            if ((mainchoice != 1) & (mainchoice != 2) & (mainchoice != 3))
            {
                throw 11;
            }
        }
        catch (int x)
        {
            cout << "\n\n Please select a Relevant Number from the menu \n\n";
            return menuBus();
        }
        switch (mainchoice)
        {
        case 1:
        {
        subMenu:
            system("cls");
            cout << "===================================================================================\n"
                 << "\n\n\t\t\t\t1.Register\n\n"
                 << "\t\t\t\t2.Modify\n\n"
                 << "\t\t\t\t3.Remove Account\n\n"
                 << "\t\t\t\t4.Go Back to Main Menu\n\n"
                 << "Enter your choice :";
            try
            {
                cin >> subChoiceOne;
                if ((subChoiceOne != 1) & (subChoiceOne != 2) & (subChoiceOne != 3) & (subChoiceOne != 4))
                {
                    throw 12;
                }
            }
            catch (int y)
            {
                cout << "\n\nError - Please select a Relevant Number from the menu \n\n";
                goto subMenu;
            }
            switch (subChoiceOne)
            {
            case 1:
            {
                system("cls");
                cout << "===================================================================================\n";
                cout << "\t\t\t"
                     << "REGISTER HERE!!"
                     << "\n\n";
                cout << "\t(Please fill in this information for the Registration)\n";
                cout << "Note: All entries in the form should be of one word and should not contain spaces.";
                cout << "\n\nPassenger Name:\n\n";
                cin >> name;
                cout << "\n\nPassenger City:\n\n ";
                cin >> City;
            contact:
                cout << "\n\nPassenger : Contact No\n\n ";
                cin >> ContactNumber;
                if (ContactNumber.size() > 10 || ContactNumber.size() < 10)
                {
                    cout << "\n\t\t!!!!Please Enter Valid Contact Number:!!!!" << endl;
                    goto contact;
                }
                cout << "\n\nPassenger : UserName \n\n ";
                cin >> UserName;
                // make the password protective
                customer_id = (gen_id());
                cout << "\n\t\tYour Customer ID is: " << customer_id << endl;
                cout << "\tRemember this for login and other future purposes.\n"
                     << endl;
                Passenger P1(name, customer_id, City, ContactNumber, UserName, Password);
                cout << "\n\tEnter any key to return to Main Menu : ";
                cin >> choice;
                getchar();
                goto mainMenu;
            }; // Sub  choice first case
            break;
            case 2:
            {
                Passenger P2;
                int n = P2.Login();
                if (n)
                {
                    P2.SearchFile_and_Update(n);
                }
                cout << "\n\tEnter any key to return : ";
                cin >> choice;
                getchar();
                goto subMenu;
            };
            break;
            case 3:
            {
                Passenger P3;
                int n = P3.Login();
                if (!n)
                {
                    cout << "\n\tEnter any key to return : ";
                    cin >> choice;
                    getchar();
                    goto subMenu;
                }
                P3.Deletes(n);
                cout << "\n\tEnter any key to return : ";
                cin >> choice;
                getchar();
                goto subMenu;
            };
            break;
            case 4:
                cout << "\n\tEnter any key to return to Main Menu : ";
                cin >> choice;
                getchar();
                goto mainMenu;
                break;
            } // sub switch one
        };    // main choice first case
        break;
        case 2:
        {

        subMenu2:
            int subChoice2;
            system("cls");
            cout << "===================================================================================="
                 << "\n\n\t\t\t\t1.Make a Reservation\n\n"
                 << "\t\t\t\t2.Modify Reservation\n\n"
                 << "\t\t\t\t3.Cancel Reservation\n\n"
                 << "\t\t\t\t4.Show Reservation\n\n"
                 << "\t\t\t\t5.Go Back to Main Menu"
                 << "\n\nEnter your choice :";
            try
            {
                cin >> subChoice2;
                if ((subChoice2 != 1) & (subChoice2 != 2) & (subChoice2 != 3) & (subChoice2 != 4) & (subChoice2 != 5))
                {
                    throw 13;
                }
            }
            catch (int y)
            {
                cout << "\n\nError - Please select a Relevant Number from the menu \n\n";
                cout << "\n\tEnter any key to return : ";
                cin >> choice;
                getchar();
                goto subMenu2;
            }
            switch (subChoice2)
            {
            case 1:
            {
                Reservations R2;
                int n = R2.Login();
                if (!n)
                {
                    cout << "Try Again!!" << endl;
                    cout << "\n\tEnter any key to return : ";
                    cin >> choice;
                    getchar();
                    goto subMenu2;
                }
                char check = 'y';
                if (check == 'y')
                {
                    Payments Pa1;
                    cout << "\nPassenger Customer ID:\n\n";
                    cin >> customer_id;
                    Pa1.Show();
                    string search1, search2;
                    cout << "\n\n Enter Your Depature station\n\n ";
                    cin >> DepSt;
                    cout << "\n\n Enter Your Arrival station\n\n ";
                    cin >> ArrSt;
                    cout << "\n\nNo. of Tickets\n\n ";
                    cin >> nt;
                    Reservations R2(n, DepSt, ArrSt, nt);
                    cout << "\n\tEnter any key to return to Main Menu : ";
                    cin >> choice;
                    getchar();
                    goto mainMenu;
                }
            };
            break;
            case 2:
            {
                system("cls");
                Reservations R3;
                int n = R3.Login();
                if (!n)
                {
                    cout << "\n\tEnter any key to return : ";
                    cin >> choice;
                    getchar();
                    goto subMenu2;
                }
                R3.SearchFile_and_Update(n);
                cout << "\n\tEnter any key to return : ";
                cin >> choice;
                getchar();
                goto subMenu2;
            };
            break;
            case 3:
            {
                Reservations R4;
                int n = R4.Login();
                if (!n)
                {
                    cout << "\n\tEnter any key to return : ";
                    cin >> choice;
                    getchar();
                    goto subMenu2;
                }
                R4.Deletes(n);
                cout << "\n\tEnter any key to return to Main Menu : ";
                cin >> choice;
                getchar();
                goto mainMenu;
            };
            break;
            case 4:
            {
                Reservations myr;
                int n = myr.Login();

                myr.Show(n);
                cout << "\n\tEnter any key to return to Main Menu : ";
                cin >> choice;
                getchar();
                goto mainMenu;
            }
            break;
            case 5:
                cout << "\n\tEnter any key to return to Main Menu : ";
                cin >> choice;
                getchar();
                goto mainMenu;
                break;
            } // second sub switch end
        };
        break;
        case 3:
        {
            cout << "\n\nThanks for Using Our Service! Hope to see you again!\n\n";
            break;
        };
        } // main switch end
    }
    catch (...)
    {
        cout << "\n\nUnexpected Error occoured, Program is terminating!!\n\n";
        exit(0);
    }
    return 0;
}

void TicketBooking::menuMovie()
{
    int k = 0;
    details d;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t************************************" << endl;
        cout << "\t\t\t\t\t\t\t*       MOVIE TICKET BOOKING       *" << endl;
        cout << "\t\t\t\t\t\t\t************************************\n\n"
             << endl;
        cout << "\n\t\t\t\t\t\t\tEnter \n\n";
        cout << "\t\t\t\t\t\t\t1. Book Movie Ticket.\n\n";
        cout << "\t\t\t\t\t\t\t2. My Booking History.\n\n";
        cout << "\t\t\t\t\t\t\t3. Return Back.\n\n";
        cout << "\t\t\t\t\t\t\tYour choice :    ";
        cin >> k;
        if (k == 1)
        {
            d.input();
            d.book();
            d.add();
        }
        else if (k == 2)
            d.display();
        else if (k == 3)
        {
            cout << "\n\t\t\t\t\t<<------!!!!  Exiting movie ticket booking section   !!!!------>>\n";
            break;
        }
        else
            cout << "\t\t\t\t\t\t\t!! Wrong input !!  Enter again.\n\n";
    } while (k != 3);
    return;
}

// **************************************** Paytm - Start *******************************************
class Paytm : public UPI
{
    Bills_Recharges br;
    TicketBooking bt;

public:
    void menu();
};

void Paytm::menu()
{
    while (2)
    {
        mainMenu();

        while (1)
        {
            int choice;
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t#########################################\n";
            cout << "\t\t\t\t\t\t\t#                 PAYTM                 #\n";
            cout << "\t\t\t\t\t\t\t#########################################\n\n\n";
            cout << "\t\t\t\t\t\t\t1. Money Transfer\n\n";
            cout << "\t\t\t\t\t\t\t2. Recharges and Bills\n\n";
            cout << "\t\t\t\t\t\t\t3. Tickets Booking\n\n";
            cout << "\t\t\t\t\t\t\t4. Logout\n\n";
            cout << "\t\t\t\t\t\t\t5. Exit\n\n";
            cout << "\t\t\t\t\t\t\t-----------------------------------------\n\n";
            cout << "\t\t\t\t\t\t\tYour Choice : ";
            cin >> choice;
            getchar();
            switch (choice)
            {
            case 1:
                MenuScreen();
                break;
            case 2:
                br.menu();
                break;
            case 3:
                bt.menu();
                break;
            case 4:
                choice = -1;
                break;
            case 5:
                cout << "\n\n\t\t\t\t\t\t\t#########################################\n";
                cout << "\t\t\t\t\t\t\t#        Thanks For Using Paytm         #\n";
                cout << "\t\t\t\t\t\t\t#########################################\n\n\n";
                exit(0);
            default:
                cout << "\t\t\t\t\t\t\tInvalid Choice. Try Again\n";
                break;
            }
            if (choice == -1)
            {
                break;
            }
        }
    }
}
// **************************************** Paytm - End *******************************************
int main()
{
    Paytm p;
    p.menu();
    return 0;
}
