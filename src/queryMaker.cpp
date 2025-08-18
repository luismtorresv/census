#include "queryMaker.hpp"

using namespace std;

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
  for (const auto &person : personArray) {
    auto it = oldestPersonPerCity.find(person.currentCity);

    if (it == oldestPersonPerCity.end() || person.assets > it->second.assets) {
      oldestPersonPerCity.insert_or_assign(person.currentCity, person);
    }
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
QueryMaker::findHighestAssetsPersonPerCity(std::vector<Person> personArray) {
  std::map<string, Person> highestAssetPersonPerCity;

  for (const auto &person : personArray) {
    auto it = highestAssetPersonPerCity.find(person.currentCity);

    if (it == highestAssetPersonPerCity.end() ||
        person.assets > it->second.assets) {
      highestAssetPersonPerCity.insert_or_assign(person.currentCity, person);
    }
  }

  return highestAssetPersonPerCity;
}
