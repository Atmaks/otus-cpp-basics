#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

struct ScoreboardEntry
{
    std::string name;
    int minAttempts;
};

typedef std::vector<ScoreboardEntry> Scoreboard;

int read_max(int argumentCount, char **arguments);
int get_the_number(int maxNumber);
std::string read_name();
int read_guess(int maxNumber);
Scoreboard read_scoreboard();
void record_attempt(Scoreboard &, std::string &, int);
void write_scoreboard(Scoreboard &);

constexpr auto MAX_INPUT_SIZE = std::numeric_limits<std::streamsize>::max();
constexpr auto SCOREBOARD_FILENAME = "scoreboard.txt";
constexpr auto DEFAULT_MAX_NUMBER = 10;

int main(int argumentCount, char **arguments)
{
    int maxNumber = read_max(argumentCount, arguments);
    int theNumber = get_the_number(maxNumber);
    Scoreboard scoreboard = read_scoreboard();
    std::string name = read_name();

    int guess = -1;
    int attempts = 0;

    while (true)
    {
        guess = read_guess(maxNumber);
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

    record_attempt(scoreboard, name, attempts);
    write_scoreboard(scoreboard);
}

int read_max(int argumentCount, char **arguments)
{
    if (argumentCount == 1) // executable name and terminator
    {
        return DEFAULT_MAX_NUMBER;
    }

    if (argumentCount != 3)
    {
        std::cout << "Wrong number of arguments: " << argumentCount << std::endl
                  << "Usage: main.exe -max 42" << std::endl;
        exit(1);
    }

    std::string firstArg = arguments[1];
    if (firstArg != "-max")
    {
        std::cout << "Invalid argument." << std::endl
                  << "Usage: main.exe -max 42" << std::endl;
        exit(1);
    }

    return std::stoi(arguments[2]);
}

int get_the_number(int maxNumber)
{
    std::srand(std::time(nullptr));
    return std::rand() % maxNumber;
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
            std::cerr << "Some weird shit, terminating..." << std::endl;
            std::exit(1);
        }

        if (std::cin.fail())
        {
            std::cout << "Failed to read name. Let's try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(MAX_INPUT_SIZE, '\n');
            continue;
        }

        if (name.length() > maxLength)
        {
            std::cout << "No more than " << maxLength << " characters please!" << std::endl;
            std::cin.ignore(MAX_INPUT_SIZE, '\n');
            continue;
        }

        break;
    }

    return name;
}

Scoreboard read_scoreboard()
{
    std::fstream fileStream{SCOREBOARD_FILENAME, std::ios::in | std::ios::out};
    Scoreboard scoreboard{};

    if (fileStream.fail())
    {
        return scoreboard;
    }

    while (fileStream.good())
    {
        std::string name;
        int minAttempts;

        fileStream >> name >> minAttempts;

        if (fileStream.eof())
        {
            break;
        }

        if (fileStream.bad() || fileStream.fail())
        {
            std::cerr << "Some weird shit while reading scoreboard, assuming the scoreboard is empty" << std::endl;
            std::exit(1);
        }

        scoreboard.push_back(ScoreboardEntry{name, minAttempts});
    }

    return scoreboard;
}

int read_guess(int maxNumber)
{
    int guess = -1;

    while (true)
    {
        std::cout << "Please enter an integer between 0 and " << maxNumber << std::endl;

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
            std::cin.ignore(MAX_INPUT_SIZE, '\n');
            continue;
        }

        if (guess < 0 || guess > 100)
        {
            std::cout << "Your guess must be between 0 and " << maxNumber << "!Try again." << std::endl;
            std::cin.ignore(MAX_INPUT_SIZE, '\n');
            continue;
        }

        break;
    }

    return guess;
}

void record_attempt(Scoreboard &scoreboard, std::string &name, int attempts)
{
    bool found = false;

    for (size_t i = 0; i < scoreboard.size(); i++)
    {
        auto &entry = scoreboard.at(i);
        if (entry.name != name || entry.minAttempts <= attempts)
        {
            continue;
        }

        entry.minAttempts = attempts;
        found = true;
        break;
    }

    if (!found)
    {
        scoreboard.push_back(ScoreboardEntry{name, attempts});
    }
}

void write_scoreboard(Scoreboard &scoreboard)
{
    std::fstream fileStream{SCOREBOARD_FILENAME, std::ios::out};

    for (size_t i = 0; i < scoreboard.size(); i++)
    {
        auto &entry = scoreboard.at(i);
        if (fileStream.bad())
        {
            std::cout << "Failed to write scoreboard! Terminating..." << std::endl;
            std::exit(1);
        }

        fileStream << entry.name << " " << entry.minAttempts << std::endl;
    }

    fileStream.close();
}
