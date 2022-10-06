#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
using namespace std;

struct menuItemType {
   string menuItem;
   double menuPrice;
   int count;
};

struct orderType {
    int menuItem;
    int quantity;
};

menuItemType menuList[8];

ifstream fin;

int numberOfOrders;
int itemFromMenu;
int numberOfItems;

void getData();
void showMenu();
void printCheck();

int main() {
   
   cin >> numberOfOrders;
   cout << fixed << setprecision(2);
    
   fin.open("menu.txt");
   
   getData();
   showMenu();
   printCheck();
   
   fin.close();
   
   return 0;
}

void printCheck(){
 
    double total = 0.00;
    int duplicates = 0;
    
    orderType orders[numberOfOrders];
    vector<orderType> finalOrders;
 
    for (int i = 0; i < numberOfOrders; i++){
     
        cin >> itemFromMenu;
        cin >> numberOfItems;
        
        orders[i].menuItem = itemFromMenu;
        orders[i].quantity = numberOfItems;
        
        for (int j = i-1; j >= 0; j--){
            if (orders[j].menuItem == orders[i].menuItem){
                orders[j].quantity += orders[i].quantity;
                orders[i].menuItem = 0;
                duplicates++;
            }
        }
        
    }
    //fill new vector
    for (int i = 0; i < numberOfOrders; i++){
        if (orders[i].menuItem != 0){
            finalOrders.push_back(orders[i]);
        }
    }
    
    cout << endl << "Your check:\n";
    
    //print contents of vector
    for (int i = 0; i < numberOfOrders - duplicates; i++){
        
        double price = menuList[finalOrders.at(i).menuItem - 1].menuPrice;
        string item = menuList[finalOrders.at(i).menuItem - 1].menuItem;
        
        cout << left << setw(14) << item << finalOrders.at(i).quantity << "  $" << price * finalOrders.at(i).quantity << endl;
        total += price * finalOrders.at(i).quantity;
        
    }
    
   
   double tax = total * 0.0886;
   double aDue = total + tax;
   
   cout << left << setw(17) << "Amount Total" << '$' << total << endl;
   cout << left << setw(17) << "Tax" << '$' << tax << endl;
   cout << left << setw(17) << "Amount Due" << '$' << aDue << endl;
   
}

void showMenu(){
   
   cout << "Welcome to Johnny Restaurant" << endl;
   
   for (int i = 0; i < 8; i++){
      
      cout << left << setw(17) << menuList[i].menuItem << '$' << menuList[i].menuPrice << endl;
      
   }
   
}

void getData(){
   
   string scan;
   string name;
   string price;
   
   int c = 0;
   
   while (getline(fin, scan)){

      name = "";
      price = "";
      bool name_end = false;
      for (long unsigned int i = 0; i < scan.size(); i++){
         //checks if menu item name has ended
          if (scan[i + 1] == '$'){
              name_end = true;
          } else if (name_end == false){
              name+= scan[i];
          } else if (scan[i] != '$'){
              price+= scan[i];
          }
          
      }
          
      menuList[c].menuItem = name;
      menuList[c].menuPrice = stod(price);
      c++;
   
   }
     
}
