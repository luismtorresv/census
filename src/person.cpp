#include "person.h"

using namespace std;
using namespace std::chrono;

Person::Person(int id, std::string name, std::chrono::year_month_day birthDate, std::string currentCity, int assets, int debt, bool isTaxFiler)
{
    this->name = name;
    this->birthDate = birthDate;
    this->currentCity = currentCity;
    this->id = id;
    this->assets = assets;
    this->debt = debt;
    this->isTaxFiler = isTaxFiler;
}

int Person::getAge()
{
    year yearOfBirth = this->birthDate.year();

    // system_clock returns a time_point, which must be turned into a year by eliminating the time of day
    const auto now = floor<days>(system_clock::now());

    // converts the time_point now into the type year_month_day, and then extracts only the year.
    year currentYear = year_month_day{floor<days>(now)}.year();

    years timeDifference = currentYear - yearOfBirth;
    int age = timeDifference.count();

    return age;
}
