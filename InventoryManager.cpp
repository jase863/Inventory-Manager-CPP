#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;

// class for inventory items to be made and edited
class InventoryItem {
    public:

        // initialize item attributes
        float _price = 0;
        string _item = "";
        int _itemQuantity = 0;
        
        // items are created by passing item, price, and quantity arguments
        InventoryItem(string item, float price, int itemQuantity) {

            _item = item;
            _price = price;
            _itemQuantity = itemQuantity;

        };

        // getters and setters to return item attributes or change them
        string getItem() {
            return _item;
        }

        void setItem(string newItem) {
            _item = newItem;
        }

        float getPrice() {
            return _price;
        }

        void setPrice(float newPrice) {
            _price = newPrice;
        }

        int getItemQuantity() {
            return _itemQuantity;
        }

        void setItemQuantity(int newItemQuantity) {
            _itemQuantity = newItemQuantity;
        }
};

// -------------------- FUNCTION DECLARATIONS --------------------

bool checkIfInMenuNumbers(string menu_choice);

bool checkIfInListLength(int userChoice, vector<InventoryItem> inventoryList);

InventoryItem SetInfo();

string ViewItems(vector<InventoryItem> inventory);

string AddItemInfo();

float AddItemPrice(string itemToAdd);

int AddItemQuantity();

vector<InventoryItem> ChooseEdit(vector<InventoryItem> inventory);

vector<InventoryItem> EditItem(int itemNumber, vector<InventoryItem> inventory);

vector<InventoryItem> EditPrice(int itemNumber, vector<InventoryItem> inventory);

vector<InventoryItem> EditQuantity(int itemNumber, vector<InventoryItem> inventory);

float CalculateTotal(vector<InventoryItem> inventory, bool requestTotal = false);

vector<InventoryItem> TakeItem(vector<InventoryItem> inventory);


// ---------------------------------------------------------------

int main(){

    bool isInMenuNumbers = false;
    
    cout << "Welcome to Inventory Manager!\n";
 
    string menuChoice = "";

    vector<InventoryItem> itemsInInventory;


    // main menu UI for adding, editing, and viewing items
    while (menuChoice != "6")
    {
        cout << "\n\nMain Menu" << "\n" << "____________________";
        cout << "\n1. Add Item\n2. View Items\n3. Edit Item\n4. Calculate Total\n5. Take From Inventory\n6. Quit\n";
        cout << "____________________\n\nPlease Enter a Menu Option: ";
        
        cin >> menuChoice;

        isInMenuNumbers = checkIfInMenuNumbers(menuChoice);

        if (isInMenuNumbers && menuChoice != "6") {

            if (menuChoice == "1") {
                itemsInInventory.push_back(SetInfo());
            }

            else if (menuChoice == "2") {
                ViewItems(itemsInInventory);
            }
            
            else if (menuChoice == "3") {                
                itemsInInventory = ChooseEdit(itemsInInventory);
            }

            else if (menuChoice == "4") {
                CalculateTotal(itemsInInventory, true);
            }

            else if (menuChoice == "5") {
                itemsInInventory = TakeItem(itemsInInventory);
            }
        }

        else if (!isInMenuNumbers){
            cout << "That is not a menu option. Please type the number of the menu option you would like to use.";
        }

        else{
            cout << "\nThank you for using Inventory Manager";
            this_thread::sleep_for(chrono::seconds(2));
        }
    } 
}

// -------------------- FUNCTION DEFINITIONS AND DESCRIPTIONS --------------------

// this function loops through a list of the menu option numbers and checks to see if the number entered by the user is in the list.
// if it is, the function will return true; otherwise, it will return false.
bool checkIfInMenuNumbers(string menuChoice) {
    
    // initialize the isInMenuNumbers boolean
    bool isInMenuNumbers = false;

    // numbers for menu options
    string menuNumbers[6] = {"1", "2", "3", "4", "5", "6"};
    
    // for each loop.
    // i represents each menu number in the list
    for (string i : menuNumbers)
    {
        // this will return true if the user-chosen number is in the list of menu numbers
        if (i == menuChoice) {
            return isInMenuNumbers = true;
        }   
    }

    return isInMenuNumbers;
}

// this function loops through a list of the numbers equal to the length of the inventory vector. It checks to see if the number entered by the user is in that range.
// if it is, the function will return true; otherwise, it will return false.
bool checkIfInListLength(int userChoice, vector<InventoryItem>inventoryList) {
    
    // initialize the isInMenuNumbers boolean
    bool isInListLength = false;

    // numbers for menu options
    if ((userChoice) <= (inventoryList.size()-1)){
        isInListLength = true;
    }

    return isInListLength;
}

