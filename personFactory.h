#ifndef PERSONFACTORY_INCLUDE
#define PERSONFACTORY_INCLUDE
#include "person.h"
#include <random>

enum taxCalendarGroup
{
    groupA,
    groupB,
    groupC
};

class PersonFactory
{
public:
    Person createPerson();

    std::vector<Person> generatePersonVector();

    int generateRandomId();

    std::string generateRandomName();

    std::chrono::year_month_day generateRandomBirthDate();

    std::string generateRandomCity();

    int generateRandomAssets();

    int generateRandomDebt();

    bool generateRandomBoolean();

    taxCalendarGroup determineTaxCalendarGroup(Person);
};

#endif