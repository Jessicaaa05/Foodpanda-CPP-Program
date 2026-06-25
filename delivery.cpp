#include "utils.h"
#include "delivery.h"

#include <iostream>
#include <iomanip>
#include <ios>
#include <chrono>
#include <ctime>

string selectDeliveryService(int &serviceChoice)
{
    cout << "\n==================================================\n";
    cout << "              SELECT DELIVERY SERVICE TYPE         \n";
    cout << "==================================================\n";
    cout << "[1] Deliver Now\n";
    cout << "[2] Deliver Later (Schedule Order)\n";

    serviceChoice = getValidInt("Select choice (1-2): ", 1, 2);

    if (serviceChoice == 1)
    {
        return "Instant Dispatch (Deliver Now)";
    }

    cout << "\n--- Available Delivery Slots ---\n";
    cout << "[1] 12:00 PM - 1:00 PM\n";
    cout << "[2] 1:00 PM - 2:00 PM\n";
    cout << "[3] 6:00 PM - 7:00 PM\n";
    cout << "[4] 7:00 PM - 8:00 PM\n";

    int timeChoice = getValidInt("Select your specific time slot (1-4): ", 1, 4);

    if (timeChoice == 1)
        return "Scheduled [12:00 PM - 1:00 PM]";
    if (timeChoice == 2)
        return "Scheduled [1:00 PM - 2:00 PM]";
    if (timeChoice == 3)
        return "Scheduled [6:00 PM - 7:00 PM]";
    return "Scheduled [7:00 PM - 8:00 PM]";
}

double calculateDeliveryFee(double distanceKm)
{
    if (distanceKm <= 4.0)
        return 3.00;
    if (distanceKm <= 10.0)
        return 4.50;
    return 8.00;
}

int calculateETA(double distanceKm)
{
    double constantSpeedKmh = 60.0;
    double travelTimeHours = distanceKm / constantSpeedKmh;
    int travelTimeMinutes = static_cast<int>(travelTimeHours * 60.0);
    
    // Ensure a minimum travel time of 5 minutes so near deliveries look realistic
    if (travelTimeMinutes < 5) travelTimeMinutes = 5; 
    
    return travelTimeMinutes;
}

// Helper to get the current system time and add the ETA minutes to compute arrival time
string getEstimatedArrivalTimeString(int etaMinutes, string &currentTimeStr)
{
    // get the current system clock time
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);
    
    // Format Current Time
    char currentBuffer[20];
    struct tm* timeInfo = localtime(&current_time);
    strftime(currentBuffer, sizeof(currentBuffer), "%I:%M %p", timeInfo);
    currentTimeStr = string(currentBuffer); // Passes current time back out

    // add the ETA minutes to calculate arrival time
    auto arrival_time_point = now + chrono::minutes(etaMinutes);
    time_t arrival_time = chrono::system_clock::to_time_t(arrival_time_point);
    
    char arrivalBuffer[20];
    struct tm* arrivalInfo = localtime(&arrival_time);
    strftime(arrivalBuffer, sizeof(arrivalBuffer), "%I:%M %p", arrivalInfo);
    
    return string(arrivalBuffer);
}

string generateTrackingNumber()
{
    int randomNumber = 100000 + rand() % 900000;
    return "FP" + to_string(randomNumber);
}

