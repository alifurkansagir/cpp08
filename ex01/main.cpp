#include <iostream>
#include <cassert>
#include <sstream>
#include <iterator>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <climits>
#include "Span.hpp"

static void	subjectTest(void)
{
	Span sp = Span(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
}

static void	exceptionTests(void)
{
	Span	sp(2);

	try
	{
		sp.shortestSpan();
	}
	catch (std::exception const &e)
	{
		std::cout << "empty: " << e.what() << std::endl;
	}
	sp.addNumber(1);
	try
	{
		sp.longestSpan();
	}
	catch (std::exception const &e)
	{
		std::cout << "one number: " << e.what() << std::endl;
	}
	sp.addNumber(2);
	try
	{
		sp.addNumber(3);
	}
	catch (std::exception const &e)
	{
		std::cout << "full: " << e.what() << std::endl;
	}

	std::vector<int>	tooMany(5, 1);
	try
	{
		Span	small(3);
		small.addRange(tooMany.begin(), tooMany.end());
	}
	catch (std::exception const &e)
	{
		std::cout << "range too big: " << e.what() << std::endl;
	}
}

static void	extremeTest(void)
{
	Span	sp(2);

	sp.addNumber(INT_MIN);
	sp.addNumber(INT_MAX);
	std::cout << "INT_MIN..INT_MAX shortest: " << sp.shortestSpan()
		<< ", longest: " << sp.longestSpan() << std::endl;
}

static void	bigTest(unsigned int n)
{
	std::vector<int>	numbers;

	numbers.reserve(n);
	for (unsigned int i = 0; i < n; i++)
		numbers.push_back(std::rand());

	Span	sp(n);
	sp.addRange(numbers.begin(), numbers.end());
	std::cout << n << " numbers -> size: " << sp.size()
		<< ", shortest: " << sp.shortestSpan()
		<< ", longest: " << sp.longestSpan() << std::endl;
}

static void	copyTest(void)
{
	std::list<int>	lst;
	for (int i = 0; i < 5; i++)
		lst.push_back(i * i);

	Span	a(10);
	a.addRange(lst.begin(), lst.end());
	Span	b(a);
	Span	c(1);
	c = a;
	a.addNumber(1000);
	std::cout << "a longest: " << a.longestSpan()
		<< ", b longest: " << b.longestSpan()
		<< ", c longest: " << c.longestSpan() << std::endl;
}

static void	rangeTests(void)
{
	Span streamSpan(4);
	std::istringstream input("1 2 3 4");
	streamSpan.addRange(std::istream_iterator<int>(input), std::istream_iterator<int>());
	assert(streamSpan.size() == 4);
	assert(streamSpan.shortestSpan() == 1);
	assert(streamSpan.longestSpan() == 3);
	Span limited(3);
	limited.addNumber(8);
	std::istringstream excess("10 20 30");
	bool full = false;
	try { limited.addRange(std::istream_iterator<int>(excess), std::istream_iterator<int>()); }
	catch (Span::FullException const &) { full = true; }
	assert(full && limited.size() == 1);
	std::vector<int> empty;
	streamSpan.addRange(empty.begin(), empty.end());
	assert(streamSpan.size() == 4);
	Span zero(0);
	zero.addRange(empty.begin(), empty.end());
	full = false;
	try { zero.addNumber(1); }
	catch (Span::FullException const &) { full = true; }
	assert(full && zero.size() == 0);
	std::cout << "range regression tests passed" << std::endl;
}

static void	boundaryTests(void)
{
	Span duplicates(3);
	duplicates.addNumber(-4);
	duplicates.addNumber(-4);
	duplicates.addNumber(9);
	assert(duplicates.shortestSpan() == 0);
	assert(duplicates.longestSpan() == 13);
	Span extremes(2);
	extremes.addNumber(INT_MIN);
	extremes.addNumber(INT_MAX);
	unsigned int expected = static_cast<unsigned int>(INT_MAX)
		- static_cast<unsigned int>(INT_MIN);
	assert(extremes.shortestSpan() == expected);
	assert(extremes.longestSpan() == expected);
	Span empty(1);
	for (int count = 0; count < 2; ++count)
	{
		bool shortestFailed = false;
		bool longestFailed = false;
		try { empty.shortestSpan(); }
		catch (Span::NoSpanException const &) { shortestFailed = true; }
		try { empty.longestSpan(); }
		catch (Span::NoSpanException const &) { longestFailed = true; }
		assert(shortestFailed && longestFailed);
		if (count == 0)
			empty.addNumber(42);
	}
	Span assigned(1);
	assigned = duplicates;
	assert(assigned.capacity() == 3 && assigned.size() == 3);
	assert(assigned.longestSpan() == 13);
	Span independent(extremes);
	extremes = duplicates;
	assert(independent.longestSpan() == expected);
	std::vector<int> numbers;
	for (int i = 0; i < 10000; ++i)
		numbers.push_back(i * 3 - 15000);
	Span large(10000);
	large.addRange(numbers.begin(), numbers.end());
	assert(large.shortestSpan() == 3 && large.longestSpan() == 29997);
	std::cout << "Span boundary tests passed" << std::endl;
}

int	main(void)
{
	boundaryTests();
	rangeTests();
	std::srand(std::time(NULL));

	std::cout << "--- subject ---" << std::endl;
	subjectTest();
	std::cout << "--- exceptions ---" << std::endl;
	exceptionTests();
	std::cout << "--- extremes ---" << std::endl;
	extremeTest();
	std::cout << "--- copy (range from std::list) ---" << std::endl;
	copyTest();
	std::cout << "--- big ---" << std::endl;
	bigTest(10000);
	bigTest(100000);
	return (0);
}
