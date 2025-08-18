#pragma once
#include "person.hpp"
#include "personFactory.hpp"
#include <map>

class QueryMaker {

public:
  Person findOldestPersonCountryWide(std::vector<Person> personArray);
  std::map<std::string, Person>
  findOldestPersonPerCity(std::vector<Person> personArray);
  Person findHighestAssetsPersonCountryWide(std::vector<Person> personArray);
  std::map<std::string, Person>
  findHighestAssetsPersonPerCity(std::vector<Person> personArray);
  Person
  findHighestAssetsPersonPerTaxCalendarGroup(std::vector<Person> personArray);
  int countPeoplePerTaxCalendarGroup(std::vector<Person> personArray);
  void validateTaxCalendarGroup(
      std::vector<Person>
          personArray); // I don't know what this function returns yet.

  std::vector<std::string>
  findCitiesWithHighestAverageAssets(std::vector<Person> personArray);
  void calculatePercentageOfPeopleOlderThan80PerTaxCalendarGroup(
      std::vector<Person> personArray); // I don't know
                                        // what this
                                        // function
                                        // returns yet.
  int countPeoplePerCity(std::vector<Person> personArray);
};