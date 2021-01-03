#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <iomanip>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <regex>
using std::regex;
#include <utility>
using std::pair;
#include "project.h"

string Store_Info::how_many(int loc) {  // Outputs Quantity per item
  pair item_stock = std::get<0>(item_stock_price);
  string output = "There are ";
  output += std::get<1>(item_stock).at(loc);  // Quantity
  output += " ";
  output += std::get<0>(item_stock).at(loc);  // Name
  output += "(s).";
  return output;
}

Store_Info::Store_Info(string n, string l) {  // Constructor for Store_Info
  store_name = n;
  location = l;
}

int number_stores() {  // Determines number of stores
  string stores;
  std::getline(cin, stores);
  regex reg{R"((\d+) Stores:)"};  // From professor's piazza post

  std::smatch m;
  std::regex_match(stores, m, reg);

  int n_stores = std::stoi(m[1].str());
  return n_stores;
}

void stock_info(vector<Store_Info> &stores,
                int n_stores) {        // Adds stock info for each store
  for (int i(0); i < n_stores; i++) {  // For each store
    string name;
    string loc;
    int counter(0);
    bool active(true);
    while (active) {  // While input != whitespace
      string line;
      std::getline(cin, line);
      if (line == "")
        active = false;
      else if (counter == 0) {
        name = line;
        counter++;
      } else if (counter == 1) {
        loc = line;
        stores[i] = Store_Info(name, loc);  // Create new store
        counter++;
      } else {
        regex reg{R"((.+),(\d+),\W(\d+.\d+))"};

        std::smatch m;
        std::regex_match(line, m, reg);
        Store_Info &current_store = stores[i];

        std::get<0>(std::get<0>(current_store.item_stock_price))
            .push_back(m[1].str());  // Defines item name
        std::get<1>(std::get<0>(current_store.item_stock_price))
            .push_back(std::stoi(m[2].str()));  // Defines amount in stock
        std::get<1>(current_store.item_stock_price)
            .push_back(std::stod(m[3].str()));  // Defines price
      }
    }
  }
}

void unique_item_identifier(
    vector<string> names,
    vector<string> &unique_items) {  // Creates vector of unique items
  for (auto name : names) {
    if (std::find(unique_items.begin(), unique_items.end(), name) ==
        unique_items.end())
      unique_items.push_back(name);
  }
}

void output_info(vector<Store_Info> stores,
                 int n_stores) {  // Outputs store & item related information
  string s_stores = std::to_string(n_stores);
  cout << "Store Related Information (ordered by in-file order):" << endl
       << "There are " << s_stores << " store(s)." << endl;
  for (auto store : stores) {  // Output distinct items per store
    vector<double> price = std::get<1>(store.item_stock_price);
    string distinct_items = std::to_string(price.size());
    cout << store.store_name << " has " << distinct_items << " distinct items."
         << endl;
  }
  vector<string> unique_items;  // Holds all of the unqiue items
  for (auto store : stores) {   // Identifies unique items per store
    pair<pair<vector<string>, vector<int>>, vector<double>> info =
        store.item_stock_price;
    vector<string> names = std::get<0>(std::get<0>(info));
    unique_item_identifier(names, unique_items);
  }
  cout << endl
       << "Item Related Information (ordered alphabetically):" << endl
       << "There are " << std::to_string(unique_items.size())
       << " distinct item(s) available for purchase." << endl;
  std::sort(unique_items.begin(), unique_items.end());
  vector<int> unique_quantities(
      unique_items.size());    // Quantity of each unique item
  for (auto store : stores) {  // For each store
    pair<pair<vector<string>, vector<int>>, vector<double>> info =
        store.item_stock_price;
    pair<vector<string>, vector<int>> item_stock = std::get<0>(info);
    int names_size = (std::get<0>(item_stock)).size();
    for (int i(0); i < names_size; i++) {  // For each item
      auto location = find(unique_items.begin(), unique_items.end(),
                           (std::get<0>(item_stock))[i]);
      if (location != end(unique_items))
        unique_quantities[location - unique_items.begin()] +=
            (std::get<1>(item_stock)[i]);
    }
  }
  int items_size = unique_items.size();
  for (int i(0); i < items_size; i++) {  // Output number of unique items
    cout << "There are " << unique_quantities[i] << " " << unique_items[i]
         << "(s)." << endl;
  }
  cout << "" << endl;
}

