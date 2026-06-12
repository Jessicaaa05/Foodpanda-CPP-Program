#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream> // For stringstream trimming functionality

using namespace std;

// Struct declarations
// 1. Define what an optional Add-On component consists of
struct AddOn {
    int id;
    string name;
    double price;
};

// 2. Expand your menu item data type to link directly with add-on records
struct MenuItem {
    string name;
    double price;
    vector<int> allowedAddOnIds; // Holds global AddOn IDs (e.g., {1, 2} means it allows Cheese & Tomato Sauce)
};

// 3. Keep your Restaurant definition identical to your current codebase
struct Restaurant {
    int id;
    string name;
    string address;
    string cuisineType;   
    string districtTag;   
    double rating;
    double minSpendForDiscount;
    double discountAmount;
    vector<MenuItem> menu; // Now safely holds the advanced MenuItems
    double currentDistance; 
};

// 4. Update the Cart container to save customized changes per individual item choice
struct CartItem {
    string name;
    double price;         // Tracks final adjusted unit price (Base Price + Selected Add-Ons)
    int quantity;
    vector<string> chosenAddOnNames; // Keeps a clean text record of added items for receipt printing
    string remark;
};

// Helper utility to convert double into string without trailing zeros (e.g. 2.4 instead of 2.400000)
string to_string_with_precision(double val, int precision = 1) {
    stringstream stream;
    stream << fixed << setprecision(precision) << val;
    return stream.str();
}

