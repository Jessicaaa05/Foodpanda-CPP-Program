#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "structures.h"
using namespace std;

std::string to_string_with_precision(double value, int n);
char getYesNoInput(std::string prompt);
int getValidInt(std::string prompt, int min, int max);
double calculateSubtotal(const std::vector<CartItem>& cart);
void displayCart(const std::vector<CartItem>& cart);

#endif