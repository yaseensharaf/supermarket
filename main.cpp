#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>
#include <ctime>
#include <iomanip>
#include <locale>
#include <cstring>
#include <cmath>

struct Product {
std::string name;
std:: string expiry_date;
int quantity;
float price;
std::string type;
};

Product product;
const int ARRAY_SIZE = 100;
/*
 I created a function that list the Database
*/
int print()
{
  std::ifstream file("market.txt");
  std::string line;
  while(getline(file, line)) 
  {
     std::string Itemname, Itemdate;
    int Itemqauntity;
    double Itemprice;
    std::string itemType;
    std::istringstream iss(line);
    if(!(iss >> Itemname >> Itemdate >> Itemqauntity >> Itemprice >> itemType))
       
        throw std::runtime_error("invalid data");
    iss >> Itemname >> Itemdate >> Itemqauntity >>  Itemprice >>itemType;

    std::cout << Itemname << " " << Itemdate << " "  << Itemqauntity << " "  << Itemprice  << " " <<itemType << std::endl; 
  } 
  return(0);
}/*
  
 I created a function that delete the empty line automatically
*/

void delete_empty_line() {
  std::fstream file_stream;
  std::string current_read_line;

  file_stream.open("market.txt", std::fstream::in | std::fstream::out | std::fstream::app);
  std::vector<std::string> lines;

  while (getline(file_stream, current_read_line)) {
 
    if (!current_read_line.empty()) {
      lines.push_back(current_read_line);
    }
  }

  file_stream.clear();
  file_stream.close();

  std::ofstream output_file("market.txt");
  for (const std::string &line : lines) {
    output_file << line << '\n';
  }
  output_file.close();
}
const int maxrow =10;

std::string Itemname[maxrow]={};
std::string Expiredate[maxrow]={};
std::string Itemquauntity[maxrow]={};
std::string price[maxrow]={};
std::string itemType[maxrow]={};
/* 
 I created a function that shows the expire date of the items
*/

void items_about_to_expire() {

  std::ifstream file("market.txt");
  std::string line;
  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string name;
    std::string expirationDate;

    getline(ss, name, '\t');
    getline(ss, expirationDate, '\t');

    tm expiration{};
    std::istringstream expirationStream(expirationDate);
    expirationStream.imbue(std::locale("en_US.utf-8"));
    expirationStream >> std::get_time(&expiration, "%m/%d/%Y");

    time_t currentTime = time(nullptr);
    tm currentDate = *localtime(&currentTime);

    double daysUntilExpiration =
        difftime(mktime(&expiration), mktime(&currentDate)) / 89999;

    if (daysUntilExpiration >= 0) {
      std::cout << name << " expires on " << expirationDate << std::endl;
    } else {
      std::cout << name << " has expired" << std::endl;
    }
  }
}

/*
  
 I created a function that can add items in the database
*/

 void AddItem()
 
{
  char name[50];
  char expd[11];
  char quano[10];
  char pric[10];
  char ityp[10];
  
  std::cin.ignore();
  
 std::cout <<"Item name ";
 std:: cin.getline(name,50);
  
  
 std::cout <<"Expire date ";
 std:: cin.getline(expd,11);
  
 std::cout <<"Item quauntity "; 
 std::cin.getline(quano,10);
  
 std::cout <<"price ";
 std:: cin.getline(pric,10);

 std::cout <<"item Type ";
 std:: cin.getline(ityp,10);
  
  for(int x = 0; x < maxrow; x++)
    {
     if (Itemname[x]=="\0")
     {
       Itemname[x]=name;
       Expiredate[x]=expd;
       Itemquauntity[x]=quano;
       price[x]=pric;
       itemType[x]=ityp;

       break;
       }  
      }  
    std::ofstream file("market.txt", std::ios::app);
  file << "\n" << name << "\t" << expd << "\t" << quano << "\t" << pric << "\t" << ityp;
       
} 
/*
  
 I created a function that edit any item in the database
*/

void editItem(){

  std::vector<Product> items;
  std::ifstream file("market.txt");
  std::string line;
  while (getline(file, line)) {
    Product item;
    std::istringstream iss(line);
    iss >> item.name >> item.expiry_date >> item.quantity >> item.price >>item.type;
    items.push_back(item);
  }
  file.close();

  std::string name;
  std::cout << "What Item u want to edit: ";
  std::cin >> name;
  
  std::cout << "\n";

  bool product_found = false;
  for (int i = 0; i < items.size(); i++) {
    if (items[i].name == name) {
      product_found = true;
      items.erase(items.begin() + i);
      break;
    }
  }

  std::ofstream output_file("market.txt");
  for (const Product &item : items) {
    output_file << item.name << '\t' << item.expiry_date << '\t'
                << item.quantity << '\t' << item.price << '\t' << 
item.type << '\n';    
  }
  output_file.close();
  Product Item;
  std::cout << "Enter the product name: ";
  std::cin >> Item.name;

  std::cout << "Enter the date: ";
  std::cin >> Item.expiry_date;
  
  std::cout << "Enter the quantity: ";
  //char quantity[100];
  std::cin >> Item.quantity;
  std::cout << "Enter the price: ";
  //std::string price;
  std::cin >> Item.price;
  std::cout << "Enter the type: ";
  std::cin >> Item.type;
  std::cout << "\n\n";
  std::ofstream File("market.txt", std::ios::app);
  if (File.is_open()) {
    File << 
          Item.name << "\t" << Item.expiry_date << "\t"
         << Item.quantity << "\t" << Item.price << "\t" << Item.type;

    File.close();

}
  }
      /*
  
 I created a function that if you write the name of it it will appear
*/

void search()
  {
    std::string name;
    std::cout << "Enter the name of the item to search for: ";
    std::cin >> name;
    std::fstream file("market.txt", std::ios::in);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(name) != std::string::npos) {
            std::cout << line << std::endl;
        }
    }
    file.close();
}
  /*
  
 I created a function that if you write the name of it it will delete the item
*/
void Delete()
 
{
    std::string name;
    std::cout << "Enter the name of the item to delete: ";
    std::cin >> name;
    std::vector<std::string> lines;
    std::fstream file("market.txt", std::ios::in);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(name) == std::string::npos) {
            lines.push_back(line);
        }
    }
    file.close();
    file.open("market.txt", std::ios::out | std::ios::trunc);
    for (const auto& l : lines) {
        file << l << std::endl;
    }
    file.close();
}
 
int main()
{ 
    
    int choice = 0;
print();
  std::string Itemname;
  int option;
  
  do{
    std::cout<<"1-Create Item"<<std::endl;
    std:: cout<<"2-Edit Item"<<std::endl;
    std:: cout<<"3-Delete Item"<<std::endl;
    std::cout<<"4-search Item"<<std::endl;
    std::cout<<"5-Items about to expire"<<std::endl;
    std::cout<<"6-Exit and Save to Text"<<std::endl;
    std::cout<<"=========================="<<std::endl;

    std::cout<<"Select option>>";
    std::cin>>option;
     switch(option)
     {
       case 1: AddItem();
        print();
       
       break;
        
       case 2 :editItem();
         print();
       
       break;
       
       case 3:Delete();
         print();
       
       break;

       case 4:search();
        
       
       break;

       case 5 :items_about_to_expire();
            
    
    }
     }while (option !=6);
  
  std::cout<<"Exit...Saving to file!"<<std::endl;
  return (0);
  }