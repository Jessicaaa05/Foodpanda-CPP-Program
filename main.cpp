#include "utils.cpp"
#include "restaurant.cpp"
#include "menu.cpp"
#include "delivery.cpp"

int main()
{
    srand(time(0));

    vector<AddOn> globalAddOns = {
        {1, "Extra Cheese", 2.00},
        {2, "Tomato Sauce", 0.50},
        {3, "Fried Egg", 1.50},
        {4, "Extra Sambal", 1.00},
        {5, "Add Fried Mandu (2pcs)", 4.00},
        {6, "Extra Salmon Slices", 12.00},
        {7, "Add Bacon Stripe", 3.00},
        {8, "Extra Rice", 2.00},
        {9, "Add Chicken Slices", 4.50},
        {10, "Extra Noodle", 2.50}};

    vector<Restaurant> restaurants = {
        {1, "Moon's Kitchen", "D'Pulze Mall, Cyberjaya", "Western", "Cyberjaya", 4.5, 30.0, 5.0, {{"Grilled Chicken", 18.50, {1, 2}}, {"Mushroom Soup", 7.00, {}}, {"Sirloin Steak", 36.90, {1, 7}}, {"Fish and Chips", 19.50, {2}}, {"Iced Lemon Tea", 4.50, {}}}, 0.0},
        {2, "Texas BBQ Barn Restaurant", "Prima 3, Cyberjaya", "Western", "Cyberjaya", 4.4, 30.0, 5.0, {{"Smoked Beef Brisket", 29.90, {1}}, {"Coleslaw side", 4.50, {}}, {"BBQ Pulled Chicken Burger", 18.00, {1, 7}}, {"Mac and Cheese", 12.50, {1}}, {"Root Beer Float", 6.00, {}}}, 0.0},
        {3, "Ekues Cabin Cafe", "Taman Ekuestrian, Putrajaya", "Western", "Putrajaya", 4.3, 35.0, 6.0, {{"Chicken Chop", 16.00, {1, 2}}, {"Wedges", 6.50, {2}}, {"Beef Meatballs", 14.00, {1}}, {"Carbonara Pasta", 17.50, {1, 7}}, {"Hot Latte", 9.00, {}}}, 0.0},
        {4, "Las Palace Corner", "Presint 9, Putrajaya", "Western", "Putrajaya", 4.2, 35.0, 6.0, {{"Lamb Chop", 24.00, {2}}, {"Garlic Bread", 5.00, {}}, {"Chicken Grill", 18.00, {1, 2}}, {"Spaghetti Aglio Olio", 14.50, {7}}, {"Sirap Bandung", 3.50, {}}}, 0.0},
        {5, "Anmour Cafe", "Puchong Jaya, Puchong", "Western", "Puchong", 4.6, 40.0, 7.0, {{"Carbonara Pasta", 19.80, {1, 7}}, {"Onion Rings", 8.00, {2}}, {"Crispy Chicken Chop", 21.00, {1, 2}}, {"Signature Pork Chop", 26.50, {7}}, {"Peach Tea", 6.50, {}}}, 0.0},
        {6, "Soru Station", "Bandar Puteri, Puchong", "Western", "Puchong", 4.4, 40.0, 7.0, {{"Platter Combo A", 35.00, {1, 7}}, {"Ice Lemon Tea", 4.00, {}}, {"Cheesy Chicken Chop", 18.90, {1}}, {"Grilled Lamb Shoulder", 26.00, {2}}, {"Mushroom Fries", 8.50, {1}}}, 0.0},
        {7, "90's Steak House", "Taman Connaught, Cheras", "Western", "Cheras", 4.5, 40.0, 7.0, {{"Ribeye Steak", 38.00, {1, 7}}, {"Mashed Potato", 6.00, {}}, {"T-Bone Steak", 49.00, {7}}, {"Grilled Salmon", 32.50, {2}}, {"Chocolate Milkshake", 11.00, {}}}, 0.0},
        {8, "Anmour Cafe", "Cheras Traders Square, Cheras", "Western", "Cheras", 4.6, 40.0, 7.0, {{"Bolognese Pasta", 18.90, {1, 7}}, {"Mushroom Soup", 7.50, {}}, {"Striploin Steak", 39.90, {7}}, {"Fried Calamari", 14.00, {2}}, {"Ice Blended Mocha", 12.00, {}}}, 0.0},
        {9, "Soru Station", "Saga Highland, Ampang", "Western", "Ampang", 4.3, 40.0, 7.0, {{"Chicken Grill Platter", 22.00, {1, 2}}, {"French Fries", 6.00, {2}}, {"Spaghetti Seafood Olio", 19.50, {7}}, {"Beef Burger Deluxe", 16.00, {1, 7}}, {"Sky Juice", 1.50, {}}}, 0.0},

        {10, "Kor.B Korean Restaurant", "Shaftsbury Square, Cyberjaya", "Korean", "Cyberjaya", 4.6, 40.0, 8.0, {{"Kimchi Jjigae", 18.00, {3, 8}}, {"Tteokbokki", 14.00, {1}}, {"Gimbap Classic", 12.00, {}}, {"Bulgogi Deopbap", 19.50, {3, 8}}, {"Korean Barley Tea", 3.00, {}}}, 0.0},
        {11, "AKP Korean Cafe", "Tamarind Square, Cyberjaya", "Korean", "Cyberjaya", 4.4, 40.0, 8.0, {{"Korean Fried Chicken", 22.50, {1}}, {"Ramen", 12.00, {3, 10}}, {"Cheese Soy Chicken", 24.00, {1}}, {"Kimchi Fried Rice", 15.00, {3}}, {"Sikhye Rice Drink", 5.50, {}}}, 0.0},
        {12, "K Garden Korean BBQ", "IOI City Mall, Putrajaya", "Korean", "Putrajaya", 4.5, 50.0, 10.0, {{"Bulgogi Beef Set", 32.00, {3, 8}}, {"Kimchi", 4.00, {}}, {"Galbi Short Ribs", 45.00, {8}}, {"Pork Belly Slices", 29.00, {1, 8}}, {"Cold Green Tea", 3.50, {}}}, 0.0},
        {13, "Jangsajang Deopbap", "Conezion Commercial, Putrajaya", "Korean", "Putrajaya", 4.5, 50.0, 10.0, {{"Chicken Deopbap", 19.50, {3, 8}}, {"Green Tea", 3.00, {}}, {"Beef Rice Bowl", 23.00, {3, 8}}, {"Salmon Deopbap", 27.50, {8}}, {"Fried Dumplings", 8.00, {5}}}, 0.0},
        {14, "HelloPan Korean Sizzling Hot", "Bandar Puteri, Puchong", "Korean", "Puchong", 4.3, 45.0, 9.0, {{"Sizzling Dakgalbi", 24.00, {1, 8}}, {"Cheese Topping", 3.50, {}}, {"Spicy Squid Sizzling", 26.50, {8}}, {"Rabokki Pan", 19.00, {1}}, {"Yuzu Soda", 7.00, {}}}, 0.0},
        {15, "Myung-Ga BBQ", "IOI Boulevard, Puchong", "Korean", "Puchong", 4.6, 45.0, 9.0, {{"Samgyeopsal Pork Set", 35.00, {8}}, {"Cold Noodles", 16.00, {10}}, {"Marinated Pork Ribs", 38.00, {8}}, {"Sundubu Jjigae", 20.00, {3, 8}}, {"Korean Citron Tea", 6.00, {}}}, 0.0},
        {16, "SEOUL VIBE Korean Restaurant", "Cheras Selatan, Cheras", "Korean", "Cheras", 4.4, 45.0, 9.0, {{"Bibimbap Bowl", 17.50, {3}}, {"Korean Pancake", 15.00, {}}, {"Yangnyeom Chicken", 23.00, {1}}, {"Japchae Noodles", 16.50, {9}}, {"Milkis Soda", 5.00, {}}}, 0.0},
        {17, "한그릇 HANGEULEUS", "Taman Segar, Cheras", "Korean", "Cheras", 4.7, 45.0, 9.0, {{"Jajangmyeon Noodles", 19.00, {3, 5}}, {"Fried Mandu", 10.00, {5}}, {"Tangsuyuk Sour Pork", 28.00, {}}, {"Jjambong Seafood Soup", 22.00, {10}}, {"Corn Tea", 3.00, {}}}, 0.0},
        {18, "Sweetree Restaurant", "Jalan Ampang Putra, Ampang", "Korean", "Ampang", 4.5, 45.0, 9.0, {{"Bulgogi Beef Hotpot", 28.00, {8, 10}}, {"Banana Milk", 6.00, {}}, {"Seafood Pancake", 22.00, {}}, {"Spicy Rice Cake", 14.50, {1}}, {"Aloe Vera Juice", 5.50, {}}}, 0.0},
        {19, "Ogos Korean BBQ Restaurant", "Ampang Point, Ampang", "Korean", "Ampang", 4.2, 45.0, 9.0, {{"Spicy Pork Belly", 26.00, {8}}, {"Steamed Egg", 8.00, {}}, {"Kimchi Soup Base", 15.00, {3}}, {"Soy Garlic Chicken Wings", 18.00, {1}}, {"Iced Green Tea", 3.00, {}}}, 0.0},

        {20, "Furu Japanese Restaurant", "Verdi Eco-Dominiums, Cyberjaya", "Japanese", "Cyberjaya", 4.7, 50.0, 10.0, {{"Salmon Sashimi", 25.00, {6}}, {"Miso Soup", 4.00, {}}, {"Ebi Tempura", 18.50, {}}, {"Chicken Katsu Curry", 22.00, {8}}, {"Hot Ocha", 2.50, {}}}, 0.0},
        {21, "Omulah Teppanyaki", "D'Pulze Mall, Cyberjaya", "Japanese", "Cyberjaya", 4.4, 50.0, 10.0, {{"Beef Teppanyaki", 24.50, {8}}, {"Garlic Fried Rice", 6.00, {3}}, {"Chicken Teppan", 18.00, {8}}, {"Salmon Teppanyaki", 28.00, {6, 8}}, {"Iced Green Tea", 3.00, {}}}, 0.0},
        {22, "Nippon Sushi Putrajaya", "Ayer8, Putrajaya", "Japanese", "Putrajaya", 4.5, 40.0, 8.0, {{"California Roll", 14.00, {}}, {"Chawanmushi", 4.50, {}}, {"Salmon Mentai Sushi", 16.50, {6}}, {"Tori Karaage", 12.00, {}}, {"Matcha Ice Cream", 7.00, {}}}, 0.0},
        {23, "Robata Sushi & Grill @ IOI Mall", "IOI City Mall, Putrajaya", "Japanese", "Putrajaya", 4.6, 55.0, 12.0, {{"Unagi Don Bowl", 38.00, {8}}, {"Green Tea", 3.00, {}}, {"Yakitori Skewers", 14.00, {}}, {"Soft Shell Crab Temaki", 12.50, {}}, {"Saba Shioyaki", 19.00, {8}}}, 0.0},
        {24, "iSHIN Fine Dine @ Puchong", "Bandar Puteri, Puchong", "Japanese", "Puchong", 4.8, 60.0, 15.0, {{"Tempura Platter", 28.00, {}}, {"Agedashi Tofu", 8.00, {}}, {"Wagyu Beef Don", 85.00, {3, 8}}, {"Sashimi Moriawase", 65.00, {6}}, {"Premium Matcha", 12.00, {}}}, 0.0},
        {25, "Shin Zushi Puchong", "Bandar Puteri, Puchong", "Japanese", "Puchong", 4.7, 45.0, 9.0, {{"Mentai Salmon Sushi", 16.00, {6}}, {"Ebi Furai", 12.00, {}}, {"Teriyaki Chicken Don", 17.50, {3, 8}}, {"Sukiyaki Beef Pot", 26.00, {10}}, {"Cold Ocha", 2.50, {}}}, 0.0},
        {26, "Warakuya Japanese Restaurant", "Cheras Traders Square, Cheras", "Japanese", "Cheras", 4.6, 50.0, 10.0, {{"Katsu Curry Rice", 21.00, {3, 8}}, {"Gyoza Side", 9.00, {5}}, {"Warakuya Pizza", 18.50, {1}}, {"Sashimi Salad", 22.00, {6}}, {"Calpis Soda", 6.50, {}}}, 0.0},
        {27, "Papasan Canteen", "Cheras Awana, Cheras", "Japanese", "Cheras", 4.5, 40.0, 8.0, {{"Oishii Salmon Don", 23.00, {3, 6, 8}}, {"Tamago Yaki", 5.00, {}}, {"Papasan Roll", 26.00, {}}, {"Squid Ink Pasta", 24.50, {}}, {"Houjicha Cold", 4.50, {}}}, 0.0},
        {28, "Sakura Sushi", "Taman Melawati, Ampang", "Japanese", "Ampang", 4.3, 35.0, 6.0, {{"Tuna Mayo Roll", 12.50, {}}, {"Edamame", 4.00, {}}, {"Chicken Katsu Don", 15.00, {3, 8}}, {"Takoyaki Platter", 9.50, {}}, {"Mineral Water", 2.00, {}}}, 0.0},
        {29, "Yaki Yaki by SBC", "Jalan Ampang, Ampang", "Japanese", "Ampang", 4.4, 45.0, 9.0, {{"Chicken Teriyaki Bento", 19.90, {3, 8}}, {"Takoyaki", 8.00, {}}, {"Yakisoba Noodles", 15.50, {10}}, {"Ebi Mayo Roll", 18.00, {}}, {"Coke", 3.50, {}}}, 0.0},

        {30, "Soi 55 Thai Kitchen - Cyberjaya", "CBD Perdana 3, Cyberjaya", "Thai", "Cyberjaya", 4.5, 30.0, 5.0, {{"Seafood Tom Yum", 18.00, {8, 10}}, {"Thai Milk Tea", 5.50, {}}, {"Pineapple Fried Rice", 15.00, {3}}, {"Pad Kra Pao", 14.50, {3, 8}}, {"Mango Sticky Rice", 10.00, {}}}, 0.0},
        {31, "10 Thai", "Glomac Cyberjaya, Cyberjaya", "Thai", "Cyberjaya", 4.3, 30.0, 5.0, {{"Green Chicken Curry", 16.50, {8}}, {"White Rice", 2.00, {8}}, {"Thai Fish Cake", 12.00, {}}, {"Pad Thai Prawn", 15.50, {10}}, {"Thai Green Milk Tea", 6.00, {}}}, 0.0},
        {32, "ParaThai @ IOI City Mall", "IOI City Mall, Putrajaya", "Thai", "Putrajaya", 4.6, 45.0, 9.0, {{"Pineapple Fried Rice", 19.00, {3}}, {"Mango Sticky Rice", 12.00, {}}, {"Red Tom Yum Prawn", 26.00, {8, 10}}, {"Pandan Chicken Slices", 18.00, {}}, {"Lemongrass Iced Tea", 7.50, {}}}, 0.0},
        {33, "Chakri Village Thai Fusion", "Alamanda Mall, Putrajaya", "Thai", "Putrajaya", 4.4, 40.0, 8.0, {{"Pad Thai Noodles", 15.00, {10}}, {"Pandan Chicken", 14.00, {}}, {"Tom Yum Clear Soup", 19.50, {8}}, {"Minced Chicken Basil", 16.00, {3, 8}}, {"Thai Coconut Water", 6.50, {}}}, 0.0},
        {34, "Restoran Basic Thai", "Bandar Puteri, Puchong", "Thai", "Puchong", 4.2, 30.0, 5.0, {{"Red Tom Yum Soup", 15.50, {8, 10}}, {"Thai Omelette", 7.00, {3}}, {"Garlic Fried Pork", 16.50, {8}}, {"Stir Fried Glass Noodles", 13.00, {10}}, {"Herbal Lemongrass", 4.00, {}}}, 0.0},
        {35, "VITONG THAI CUISINE", "Puchong Jaya, Puchong", "Thai", "Puchong", 4.5, 35.0, 6.0, {{"Basil Minced Chicken", 14.00, {3, 8}}, {"Singha Soda", 4.00, {}}, {"Clear Tom Yum Seafood", 22.00, {10}}, {"Stir Fry Kailan Salted Fish", 12.50, {8}}, {"Thai Mango Salad", 10.00, {}}}, 0.0},
        {36, "Baan Thai @ Pudu Ulu", "Pudu Ulu, Cheras", "Thai", "Cheras", 4.6, 40.0, 8.0, {{"Steam Fish Lemon", 39.00, {8}}, {"Stir Fry Kangkung", 9.00, {4}}, {"BBQ Pork Neck Platter", 28.00, {}}, {"Thai Red Curry Chicken", 18.00, {8}}, {"Iced Herbal Tea", 4.50, {}}}, 0.0},
        {37, "Sun Thai Food (Muslim Friendly)", "Taman Midah, Cheras", "Thai", "Cheras", 4.4, 30.0, 5.0, {{"Claypot Glass Noodles", 22.00, {10}}, {"Lemongrass Juice", 4.50, {}}, {"Vegetable Tom Yum", 15.00, {8}}, {"Fried Turmeric Chicken", 14.00, {4, 8}}, {"Thai Tea Ice", 5.00, {}}}, 0.0},
        {38, "Nakhon Thai Restaurant", "Ampang Point, Ampang", "Thai", "Ampang", 4.3, 35.0, 6.0, {{"Clear Tom Yum Fish", 24.00, {8}}, {"Papaya Salad", 9.50, {4}}, {"Green Curry Beef", 22.00, {8}}, {"Pineapple Seafood Rice", 17.00, {3}}, {"Chrysanthemum Tea", 3.50, {}}}, 0.0},
        {39, "Restoran Tomyam Kaw", "Kampung Pandan, Ampang", "Thai", "Ampang", 4.1, 25.0, 4.0, {{"Beef Tom Yum Skillet", 16.00, {8, 10}}, {"Iced Sirap", 2.50, {}}, {"Mee Celup Special", 8.50, {10}}, {"Telur Bungkus", 7.50, {3}}, {"Teh O Ais Limau", 3.00, {}}}, 0.0},

        {40, "Canton Boy @ Dpulze", "D'Pulze Mall, Cyberjaya", "Chinese", "Cyberjaya", 4.6, 40.0, 8.0, {{"Siew Mai Dim Sum", 10.50, {}}, {"Steamed Prawn Cheong Fun", 12.00, {}}, {"BBQ Chicken Bun", 9.00, {}}, {"Golden Egg Tart (3pcs)", 9.50, {}}, {"Iced HK Milk Tea", 6.50, {}}}, 0.0},
        {41, "Restoran Hinz Kitchen", "Taman Tasik, Cyberjaya", "Chinese", "Cyberjaya", 4.3, 30.0, 5.0, {{"Sweet & Sour Pork Rice", 13.00, {3, 8}}, {"Chinese Herbal Tea", 2.50, {}}, {"Ginger Onion Beef Rice", 14.50, {3, 8}}, {"Wat Tan Hor Noodles", 11.00, {10}}, {"Fried Chicken Wing", 8.00, {}}}, 0.0},
        {42, "Le Mei Chinese Restaurant", "Le Méridien, Putrajaya", "Chinese", "Putrajaya", 4.8, 80.0, 20.0, {{"Roasted Peking Duck", 68.00, {8}}, {"Premium Pu-Er Tea", 12.00, {}}, {"Abalone Soup Pot", 95.00, {}}, {"X.O Sauce Fried Rice", 38.00, {3}}, {"Chilled Mango Sago", 16.00, {}}}, 0.0},
        {43, "Mohd Chan Restaurant @ Putrajaya", "Presint 15, Putrajaya", "Chinese", "Putrajaya", 4.4, 35.0, 6.0, {{"Kam Heong Chicken Rice", 14.50, {3, 8}}, {"Yong Chow Fried Rice", 12.00, {3}}, {"Butter Prawn Slices", 24.00, {8}}, {"Classic Sweet Sour Fish", 22.00, {8}}, {"Luo Han Guo Drink", 4.50, {}}}, 0.0},
        {44, "siong tong gai", "Bandar Puteri, Puchong", "Chinese", "Puchong", 4.5, 50.0, 10.0, {{"Steam Asam Fish", 42.00, {8}}, {"Stir Fry Garlic Qing Long", 14.00, {}}, {"Signature Tofu Pot", 18.00, {8}}, {"Crispy Fried Pork Belly", 26.50, {8}}, {"Iced Jasmine Tea", 4.00, {}}}, 0.0},
        {45, "湘粤楼 Restoran Xiang Yue", "Puchong Jaya, Puchong", "Chinese", "Puchong", 4.4, 40.0, 8.0, {{"Kung Pao Chicken", 16.00, {3, 8}}, {"Claypot Tofu", 12.00, {8}}, {"Sweet and Sour Pork", 22.00, {8}}, {"Fried Garlic Ribs", 28.00, {}}, {"Warm Herbal Tea", 3.50, {}}}, 0.0},
        {46, "Fatt Hei Len Restaurant", "Taman Taynton View, Cheras", "Chinese", "Cheras", 4.6, 40.0, 8.0, {{"Claypot Seafood Pork Belly", 26.00, {8}}, {"White Rice", 2.00, {8}}, {"Steamed Tilapia Ginger", 38.00, {8}}, {"Marmite Chicken Pieces", 18.00, {8}}, {"Lohan Tea Pitcher", 7.00, {}}}, 0.0},
        {47, "Hau Kee Seafood Restaurant", "Taman Segar, Cheras", "Chinese", "Cheras", 4.4, 45.0, 9.0, {{"Butter Prawns", 32.00, {}}, {"Salted Egg Squid", 24.00, {}}, {"Kam Heong Clams", 18.50, {4}}, {"Claypot Kangkong Belacan", 13.00, {4}}, {"Iced Sugarcane Juice", 5.00, {}}}, 0.0},
        {48, "Foong Foong Yong Tau Foo", "Kampung Baru Ampang, Ampang", "Chinese", "Ampang", 4.6, 30.0, 5.0, {{"Mixed Yong Tau Foo (6pcs)", 15.00, {}}, {"Herbal Jelly", 5.00, {}}, {"Fried Fuchuk Slices", 10.00, {}}, {"Dumpling Soup Bowl", 12.00, {10}}, {"Chrysanthemum Ice", 3.00, {}}}, 0.0},
        {49, "Mei Kuan Charcoal Claypot Rice", "Bandar Baru Ampang, Ampang", "Chinese", "Ampang", 4.5, 30.0, 5.0, {{"Charcoal Claypot Chicken Rice", 14.00, {3, 8}}, {"Soup of the Day", 6.00, {}}, {"Claypot Waxed Meat Rice", 18.00, {8}}, {"Stir Fried Lettuce", 10.00, {}}, {"Iced Chinese Tea", 1.50, {}}}, 0.0}};

    string customerName, customerPhone;
    string selectedLocation, customerAddress;

    showWelcomeBanner();
    getCustomerInfo(customerName, customerPhone);
    selectDeliveryRegion(selectedLocation, customerAddress);

    bool systemRunning = true;

    while (systemRunning)
    {
        string selectedCuisine = selectCuisine();

        vector<Restaurant> availableRestaurants =
            getAvailableRestaurants(
                restaurants,
                selectedCuisine,
                selectedLocation);

        displayRestaurantList(
            availableRestaurants,
            selectedCuisine,
            selectedLocation);

        Restaurant selectedRes = selectRestaurant(availableRestaurants);

        cout << "\n==================================================\n";
        cout << "         ✓ Restaurant Selected Successfully\n";
        cout << "==================================================\n";
        cout << " Restaurant : " << selectedRes.name << "\n";
        cout << " Location   : " << selectedRes.address << "\n";
        cout << " Rating     : " << fixed << setprecision(1)
             << selectedRes.rating << "/5\n";
        cout << " Distance   : "
             << to_string_with_precision(selectedRes.currentDistance, 1)
             << " km away\n";

        cout << "==================================================\n";
        cout << "Let's arrange your delivery.\n";

        int serviceChoice;
        string selectedTimeSlot =
            selectDeliveryService(serviceChoice);

        vector<CartItem> cart;
        bool ordering = true;

        while (ordering)
        {
            cout << "\n==================================================\n";
            cout << "              " << selectedRes.name << "\n";
            cout << "==================================================\n";

            if (cart.empty())
            {
                cout << "[1] Browse Menu\n";
                cout << "[2] Change Restaurant / Cuisine\n";

                int option =
                    getValidInt("Choose option (1-2): ", 1, 2);

                if (option == 1)
                {
                    addItemToCart(
                        cart,
                        selectedRes,
                        globalAddOns);
                }
                else
                {
                    ordering = false;
                }
            }
            else
            {
                cout << "[1] Browse Menu\n";
                cout << "[2] View / Edit Basket\n";
                cout << "[3] Checkout\n";
                cout << "[4] Cancel Order\n";

                int option =
                    getValidInt("Choose option (1-4): ", 1, 4);

                if (option == 1)
                {
                    addItemToCart(
                        cart,
                        selectedRes,
                        globalAddOns);
                }
                else if (option == 2)
                {
                    bool goCheckout = handleBasket(cart);

                    if (goCheckout && !cart.empty())
                    {
                        bool finished = checkoutOrder(
                            cart,
                            selectedRes,
                            customerName,
                            customerPhone,
                            customerAddress,
                            selectedLocation,
                            selectedTimeSlot,
                            serviceChoice);

                        if (finished)
                        {
                            return 0;
                        }
                    }
                }
                else if (option == 3)
                {
                    bool finished = checkoutOrder(
                        cart,
                        selectedRes,
                        customerName,
                        customerPhone,
                        customerAddress,
                        selectedLocation,
                        selectedTimeSlot,
                        serviceChoice);

                    if (finished)
                    {
                        return 0;
                    }
                }
                else if (option == 4)
                {
                    char confirmCancel =
                        getYesNoInput("Cancel your current order? (y/n): ");

                    if (confirmCancel == 'y')
                    {
                        cout << "\n✗ ORDER CANCELLED BY "
                             << customerName << ".\n";
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}