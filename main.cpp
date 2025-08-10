#include <iostream>
#include <cstdlib>
#include <string>

int get_the_number();
std::string read_name();
int read_guess();

constexpr auto maxInputSize = std::numeric_limits<std::streamsize>::max();

int main(int argumentsCount, char **arguments)
{
    int theNumber = get_the_number();
    std::string name = read_name();

    int guess = -1;
    int attempts = 0;

    while (true)
    {
        guess = read_guess();
        attempts += 1;

        if (guess > theNumber)
        {
            std::cout << "less than" << std::endl;
        }
        else if (guess < theNumber)
        {
            std::cout << "greater than" << std::endl;
        }
        else
        {
            std::cout << "You guessed right!";
            break;
        }
    }

    std::cout << " Name: " << name << " Attempts: " << attempts << std::endl;
}

int get_the_number()
{
    std::srand(std::time(nullptr));
    return std::rand() % 100;
}

std::string read_name()
{
    std::string name;
    const int maxLength = 20;

    while (true)
    {
        std::cout << "Hi! Enter your name please:" << std::endl;

        std::cin >> name;

        if (std::cin.eof() || std::cin.bad())
        {
            std::cout << "Some weird shit, terminating..." << std::endl;
            std::exit(1);
        }

        if (std::cin.fail())
        {
            std::cout << "Failed to read name. Let's try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(maxInputSize, '\n');
            continue;
        }

        if (name.length() > maxLength)
        {
            std::cout << "No more than " << maxLength << " characters please!" << std::endl;
            std::cin.ignore(maxInputSize, '\n');
            continue;
        }

        break;
    }

    return name;
}

int read_guess()
{
    int guess = -1;

    while (true)
    {
        std::cout << "Please enter an integer between 0 and 100" << std::endl;

        std::cin >> guess;

        if (std::cin.eof() || std::cin.bad())
        {
            std::cout << "Some weird shit, terminating..." << std::endl;
            std::exit(1);
        }

        if (std::cin.fail())
        {
            std::cout << "Failed to read the guess. ";
            std::cin.clear();
            std::cin.ignore(maxInputSize, '\n');
            continue;
        }

        if (guess < 0 || guess > 100)
        {
            std::cout << "Your guess must be between 0 and 100! Try again." << std::endl;
            std::cin.ignore(maxInputSize, '\n');
            continue;
        }

        break;
    }

    return guess;
}