int main() {
    srand(time(0));

    // Master Add-On Registry (Add this inside main before the restaurants vector)
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
        {10, "Extra Noodle", 2.50}
    };

    vector<Restaurant> restaurants = {
        // === WESTERN FOOD ===
        {1, "Moon's Kitchen", "D'Pulze Mall, Cyberjaya", "Western", "Cyberjaya", 4.5, 30.0, 5.0, 
            {{"Grilled Chicken", 18.50, {1, 2}}, {"Mushroom Soup", 7.00, {}}, {"Sirloin Steak", 36.90, {1, 7}}, {"Fish and Chips", 19.50, {2}}, {"Iced Lemon Tea", 4.50, {}}}, 0.0},
        {2, "Texas BBQ Barn Restaurant", "Prima 3, Cyberjaya", "Western", "Cyberjaya", 4.4, 30.0, 5.0, 
            {{"Smoked Beef Brisket", 29.90, {1}}, {"Coleslaw side", 4.50, {}}, {"BBQ Pulled Chicken Burger", 18.00, {1, 7}}, {"Mac and Cheese", 12.50, {1}}, {"Root Beer Float", 6.00, {}}}, 0.0},
        {3, "Ekues Cabin Cafe", "Taman Ekuestrian, Putrajaya", "Western", "Putrajaya", 4.3, 35.0, 6.0, 
            {{"Chicken Chop", 16.00, {1, 2}}, {"Wedges", 6.50, {2}}, {"Beef Meatballs", 14.00, {1}}, {"Carbonara Pasta", 17.50, {1, 7}}, {"Hot Latte", 9.00, {}}}, 0.0},
        {4, "Las Palace Corner", "Presint 9, Putrajaya", "Western", "Putrajaya", 4.2, 35.0, 6.0, 
            {{"Lamb Chop", 24.00, {2}}, {"Garlic Bread", 5.00, {}}, {"Chicken Grill", 18.00, {1, 2}}, {"Spaghetti Aglio Olio", 14.50, {7}}, {"Sirap Bandung", 3.50, {}}}, 0.0},
        {5, "Anmour Cafe", "Puchong Jaya, Puchong", "Western", "Puchong", 4.6, 40.0, 7.0, 
            {{"Carbonara Pasta", 19.80, {1, 7}}, {"Onion Rings", 8.00, {2}}, {"Crispy Chicken Chop", 21.00, {1, 2}}, {"Signature Pork Chop", 26.50, {7}}, {"Peach Tea", 6.50, {}}}, 0.0},
        {6, "Soru Station", "Bandar Puteri, Puchong", "Western", "Puchong", 4.4, 40.0, 7.0, 
            {{"Platter Combo A", 35.00, {1, 7}}, {"Ice Lemon Tea", 4.00, {}}, {"Cheesy Chicken Chop", 18.90, {1}}, {"Grilled Lamb Shoulder", 26.00, {2}}, {"Mushroom Fries", 8.50, {1}}}, 0.0},
        {7, "90's Steak House", "Taman Connaught, Cheras", "Western", "Cheras", 4.5, 40.0, 7.0, 
            {{"Ribeye Steak", 38.00, {1, 7}}, {"Mashed Potato", 6.00, {}}, {"T-Bone Steak", 49.00, {7}}, {"Grilled Salmon", 32.50, {2}}, {"Chocolate Milkshake", 11.00, {}}}, 0.0},
        {8, "Anmour Cafe", "Cheras Traders Square, Cheras", "Western", "Cheras", 4.6, 40.0, 7.0, 
            {{"Bolognese Pasta", 18.90, {1, 7}}, {"Mushroom Soup", 7.50, {}}, {"Striploin Steak", 39.90, {7}}, {"Fried Calamari", 14.00, {2}}, {"Ice Blended Mocha", 12.00, {}}}, 0.0},
        {9, "Soru Station", "Saga Highland, Ampang", "Western", "Ampang", 4.3, 40.0, 7.0, 
            {{"Chicken Grill Platter", 22.00, {1, 2}}, {"French Fries", 6.00, {2}}, {"Spaghetti Seafood Olio", 19.50, {7}}, {"Beef Burger Deluxe", 16.00, {1, 7}}, {"Sky Juice", 1.50, {}}}, 0.0},

        // === KOREAN FOOD ===
        {10, "Kor.B Korean Restaurant", "Shaftsbury Square, Cyberjaya", "Korean", "Cyberjaya", 4.6, 40.0, 8.0, 
            {{"Kimchi Jjigae", 18.00, {3, 8}}, {"Tteokbokki", 14.00, {1}}, {"Gimbap Classic", 12.00, {}}, {"Bulgogi Deopbap", 19.50, {3, 8}}, {"Korean Barley Tea", 3.00, {}}}, 0.0},
        {11, "AKP Korean Cafe", "Tamarind Square, Cyberjaya", "Korean", "Cyberjaya", 4.4, 40.0, 8.0, 
            {{"Korean Fried Chicken", 22.50, {1}}, {"Ramen", 12.00, {3, 10}}, {"Cheese Soy Chicken", 24.00, {1}}, {"Kimchi Fried Rice", 15.00, {3}}, {"Sikhye Rice Drink", 5.50, {}}}, 0.0},
        {12, "K Garden Korean BBQ", "IOI City Mall, Putrajaya", "Korean", "Putrajaya", 4.5, 50.0, 10.0, 
            {{"Bulgogi Beef Set", 32.00, {3, 8}}, {"Kimchi", 4.00, {}}, {"Galbi Short Ribs", 45.00, {8}}, {"Pork Belly Slices", 29.00, {1, 8}}, {"Cold Green Tea", 3.50, {}}}, 0.0},
        {13, "Jangsajang Deopbap", "Conezion Commercial, Putrajaya", "Korean", "Putrajaya", 4.5, 50.0, 10.0, 
            {{"Chicken Deopbap", 19.50, {3, 8}}, {"Green Tea", 3.00, {}}, {"Beef Rice Bowl", 23.00, {3, 8}}, {"Salmon Deopbap", 27.50, {8}}, {"Fried Dumplings", 8.00, {5}}}, 0.0},
        {14, "HelloPan Korean Sizzling Hot", "Bandar Puteri, Puchong", "Korean", "Puchong", 4.3, 45.0, 9.0, 
            {{"Sizzling Dakgalbi", 24.00, {1, 8}}, {"Cheese Topping", 3.50, {}}, {"Spicy Squid Sizzling", 26.50, {8}}, {"Rabokki Pan", 19.00, {1}}, {"Yuzu Soda", 7.00, {}}}, 0.0},
        {15, "Myung-Ga BBQ", "IOI Boulevard, Puchong", "Korean", "Puchong", 4.6, 45.0, 9.0, 
            {{"Samgyeopsal Pork Set", 35.00, {8}}, {"Cold Noodles", 16.00, {10}}, {"Marinated Pork Ribs", 38.00, {8}}, {"Sundubu Jjigae", 20.00, {3, 8}}, {"Korean Citron Tea", 6.00, {}}}, 0.0},
        {16, "SEOUL VIBE Korean Restaurant", "Cheras Selatan, Cheras", "Korean", "Cheras", 4.4, 45.0, 9.0, 
            {{"Bibimbap Bowl", 17.50, {3}}, {"Korean Pancake", 15.00, {}}, {"Yangnyeom Chicken", 23.00, {1}}, {"Japchae Noodles", 16.50, {9}}, {"Milkis Soda", 5.00, {}}}, 0.0},
        {17, "한그릇 HANGEULEUS", "Taman Segar, Cheras", "Korean", "Cheras", 4.7, 45.0, 9.0, 
            {{"Jajangmyeon Noodles", 19.00, {3, 5}}, {"Fried Mandu", 10.00, {5}}, {"Tangsuyuk Sour Pork", 28.00, {}}, {"Jjambong Seafood Soup", 22.00, {10}}, {"Corn Tea", 3.00, {}}}, 0.0},
        {18, "Sweetree Restaurant", "Jalan Ampang Putra, Ampang", "Korean", "Ampang", 4.5, 45.0, 9.0, 
            {{"Bulgogi Beef Hotpot", 28.00, {8, 10}}, {"Banana Milk", 6.00, {}}, {"Seafood Pancake", 22.00, {}}, {"Spicy Rice Cake", 14.50, {1}}, {"Aloe Vera Juice", 5.50, {}}}, 0.0},
        {19, "Ogos Korean BBQ Restaurant", "Ampang Point, Ampang", "Korean", "Ampang", 4.2, 45.0, 9.0, 
            {{"Spicy Pork Belly", 26.00, {8}}, {"Steamed Egg", 8.00, {}}, {"Kimchi Soup Base", 15.00, {3}}, {"Soy Garlic Chicken Wings", 18.00, {1}}, {"Iced Green Tea", 3.00, {}}}, 0.0},

        // === JAPANESE FOOD ===
        {20, "Furu Japanese Restaurant", "Verdi Eco-Dominiums, Cyberjaya", "Japanese", "Cyberjaya", 4.7, 50.0, 10.0, 
            {{"Salmon Sashimi", 25.00, {6}}, {"Miso Soup", 4.00, {}}, {"Ebi Tempura", 18.50, {}}, {"Chicken Katsu Curry", 22.00, {8}}, {"Hot Ocha", 2.50, {}}}, 0.0},
        {21, "Omulah Teppanyaki", "D'Pulze Mall, Cyberjaya", "Japanese", "Cyberjaya", 4.4, 50.0, 10.0, 
            {{"Beef Teppanyaki", 24.50, {8}}, {"Garlic Fried Rice", 6.00, {3}}, {"Chicken Teppan", 18.00, {8}}, {"Salmon Teppanyaki", 28.00, {6, 8}}, {"Iced Green Tea", 3.00, {}}}, 0.0},
        {22, "Nippon Sushi Putrajaya", "Ayer8, Putrajaya", "Japanese", "Putrajaya", 4.5, 40.0, 8.0, 
            {{"California Roll", 14.00, {}}, {"Chawanmushi", 4.50, {}}, {"Salmon Mentai Sushi", 16.50, {6}}, {"Tori Karaage", 12.00, {}}, {"Matcha Ice Cream", 7.00, {}}}, 0.0},
        {23, "Robata Sushi & Grill @ IOI Mall", "IOI City Mall, Putrajaya", "Japanese", "Putrajaya", 4.6, 55.0, 12.0, 
            {{"Unagi Don Bowl", 38.00, {8}}, {"Green Tea", 3.00, {}}, {"Yakitori Skewers", 14.00, {}}, {"Soft Shell Crab Temaki", 12.50, {}}, {"Saba Shioyaki", 19.00, {8}}}, 0.0},
        {24, "iSHIN Fine Dine @ Puchong", "Bandar Puteri, Puchong", "Japanese", "Puchong", 4.8, 60.0, 15.0, 
            {{"Tempura Platter", 28.00, {}}, {"Agedashi Tofu", 8.00, {}}, {"Wagyu Beef Don", 85.00, {3, 8}}, {"Sashimi Moriawase", 65.00, {6}}, {"Premium Matcha", 12.00, {}}}, 0.0},
        {25, "Shin Zushi Puchong", "Bandar Puteri, Puchong", "Japanese", "Puchong", 4.7, 45.0, 9.0, 
            {{"Mentai Salmon Sushi", 16.00, {6}}, {"Ebi Furai", 12.00, {}}, {"Teriyaki Chicken Don", 17.50, {3, 8}}, {"Sukiyaki Beef Pot", 26.00, {10}}, {"Cold Ocha", 2.50, {}}}, 0.0},
        {26, "Warakuya Japanese Restaurant", "Cheras Traders Square, Cheras", "Japanese", "Cheras", 4.6, 50.0, 10.0, 
            {{"Katsu Curry Rice", 21.00, {3, 8}}, {"Gyoza Side", 9.00, {5}}, {"Warakuya Pizza", 18.50, {1}}, {"Sashimi Salad", 22.00, {6}}, {"Calpis Soda", 6.50, {}}}, 0.0},
        {27, "Papasan Canteen", "Cheras Awana, Cheras", "Japanese", "Cheras", 4.5, 40.0, 8.0, 
            {{"Oishii Salmon Don", 23.00, {3, 6, 8}}, {"Tamago Yaki", 5.00, {}}, {"Papasan Roll", 26.00, {}}, {"Squid Ink Pasta", 24.50, {}}, {"Houjicha Cold", 4.50, {}}}, 0.0},
        {28, "Sakura Sushi", "Taman Melawati, Ampang", "Japanese", "Ampang", 4.3, 35.0, 6.0, 
            {{"Tuna Mayo Roll", 12.50, {}}, {"Edamame", 4.00, {}}, {"Chicken Katsu Don", 15.00, {3, 8}}, {"Takoyaki Platter", 9.50, {}}, {"Mineral Water", 2.00, {}}}, 0.0},
        {29, "Yaki Yaki by SBC", "Jalan Ampang, Ampang", "Japanese", "Ampang", 4.4, 45.0, 9.0, 
            {{"Chicken Teriyaki Bento", 19.90, {3, 8}}, {"Takoyaki", 8.00, {}}, {"Yakisoba Noodles", 15.50, {10}}, {"Ebi Mayo Roll", 18.00, {}}, {"Coke", 3.50, {}}}, 0.0},

        // === THAI FOOD ===
        {30, "Soi 55 Thai Kitchen - Cyberjaya", "CBD Perdana 3, Cyberjaya", "Thai", "Cyberjaya", 4.5, 30.0, 5.0, 
            {{"Seafood Tom Yum", 18.00, {8, 10}}, {"Thai Milk Tea", 5.50, {}}, {"Pineapple Fried Rice", 15.00, {3}}, {"Pad Kra Pao", 14.50, {3, 8}}, {"Mango Sticky Rice", 10.00, {}}}, 0.0},
        {31, "10 Thai", "Glomac Cyberjaya, Cyberjaya", "Thai", "Cyberjaya", 4.3, 30.0, 5.0, 
            {{"Green Chicken Curry", 16.50, {8}}, {"White Rice", 2.00, {8}}, {"Thai Fish Cake", 12.00, {}}, {"Pad Thai Prawn", 15.50, {10}}, {"Thai Green Milk Tea", 6.00, {}}}, 0.0},
        {32, "ParaThai @ IOI City Mall", "IOI City Mall, Putrajaya", "Thai", "Putrajaya", 4.6, 45.0, 9.0, 
            {{"Pineapple Fried Rice", 19.00, {3}}, {"Mango Sticky Rice", 12.00, {}}, {"Red Tom Yum Prawn", 26.00, {8, 10}}, {"Pandan Chicken Slices", 18.00, {}}, {"Lemongrass Iced Tea", 7.50, {}}}, 0.0},
        {33, "Chakri Village Thai Fusion", "Alamanda Mall, Putrajaya", "Thai", "Putrajaya", 4.4, 40.0, 8.0, 
            {{"Pad Thai Noodles", 15.00, {10}}, {"Pandan Chicken", 14.00, {}}, {"Tom Yum Clear Soup", 19.50, {8}}, {"Minced Chicken Basil", 16.00, {3, 8}}, {"Thai Coconut Water", 6.50, {}}}, 0.0},
        {34, "Restoran Basic Thai", "Bandar Puteri, Puchong", "Thai", "Puchong", 4.2, 30.0, 5.0, 
            {{"Red Tom Yum Soup", 15.50, {8, 10}}, {"Thai Omelette", 7.00, {3}}, {"Garlic Fried Pork", 16.50, {8}}, {"Stir Fried Glass Noodles", 13.00, {10}}, {"Herbal Lemongrass", 4.00, {}}}, 0.0},
        {35, "VITONG THAI CUISINE", "Puchong Jaya, Puchong", "Thai", "Puchong", 4.5, 35.0, 6.0, 
            {{"Basil Minced Chicken", 14.00, {3, 8}}, {"Singha Soda", 4.00, {}}, {"Clear Tom Yum Seafood", 22.00, {10}}, {"Stir Fry Kailan Salted Fish", 12.50, {8}}, {"Thai Mango Salad", 10.00, {}}}, 0.0},
        {36, "Baan Thai @ Pudu Ulu", "Pudu Ulu, Cheras", "Thai", "Cheras", 4.6, 40.0, 8.0, 
            {{"Steam Fish Lemon", 39.00, {8}}, {"Stir Fry Kangkung", 9.00, {4}}, {"BBQ Pork Neck Platter", 28.00, {}}, {"Thai Red Curry Chicken", 18.00, {8}}, {"Iced Herbal Tea", 4.50, {}}}, 0.0},
        {37, "Sun Thai Food (Muslim Friendly)", "Taman Midah, Cheras", "Thai", "Cheras", 4.4, 30.0, 5.0, 
            {{"Claypot Glass Noodles", 22.00, {10}}, {"Lemongrass Juice", 4.50, {}}, {"Vegetable Tom Yum", 15.00, {8}}, {"Fried Turmeric Chicken", 14.00, {4, 8}}, {"Thai Tea Ice", 5.00, {}}}, 0.0},
        {38, "Nakhon Thai Restaurant", "Ampang Point, Ampang", "Thai", "Ampang", 4.3, 35.0, 6.0, 
            {{"Clear Tom Yum Fish", 24.00, {8}}, {"Papaya Salad", 9.50, {4}}, {"Green Curry Beef", 22.00, {8}}, {"Pineapple Seafood Rice", 17.00, {3}}, {"Chrysanthemum Tea", 3.50, {}}}, 0.0},
        {39, "Restoran Tomyam Kaw", "Kampung Pandan, Ampang", "Thai", "Ampang", 4.1, 25.0, 4.0, 
            {{"Beef Tom Yum Skillet", 16.00, {8, 10}}, {"Iced Sirap", 2.50, {}}, {"Mee Celup Special", 8.50, {10}}, {"Telur Bungkus", 7.50, {3}}, {"Teh O Ais Limau", 3.00, {}}}, 0.0},

        // === CHINESE FOOD ===
        {40, "Canton Boy @ Dpulze", "D'Pulze Mall, Cyberjaya", "Chinese", "Cyberjaya", 4.6, 40.0, 8.0, 
            {{"Siew Mai Dim Sum", 10.50, {}}, {"Steamed Prawn Cheong Fun", 12.00, {}}, {"BBQ Chicken Bun", 9.00, {}}, {"Golden Egg Tart (3pcs)", 9.50, {}}, {"Iced HK Milk Tea", 6.50, {}}}, 0.0},
        {41, "Restoran Hinz Kitchen", "Taman Tasik, Cyberjaya", "Chinese", "Cyberjaya", 4.3, 30.0, 5.0, 
            {{"Sweet & Sour Pork Rice", 13.00, {3, 8}}, {"Chinese Herbal Tea", 2.50, {}}, {"Ginger Onion Beef Rice", 14.50, {3, 8}}, {"Wat Tan Hor Noodles", 11.00, {10}}, {"Fried Chicken Wing", 8.00, {}}}, 0.0},
        {42, "Le Mei Chinese Restaurant", "Le Méridien, Putrajaya", "Chinese", "Putrajaya", 4.8, 80.0, 20.0, 
            {{"Roasted Peking Duck", 68.00, {8}}, {"Premium Pu-Er Tea", 12.00, {}}, {"Abalone Soup Pot", 95.00, {}}, {"X.O Sauce Fried Rice", 38.00, {3}}, {"Chilled Mango Sago", 16.00, {}}}, 0.0},
        {43, "Mohd Chan Restaurant @ Putrajaya", "Presint 15, Putrajaya", "Chinese", "Putrajaya", 4.4, 35.0, 6.0, 
            {{"Kam Heong Chicken Rice", 14.50, {3, 8}}, {"Yong Chow Fried Rice", 12.00, {3}}, {"Butter Prawn Slices", 24.00, {8}}, {"Classic Sweet Sour Fish", 22.00, {8}}, {"Luo Han Guo Drink", 4.50, {}}}, 0.0},
        {44, "siong tong gai", "Bandar Puteri, Puchong", "Chinese", "Puchong", 4.5, 50.0, 10.0, 
            {{"Steam Asam Fish", 42.00, {8}}, {"Stir Fry Garlic Qing Long", 14.00, {}}, {"Signature Tofu Pot", 18.00, {8}}, {"Crispy Fried Pork Belly", 26.50, {8}}, {"Iced Jasmine Tea", 4.00, {}}}, 0.0},
        {45, "湘粤楼 Restoran Xiang Yue", "Puchong Jaya, Puchong", "Chinese", "Puchong", 4.4, 40.0, 8.0, 
            {{"Kung Pao Chicken", 16.00, {3, 8}}, {"Claypot Tofu", 12.00, {8}}, {"Sweet and Sour Pork", 22.00, {8}}, {"Fried Garlic Ribs", 28.00, {}}, {"Warm Herbal Tea", 3.50, {}}}, 0.0},
        {46, "Fatt Hei Len Restaurant", "Taman Taynton View, Cheras", "Chinese", "Cheras", 4.6, 40.0, 8.0, 
            {{"Claypot Seafood Pork Belly", 26.00, {8}}, {"White Rice", 2.00, {8}}, {"Steamed Tilapia Ginger", 38.00, {8}}, {"Marmite Chicken Pieces", 18.00, {8}}, {"Lohan Tea Pitcher", 7.00, {}}}, 0.0},
        {47, "Hau Kee Seafood Restaurant", "Taman Segar, Cheras", "Chinese", "Cheras", 4.4, 45.0, 9.0, 
            {{"Butter Prawns", 32.00, {}}, {"Salted Egg Squid", 24.00, {}}, {"Kam Heong Clams", 18.50, {4}}, {"Claypot Kangkong Belacan", 13.00, {4}}, {"Iced Sugarcane Juice", 5.00, {}}}, 0.0},
        {48, "Foong Foong Yong Tau Foo", "Kampung Baru Ampang, Ampang", "Chinese", "Ampang", 4.6, 30.0, 5.0, 
            {{"Mixed Yong Tau Foo (6pcs)", 15.00, {}}, {"Herbal Jelly", 5.00, {}}, {"Fried Fuchuk Slices", 10.00, {}}, {"Dumpling Soup Bowl", 12.00, {10}}, {"Chrysanthemum Ice", 3.00, {}}}, 0.0},
        {49, "Mei Kuan Charcoal Claypot Rice", "Bandar Baru Ampang, Ampang", "Chinese", "Ampang", 4.5, 30.0, 5.0, 
            {{"Charcoal Claypot Chicken Rice", 14.00, {3, 8}}, {"Soup of the Day", 6.00, {}}, {"Claypot Waxed Meat Rice", 18.00, {8}}, {"Stir Fried Lettuce", 10.00, {}}, {"Iced Chinese Tea", 1.50, {}}}, 0.0}
    };

    string customerName, customerPhone;
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
    cout << "|_|    \\____/ \\____/|_____/|_| /_/    \\_\\_| \\_|_____/_/    \\_\\        \n";
    cout << "\n";
    
    cout << "--- CUSTOMER REGISTRATION PROFILE ---\n";
    
    cout << "Full Name   : ";
    getline(cin, customerName);
    while (customerName.empty() || customerName.find_first_not_of(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
        cout << "⚠️ Invalid name. Please enter a valid name (letters only): ";
        getline(cin, customerName);
    }

    while (true) {
        cout << "Phone Number: ";
        getline(cin, customerPhone);

        if (customerPhone.length() < 10 || customerPhone.length() > 11) {
            cout << "⚠️ Invalid length. Phone number must be 10 or 11 digits long.\n";
            continue;
        }

        bool isValid = true;
        for (size_t i = 0; i < customerPhone.length(); ++i) {
            if (!isdigit(customerPhone[i])) {
                isValid = false;
                break;
            }
        }
        if (!isValid) {
            cout << "⚠️ Invalid characters detected. Phone number must contain digits only (no letters/spaces).\n";
            continue;
        }
        break;
    }
    
    // District Dropdown Menu
    cout << "\n--- SELECT DELIVERY REGION ---\n";
    cout << "[1] Cyberjaya\n";
    cout << "[2] Putrajaya\n";
    cout << "[3] Puchong\n";
    cout << "[4] Cheras\n";
    cout << "[5] Ampang\n";

    int locationChoice;
    cout << "Select your current location (1-5): ";
    while (!(cin >> locationChoice) || locationChoice < 1 || locationChoice > 5) {
        cout << "⚠️ Invalid selection. Choose a valid option number (1-5): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();

    string selectedLocation;
    string customerAddress;
    if (locationChoice == 1) { selectedLocation = "Cyberjaya"; customerAddress = "Multimedia University (MMU), Cyberjaya"; }
    else if (locationChoice == 2) { selectedLocation = "Putrajaya"; customerAddress = "Alamanda Shopping Centre, Putrajaya"; }
    else if (locationChoice == 3) { selectedLocation = "Puchong"; customerAddress = "IOI Mall Puchong, Bandar Puchong Jaya"; }
    else if (locationChoice == 4) { selectedLocation = "Cheras"; customerAddress = "Leisure Mall Cheras, Taman Segar"; }
    else if (locationChoice == 5) { selectedLocation = "Ampang"; customerAddress = "Ampang Point Shopping Complex, Ampang"; }

    // Cuisine Choice Selection
    cout << "\n--- WHICH TYPES OF CUISINE DO YOU PREFER NOW? 😊 ---\n";
    cout << "[1] Western Food\n";
    cout << "[2] Korean Food\n";
    cout << "[3] Japanese Food\n";
    cout << "[4] Thai Food\n";
    cout << "[5] Chinese Food\n";
    
    int cuisineChoice;
    cout << "Select cuisine type (1-5): ";
    while (!(cin >> cuisineChoice) || cuisineChoice < 1 || cuisineChoice > 5) {
        cout << "⚠️ Invalid choice. Select a valid cuisine number (1-5): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();

    string selectedCuisine;
    if (cuisineChoice == 1) selectedCuisine = "Western";
    else if (cuisineChoice == 2) selectedCuisine = "Korean";
    else if (cuisineChoice == 3) selectedCuisine = "Japanese";
    else if (cuisineChoice == 4) selectedCuisine = "Thai";
    else if (cuisineChoice == 5) selectedCuisine = "Chinese";

    // --- ENHANCED FILTERING STAGE: DYNAMIC DISTANCE GENERATION ---
    // Distances are generated IMMEDIATELY before selecting the restaurant
    vector<Restaurant> availableRestaurants;
    for (auto res : restaurants) { 
        if (res.cuisineType == selectedCuisine) {
            double distanceKm = 0.0;
            if (selectedLocation == res.districtTag) {
                // Same Town Logistics: 1.0 to 4.0 KM
                distanceKm = 1.0 + (double(rand()) / RAND_MAX) * (4.0 - 1.0); 
            } else {
                // Cross-Town Logistics: 6.5 to 14.5 KM max
                distanceKm = 6.5 + (double(rand()) / RAND_MAX) * (14.5 - 6.5); 
            }
            res.currentDistance = distanceKm; // Bind calculated mileage to the object instance
            availableRestaurants.push_back(res);
        }
    }

    // Tabular display showing calculated distance inline before choosing
    cout << "\n===========================================================================================\n";
    cout << "ALL AVAILABLE " << selectedCuisine << " PARTNER OUTLETS (DELIVERING TO " << selectedLocation << ")\n";
    cout << "===========================================================================================\n";
    cout << left << setw(6) << "ID" << setw(45) << "Restaurant Name (Distance)" << setw(35) << "Outlet Hub Location" << "Rating\n";
    cout << "-------------------------------------------------------------------------------------------\n";
    for (size_t i = 0; i < availableRestaurants.size(); ++i) {
        string nameWithDistance = availableRestaurants[i].name + " (" + to_string_with_precision(availableRestaurants[i].currentDistance, 1) + " km)";
        cout << "[" << setw(2) << i + 1 << "]  " 
             << left << setw(45) << nameWithDistance 
             << setw(35) << availableRestaurants[i].address
             << availableRestaurants[i].rating << " ⭐\n";
    }
    cout << "===========================================================================================\n";

    int resChoice;
    cout << "Select a restaurant ID (1-" << availableRestaurants.size() << "): ";
    while (!(cin >> resChoice) || resChoice < 1 || resChoice > (int)availableRestaurants.size()) {
        cout << "⚠️ Invalid choice. Please select from the active vendors: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
    Restaurant selectedRes = availableRestaurants[resChoice - 1];
    cin.ignore(); 

    // Delivery Scheduling System 
    cout << "\n==================================================\n";
    cout << "              SELECT DELIVERY SERVICE TYPE         \n";
    cout << "==================================================\n";
    cout << "[1] Deliver Now\n";
    cout << "[2] Deliver Later (Schedule Order)\n";
    
    int serviceChoice;
    cout << "\nSelect choice (1-2): ";
    while (!(cin >> serviceChoice) || serviceChoice < 1 || serviceChoice > 2) {
        cout << "⚠️ Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();

    string selectedTimeSlot;
    if (serviceChoice == 1) {
        selectedTimeSlot = "Instant Dispatch (Deliver Now)";
    } else {
        cout << "\n--- Available Delivery Slots ---\n";
        cout << "[1] 12:00 PM - 1:00 PM\n";
        cout << "[2] 1:00 PM - 2:00 PM\n";
        cout << "[3] 6:00 PM - 7:00 PM\n";
        cout << "[4] 7:00 PM - 8:00 PM\n";
        
        int timeChoice;
        cout << "\nSelect your specific time slot (1-4): ";
        while (!(cin >> timeChoice) || timeChoice < 1 || timeChoice > 4) {
            cout << "⚠️ Invalid slot. Please choose a valid option (1-4): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore();

        if (timeChoice == 1) selectedTimeSlot = "Scheduled [12:00 PM - 1:00 PM]";
        else if (timeChoice == 2) selectedTimeSlot = "Scheduled [1:00 PM - 2:00 PM]";
        else if (timeChoice == 3) selectedTimeSlot = "Scheduled [6:00 PM - 7:00 PM]";
        else if (timeChoice == 4) selectedTimeSlot = "Scheduled [7:00 PM - 8:00 PM]";
    }

    // Ordering Cart Processing Menu
    vector<CartItem> cart;
    char addMore = 'y';

    while (tolower(addMore) == 'y') {
        cout << "\n--------------------------------------------------\n";
        cout << "   " << selectedRes.name << " - Menu Display\n";
        cout << "--------------------------------------------------\n";
        for (size_t i = 0; i < selectedRes.menu.size(); ++i) {
            cout << "[" << i + 1 << "] " << left << setw(25) << selectedRes.menu[i].name 
                 << "RM " << fixed << setprecision(2) << selectedRes.menu[i].price << "\n";
        }

        int itemChoice;
        cout << "\nSelect item number to add to cart: ";
        while (!(cin >> itemChoice) || itemChoice < 1 || itemChoice > (int)selectedRes.menu.size()) {
            cout << "⚠️ Invalid item selection. Try again: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        int qty;
        cout << "Enter quantity: ";
        while (!(cin >> qty) || qty <= 0) {
            cout << "⚠️ Quantity must be 1 or higher: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(); 

        string itemRemark;
        cout << "Add optional instructions/remarks (or press Enter to skip): ";
        getline(cin, itemRemark);

        MenuItem chosenItem = selectedRes.menu[itemChoice - 1];
        cart.push_back({chosenItem.name, chosenItem.price, qty, itemRemark});

        cout << "\nWould you like to add more items from this vendor? (y/n): ";
        cin >> addMore;
        cin.ignore();
    }

    char cutleryOpt;
    cout << "\n==================================================\n";
    cout << "                FINALIZING CHECKOUT                \n";
    cout << "==================================================\n";
    cout << "Opt-In for One-use dinnerware? (y/n) [RM 0.50 charge]: ";
    cin >> cutleryOpt;

    // --- LOGISTICS SHIPPING VERIFICATION ---
    // Retrieving the EXACT tracking distance mapped during the selection process
    double distanceKm = selectedRes.currentDistance; 

    // Tiered calculation mapping based strictly on the selected restaurant's distance
    double finalDeliveryFee = 3.00; // Base Fee for <= 4.0 KM
    if (distanceKm > 4.0 && distanceKm <= 10.0) {
        finalDeliveryFee = 4.50;    // Tier 2
    } else if (distanceKm > 10.0) {
        finalDeliveryFee = 8.00;    // Tier 3
    }

    cout << "\n==================================================\n";
    cout << "           LIVE ROUTE & LOGISTICS ESTIMATE         \n";
    cout << "==================================================\n";
    cout << "Target Vendor     : " << selectedRes.name << " (" << selectedRes.districtTag << " Outlet)\n";
    cout << "Delivery Dropoff  : " << selectedLocation << "\n";
    cout << "Calculated Distance: " << fixed << setprecision(1) << distanceKm << " KM\n";
    cout << "--------------------------------------------------\n";
    cout << "👉 TOTAL DELIVERY FEE: RM " << fixed << setprecision(2) << finalDeliveryFee << "\n";
    cout << "==================================================\n";
    
    char proceedChoice;
    cout << "Do you want to proceed with this delivery fee? (y/n): ";
    cin >> proceedChoice;

    if (tolower(proceedChoice) != 'y') {
        cout << "\n❌ ORDER CANCELLED BY USER.\n";
        cout << "Thank you for using Foodpanda. Your basket has been cleared.\n";
        cout << "==================================================\n";
        return 0; 
    }

    double subtotal = 0;
    for (const auto& cartItem : cart) {
        subtotal += cartItem.price * cartItem.quantity;
    }

    double discountApplied = 0.0;
    if (subtotal >= selectedRes.minSpendForDiscount) {
        discountApplied = selectedRes.discountAmount;
    }

    double dinnerwareCharge = (tolower(cutleryOpt) == 'y') ? 0.50 : 0.00;
    int predictedEtaMinutes = 10 + (distanceKm * 3.5); 
    double finalGrandTotal = subtotal - discountApplied + finalDeliveryFee + dinnerwareCharge;

    // --- OFFICIAL RECEIPT LAYOUT VIEW ---
    cout << "\n==================================================\n";
    cout << "                FOODPANDA OFFICIAL RECEIPT         \n";
    cout << "==================================================\n";
    cout << "Customer Name   : " << customerName << "\n";
    cout << "Contact Number  : " << customerPhone << "\n"; 
    cout << "Delivery Address: " << customerAddress << "\n";
    cout << "--------------------------------------------------\n";
    cout << "Vendor Outlet   : " << selectedRes.name << "\n";
    cout << "Vendor Address  : " << selectedRes.address << "\n";
    cout << "Delivery Mode   : " << selectedTimeSlot << "\n";
    cout << "Route Distance  : " << fixed << setprecision(1) << distanceKm << " KM\n"; // Matches selection & estimate exactly!
    cout << "--------------------------------------------------\n";
    cout << left << setw(22) << "Item Name" << setw(6) << "Qty" << setw(10) << "Unit Price" << "Line Total\n";
    cout << "--------------------------------------------------\n";

    for (const auto& cartItem : cart) {
        double totalItemLinePrice = cartItem.price * cartItem.quantity;
        cout << left << setw(22) << cartItem.name 
             << setw(6) << cartItem.quantity 
             << "RM " << setw(7) << cartItem.price 
             << "RM " << fixed << setprecision(2) << totalItemLinePrice << "\n";
        if (!cartItem.remark.empty()) {
            cout << "  └─ Request: " << cartItem.remark << "\n";
        }
    }

    cout << "--------------------------------------------------\n";
    cout << right << setw(36) << "Basket Subtotal: RM " << subtotal << "\n";
    if (discountApplied > 0) {
        cout << right << setw(36) << "Vendor Promo Discount: -RM " << discountApplied << "\n";
    }
    cout << right << setw(36) << "Logistics Shipping Fee: RM " << finalDeliveryFee << "\n";
    if (dinnerwareCharge > 0) {
        cout << right << setw(36) << "One-use Dinnerware Charge: RM " << dinnerwareCharge << "\n";
    } else {
        cout << right << setw(36) << "Eco-Cutlery Save: RM " << 0.00 << "\n";
    }
    
    cout << "--------------------------------------------------\n";
    cout << right << setw(36) << "TOTAL PAYABLE BALANCE: RM " << finalGrandTotal << "\n";
    cout << "--------------------------------------------------\n";
    
    if (serviceChoice == 1) {
        cout << "Estimated Delivery Window: " << predictedEtaMinutes << " minutes\n";
    } else {
        cout << "Your order has been queued successfully for your chosen slot.\n";
    }
    cout << "==================================================\n";

    return 0;
}
