#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;

struct menuItemType {
   string menuItem;
   double menuPrice;
   int count;
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
    
   fin.open("menu.txt");
   
   getData();
   showMenu();
   printCheck();
   
   fin.close();
   
   return 0;
}

void printCheck(){
 
   double total = 0.00;
 
   cout << endl << "Your check:\n";
   
   for (int i = 0; i < numberOfOrders; i++){
      
      cin >> itemFromMenu;
      cin >> numberOfItems;
      cout << left << setw(16) << menuList[itemFromMenu - 1].menuItem << '\t' << numberOfItems << " $" << menuList[itemFromMenu - 1].menuPrice * numberOfItems << endl;
      total += (menuList[itemFromMenu - 1].menuPrice * numberOfItems);
      
   }
   
   double tax = total * 0.086;
   double aDue = total + tax;
   
   cout << left << setw(19) << "Amount Total" << '$' << total << endl;
   cout << left << setw(19) << "Tax" << '$' << tax << endl;
   cout << left << setw(19) << "Amount Due" << '$' << aDue;
   
}

void showMenu(){
   
   cout << fixed << setprecision(2);
   
   cout << "Welcome to Johnny Restaurant" << endl;
   
   for (int i = 0; i < 8; i++){
      
      cout << left << setw(19) << menuList[i].menuItem << '$' << menuList[i].menuPrice << endl;
      
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