// This function gathers info to create a new InventoryItem object and returns the object

InventoryItem SetInfo() {

    string itemToAdd = AddItemInfo();
    float itemPrice = AddItemPrice(itemToAdd);
    int itemQuantity = AddItemQuantity();

    InventoryItem *newItem = new InventoryItem(itemToAdd, itemPrice, itemQuantity);

    return *newItem;
}

// This function uses a for each loop to print out the attributes of each item in the inventory.
string ViewItems(vector<InventoryItem> inventory) {

    if (CalculateTotal(inventory) == 0 && inventory.empty()) {

        return "";
    } 

    else {

        cout << "\n\n" << "Inventory Items";
        cout << "\n" << "--------------------";

        int index = 0;
        // i represents each of the items, and itemslist is the vector that the program loops through.
        for (InventoryItem i : inventory) {

            if (i.getItemQuantity() > 0 && !inventory.empty()) {
            // This will print the attributes of each InventoryItem in the vector.
            cout << "\n" << index + 1 << ". " << i.getItem() << " - $" << fixed << setprecision(2) << i.getPrice() << " Ea - QTY: " << i.getItemQuantity() << " = $" << fixed << setprecision(2) << (i.getPrice()) * (i.getItemQuantity());
            }

            else {
                cout << "\n" << index + 1 << ". " << i.getItem() << " - OUT OF STOCK";
            }

            // This adds 1 to the index with each iteration, allowing the list number being printed to increase.
            index ++;
        }

        return "\n--------------------";

    }
}

// This function gets the item's name from the user and returns it.
string AddItemInfo(){

    string itemToAdd = " ";

    cout << "\nWhat is the name of the item? ";
    cin >> itemToAdd;

    return itemToAdd;
}

// This function gets the item's price from the user and returns it.
float AddItemPrice(string itemToAdd) {

    bool isGoodPrice = false;
    float itemPrice = 0;

    while (!isGoodPrice){

        cout << "\nWhat is the price of the " << itemToAdd << "? $";
        cin >> itemPrice;

        // cin.fail returns a boolean (true) if the data types don't match. Using it allows the program to clear the user input and loop back through.
        if (cin.fail()) {
        cout << "\nThat is not a number. Please type a number with a decimal point: ";
        
        // clears the incorrect data type and ignores the rest of the user input
        cin.clear();
        cin.ignore(100, '\n');

        }

        else{
            isGoodPrice = true;
        }
    }

    return itemPrice;

}

// This function gets the quantity of the item from the user and returns it. See AddItemPrice above for additional notes.
int AddItemQuantity() {

    bool isGoodQuantity = false;
    int itemQuantity = 0;

    while (!isGoodQuantity){

        cout << "\nPlease enter the quantity: ";
        cin >> itemQuantity;

        if (cin.fail()) {
        cout << "\nThat is not a number. Please type a quantity using a number: ";

        cin.clear();
        cin.ignore(100, '\n');

        }

        else{
            isGoodQuantity = true;
        }
    }

    return itemQuantity;
}

// This function allows the user to choose an attribute of an item to change. Once the item is changed, the function returns an updated vector
// that replaces the current one.

vector<InventoryItem> ChooseEdit(vector<InventoryItem> inventory) {

    if (CalculateTotal(inventory) == 0) {

        return inventory;
    } 

    else {

        ViewItems(inventory);

        bool isGoodListNumber = false;
        bool isGoodAttributeNumber = false;
        int itemNumber = 0;
        int attributeNumber = 0;

        // check to see if the number is in the range of the vector
        while (!isGoodListNumber){

            cout << "\n\nWhich item number would you like to edit? ";
            cin >> itemNumber;

        // check to see if the input value is a number and if it is within the range of the vector
            if (cin.fail() || !checkIfInListLength(itemNumber-1, inventory)) {
                cout << "\nThat is not a number or not in the list. Please type a number in the list: ";

                cin.clear();
                cin.ignore(100, '\n');

                }

            // Changes the boolean to true and exits the loop
            else{
                isGoodListNumber = true;
            }
        }

        // Check to see if the number is in the range of the options
        while (!isGoodAttributeNumber){

            //Options of item attributes to change
            cout << "\n1. Item Name\n2. Item Price\n3. Item Quantity\n";
            cout << "\nWhich item Attribute would you like to edit? ";
            cin >> attributeNumber;

            if (cin.fail() || attributeNumber != 1 && attributeNumber !=2 && attributeNumber !=3) {
                cout << "\nThat is not a number or not an option. Please type 1, 2, or 3: ";

                cin.clear();
                cin.ignore(100, '\n');

            }

            else{
                isGoodAttributeNumber = true;
            }
        }
        
        // Allows the user to change the item's name
        if (attributeNumber == 1) {

            return EditItem(itemNumber, inventory);
        }

        // Allows the user to change the item's price
        else if (attributeNumber == 2) {

            return EditPrice(itemNumber, inventory);
        }

        // Allows the user to change the item's quantity
        else {

            return EditQuantity(itemNumber, inventory);
        }

    }
}

