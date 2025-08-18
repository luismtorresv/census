#include "personFactory.hpp"

using namespace std;
using namespace std::chrono;

vector<Person> PersonFactory::generatePersonVector(int n) {
  vector<Person> personArray;
  personArray.reserve(
      n); // Not only does this reserve a set memory space, it also prevents the
          // array from seeking a default constructors

  for (int i = 0; i < n; i++) {
    personArray.push_back(createPerson());
  }

  return personArray;
}

Person PersonFactory::createPerson() {
  int id = generateRandomId();
  string name = generateRandomName();
  year_month_day birthDate = generateRandomBirthDate();
  string city = generateRandomCity();
  int assets = generateRandomAssets();
  int debt = generateRandomDebt();
  bool isTaxFiler = generateRandomBoolean();

  return Person{id, name, birthDate, city, assets, debt, isTaxFiler};
}

int PersonFactory::generateRandomId() {
  static long counter = 1'000'000'000;
  return counter++;
}

string PersonFactory::generateRandomName() {
  const static vector<string> names = {
      "Juan",      "Carlos",   "José",      "James",    "Andrés",   "Miguel",
      "Luis",      "Pedro",    "Alejandro", "Ricardo",  "Felipe",   "David",
      "Jorge",     "Santiago", "Daniel",    "Edison",   "Nestor",   "Gertridis",
      "Aidan",     "Solomon",  "Glory",     "María",    "Luisa",    "Carmen",
      "Ana",       "Sofía",    "Isabel",    "Laura",    "Andrea",   "Paula",
      "Valentina", "Camila",   "Daniela",   "Carolina", "Fernanda", "Gabriela",
      "Patricia",  "Claudia",  "Caligo",    "Diana",    "Lucía",    "Ximena",
      "Xenaria"};

  const static vector<string> surnames = {
      "Gómez",    "Rodríguez", "Martínez", "López",  "García", "Pérez",
      "González", "Sánchez",   "Ramírez",  "Torres", "Díaz",   "Vargas",
      "Castro",   "Ruiz",      "Álvarez",  "Romero", "Suárez", "Rojas",
      "Moreno",   "Muñoz",     "Valencia", "Griven"};

  // Generate a random number to input as position for vectors 'names' and
  // 'surnames'.

  int random_name_pos = generateRandomNumber(0, names.size());
  int random_surname_pos = generateRandomNumber(0, surnames.size());

  return names[random_name_pos] + surnames[random_surname_pos];
}

year_month_day PersonFactory::generateRandomBirthDate() {
  unsigned int rand_day = generateRandomNumber(1, 31);
  unsigned int rand_month = generateRandomNumber(1, 12);
  int rand_year = generateRandomNumber(1925, 2025);

  return year{rand_year} / month{rand_month} /
         day{rand_day}; // this is the expected expression.
};

string PersonFactory::generateRandomCity() {
  const static std::vector<std::string> colombianCities = {
      "Bogotá",      "Medellín",   "Cali",        "Barranquilla",  "Cartagena",
      "Bucaramanga", "Pereira",    "Santa Marta", "Cúcuta",        "Ibagué",
      "Manizales",   "Pasto",      "Neiva",       "Villavicencio", "Armenia",
      "Sincelejo",   "Valledupar", "Montería",    "Popayán",       "Tunja",
  };

  // Generate a random number to input as position for vector 'colombianCities'.
  int random_cities_pos = generateRandomNumber(0, colombianCities.size());

  return colombianCities[random_cities_pos];
}

int PersonFactory::generateRandomNumber(int min, int max) {
  static mt19937 generator(random_device{}()); // This is the seed
  uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

int PersonFactory::generateRandomAssets() {
  return generateRandomNumber(1000, 10000);
}

int PersonFactory::generateRandomDebt() {
  return generateRandomNumber(1000, 10000);
}

bool PersonFactory::generateRandomBoolean() {
  int random_val = generateRandomNumber(0, 1);

  return (random_val == 0) ? true : false;
}

taxCalendarGroup PersonFactory::determineTaxCalendarGroup(int id) {
  int lastTwoDigits = id % 100;
  taxCalendarGroup group;

  // We will assume that the number shall always be positive.
  if (lastTwoDigits <= 39) {
    group = groupA;
  } else if (lastTwoDigits <= 79) {
    group = groupB;
  } else {
    group = groupC;
  }

  return group;
}
