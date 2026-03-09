#include <iostream>
#include <iomanip>
#include <string>
#include <limits> 

using namespace std;

const int SLAB1_LIMIT = 100;
const int SLAB2_LIMIT = 300;
const int SLAB3_LIMIT = 500;

const double RATE_SLAB1 = 1.50;
const double RATE_SLAB2 = 2.50;
const double RATE_SLAB3 = 4.00;
const double RATE_SLAB4 = 6.00;

const double FIXED_CHARGE = 50.00;
const double TAX_RATE = 0.18;     

struct Customer {
    string name;
    int customerID;
    int unitsConsumed;
};

double calculateBill(int units) {
    double bill = FIXED_CHARGE;

    if (units <= SLAB1_LIMIT) {
        bill += units * RATE_SLAB1;
    } else if (units <= SLAB2_LIMIT) {
        bill += (SLAB1_LIMIT * RATE_SLAB1) + ((units - SLAB1_LIMIT) * RATE_SLAB2);
    } else if (units <= SLAB3_LIMIT) {
        bill += (SLAB1_LIMIT * RATE_SLAB1) + ((SLAB2_LIMIT - SLAB1_LIMIT) * RATE_SLAB2) + ((units - SLAB2_LIMIT) * RATE_SLAB3);
    } else {
        bill += (SLAB1_LIMIT * RATE_SLAB1) + ((SLAB2_LIMIT - SLAB1_LIMIT) * RATE_SLAB2) + ((SLAB3_LIMIT - SLAB2_LIMIT) * RATE_SLAB3) + ((units - SLAB3_LIMIT) * RATE_SLAB4);
    }

    return bill;
}

double calculateTax(double bill) {
    return bill * TAX_RATE;
}

int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0) {
            return value;
        } else {
            cout << "Invalid input. Please enter a positive number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

Customer getCustomerInput() {
    Customer c;
    cout << "Enter Customer Name   : ";
    getline(cin >> ws, c.name);
    
    c.customerID = getValidInt("Enter Customer ID     : ");
    c.unitsConsumed = getValidInt("Enter Units Consumed  : ");
    
    return c;
}

void printBill(const Customer& c) {
    double bill   = calculateBill(c.unitsConsumed);
    double tax    = calculateTax(bill);
    double total  = bill + tax;

    cout << "\n----------------------------------------\n";
    cout << fixed << setprecision(2);
    cout << "Customer Name    : " << c.name<< "\n";
    cout << "Customer ID      : " << c.customerID<< "\n";
    cout << "Units Consumed   : " << c.unitsConsumed<< " kWh\n";
    cout << "----------------------------------------\n";
    cout << "Slab Rates Applied:\n";
    cout << "  0  - " << setw(3) << SLAB1_LIMIT << "  units @ Rs " << RATE_SLAB1 << "/unit\n";
    cout << setw(4) << SLAB1_LIMIT + 1 << "- " << setw(3) << SLAB2_LIMIT << "  units @ Rs " << RATE_SLAB2 << "/unit\n";
    cout << setw(4) << SLAB2_LIMIT + 1 << "- " << setw(3) << SLAB3_LIMIT << "  units @ Rs " << RATE_SLAB3 << "/unit\n";
    cout << "  " << SLAB3_LIMIT << "+      units @ Rs " << RATE_SLAB4 << "/unit\n";
    cout << "----------------------------------------\n";
    cout << "Fixed Charge : Rs " << FIXED_CHARGE << "\n";
    cout << "Base Amount  : Rs " << bill - FIXED_CHARGE << "\n"; 
    cout << "Bill Amount  : Rs " << bill << "\n";
    cout << "Tax ("<< TAX_RATE * 100 << "% GST): Rs "<< tax<< "\n";
    cout << "----------------------------------------\n";
    cout << "Total Payable: Rs "<< total<< "\n";
    cout << "----------------------------------------\n";
}

int main() {
    Customer customer = getCustomerInput();
    printBill(customer);
    return 0;
}