// This function allows the user to change an item's name. Once the item is changed, the function returns an updated vector
// that replaces the current one.

vector<InventoryItem> EditItem(int itemNumber, vector<InventoryItem> inventory) {

    string newItemName = AddItemInfo();

    for (InventoryItem i : inventory) {

        if (i.getItem() == inventory.at(itemNumber-1).getItem()) {
            inventory[itemNumber-1].setItem(newItemName);  
        }
    }

    return inventory;
}

// This function allows the user to change an item's price. Once the item is changed, the function returns an updated vector
// that replaces the current one.
vector<InventoryItem> EditPrice(int itemNumber, vector<InventoryItem> inventory) {

    float newItemPrice = AddItemPrice(inventory.at(itemNumber-1).getItem());

    for (InventoryItem i : inventory) {

        if (i.getItem() == inventory.at(itemNumber-1).getItem()) {
            inventory[itemNumber-1].setPrice(newItemPrice);  
        }
    }

    return inventory;
}

// This function allows the user to change an item's quantity. Once the item is changed, the function returns an updated vector
// that replaces the current one.
vector<InventoryItem> EditQuantity(int itemNumber, vector<InventoryItem> inventory) {

    int newItemQuantity = AddItemQuantity();

    for (InventoryItem i : inventory) {

        if (i.getItem() == inventory[itemNumber-1].getItem()) {
            inventory[itemNumber-1].setItemQuantity(newItemQuantity);  
        }
    }

    return inventory;
}

// This function loops through the inventory and adds up the total amount of all inventory.
float CalculateTotal(vector<InventoryItem> inventory, bool requestTotal) {

    float totalOfInventory = 0;

    for (InventoryItem i : inventory) {

        totalOfInventory += (i.getPrice() * i.getItemQuantity());
        }
    
    // This should only print if there is a total and requestTotal == true.
    if (totalOfInventory > 0 && requestTotal) {
        cout << "\nTotal of all Items" << "\n--------------------";
        
        // "fixed" and "setprecision()" cause floating point numbers to always print to the precision indicated (in this case, 2).
        cout << "\n$" << fixed << setprecision(2) << totalOfInventory;

        return totalOfInventory;
    }

    else if (totalOfInventory == 0){
        cout << "\n\n\nThere is currently no inventory\n\n";

        return totalOfInventory;
    }

    return totalOfInventory;
    
}

// This function allows the user to select a quantity of items to take. The user is only allowed to select the available quantity.
// The function returns an updated vector that replaces the current one.
vector<InventoryItem> TakeItem(vector<InventoryItem> inventory) {

    bool isGoodListNumber = false;
    bool isGoodAmount = false;
    int itemNumber = 0;
    int quantityToTake = 0;
    int currentQuantity = 0;

    if (CalculateTotal(inventory) == 0) {

        return inventory;
    } 

    // Check to see if the number is in the range of the vector
    while (!isGoodListNumber){

        ViewItems(inventory);

        cout << "\n\nWhich item would you like to take from (item number)? ";

        cin >> itemNumber;

        if (cin.fail() || !checkIfInListLength(itemNumber-1, inventory)) {
            cout << "\nThat is not a number or not in the list. Please type a number in the list: ";

            cin.clear();
            cin.ignore(100, '\n');

            }

        // Changes the boolean to true and exits the loop
        else{
            isGoodListNumber = true;
        }
    }

    currentQuantity = inventory.at(itemNumber - 1).getItemQuantity();


    // Check to see if the number is in the range of the options
    while (!isGoodAmount){

        //Options of item attributes to change
        cout << "\nHow much would you like to take? ";
        cin >> quantityToTake;

        if (cin.fail() || quantityToTake > currentQuantity){
            cout << "\nThat is not a number or that amount is not available: ";

            cin.clear();
            cin.ignore(100, '\n');

        }

        else{
            isGoodAmount = true;
        }
        
    }

    // Subtracts the specified quantity from the current quantity of the selected it.
    inventory[itemNumber-1].setItemQuantity(currentQuantity - quantityToTake);

    return inventory;

}