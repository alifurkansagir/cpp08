#include <iostream>
#include <cassert>
#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

template <typename T>
static void	test(T &container, int value, std::string const &name)
{
	try
	{
		typename T::iterator	it = easyfind(container, value);
		std::cout << name << ": found " << *it
			<< " at index " << std::distance(container.begin(), it) << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << name << ": " << value << " -> " << e.what() << std::endl;
	}
}

static void	regressionTests(void)
{
	std::vector<int> values;
	values.push_back(-7);
	values.push_back(12);
	values.push_back(-7);
	assert(easyfind(values, -7) == values.begin());
	std::vector<int> const copy(values);
	assert(easyfind(copy, 12) == copy.begin() + 1);
	*easyfind(values, 12) = 99;
	assert(values[1] == 99);
	std::list<int> empty;
	bool missing = false;
	try { easyfind(empty, 0); }
	catch (std::runtime_error const &) { missing = true; }
	assert(missing);
	std::cout << "easyfind regression tests passed" << std::endl;
}

int	main(void)
{
	regressionTests();
	std::vector<int>	vec;
	std::list<int>		lst;
	std::deque<int>		deq;

	for (int i = 0; i < 10; i++)
	{
		vec.push_back(i * 2);
		lst.push_back(i * 3);
		deq.push_front(i);
	}
	vec.push_back(4); // tekrar eden deger: ilk eslesme bulunmali

	std::cout << "--- vector ---" << std::endl;
	test(vec, 4, "vector");
	test(vec, 18, "vector");
	test(vec, 5, "vector");

	std::cout << "--- list ---" << std::endl;
	test(lst, 9, "list");
	test(lst, 10, "list");

	std::cout << "--- deque ---" << std::endl;
	test(deq, 0, "deque");
	test(deq, 42, "deque");

	std::cout << "--- const vector ---" << std::endl;
	std::vector<int> const	cvec(vec);
	try
	{
		std::cout << "found " << *easyfind(cvec, 6) << std::endl;
		easyfind(cvec, -1);
	}
	catch (std::exception const &e)
	{
		std::cout << "-1 -> " << e.what() << std::endl;
	}

	std::cout << "--- empty ---" << std::endl;
	std::vector<int>	empty;
	test(empty, 0, "empty vector");

	std::cout << "--- modify via iterator ---" << std::endl;
	*easyfind(vec, 8) = 100;
	test(vec, 100, "vector");
	return (0);
}
