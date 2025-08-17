#include "personFactory.h"

using namespace std;

Person PersonFactory::createPerson()
{
    int id = generateRandomId();
}

int PersonFactory::generateRandomId()
{
    static long contador = 1000000000; // Inicia en 1,000,000,000
    return contador++;
}

string PersonFactory::generateRandomName()
{
    const static vector<string> names = {
        "Juan", "Carlos", "José", "James", "Andrés", "Miguel", "Luis", "Pedro", "Alejandro", "Ricardo",
        "Felipe", "David", "Jorge", "Santiago", "Daniel", "Edison", "Nestor", "Gertridis", "Aidan", "Solomon",
        "Glory", "María", "Luisa", "Carmen", "Ana", "Sofía", "Isabel", "Laura", "Andrea", "Paula", "Valentina",
        "Camila", "Daniela", "Carolina", "Fernanda", "Gabriela", "Patricia", "Claudia", "Caligo", "Diana", "Lucía",
        "Ximena", "Xenaria"};

    const static vector<string> surnames = {
        "Gómez", "Rodríguez", "Martínez", "López", "García", "Pérez", "González", "Sánchez", "Ramírez", "Torres",
        "Díaz", "Vargas", "Castro", "Ruiz", "Álvarez", "Romero", "Suárez", "Rojas", "Moreno", "Muñoz", "Valencia",
        "Griven"};

    /*Generate a random number to input as position for vectors 'names' and 'surnames'.
    Taken from: https://stackoverflow.com/questions/69025745/can-i-pick-a-random-element-from-an-array-in-c*/

    mt19937 generator(random_device{}());

    uniform_int_distribution<size_t> names_distribution(0, names.size() - 1);       // equal chance to get a random name
    uniform_int_distribution<size_t> surnames_distribution(0, suranmes.size() - 1); // equal chance to get a random surname

    random_name_pos = names_distribution(generator);
    random_surname_pos = surnames_distribution(generator);

    return names[random_name_pos] + surnames[random_surname_pos]
}
