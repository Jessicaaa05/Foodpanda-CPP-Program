#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include <vector>
#include "structures.h"
using namespace std;

void showWelcomeBanner();
void getCustomerInfo(string &customerName, string &customerPhone);
void selectDeliveryRegion(string &selectedLocation, string &customerAddress);
string selectCuisine();
vector<Restaurant> getAvailableRestaurants(
    const vector<Restaurant> &restaurants,
    const string &selectedCuisine,
    const string &selectedLocation);
void displayRestaurantList(
    const vector<Restaurant> &availableRestaurants,
    const string &selectedCuisine,
    const string &selectedLocation);
Restaurant selectRestaurant(const vector<Restaurant> &availableRestaurants);

#endif