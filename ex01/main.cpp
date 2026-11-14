#include <iostream>
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

int	main(void)
{
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
