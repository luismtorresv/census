#pragma once
#include "person.hpp"
#include "personFactory.hpp"
#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

class QueryMaker {

public:
  Person findOldestPersonCountryWide(std::vector<Person> personArray);
  std::map<std::string, Person>
  findOldestPersonPerCity(std::vector<Person> personArray);
  Person findHighestAssetsPersonCountryWide(std::vector<Person> personArray);
  std::map<std::string, Person>
  findHighestAssetsPersonPerCity(std::vector<Person> personArray);

  std::map<taxCalendarGroup, Person>
  findHighestAssetsPersonPerTaxCalendarGroup(std::vector<Person> &personArray);
  std::map<taxCalendarGroup, int>
  countPeoplePerTaxCalendarGroup(std::vector<Person> &personArray);

  // Additional queries:
  // Return vector of pairs (city, average_assets) sorted desc by average.
  // topK indicates how many top cities to return (default 5). If topK == 0 ->
  // return all.
  std::vector<std::pair<std::string, double>>
  findCitiesWithHighestAverageAssets(const std::vector<Person> &personArray,
                                     bool usePassByReference = true,
                                     std::size_t topK = 5);
  std::map<taxCalendarGroup, double>
  calculatePercentageOfPeopleOlderThan80PerTaxCalendarGroup(
      const std::vector<Person> &personArray, bool usePassByReference = true);
  std::map<std::string, int>
  countPeoplePerCity(const std::vector<Person> &personArray,
                     bool usePassByReference = true);
};