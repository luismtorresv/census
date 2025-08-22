#include "queryMaker.hpp"

using namespace std;

Person QueryMaker::findOldestPersonCountryWide(std::vector<Person> &personArray,
                                               bool usePassByReference) {
  std::vector<Person> localCopy;
  const std::vector<Person> *dataPtr = &personArray;
  if (!usePassByReference) {
    localCopy = personArray;
    dataPtr = &localCopy;
  }
  const std::vector<Person> &data = *dataPtr;

  int n = data.size();
  Person oldestPerson = data[0];

  for (int i = 1; i < n; i++) {
    if (data[i].age > oldestPerson.age) {
      oldestPerson = data[i];
    }
  }

  return oldestPerson;
}

std::map<std::string, Person>
QueryMaker::findOldestPersonPerCity(std::vector<Person> &personArray,
                                    bool usePassByReference) {
  std::vector<Person> localCopy;
  const std::vector<Person> *dataPtr = &personArray;
  if (!usePassByReference) {
    localCopy = personArray;
    dataPtr = &localCopy;
  }
  const std::vector<Person> &data = *dataPtr;

  std::map<std::string, Person> oldestPersonPerCity;
  for (const auto &person : data) {
    auto it = oldestPersonPerCity.find(person.currentCity);

    if (it == oldestPersonPerCity.end() || person.age > it->second.age) {
      oldestPersonPerCity.insert_or_assign(person.currentCity, person);
    }
  }

  return oldestPersonPerCity;
}

Person
QueryMaker::findHighestAssetsPersonCountryWide(std::vector<Person> &personArray,
                                               bool usePassByReference) {
  std::vector<Person> localCopy;
  const std::vector<Person> *dataPtr = &personArray;
  if (!usePassByReference) {
    localCopy = personArray;
    dataPtr = &localCopy;
  }
  const std::vector<Person> &data = *dataPtr;

  int n = data.size();
  Person PersonOfHighestAssets = data[0];

  for (int i = 1; i < n; i++) {
    if (data[i].assets > PersonOfHighestAssets.assets) {
      PersonOfHighestAssets = data[i];
    }
  }

  return PersonOfHighestAssets;
}

