#ifndef UTILS_CPP
#define UTILS_CPP

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cctype>

using namespace std;

struct AddOn
{
    int id;
    string name;
    double price;
};

struct MenuItem
{
    string name;
    double price;
    vector<int> allowedAddOnIds;
};

struct Restaurant
{
    int id;
    string name;
    string address;
    string cuisineType;
    string districtTag;
    double rating;
    double minSpendForDiscount;
    double discountAmount;
    vector<MenuItem> menu;
    double currentDistance;
};

struct CartItem
{
    string name;
    double basePrice;
    double price;
    int quantity;
    vector<string> chosenAddOnNames;
    vector<double> chosenAddOnPrices;
    string remark;
};

string to_string_with_precision(double val, int precision = 1)
{
    stringstream stream;
    stream << fixed << setprecision(precision) << val;
    return stream.str();
}

char getYesNoInput(string prompt)
{
    char choice;

    while (true)
    {
        cout << prompt;
        cin >> choice;
        choice = tolower(choice);

        if (choice == 'y' || choice == 'n')
        {
            cin.ignore(10000, '\n');
            return choice;
        }

        cout << "⚠️ Please enter 'y' for yes or 'n' for no only.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int getValidInt(string prompt, int min, int max)
{
    int value;

    while (true)
    {
        cout << prompt;

        if (cin >> value && value >= min && value <= max)
        {
            cin.ignore(10000, '\n');
            return value;
        }

        cout << "⚠️ Please choose a valid option from "
             << min << " to " << max << ".\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

double calculateSubtotal(const vector<CartItem> &cart)
{
    double subtotal = 0;

    for (const auto &item : cart)
    {
        subtotal += item.price * item.quantity;
    }

    return subtotal;
}

void displayCart(const vector<CartItem> &cart)
{
    if (cart.empty())
    {
        cout << "\n🛒 Your basket is empty. Browse the menu to add something delicious.\n";
        return;
    }

    double subtotal = 0;

    cout << "\n==================================================\n";
    cout << "                    YOUR BASKET 🛒                 \n";
    cout << "==================================================\n";

    for (size_t i = 0; i < cart.size(); ++i)
    {
        double itemTotal = cart[i].price * cart[i].quantity;
        subtotal += itemTotal;

        cout << "\n"
             << i + 1 << ". " << cart[i].name << "\n";
        cout << "   Quantity   : " << cart[i].quantity << "\n";
        cout << "   Price      : RM " << fixed << setprecision(2)
             << cart[i].price << " each\n";

        if (!cart[i].chosenAddOnNames.empty())
        {
            cout << "   Extras     :\n";

            for (size_t j = 0; j < cart[i].chosenAddOnNames.size(); ++j)
            {
                cout << "      + " << left << setw(24)
                     << cart[i].chosenAddOnNames[j]
                     << "RM " << right << setw(6)
                     << fixed << setprecision(2)
                     << cart[i].chosenAddOnPrices[j] << "\n";
            }
        }

        if (!cart[i].remark.empty())
        {
            cout << "   Note       : " << cart[i].remark << "\n";
        }

        cout << "   Item Total : RM " << fixed << setprecision(2)
             << itemTotal << "\n";
        cout << "--------------------------------------------------\n";
    }

    cout << "Subtotal: RM " << fixed << setprecision(2) << subtotal << "\n";
    cout << "==================================================\n";
}

#endif