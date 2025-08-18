#include "queryMaker.hpp"

using namespace std;

const static std::vector<std::string> colombianCities = {
    "Bogotá",      "Medellín",   "Cali",        "Barranquilla",  "Cartagena",
    "Bucaramanga", "Pereira",    "Santa Marta", "Cúcuta",        "Ibagué",
    "Manizales",   "Pasto",      "Neiva",       "Villavicencio", "Armenia",
    "Sincelejo",   "Valledupar", "Montería",    "Popayán",       "Tunja",
};

Person QueryMaker::findOldestPersonCountryWide(vector<Person> personArray) {

  // get size
  int n = personArray.size();

  Person oldestPerson = personArray[0];

  for (int i = 1; i < n; i++) {
    if (personArray[i].age > oldestPerson.age) {
      oldestPerson = personArray[i]; // Update max if current person's age is
                                     // greater than the current one.
    }
  }

  return oldestPerson;
}

std::map<string, Person>
QueryMaker::findOldestPersonPerCity(vector<Person> personArray) {
  std::map<string, Person> oldestPersonPerCity;

  for (string city : colombianCities) {
    vector<Person> personsInCity;

    // Filters the personArray and pushes back only the people who beling to the
    // inputted city
    for (Person person : personArray) {
      if (person.currentCity == city) {
        personsInCity.push_back(person);
      }
    }

    oldestPersonPerCity.emplace(city,
                                findOldestPersonCountryWide(personsInCity));
  }

  return oldestPersonPerCity;
}

Person
QueryMaker::findHighestAssetsPersonCountryWide(vector<Person> personArray) {
  // get size
  int n = personArray.size();

  Person PersonOfHighestAssets = personArray[0];

  for (int i = 1; i < n; i++) {
    if (personArray[i].assets > PersonOfHighestAssets.assets) {
      PersonOfHighestAssets =
          personArray[i]; // replace current person of highest assets with the
                          // newfound person
    }
  }

  return PersonOfHighestAssets;
}

std::map<string, Person>
QueryMaker::findHighestAssetsPersonPerCity(vector<Person> personArray) {
  std::map<string, Person> HighestAssetPerCity;

  for (string city : colombianCities) {
    vector<Person> personsInCity;

    // Filters the personArray and pushes back only the people who beling to the
    // inputted city
    for (Person person : personArray) {
      if (person.currentCity == city) {
        personsInCity.push_back(person);
      }
    }

    HighestAssetPerCity.emplace(
        city, findHighestAssetsPersonCountryWide(personsInCity));
  }

  return HighestAssetPerCity;
}
