#pragma once
#include "BST.h"
#include <iostream>
#include <string>

const double PI = 3.141592653589793238463;
const double EARTH_RADIUS = 6371.137;

class cityInfo {
private:
public:
  string cityName;
  string latitude;
  string longitude;
  string country;

  cityInfo(const string &cName = "", const string &lat = "",
           const string &lon = "", const string &cnt = "")
      : cityName(cName), latitude(lat), longitude(lon), country(cnt) {}

  // Overloaded insertion operator for easy printing
  friend ostream &operator<<(ostream &os, const cityInfo &city) {
    os << "City Name: " << city.cityName << "\n"
       << "Latitude: " << city.latitude << "\n"
       << "Longitude: " << city.longitude << "\n"
       << "Country: " << city.country;
    return os;
  }
};

double DMS_to_DD(int degree, int minute, int second, char dir);

double compute_distance(const cityInfo &city1, const cityInfo &city2);

void load_initial_cities(BST<string, cityInfo> &cityTree,
                         const string &filename);

cityInfo search_city_in_tree(BST<string, cityInfo> &cityTree,
                             const string &cityName);

void print_all_cities_from_tree(BST<string, cityInfo> &cityTree);
