#include "monitor.h"
#include "person.hpp"
#include "personFactory.hpp"
#include "queryMaker.hpp"
#include "record.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

void showMenu() {
  std::cout << "\n\n=== CENSUS ===";
  std::cout << "\n0. Create new dataset";
  std::cout << "\n1. Search for oldest person";
  std::cout << "\n2. Search for individual with the most assets";
  std::cout << "\n3. Tax filer queries";
  std::cout << "\n4. Additional queries";
  std::cout << "\n5. Show performance statistics";
  std::cout << "\n6. Export statistics to CSV";
  std::cout << "\n7. Exit";
  std::cout << "\nSelect an option: ";
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
  PersonFactory factory;
  QueryMaker query;
  Monitor monitor;

  bool usePointers;
  int referenceChoice;
  std::cout << "Pointers (0) or Value (1)? ";
  std::cin >> referenceChoice;
  usePointers = (referenceChoice == 0);

  int option;
  do {
    showMenu();
    std::cin >> option;

    long memStart = monitor.getMemoryUsage();

    switch (option) {
    case 0: { // Create dataset
      int n;
      std::cout << "\nEnter dataset size: ";
      std::cin >> n;

      if (n <= 0) {
        std::cout << "Dataset must contain at least 1 person.\n";
        break;
      }

      monitor.startTimer();
      persons = std::move(factory.generatePersonVector(n));
      double t = monitor.stopTimer();
      long mem = monitor.getMemoryUsage() - memStart;

      std::cout << "\nDataset of size " << n << " created in " << t
                << " ms, Memory: " << mem << " KB\n";
      monitor.record("Create dataset", t, mem);
      monitor.showRecord("Create dataset", t, mem);
      break;
    }

    case 1: { // Oldest person
      int choice;
      std::cout << "\nSearch oldest person countrywide (0) or by city (1)? ";
      std::cin >> choice;

      monitor.startTimer();
      if (choice == 0) {
        Person oldest = query.findOldestPersonCountryWide(persons, usePointers);
        std::cout << "Oldest person: " << oldest.name << ", Age: " << oldest.age
                  << "\n";
      } else if (choice == 1) {
        std::cout << "\nOldest individuals per city:\n";
        printHashMap(query.findOldestPersonPerCity(persons, usePointers));
      } else {
        std::cout << "Invalid option.\n";
      }
      double t = monitor.stopTimer();
      long mem = monitor.getMemoryUsage() - memStart;
      monitor.record("Find oldest person", t, mem);
      monitor.showRecord("Find oldest person", t, mem);
      break;
    }

    case 2: { // Highest assets
      int choice;
      std::cout << "\nFind richest person countrywide (0), by city (1), or by "
                   "tax group (2)? ";
      std::cin >> choice;

      monitor.startTimer();
      if (choice == 0) {
        Person richest =
            query.findHighestAssetsPersonCountryWide(persons, usePointers);
        std::cout << "Richest person: " << richest.name
                  << ", Assets: " << richest.assets << "\n";
      } else if (choice == 1) {
        std::cout << "\nRichest person per city:\n";
        printHashMap(query.findHighestAssetsPersonPerCity(persons));
      } else if (choice == 2) {
        auto richestByGroup =
            query.findHighestAssetsPersonPerTaxCalendarGroup(persons);
        for (const auto &[grp, person] : richestByGroup) {
          std::cout << taxCalendarGroupToString(grp) << " -> " << person.name
                    << "\n";
        }
      } else {
        std::cout << "Invalid option.\n";
      }
      double t = monitor.stopTimer();
      long mem = monitor.getMemoryUsage() - memStart;
      monitor.record("Find highest assets", t, mem);
      monitor.showRecord("Find highest assets", t, mem);
      break;
    }

    case 3: { // Tax filer queries
      int choice;
      std::cout << "\nChoose: Count people per tax group (0): ";
      std::cin >> choice;

      monitor.startTimer();
      if (choice == 0) {
        auto counts = query.countPeoplePerTaxCalendarGroup(persons);
        for (const auto &[grp, count] : counts) {
          std::cout << taxCalendarGroupToString(grp) << " -> " << count << "\n";
        }
      } else {
        std::cout << "Invalid option.\n";
      }
      double t = monitor.stopTimer();
      long mem = monitor.getMemoryUsage() - memStart;
      monitor.record("Tax filer queries", t, mem);
      monitor.showRecord("Tax filer queries", t, mem);
      break;
    }

    case 4: { // Additional queries
      int choice;
      std::cout << "\nChoose: Avg assets per city (0), % over 80 by tax group "
                   "(1), Count per city (2): ";
      std::cin >> choice;

      monitor.startTimer();
      if (choice == 0) {
        auto avgAssets = query.findCitiesWithHighestAverageAssets(persons);
        for (const auto &[city, avg] : avgAssets) {
          std::cout << "City: " << city << " -> Avg assets: " << avg << "\n";
        }
      } else if (choice == 1) {
        auto percentOver80 =
            query.calculatePercentageOfPeopleOlderThan80PerTaxCalendarGroup(
                persons);
        for (const auto &[grp, pct] : percentOver80) {
          std::cout << taxCalendarGroupToString(grp) << " -> " << pct << "%\n";
        }
      } else if (choice == 2) {
        auto countPerCity = query.countPeoplePerCity(persons);
        for (const auto &[city, cnt] : countPerCity) {
          std::cout << "City: " << city << " -> " << cnt << " people\n";
        }
      } else {
        std::cout << "Invalid option.\n";
      }
      double t = monitor.stopTimer();
      long mem = monitor.getMemoryUsage() - memStart;
      monitor.record("Additional queries", t, mem);
      monitor.showRecord("Additional queries", t, mem);
      break;
    }

    case 5: { // Show performance
      monitor.showSummary();
      break;
    }

    case 6: { // Export stats
      monitor.exportCSV();
      break;
    }

    case 7:
      std::cout << "Exiting...\n";
      break;

    default:
      std::cout << "Invalid option.\n";
      break;
    }

  } while (option != 7);

  return 0;
}
