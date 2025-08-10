#include <iostream>
#include <cstdlib>

int get_the_number();
int read_guess();

int main(int argumentsCount, char **arguments)
{
    int theNumber = get_the_number();
    int guess = -1;

    while (true)
    {
        guess = read_guess();

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
            std::cout << "You guessed right!" << std::endl;
            break;
        }
    }
}

int get_the_number()
{
    std::srand(std::time(nullptr));
    return std::rand() % 100;
}

constexpr auto maxInputSize = std::numeric_limits<std::streamsize>::max();
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
