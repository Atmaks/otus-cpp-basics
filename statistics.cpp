#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>
#include <vector>
#include <string>

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
	Min() : m_min{std::numeric_limits<double>::max()}
	{
	}

	void update(double next) override
	{
		if (next < m_min)
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
};

class Max : public IStatistics
{
public:
	Max() : max{std::numeric_limits<double>::lowest()}
	{
	}

	void update(double next) override
	{
		if (next > max)
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

class Percentile : public IStatistics
{
public:
	Percentile(int percent) : percent{percent}
	{
	}

	void update(double next) override
	{
		this->inputs.push_back(next);
	}

	double eval() const override
	{
		// нечаянно не поделить на ноль
		if (this->inputs.size() == 0)
		{
			return 0;
		}

		double percentileRatio = this->percent / 100.0;
		int nearestIndex = (int)(this->inputs.size() * percentileRatio);
		return this->inputs[nearestIndex];
	}

	const char *name() const override
	{
		return "percentile (exclusive)";
	}

private:
	int percent;
	std::vector<double> inputs{};
};

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Please, call with one argument "
				  << "( example: " << argv[0] << " <path to file input.txt> )";
		return 1;
	}

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];
	std::string inFileName(argv[1]);

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new StandardDeviation{};
	statistics[4] = new Percentile{90};
	statistics[5] = new Percentile{95};

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
		// delete right away
		delete statistics[i];
	}

	return 0;
}
