#pragma once

#include <chrono>
#include <string>

class Person {

public:
  // Personal information
  std::string name;
  std::chrono::year_month_day birthDate;
  std::string currentCity;
  int id;
  int age;

  // Tax data
  int assets;      // Total value
  int debt;        // Due payments
  bool isTaxFiler; // Declares if the person declares rent.
  // enum taxCalendarGroup;

  Person(int id, std::string name, std::chrono::year_month_day birthDate,
         std::string currentCity, int assets, int debt, bool isTaxFiler);
  int getAge() const;
};
