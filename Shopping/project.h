#ifndef __X_H_INCLUDED__
#define __X_H_INCLUDED__

#include <iostream>
using std::cin; using std::cout;
#include <iomanip>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <regex>
using std::regex;
#include <utility>
using std::pair;

struct Store_Info{ // Stores all info for a given item
    string store_name;
    string location;
    // vector<string> = item | vector<int> = stock || vector<double> = price
    pair<pair<vector<string>, vector<int>>, vector<double>> item_stock_price;

    Store_Info() = default;
    Store_Info(string, string);

    string how_many(int);
};

#endif 