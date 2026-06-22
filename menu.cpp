#ifndef MENU_CPP
#define MENU_CPP

#include "utils.cpp"

bool isItemInCart(const vector<CartItem> &cart, const string &itemName)
{
    for (const auto &item : cart)
    {
        if (item.name == itemName)
        {
            return true;
        }
    }
    return false;
}

void displayMenu(const Restaurant &selectedRes)
{
    cout << "\n==================================================\n";
    cout << "                    Browse Menu                    \n";
    cout << "==================================================\n";

    for (size_t i = 0; i < selectedRes.menu.size(); ++i)
    {
        cout << "[" << i + 1 << "] "
             << left << setw(25)
             << selectedRes.menu[i].name
             << "RM "
             << fixed << setprecision(2)
             << selectedRes.menu[i].price
             << "\n";
    }

    cout << "\n[0] Back to Order Options\n";
}

void addItemToCart(
    vector<CartItem> &cart,
    const Restaurant &selectedRes,
    const vector<AddOn> &globalAddOns)
{
    displayMenu(selectedRes);

    int itemChoice = getValidInt(
        "\nSelect an item number to add to your basket: ",
        0,
        selectedRes.menu.size());

    if (itemChoice == 0)
    {
        return;
    }

    MenuItem chosenItem = selectedRes.menu[itemChoice - 1];

    if (isItemInCart(cart, chosenItem.name))
    {
        cout << "\n✗ You've already added this item to your basket.\n";
        cout << "Please update the quantity from your basket instead.\n";
        return;
    }

    cout << "\nSelected Item: " << chosenItem.name << "\n";

    int qty = getValidInt("Quantity: ", 1, 99);

    double finalUnitPrice = chosenItem.price;
    vector<string> selectedAddOns;
    vector<double> selectedAddOnPrices;

    if (!chosenItem.allowedAddOnIds.empty())
    {
        vector<int> displayedAddOnIds;

        cout << "\nWould you like to add anything extra?\n\n";

        for (size_t i = 0; i < chosenItem.allowedAddOnIds.size(); ++i)
        {
            int realAddOnId = chosenItem.allowedAddOnIds[i];
            displayedAddOnIds.push_back(realAddOnId);

            for (const auto &addOn : globalAddOns)
            {
                if (addOn.id == realAddOnId)
                {
                    cout << "[" << i + 1 << "] "
                         << left << setw(25)
                         << addOn.name
                         << "+RM "
                         << fixed << setprecision(2)
                         << addOn.price << "\n";
                }
            }
        }

        cout << "\n[0] Continue\n";

        while (true)
        {
            int addOnChoice = getValidInt(
                "\nSelect an add-on number, or 0 to continue: ",
                0,
                displayedAddOnIds.size());

            if (addOnChoice == 0)
            {
                break;
            }

            int realAddOnId = displayedAddOnIds[addOnChoice - 1];

            for (const auto &addOn : globalAddOns)
            {
                if (addOn.id == realAddOnId)
                {
                    bool alreadyAdded = false;

                    for (const auto &selectedName : selectedAddOns)
                    {
                        if (selectedName == addOn.name)
                        {
                            alreadyAdded = true;
                            break;
                        }
                    }

                    if (alreadyAdded)
                    {
                        cout << "✗ " << addOn.name << " is already added.\n";
                    }
                    else
                    {
                        finalUnitPrice += addOn.price;
                        selectedAddOns.push_back(addOn.name);
                        selectedAddOnPrices.push_back(addOn.price);
                        cout << "✓ " << addOn.name << " added.\n";
                    }
                }
            }
        }
    }

    string itemRemark;
    cout << "\nAdd a note for the restaurant (Optional)\n";
    cout << "Press Enter to skip: ";
    getline(cin, itemRemark);

    cart.push_back({chosenItem.name,
                    chosenItem.price,
                    finalUnitPrice,
                    qty,
                    selectedAddOns,
                    selectedAddOnPrices,
                    itemRemark});

    cout << "\n✓ " << chosenItem.name << " added to your basket.\n";
}

bool handleBasket(vector<CartItem> &cart)
{
    bool basketMenu = true;

    while (basketMenu)
    {
        displayCart(cart);

        cout << "\n[1] Edit an Item\n";
        cout << "[2] Proceed to Checkout\n";
        cout << "[0] Back to Order Options\n";

        int basketChoice = getValidInt("Choose option (0-2): ", 0, 2);

        if (basketChoice == 0)
        {
            return false;
        }

        if (basketChoice == 2)
        {
            return true;
        }

        int itemNo = getValidInt(
            "\nSelect an item to edit, or enter 0 to go back: ",
            0,
            cart.size());

        if (itemNo == 0)
        {
            continue;
        }

        cout << "\nEditing: " << cart[itemNo - 1].name << "\n";
        cout << "Current Quantity: " << cart[itemNo - 1].quantity << "\n";
        cout << "[1] Change Quantity\n";
        cout << "[2] Remove This Item\n";
        cout << "[0] Back to Basket\n";

        int editChoice = getValidInt("Choose option (0-2): ", 0, 2);

        if (editChoice == 1)
        {
            int newQty = getValidInt("Enter new quantity: ", 1, 99);
            cart[itemNo - 1].quantity = newQty;
            cout << "\n✓ Quantity updated successfully.\n";
        }
        else if (editChoice == 2)
        {
            char confirmRemove =
                getYesNoInput("Remove this item from your basket? (y/n): ");

            if (confirmRemove == 'y')
            {
                cout << "\n "
                     << cart[itemNo - 1].name
                     << " removed from basket.\n";

                cart.erase(cart.begin() + itemNo - 1);

                if (cart.empty())
                {
                    cout << "\n Your basket is now empty.\n";
                    return false;
                }
            }
        }
    }

    return false;
}

#endif