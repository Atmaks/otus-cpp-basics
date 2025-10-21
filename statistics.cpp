#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>

class IStatistics
{
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char *name() const = 0;
};

class Min : public IStatistics
{
public:
	Min() : m_min{std::numeric_limits<double>::min()}
	{
	}

	void update(double next) override
	{
		if (!this->encounteredAtLeastOneNumber)
		{
			this->m_min = next;
			this->encounteredAtLeastOneNumber = true;
		}
		else if (next < m_min)
		{
			m_min = next;
		}
	}

	double eval() const override
	{
		return m_min;
	}

	const char *name() const override
	{
		return "min";
	}

private:
	double m_min;
	bool encounteredAtLeastOneNumber = false;
};

class Max : public IStatistics
{
public:
	Max() : max{0}
	{
	}

	void update(double next) override
	{
		if (!this->encounteredAtLeastOneNumber)
		{
			this->max = next;
			this->encounteredAtLeastOneNumber = true;
		}
		else if (next > max)
		{
			this->max = next;
		}
	}

	double eval() const override
	{
		return this->max;
	}

	const char *name() const override
	{
		return "max";
	}

private:
	double max;
	bool encounteredAtLeastOneNumber = false;
};

class Mean : public IStatistics
{
public:
	void update(double next) override
	{
		this->mean = (next + this->count * this->mean) / (this->count + 1);
		this->count += 1;
	}

	double eval() const override
	{
		return this->mean;
	}

	const char *name() const override
	{
		return "mean";
	}

private:
	double mean = 0;
	int count = 0;
};

class StandardDeviation : public IStatistics
{
public:
	void update(double next) override
	{
		this->sum += next;
		this->sumOfSquares += next * next;
		this->count++;
	}

	double eval() const override
	{
		// нечаянно не поделить на ноль
		if (this->count == 0)
		{
			return 0;
		}

		// разность между средним суммы квадратов и квадратом среднего
		return std::sqrt((this->sumOfSquares / this->count) - (this->sum * this->sum) / (this->count * this->count));
	}

	const char *name() const override
	{
		return "standard deviation";
	}

private:
	double sum = 0;
	double sumOfSquares = 0;
	int count = 0;
};

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Please, call with one argument "
				  << "( example: " << argv[0] << " <path to file input.txt> )";
		return 1;
	}

	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];
	std::string inFileName(argv[1]);

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new StandardDeviation{};

	double val = 0;

	std::ifstream inFile(inFileName, std::ios::in);
	if (!inFile.is_open())
	{
		std::cerr << "Failed to open input file " << inFileName << "\n";
		return 1;
	}

	while (inFile >> val)
	{
		for (size_t i = 0; i < statistics_count; ++i)
		{
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good())
	{
		std::cerr << "Failed to read input\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i)
	{
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	return 0;
}
