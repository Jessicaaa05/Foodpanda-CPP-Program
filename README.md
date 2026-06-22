# Foodpanda C++ Console Application

A modular, high-fidelity C++ console application that simulates an on-demand food delivery infrastructure platform.

---

## System Workflow & Key Features

This console application simulates a streamlined, production-grade food delivery pipeline:

### 1. User Profile Registration

* Prompts for customer **Full Name** and **Phone Number**
* Includes strict input validation:

  * Prevents numeric names
  * Ensures correct phone number digit length

### 2. Choose Delivery Region & Cuisine

* Select a drop-off district:

  * Cyberjaya
  * Putrajaya
  * Puchong
* Choose cuisine preference:

  * Western
  * Korean
  * Japanese
  * Thai
  * Chinese

### 3. Choose Restaurant

* Dynamically generates delivery distances (1.0 – 14.5 KM)
* Displays available restaurants in a structured table:

  * Name
  * Distance
  * Rating

### 4. Choose Menu & Add-ons

* Displays full restaurant menu with pricing
* Supports optional add-ons:

  * Example: *Extra Cheese*, *Fried Egg*
* Add-ons are mapped specifically to each menu item

### 5. Stateful CRUD Cart Management

* Tracks:

  * Items
  * Quantities
  * Add-ons
  * Remarks
* Supports full cart operations:

  * Create
  * Read
  * Update
  * Delete

### 6. Smooth Checkout Process

* Automatically calculates shipping fees based on distance
* Uses system clock for:

  * Order timestamp
  * Estimated delivery time
* Generates:

  * Detailed receipt
  * 6-digit tracking number

---

## Data Model Layout

Core domain models (defined in `utils.cpp`):

```cpp
struct AddOn {
    int id;
    string name;
    double price;
};

struct MenuItem {
    string name;
    double price;
    vector<int> allowedAddOnIds; // Mapped lookup pointers
};

struct Restaurant {
    int id;
    string name;
    string address;
    string cuisineType;
    string districtTag;
    double rating;
    double minSpendForDiscount;
    double discountAmount;
    vector<MenuItem> menu;
    double currentDistance; // Dynamically assigned at runtime
};

struct CartItem {
    string name;
    double basePrice;
    double price; // Final unit price (base + add-ons)
    int quantity;
    vector<string> chosenAddOnNames;
    vector<double> chosenAddOnPrices;
    string remark;
};
```

---

## File System Blueprint

The project follows a **modular architecture**:

```
📁 foodpanda-console-app
│
├── main.cpp        # Entry point, initializes system and global data
├── restaurant.cpp  # Handles onboarding & restaurant filtering
├── menu.cpp        # Menu browsing, add-ons, cart interaction
├── delivery.cpp    # Shipping logic, timing, receipt generation
└── utils.cpp       # Core structs, utilities, validation logic
```

### File Responsibilities

* **main.cpp**

  * System entry point
  * Initializes 49 restaurants across 5 cuisines
  * Controls main runtime loop

* **restaurant.cpp**

  * User onboarding
  * Region & cuisine selection
  * Restaurant filtering

* **menu.cpp**

  * Menu display
  * Add-on selection loops
  * Cart state management

* **delivery.cpp**

  * Delivery fee calculation
  * Time estimation
  * Receipt rendering

* **utils.cpp**

  * Struct definitions
  * Helper functions
  * Input validation utilities

---

## Compilation & Execution

Make sure you have a C++ compiler (C++11 or newer).

```bash
# Clone the repository
git clone https://github.com/your-username/foodpanda-console-app.git

# Navigate into the project
cd foodpanda-console-app

# Compile the project
g++ -std=c++11 main.cpp -o foodpanda_service

# Run the application
./foodpanda_service
```

---

## Project Context

This project serves as an **engineering case study** demonstrating how modern digital aggregator platforms operate.

It highlights:

* Structured workflow management
* Stateful system design
* Real-world delivery logic simulation
* Clean modular architecture

By replacing manual processes with programmatic logic, this system mirrors the core mechanics behind real-world food delivery platforms like Foodpanda, GrabFood, and Uber Eats.

---

## 💡 Key Learning Outcomes

* Modular C++ system design
* State management using vectors
* Input validation and user interaction loops
* Simulation of real-world logistics systems
* Clean separation of concerns

---
