#include "person.hpp"
#include "personFactory.hpp"
#include "queryMaker.hpp"
#include "record.hpp"
#include <iostream>

void mostrarMenu() {
  std::cout << "\n\n=== CENSUS ===";
  std::cout << "\n0. Make new Dataset";
  std::cout << "\n1. Search for oldest person";
  std::cout << "\n2. Search for individual with the most assets";
  std::cout << "\n3. Search for Tax Filer";
  std::cout << "\n4. Additional Queries";
  std::cout << "\n5. Exit";
  std::cout << "\n Seleccione una opción: ";
}

void printHashMap(const std::map<std::string, Person> &personMap) {
  for (const auto &[key, person] : personMap) {
    std::cout << "City: " << key << "\n";
    std::cout << "Person: " << person.name << "\n\n";
  }
}

std::string taxCalendarGroupToString(taxCalendarGroup group) {
  switch (group) {
  case groupA:
    return "Group A";
  case groupB:
    return "Group B";
  case groupC:
    return "Group C";
  default:
    return "Unknown Group";
  }
}

int main() {
  std::vector<Person> persons;
  int option;
  PersonFactory factory;
  QueryMaker query;

  bool Pointers;
  int checkReference;
  std::cout << "Pointers(0) or Value(1)?";
  std::cin >> checkReference;
  Pointers = (checkReference == 0) ? true : false;

  do {

    mostrarMenu();
    std::cin >> option;

    switch (option) {
    case 0: {
      int n;
      std::cout << "\nSet the size of the new array: ";
      std::cin >> n;

      if (n <= 0) {
        std::cout << "Don't use negative numbers!";
        break;
      }

      // Record the time taken and memory used.
      persons = std::move(factory.generatePersonVector(n));

      std::cout << "\nArray of size " << n << " created!";
      break;
    }

    case 1: {
      int optionForOldest;

      std::cout
          << "\n Search for oldest person countrywide (0) or by city (1)?";
      std::cin >> optionForOldest;

      switch (optionForOldest) {
      case 0: {
        Person oldestPerson =
            query.findOldestPersonCountryWide(persons, Pointers);
        std::cout << "The oldest person countrywide is " << oldestPerson.name
                  << ". He is " << oldestPerson.age << " years old!";
        break;
      }
      case 1: {
        std::cout << "\nThe oldest individuals per city are: \n";
        printHashMap(query.findOldestPersonPerCity(persons, Pointers));
        break;
      }
      default: {
        std::cout << "choose either 0 or 1";
        break;
      }
      }
      break;
    }

    case 2: {
      int optionForHighestAssets;

      std::cout << "\n Search for the person with the highest assets "
                   "countrywide (0), by city (1), or by tax group (2)?";
      std::cin >> optionForHighestAssets;

      switch (optionForHighestAssets) {
      case 0: {
        Person highestAssetIndividual =
            query.findHighestAssetsPersonCountryWide(persons, Pointers);
        std::cout << "The person with the highest assets countrywide is "
                  << highestAssetIndividual.name << ". He has "
                  << highestAssetIndividual.assets << " assets!";
        break;
      }
      case 1: {
        std::cout << "\nThe person with the highest assets per city are:  \n";
        printHashMap(query.findHighestAssetsPersonPerCity(persons));
        break;
      }

      case 2: {
        std::cout << "\nThe person with the highest assets per tax calendar "
                     "group is:  \n";
        std::map<taxCalendarGroup, Person> highestAssetIndividuals =
            query.findHighestAssetsPersonPerTaxCalendarGroup(persons);

        for (const auto &[key, Person] : highestAssetIndividuals) {
          std::cout << "\n" << taxCalendarGroupToString(key);
          std::cout << "\nName: " << Person.name;
        }

        break;
      }
      default: {
        std::cout << "choose either 0 or 1";
        break;
      }
      }
      break;
    }
    case 3: {
      int optionTaxFiler;

      std::cout << "\n Choose one of the following Tax Filer quieries: Count "
                   "the people per their tax group (0)";
      std::cin >> optionTaxFiler;

      switch (optionTaxFiler) {
      case 0: {
        std::cout << "Now displaying the amount of people per tax group: ";
        std::map<taxCalendarGroup, int> peoplePerTaxGroup =
            query.countPeoplePerTaxCalendarGroup(persons);

        for (const auto &[key, count] : peoplePerTaxGroup) {
          std::cout << "\n" << taxCalendarGroupToString(key);
          std::cout << "\nCount: " << count;
        }

        break;
      }
      default: {
        std::cout << "choose a valid number";
        break;
      } break;
      }

      break;
    }
    case 4: {
      int optionAdditionalQ;

      std::cout << "\n Choose one of the following additional queries: Average "
                   "assets per city (0), Calculate the percentage of people "
                   "older than 80 per tax calendar group (1), or view the "
                   "amount of people per city (2)?";
      std::cin >> optionAdditionalQ;

      switch (optionAdditionalQ) {
      case 0: {
        std::cout << "The cities with the highest average assets are: ";
        const auto &CityAssetsPair =
            query.findCitiesWithHighestAverageAssets(persons);

        for (const auto &pair : CityAssetsPair) {
          std::cout << "\nCity: " << pair.first;
          std::cout << "\nAssets: " << pair.second;
        }
        break;
      }
      case 1: {
        std::cout << "Calculate the percentage of people older than 80 per tax "
                     "calendar group";
        std::map<taxCalendarGroup, double> percentageOlderThan80 =
            query.calculatePercentageOfPeopleOlderThan80PerTaxCalendarGroup(
                persons);

        for (const auto &[key, amount] : percentageOlderThan80) {
          std::cout << "\n" << taxCalendarGroupToString(key);
          std::cout << "\n" << amount;
        }
        break;
      }
      case 2: {
        std::cout << "Display the amount of people per city";
        std::map<std::string, int> count = query.countPeoplePerCity(persons);

        for (const auto &[key, amount] : count) {
          std::cout << "City: " << key << "\n";
          std::cout << "Number of people: " << amount << "\n";
        }
        break;
      }
      default: {
        std::cout << "choose either 0, 1 or 2";
        break;
      }
      }
      break;
    }
    }
  } while (option != 5);

  return 0;
}