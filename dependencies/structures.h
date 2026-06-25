#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

struct AddOn {
    int id;
    std::string name;
    double price;
};

struct MenuItem {
    std::string name;
    double price;
    std::vector<int> allowedAddOnIds;
};

struct Restaurant {
    int id;
    std::string name;
    std::string address;
    std::string cuisineType;
    std::string districtTag;
    double rating;
    double minSpendForDiscount;
    double discountAmount;
    std::vector<MenuItem> menu;
    double currentDistance;
};

struct CartItem {
    std::string name;
    double basePrice;
    double price;
    int quantity;
    std::vector<std::string> chosenAddOnNames;
    std::vector<double> chosenAddOnPrices;
    std::string remark;
};

#endif