std::map<string, Person>
QueryMaker::findHighestAssetsPersonPerCity(std::vector<Person> &personArray) {
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

std::map<taxCalendarGroup, Person>
QueryMaker::findHighestAssetsPersonPerTaxCalendarGroup(
    std::vector<Person> &personArray) {
  std::map<taxCalendarGroup, Person> highestAssetPersonTaxCalendarGroup;
  PersonFactory factory;
  taxCalendarGroup taxGroup;

  for (const auto &person : personArray) {
    taxGroup = factory.determineTaxCalendarGroup(person.id);
    auto it = highestAssetPersonTaxCalendarGroup.find(taxGroup);

    if (it == highestAssetPersonTaxCalendarGroup.end() ||
        person.assets > it->second.assets) {
      highestAssetPersonTaxCalendarGroup.insert_or_assign(taxGroup, person);
    }
  }
  return highestAssetPersonTaxCalendarGroup;
}

std::map<taxCalendarGroup, int>
QueryMaker::countPeoplePerTaxCalendarGroup(std::vector<Person> &personArray,
                                           bool usePassByReference) {
  std::map<taxCalendarGroup, int> peoplePerGroup;

  std::vector<Person> localCopy;
  const std::vector<Person> *dataPtr = &personArray;
  if (!usePassByReference) {
    localCopy = personArray;
    dataPtr = &localCopy;
  }
  const std::vector<Person> &data = *dataPtr;

  peoplePerGroup[taxCalendarGroup::groupA] = 0;
  peoplePerGroup[taxCalendarGroup::groupB] = 0;
  peoplePerGroup[taxCalendarGroup::groupC] = 0;
  PersonFactory factory;

  for (const auto &person : data) {
    taxCalendarGroup taxGroup = factory.determineTaxCalendarGroup(person.id);
    peoplePerGroup[taxGroup] += 1;
  }

  return peoplePerGroup;
}

vector<pair<string, double>> QueryMaker::findCitiesWithHighestAverageAssets(
    const vector<Person> &personArray, bool usePassByReference, size_t topK) {

  vector<Person> localCopy;
  const vector<Person> *dataPtr = &personArray;
  if (!usePassByReference) {
    localCopy = personArray;
    dataPtr = &localCopy;
  }
  const vector<Person> &data = *dataPtr;

  // accumulate sums and counts per city
  unordered_map<string, pair<long long, int>>
      citySumCount; // city -> (sumAssets, count)
  citySumCount.reserve(256);

  for (const auto &p : data) {
    const string &city = p.currentCity;
    auto it = citySumCount.find(city);
    if (it == citySumCount.end()) {
      citySumCount.emplace(city,
                           make_pair(static_cast<long long>(p.assets), 1));
    } else {
      it->second.first += static_cast<long long>(p.assets);
      it->second.second += 1;
    }
  }

  // compute averages and push into vector
  vector<pair<string, double>> averages;
  averages.reserve(citySumCount.size());
  for (auto &kv : citySumCount) {
    const string &city = kv.first;
    long long sum = kv.second.first;
    int count = kv.second.second;
    double avg = (count > 0)
                     ? static_cast<double>(sum) / static_cast<double>(count)
                     : 0.0;
    averages.emplace_back(city, avg);
  }

  // sort descending by average
  sort(averages.begin(), averages.end(),
       [](const pair<string, double> &a, const pair<string, double> &b) {
         return a.second > b.second;
       });

  // if topK == 0 -> return all
  if (topK == 0 || topK >= averages.size())
    return averages;

  // otherwise return topK
  vector<pair<string, double>> result(
      averages.begin(), averages.begin() + static_cast<ptrdiff_t>(topK));
  return result;
}

std::map<taxCalendarGroup, double>
QueryMaker::calculatePercentageOfPeopleOlderThan80PerTaxCalendarGroup(
    const std::vector<Person> &personArray, bool usePassByReference) {

  std::vector<Person> localCopy;
  const std::vector<Person> *dataPtr = &personArray;
  if (!usePassByReference) {
    localCopy = personArray;
    dataPtr = &localCopy;
  }
  const std::vector<Person> &data = *dataPtr;

  PersonFactory factory;

  // counters per group
  std::map<taxCalendarGroup, long long> totalCount;
  std::map<taxCalendarGroup, long long> olderThan80Count;

  totalCount[taxCalendarGroup::groupA] = 0;
  totalCount[taxCalendarGroup::groupB] = 0;
  totalCount[taxCalendarGroup::groupC] = 0;
  olderThan80Count = totalCount;

  for (const auto &p : data) {
    taxCalendarGroup grp = factory.determineTaxCalendarGroup(p.id);

    totalCount[grp] += 1;

    int age = 0;
    try {
      age = p.getAge();
    } catch (...) {
      age = 0;
    }

    if (age > 80)
      olderThan80Count[grp] += 1;
  }

  // calculate percentages (0.0 - 100.0)
  std::map<taxCalendarGroup, double> percentage;
  for (const auto &kv : totalCount) {
    taxCalendarGroup grp = kv.first;
    long long tot = kv.second;
    long long older = olderThan80Count[grp];
    double pct = 0.0;
    if (tot > 0)
      pct = (static_cast<double>(older) / static_cast<double>(tot)) * 100.0;
    percentage[grp] = pct;
  }

  return percentage;
}

map<string, int>
QueryMaker::countPeoplePerCity(const vector<Person> &personArray,
                               bool usePassByReference) {
  vector<Person> localCopy;
  const vector<Person> *dataPtr = &personArray;
  if (!usePassByReference) {
    localCopy = personArray;
    dataPtr = &localCopy;
  }
  const vector<Person> &data = *dataPtr;

  unordered_map<string, int> tmp;
  tmp.reserve(256);
  for (const auto &p : data) {
    tmp[p.currentCity] += 1;
  }

  map<string, int> result;
  for (const auto &kv : tmp)
    result.emplace(kv.first, kv.second);
  return result;
}