#include "BST.h"
#include "Dictionary_functions.h"
#include "Node.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>  

using namespace std;

bool file_exists(const string &filename) {
  ifstream file(filename);
  return file.good();
}

int main() {
  BST<string, cityInfo> cityTree;
  string filename = "cities.txt";

  int choice;
  do {
    cout << "\n--- City Dictionary Menu ---\n";
    cout << "1. Start with New City List\n";
    cout << "2. Update Existing City List\n";
    cout << "3. Search & View Cities\n";
    cout << "4. Close the Program\n";
    cout << "What would you like to do? (Choose a number): ";
    cin >> choice;
    cin.ignore();  

    char ans;
    switch (choice) {
    case 1:
      if (file_exists(filename)) {
        cout << "A file with city information already exists. Please use the "
                "'Update Existing City List' option.\n";
      } else {
        load_initial_cities(cityTree, filename);
        cityTree.save_to_file(filename);
        cout << "Created and saved a new city list to " << filename << ".\n";
      }
      break;

    case 2:
      load_initial_cities(cityTree, filename);
      cout << "Loaded cities from " << filename << ".\n";

      cout << "Would you like to add a new city to the list? (Y/N): ";
      cin >> ans;
      cin.ignore();  

      while (tolower(ans) == 'y') {
        cityInfo newCity;
        cout << "Enter the city's name: ";
        getline(cin, newCity.cityName);
        cout << "Enter its latitude: ";
        cin >> newCity.latitude;
        cout << "Enter its longitude: ";
        cin >> newCity.longitude;
        cout << "Enter the country it's in: ";
        cin.ignore();  
        getline(cin, newCity.country);

        cityTree.insert(newCity.cityName, newCity);

        cout << "Want to add another city? (yes/no): ";
        cin >> ans;
        cin.ignore();  
      }

      cityTree.save_to_file(filename);
      cout << "Saved the updated city list to " << filename << ".\n";
      break;

    case 3:
      if (!file_exists(filename)) {
        cout << "No city list found. Please start with a new city list first.\n";
      } else {
        load_initial_cities(cityTree, filename);
        cout << "Cities are ready for searching.\n";

        cout << "Want to search for a specific city? (Y/N): ";
        cin >> ans;
        cin.ignore();  

        if (tolower(ans) == 'y') {
          string cityName;
          cout << "Which city are you looking for? ";
          getline(cin, cityName);
          cityInfo foundCity = search_city_in_tree(cityTree, cityName);
          cout << "Found: " << foundCity.cityName
               << "\nLatitude: " << foundCity.latitude
               << "\nLongitude: " << foundCity.longitude
               << "\nCountry: " << foundCity.country << "\n";
        }

        cout << "Want to see all cities in the list? (Y/N): ";
        cin >> ans;
        cin.ignore();  

        if (tolower(ans) == 'y') {
          print_all_cities_from_tree(cityTree);
        }

        cout << "Want to calculate the distance between two cities? (Y/N): ";
        cin >> ans;
        cin.ignore();  

        if (tolower(ans) == 'y') {
          string city1Name, city2Name;
          cout << "Name of the first city: ";
          getline(cin, city1Name);
          cout << "Name of the second city: ";
          getline(cin, city2Name);

          cityInfo city1 = search_city_in_tree(cityTree, city1Name);
          cityInfo city2 = search_city_in_tree(cityTree, city2Name);

          double distance = compute_distance(city1, city2);
          cout << "Distance between " << city1Name << " and " << city2Name
               << " is: " << distance << " Km.\n";
        }
      }
      break;

    case 4:
      cout << "Thank you for using the City Manager. Stay safe!\n";
      break;

    default:
      cout << "Sorry, I didn't understand that. Please choose a number from "
              "the menu.\n";
    }
  } while (choice != 4);

  return 0;
}