void shopping(vector<Store_Info> stores) {  // Outputs shopping info
  cout << "Shopping:" << endl;
  string line1;
  std::getline(cin, line1);
  regex reg1{R"((\d+) items on my shopping list:)"};

  std::smatch m1;
  std::regex_match(line1, m1, reg1);
  int shopping_list = std::stoi(m1[1].str());
  double to_bring(0);                       // Amount of money to bring
  for (int i(0); i < shopping_list; i++) {  // For each item on list
    string line2;
    std::getline(cin, line2);
    regex reg2{R"((\d+) (.+))"};

    std::smatch m2;
    std::regex_match(line2, m2, reg2);
    int number_needed = std::stoi(m2[1].str());
    string item_needed = m2[2].str();
    int number_selling = 0;
    vector<pair<double, Store_Info>> selling_stores;

    for (auto store : stores) {  // Determines if store has item
      pair<pair<vector<string>, vector<int>>, vector<double>> info =
          store.item_stock_price;
      pair<vector<string>, vector<int>> item_stock = std::get<0>(info);
      auto location = find((std::get<0>(item_stock)).begin(),
                           (std::get<0>(item_stock)).end(), item_needed);
      if (location != end((std::get<0>(item_stock)))) {
        number_selling += 1;
        selling_stores.push_back(std::make_pair(
            (std::get<1>(info))[location - std::get<0>(item_stock).begin()],
            store));
      }
    }
    cout << "Trying to order " << number_needed << " " << item_needed << "(s)."
         << endl;
    cout << number_selling << " store(s) sell " << item_needed << "." << endl;

    std::sort(selling_stores.begin(), selling_stores.end(),
              [](auto &left, auto &right) {
                return left.first < right.first;
              });  // Sorts by cheapest price
    double total_price(0.00);
    vector<pair<int, Store_Info>> ordered_from;

    for (auto seller : selling_stores) {  // For each store that has item
      int order(0);
      pair<pair<vector<string>, vector<int>>, vector<double>> info =
          (std::get<1>(seller)).item_stock_price;
      pair<vector<string>, vector<int>> item_stock = std::get<0>(info);
      auto location = find((std::get<0>(item_stock)).begin(),
                           (std::get<0>(item_stock)).end(), item_needed);
      int n_available =
          (std::get<1>(item_stock))[location - std::get<0>(item_stock).begin()];
      while (
          number_needed != 0 &&
          n_available !=
              0) {  // Repeats while item is in stock and desired amount is > 0
        order++;
        total_price += std::get<0>(seller);
        number_needed--;
        n_available--;
      }
      ordered_from.push_back(std::make_pair(order, std::get<1>(seller)));
      if (number_needed == 0) break;
    }
    cout << "Total price: $" << std::fixed << std::setprecision(2)
         << total_price << endl;
    for (auto store : ordered_from) {  // Outputs amount to order per store
      int order_quantity = std::get<0>(store);
      string store_name = (std::get<1>(store)).store_name;
      string location = (std::get<1>(store).location);
      cout << "Order " << order_quantity << " from " << store_name << " in "
           << location << endl;
    }
    to_bring += total_price;
  }
  cout << "" << endl
       << "Be sure to bring $" << std::fixed << std::setprecision(2) << to_bring
       << " when you leave for the stores." << endl;
}

int main() {
  int n_stores = number_stores();       // Number of stores
  vector<Store_Info> stores(n_stores);  // Container for each store
  stock_info(stores, n_stores);         // Adds stock info for each store
  output_info(stores, n_stores);  // Outputs store & item related information
  shopping(stores);               // Outputs shopping info
}