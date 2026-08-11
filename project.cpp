#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// ======================= EV Class =======================

class EV
{
public:
    string ownerName;
    string vehicleNumber;
    string vehicleType;
    float batteryCapacity;
};

// ================= Charging Station =====================

class ChargingStation
{
private:
    int totalSlots;
    int availableSlots;

public:
    ChargingStation(int slots = 5)
    {
        totalSlots = slots;
        availableSlots = slots;
    }

    void displaySlots()
    {
        cout << "\n========== Charging Station Status ==========\n";
        cout << "Total Slots     : " << totalSlots << endl;
        cout << "Available Slots : " << availableSlots << endl;
    }

    bool bookSlot()
    {
        if (availableSlots > 0)
        {
            availableSlots--;
            cout << "\nSlot Booked Successfully!\n";
            return true;
        }

        cout << "\nNo Slots Available!\n";
        return false;
    }

    void releaseSlot()
    {
        if (availableSlots < totalSlots)
            availableSlots++;
    }
};

// ===================== Billing ==========================

class Billing
{
public:
    static float generateBill(float units)
    {
        float rate = 18.0;
        return units * rate;
    }
};

// =============== Function Prototypes ====================

void signUp();
bool login();
void evMenu();

// ======================= SIGN UP =======================

void signUp()
{
    while (true)
    {
        string username, password;
        string user, pass;
        bool exists = false;

        cout << "\n========== SIGN UP TO CONTINUE ==========\n";
        cout << "Enter Username : ";
        cin >> username;

        cout << "Enter Password : ";
        cin >> password;

        ifstream infile("users.txt");

        while (infile >> user >> pass)
        {
            if (user == username)
            {
                exists = true;
                break;
            }
        }

        infile.close();

        if (exists)
        {
            cout << "\nUsername already exists!";
            cout << "\nPlease try another username.\n";
            {
                return;
            }
            continue;
        }

        ofstream outfile("users.txt", ios::app);
        outfile << username << " " << password << endl;
        outfile.close();

        cout << "\n CONGRULATIONS ,Signup Successful!\n";
        break;
    }
}

// ======================= LOGIN =======================

bool login()
{
    while (true)
    {
        string username, password;
        string user, pass;

        cout << "\n========== LOGIN TO CONTINUE ==========\n";
        cout << "Enter Username : ";
        cin >> username;

        cout << "Enter Password : ";
        cin >> password;

        ifstream infile("users.txt");

        while (infile >> user >> pass)
        {
            if (user == username && pass == password)
            {
                infile.close();
                cout << "\nLogged in Successful!\n";
                return true;
            }
        }

        infile.close();

        cout << "\nInvalid Username or Password!\n";
        cout << "Do you want to try again? (yes/no) : ";
        string choice;
        cin >> choice;
        if (choice != "yes" && choice != "y")
        {
            return false;
        }
    }
}

// ======================= MAIN =======================

int main()
{
    int choice;

    while (true)
    {
        cout <<            "\n====================================";
        cout <<             "\n====================================";
        cout << "\n          WELCOME TO SMART EV CHARGING STATION";
        cout <<           "\n====================================";
        cout <<         
        "\n====================================";
        cout << "\n1. Sign Up";
        cout << "\n2. Login";
        cout << "\n3. Exit";
        cout << "\n\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            signUp();
            break;

        case 2:
            if (login())
            {
                evMenu();      // Login Successful होने पर EV Menu खुलेगा
            }
            break;

        case 3:
            cout << "\nThank You for Using Smart EV Charging Station!\n";
            return 0;

        default:
            cout << "\nInvalid Choice! Please Try Again.\n";
        }
    }

    return 0;
}

// ======================= EV MENU =======================

void evMenu()
{
    ChargingStation station(20);
    vector<EV> users;

    int choice;

    do
    {
        cout << "\n====================================";
        cout << "\n  SILENT CODERS TEAM WELCOMES YOU TO EV CHARGING STATION";
        cout << "\n====================================";
        cout << "\n1. Register EV";
        cout << "\n2. View Registered EVs";
        cout << "\n3. View Charging Slots";
        cout << "\n4. Book Charging Slot";
        cout << "\n5. Generate Bill";
        cout << "\n6. Logout";
        cout << "\n\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            EV e;

            cin.ignore();

            cout << "\nOwner Name : ";
            getline(cin, e.ownerName);

            cout << "Vehicle Number : ";
            getline(cin, e.vehicleNumber);

            cout << "Vehicle Type : ";
            getline(cin, e.vehicleType);

            cout << "Battery Capacity (kWh) : ";
            cin >> e.batteryCapacity;

            users.push_back(e);

            cout << "\nVehicle Registered Successfully!\n";
            break;
        }

        case 2:
        {
            cout << "\n========== Registered EVs ==========\n";
            if (users.empty())
            {
                cout << "No EVs Registered Yet!\n";
            }
            else
            {
                for (const auto &e : users)
                {
                    cout << "Owner Name      : " << e.ownerName << endl;
                    cout << "Vehicle Number  : " << e.vehicleNumber << endl;
                    cout << "Vehicle Type    : " << e.vehicleType << endl;
                    cout << "Battery Capacity: " << e.batteryCapacity << " kWh" << endl;
                    cout << "-----------------------------------\n";
                }
            }
            break;
        }

        case 3:
        {
            station.displaySlots();
            cout <<"slots displayed successfully";
            break;
        }

        case 4:
        {
            int user,pass;
            station.bookSlot();
            break;
        }

        case 5:
        {
            float units;

            cout << "\nEnter Energy Consumed (kWh) : ";
            cin >> units;

            float amount = Billing::generateBill(units);

            cout << fixed << setprecision(2);
            cout << "\nTotal Bill = rupees" << amount << endl;

            break;
        }

        case 6:
        {
            cout << "\nLogged Out...\n";
            break;
        }

        default:
        {
            cout << "\nInvalid Choice!\n";
            break;
        }
        }
    }
    while (choice != 6);
}