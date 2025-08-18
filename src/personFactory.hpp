#pragma once

#include "person.hpp"
#include <random>

enum taxCalendarGroup { groupA, groupB, groupC };

class PersonFactory {
public:
  const static std::vector<std::string> colombianCities;

  Person createPerson();
  std::vector<Person> generatePersonVector(int n);

  int generateRandomId();
  std::string generateRandomName();
  std::chrono::year_month_day generateRandomBirthDate();
  std::string generateRandomCity();
  int generateRandomNumber(int min, int max);
  int generateRandomAssets();
  int generateRandomDebt();
  bool generateRandomBoolean();

  taxCalendarGroup determineTaxCalendarGroup(int id);
};
