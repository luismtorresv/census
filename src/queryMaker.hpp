#pragma once

#include "person.hpp"

class QueryMaker{

public:
    Person findOldestPersonCountryWide();
    Person findOldestPersonPerCity();
    Person findHighestAssestsPersonCountryWide();
    Person findHighestAssestsPersonPerCity();
    Person findHighestAssestsPersonPerTaxCalendarGroup();
    int countPeoplePerTaxCalendarGroup();
    void validateTaxCalendarGroup(); //I don't know what this function returns yet.

    std::vector<std::string> findCitiesWithHighestAverageAssets();
    void calculatePercentageOfPeopleOlderThan80PerTaxCalendarGroup(); //I don't know what this function returns yet.
    int countPeoplePerCity();
}