bool checkoutOrder(
    vector<CartItem> &cart,
    const Restaurant &selectedRes,
    const string &customerName,
    const string &customerPhone,
    const string &customerAddress,
    const string &selectedLocation,
    const string &selectedTimeSlot,
    int serviceChoice)
{
    char cutleryOpt;

    cout << "\n==================================================\n";
    cout << "                  Review Your Order                \n";
    cout << "==================================================\n";

    while (true)
    {
        cout << "Would you like to include cutlery? (y/n): ";
        cin >> cutleryOpt;
        cutleryOpt = tolower(cutleryOpt);

        if (cutleryOpt == 'y' || cutleryOpt == 'n')
        {
            cin.ignore(10000, '\n');
            break;
        }

        cout << "⚠️ Please enter y or n only.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    double distanceKm = selectedRes.currentDistance;
    double deliveryFee = calculateDeliveryFee(distanceKm);

    cout << "\n==================================================\n";
    cout << "                  Delivery Details                 \n";
    cout << "==================================================\n";
    cout << "Restaurant    : " << selectedRes.name << "\n";
    cout << "Delivering To : " << selectedLocation << "\n";
    cout << "Distance      : " << fixed << setprecision(1) << distanceKm << " KM\n";
    cout << "Delivery Fee  : RM " << fixed << setprecision(2) << deliveryFee << "\n";
    cout << "==================================================\n";

    char proceedChoice =
        getYesNoInput("Proceed with this delivery fee? (y/n): ");

    if (proceedChoice == 'n')
    {
        cout << "\nReturning to your basket. Your order is still saved.\n";
        return false;
    }

    double subtotal = calculateSubtotal(cart);
    double discountApplied = 0.0;

    if (subtotal >= selectedRes.minSpendForDiscount)
    {
        discountApplied = selectedRes.discountAmount;
    }

    double cutleryCharge = (cutleryOpt == 'y') ? 0.50 : 0.00;
    double finalGrandTotal =
        subtotal - discountApplied + deliveryFee + cutleryCharge;

    int predictedEtaMinutes = calculateETA(distanceKm);
    string orderPlacementTime = "";
    string estimatedArrivalTime = getEstimatedArrivalTimeString(predictedEtaMinutes, orderPlacementTime);
    string trackingNumber = generateTrackingNumber();

    cout << "\n==================================================\n";
    cout << "                    Order Summary                  \n";
    cout << "==================================================\n";
    cout << "Tracking Number : " << trackingNumber << "\n";
    cout << "Customer Name   : " << customerName << "\n";
    cout << "Contact Number  : " << customerPhone << "\n";
    cout << "Delivery Address: " << customerAddress << "\n";
    cout << "Restaurant      : " << selectedRes.name << "\n";
    cout << "Delivery Mode   : " << selectedTimeSlot << "\n";
    cout << "--------------------------------------------------\n";

    displayCart(cart);

    cout << "Delivery Fee : RM " << fixed << setprecision(2) << deliveryFee << "\n";
    cout << "Cutlery      : RM " << fixed << setprecision(2) << cutleryCharge << "\n";

    if (discountApplied > 0)
    {
        cout << "Discount     : -RM " << fixed << setprecision(2) << discountApplied << "\n";
    }

    cout << "Total Amount : RM " << fixed << setprecision(2) << finalGrandTotal << "\n";

    if (serviceChoice == 1)
    {
        cout << "Order Time   : " << orderPlacementTime << "\n";
        cout << "Duration     : " << predictedEtaMinutes << " mins\n";
        cout << "Est. Arrival : " << estimatedArrivalTime << "\n";
    }
    else
    {
        cout << "Delivery Slot: " << selectedTimeSlot << "\n";
    }

    cout << "==================================================\n";

    cout << "\n[1] Confirm & Place Order\n";
    cout << "[2] Back to Basket\n";
    cout << "[3] Cancel Order\n";

    int receiptChoice = getValidInt("Choose option (1-3): ", 1, 3);

    if (receiptChoice == 2)
    {
        cout << "\nReturning to your basket. Your order is still saved.\n";
        return false;
    }

    if (receiptChoice == 3)
    {
        cout << "\n❌ ORDER CANCELLED BY " << customerName << ".\n";
        return true;
    }

    cout << "\n==================================================\n";
    cout << "                  🎉 Order Confirmed!              \n";
    cout << "==================================================\n";
    cout << "Tracking Number : " << trackingNumber << "\n";
    cout << "Order Date/Time : " << orderPlacementTime << "\n";

    if (serviceChoice == 1)
    {
        cout << "\nStatus: Your order has been received.\n";
        cout << "Your order has been sent to "
             << selectedRes.name << ".\n";
        cout << "The restaurant is preparing your food now.\n";
        cout << "Est. Reach Time : " 
             << estimatedArrivalTime << " (" << predictedEtaMinutes << " mins transit)\n";
    }
    else
    {
        cout << "\nStatus: Your scheduled order has been confirmed.\n";
        cout << selectedRes.name
             << " will start preparing your food closer to your selected delivery time.\n";
        cout << "Scheduled Delivery Slot: " << selectedTimeSlot << "\n";
    }

    cout << "==================================================\n";
    cout << "\nThank you for ordering with Foodpanda!\n";
    cout << "Enjoy your meal!\n";

    return true;
}