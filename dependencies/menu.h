#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "structures.h"
using namespace std;

bool isItemInCart(const vector<CartItem> &cart, const string &itemName);
void displayMenu(const Restaurant &selectedRes);
void addItemToCart(
    vector<CartItem> &cart,
    const Restaurant &selectedRes,
    const vector<AddOn> &globalAddOns);
bool handleBasket(vector<CartItem> &cart);

#endif