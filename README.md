#include <iostream>
#include <vector>
#include <iomanip>
#include<fstream>
#include <string>
using namespace std;
// -------------------- EV Structure --------------------
class EV
{
public:
    string ownerName;
    string vehicleNumber;
    string vehicleType;
     float batteryCapacity;
};
// -------------------- Charging Station --------------------
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
        cout << "\n===== Charging Station Status =====\n";
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
// -------------------- Billing --------------------
class Billing
{
public:
    static float generateBill(float units)
    {
        float rate = 18.0;      // ₹18 per kWh
        return units * rate;
    }
};
void signUp()
{
    string username, password;
    string user, pass;
    bool exists = false;

    cout << "\n===== SIGN UP =====\n";
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;

    ifstream in("users.txt");

    while (in >> user >> pass)
    {
        if (user == username)
        {
            exists = true;
            break;
        }
    }

    in.close();

    if (exists)
    {
        cout << "\nUsername Already Exists!\n";
        return;
    }

    ofstream out("users.txt", ios::app);
    out << username << " " << password << endl;
    out.close();

    cout << "\nSignup Successful!\n";
}

bool login()
{
    string username, password;
    string user, pass;

    cout << "\n===== LOGIN =====\n";
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;

    ifstream in("users.txt");

    while (in >> user >> pass)
    {
        if (user == username && pass == password)
        {
            in.close();
            cout << "\nLogin Successful!\n";
            return true;
        }
    }

    in.close();
    cout << "\nInvalid Username or Password!\n";
    return false;
}
// -------------------- Main --------------------
int main()
{
    ChargingStation station(5);
    vector<EV> users;
    int choice;
    int firstChoice;

cout << "==============================\n";
cout << " SMART EV CHARGING STATION\n";
cout << "==============================\n";

cout << "1. Sign Up\n";
cout << "2. Login\n";
cout << "Enter Choice : ";
cin >> firstChoice;

if(firstChoice == 1)
{
    signUp();
}

if(!login())
{
    cout << "\nAccess Denied!\n";
    return 0;
}
    do
    {
        cout << "\n==============================";
        cout << "\n SMART EV CHARGING STATION";
        cout << "\n==============================";
        cout << "\n1. Register EV";
        cout << "\n2. View Charging Slots";
        cout << "\n3. Book Charging Slot";
        cout << "\n4. Generate Bill";
        cout << "\n5. Exit";
        cout << "\n\nEnter Choice : ";
        cin >> choice;
        switch(choice)
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
                cout << "Battery Capacity (kWh): ";
                cin >> e.batteryCapacity;
                users.push_back(e);
                cout << "\nVehicle Registered Successfully!\n";
                break;
            }
            case 2:
            {
                station.displaySlots();
                break;
            }
            case 3:
            {
                station.bookSlot();
                break;
            }
            case 4:
            {
                float units;
                cout << "\nEnter Energy Consumed (kWh): ";
                cin >> units;
                float amount = Billing::generateBill(units);
                cout << fixed << setprecision(2);
                cout << "\nTotal Bill = ₹" << amount << endl;
                break;
            }
            case 5:
            {
                cout << "\nThank You for Using Smart EV Charging Station!\n";
                break;
            }
            default:
            {
                cout << "\nInvalid Choice!\n";
            }
        }
    } while(choice != 5);
    return 0;
}
