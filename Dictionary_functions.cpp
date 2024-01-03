#include "Dictionary_functions.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;
const regex COORDINATE_PATTERN(R"((\d+)°(\d+)′([NSWE]))");


void insert_city_to_tree(BST<string, cityInfo> &cityTree, const cityInfo &newCity) {
    cityTree.insert(newCity.cityName, newCity);
}


void load_initial_cities(BST<string, cityInfo> &cityTree, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file: " << filename << endl;
        return;
    }
    string line;
    cityInfo CityInfo;
    regex pattern(R"((.+?)\s+(\d+°\d+′[NS])\s+(\d+°\d+′[EW])\s+(.+))");

    while (getline(file, line)) {
        smatch match;
        if (regex_match(line, match, pattern)) {
            CityInfo.cityName = match[1];
            CityInfo.latitude = match[2];
            CityInfo.longitude = match[3];
            CityInfo.country = match[4];

            cityTree.insert(CityInfo.cityName, CityInfo);
        } else {
            cerr << "Error parsing line: " << line << endl;
        }
    }
    file.close();
}



cityInfo search_city_in_tree(BST<string, cityInfo> &cityTree, const string &cityName) {
    Node<string, cityInfo> *foundNode = cityTree.search(cityName);
    if (foundNode) {
        return foundNode->data;
    } else {
        throw runtime_error("City not found in the tree.");
    }
}



void print_all_cities_from_tree(BST<string, cityInfo> &cityTree) {
    cityTree.traverse();
}



pair<double, double> parseCoordinate(const string &singleCoord) {
    smatch match;
    if (regex_match(singleCoord, match, COORDINATE_PATTERN)) {
        double degrees = stod(match[1].str());
        double minutes = stod(match[2].str());
        char direction = match[3].str()[0];
        double decimalDegrees = degrees + minutes / 60.0;
        if (direction == 'S' || direction == 'W') {
            decimalDegrees *= -1;
        }
        return make_pair(decimalDegrees, 0.0);
    } else {
        throw invalid_argument("Invalid coordinate format");
    }
}



double compute_distance(const cityInfo &city1, const cityInfo &city2) {
    pair<double, double> latLong1, latLong2;
    latLong1.first = parseCoordinate(city1.latitude).first;
    latLong2.first = parseCoordinate(city2.latitude).first;
    latLong1.second = parseCoordinate(city1.longitude).first;
    latLong2.second = parseCoordinate(city2.longitude).first;

    double lat1 = latLong1.first * M_PI / 180.0;
    double long1 = latLong1.second * M_PI / 180.0;
    double lat2 = latLong2.first * M_PI / 180.0;
    double long2 = latLong2.second * M_PI / 180.0;

    double delta_phi = lat2 - lat1;
    double delta_lambda = long2 - long1;
    double a = pow(sin(delta_phi / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(delta_lambda / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS * c;
}
