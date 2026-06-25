#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>
#include <vector>
#include "structures.h"
using namespace std;

string selectDeliveryService(int &serviceChoice);
double calculateDeliveryFee(double distanceKm);
int calculateETA(double distanceKm);
string getEstimatedArrivalTimeString(int etaMinutes, string &currentTimeStr);
string generateTrackingNumber();
bool checkoutOrder(
    vector<CartItem> &cart,
    const Restaurant &selectedRes,
    const string &customerName,
    const string &customerPhone,
    const string &customerAddress,
    const string &selectedLocation,
    const string &selectedTimeSlot,
    int serviceChoice);

#endif