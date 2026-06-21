#ifndef RESTAURANT_CPP
#define RESTAURANT_CPP

#include "utils.cpp"

void showWelcomeBanner()
{
    cout << "__          ________ _      _____ ____  __  __ ______   _______ ____  \n";
    cout << "\\ \\        / /  ____| |    / ____/ __ \\|  \\/  |  ____| |__   __/ __ \\ \n";
    cout << " \\ \\  /\\  / /| |__  | |   | |   | |  | | \\  / | |__       | | | |  | |\n";
    cout << "  \\ \\/  \\/ / |  __| | |   | |   | |  | | |\\/| |  __|      | | | |  | |\n";
    cout << "   \\  /\\  /  | |____| |___| |___| |__| | |  | | |____     | | | |__| |\n";
    cout << "    \\/  \\/   |______|______\\_____\\____/|_|  |_|______|    |_|  \\____/ \n";
    cout << "                                                                        \n";
    cout << " ______ ____   ____  _____  _____        _   _ _____                   \n";
    cout << "|  ____/ __ \\ / __ \\|  __ \\|  __ \\ /\\   | \\ | |  __ \\   /\\            \n";
    cout << "| |__ | |  | | |  | | |  | | |__) /  \\  |  \\| | |  | | /  \\           \n";
    cout << "|  __|| |  | | |  | | |  | |  ___/ /\\ \\ | . ` | |  | |/ /\\ \\          \n";
    cout << "| |   | |__| | |__| | |__| | |  / ____ \\| |\\  | |__| / ____ \\         \n";
    cout << "|_|    \\____/ \\____/|_____/|_| /_/    \\_\\_| \\_|_____/_/    \\_\\        \n\n";
}

void getCustomerInfo(string &customerName, string &customerPhone)
{
    cout << "--- CUSTOMER REGISTRATION PROFILE ---\n";

    cout << "Full Name   : ";
    getline(cin, customerName);

    while (customerName.empty() ||
           customerName.find_first_not_of(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
    {
        cout << "⚠️ Invalid name. Please enter a valid name (letters only): ";
        getline(cin, customerName);
    }

    while (true)
    {
        cout << "Phone Number: ";
        getline(cin, customerPhone);

        if (customerPhone.length() < 10 || customerPhone.length() > 11)
        {
            cout << "⚠️ Invalid length. Phone number must be 10 or 11 digits long.\n";
            continue;
        }

        bool isValid = true;

        for (size_t i = 0; i < customerPhone.length(); ++i)
        {
            if (!isdigit(customerPhone[i]))
            {
                isValid = false;
                break;
            }
        }

        if (!isValid)
        {
            cout << "⚠️ Invalid characters detected. Phone number must contain digits only.\n";
            continue;
        }

        break;
    }
}

void selectDeliveryRegion(string &selectedLocation, string &customerAddress)
{
    cout << "\n--- SELECT DELIVERY REGION ---\n";
    cout << "[1] Cyberjaya\n";
    cout << "[2] Putrajaya\n";
    cout << "[3] Puchong\n";
    cout << "[4] Cheras\n";
    cout << "[5] Ampang\n";

    int locationChoice = getValidInt("Select your current location (1-5): ", 1, 5);

    if (locationChoice == 1)
    {
        selectedLocation = "Cyberjaya";
        customerAddress = "Multimedia University (MMU), Cyberjaya";
    }
    else if (locationChoice == 2)
    {
        selectedLocation = "Putrajaya";
        customerAddress = "Alamanda Shopping Centre, Putrajaya";
    }
    else if (locationChoice == 3)
    {
        selectedLocation = "Puchong";
        customerAddress = "IOI Mall Puchong, Bandar Puchong Jaya";
    }
    else if (locationChoice == 4)
    {
        selectedLocation = "Cheras";
        customerAddress = "Leisure Mall Cheras, Taman Segar";
    }
    else
    {
        selectedLocation = "Ampang";
        customerAddress = "Ampang Point Shopping Complex, Ampang";
    }
}

string selectCuisine()
{
    cout << "\n--- WHAT ARE YOU CRAVING TODAY? 🍽️ ---\n";
    cout << "[1] Western Food\n";
    cout << "[2] Korean Food\n";
    cout << "[3] Japanese Food\n";
    cout << "[4] Thai Food\n";
    cout << "[5] Chinese Food\n";

    int cuisineChoice = getValidInt("Choose a cuisine (1-5): ", 1, 5);

    if (cuisineChoice == 1)
        return "Western";
    if (cuisineChoice == 2)
        return "Korean";
    if (cuisineChoice == 3)
        return "Japanese";
    if (cuisineChoice == 4)
        return "Thai";
    return "Chinese";
}

vector<Restaurant> getAvailableRestaurants(
    const vector<Restaurant> &restaurants,
    const string &selectedCuisine,
    const string &selectedLocation)
{
    vector<Restaurant> availableRestaurants;

    for (auto res : restaurants)
    {
        if (res.cuisineType == selectedCuisine)
        {
            double distanceKm = 0.0;

            if (selectedLocation == res.districtTag)
            {
                distanceKm = 1.0 + (double(rand()) / RAND_MAX) * (4.0 - 1.0);
            }
            else
            {
                distanceKm = 6.5 + (double(rand()) / RAND_MAX) * (14.5 - 6.5);
            }

            res.currentDistance = distanceKm;
            availableRestaurants.push_back(res);
        }
    }

    return availableRestaurants;
}

void displayRestaurantList(
    const vector<Restaurant> &availableRestaurants,
    const string &selectedCuisine,
    const string &selectedLocation)
{
    const string tableLine =
        "==============================================================================================================";
    const string dashLine =
        "--------------------------------------------------------------------------------------------------------------";

    cout << "\n"
         << tableLine << "\n";
    cout << setw(72) << (selectedCuisine + " Restaurants Near " + selectedLocation) << "\n";
    cout << tableLine << "\n";

    cout << left
         << setw(7) << "No."
         << setw(55) << "Restaurant"
         << setw(35) << "Location"
         << "Rating\n";

    cout << dashLine << "\n";

    for (size_t i = 0; i < availableRestaurants.size(); ++i)
    {
        string nameWithDistance =
            availableRestaurants[i].name + " (" +
            to_string_with_precision(availableRestaurants[i].currentDistance, 1) +
            " km)";

        cout << "[" << right << setw(2) << i + 1 << "]  "
             << left << setw(55) << nameWithDistance
             << setw(35) << availableRestaurants[i].address
             << fixed << setprecision(1)
             << availableRestaurants[i].rating << " ⭐\n";
    }

    cout << tableLine << "\n";
}

Restaurant selectRestaurant(const vector<Restaurant> &availableRestaurants)
{
    int resChoice = getValidInt(
        "Select a restaurant number (1-" + to_string(availableRestaurants.size()) + "): ",
        1,
        availableRestaurants.size());

    return availableRestaurants[resChoice - 1];
}

#endif