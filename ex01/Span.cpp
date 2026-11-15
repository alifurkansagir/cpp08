#include "Span.hpp"
#include <algorithm>

Span::Span(void) : _maxSize(0)
{
}

Span::Span(unsigned int n) : _maxSize(n)
{
	_numbers.reserve(n);
}

Span::Span(Span const &other) : _maxSize(other._maxSize), _numbers(other._numbers)
{
}

Span	&Span::operator=(Span const &other)
{
	if (this != &other)
	{
		std::vector<int> copy(other._numbers);
		_numbers.swap(copy);
		_maxSize = other._maxSize;
	}
	return (*this);
}

Span::~Span(void)
{
}

void	Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw FullException();
	_numbers.push_back(number);
}

// Sirala, yan yana elemanlar arasindaki en kucuk farki bul.
// Unsigned subtraction represents the full distance without signed overflow.
unsigned int	Span::shortestSpan(void) const
{
	if (_numbers.size() < 2)
		throw NoSpanException();

	std::vector<int>	sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());

	unsigned int shortest = static_cast<unsigned int>(sorted[1])
		- static_cast<unsigned int>(sorted[0]);
	for (std::vector<int>::size_type i = 2; i < sorted.size(); i++)
	{
		unsigned int diff = static_cast<unsigned int>(sorted[i])
			- static_cast<unsigned int>(sorted[i - 1]);
		if (diff < shortest)
			shortest = diff;
	}
	return (shortest);
}

// En buyuk - en kucuk.
unsigned int	Span::longestSpan(void) const
{
	if (_numbers.size() < 2)
		throw NoSpanException();

	int	min = *std::min_element(_numbers.begin(), _numbers.end());
	int	max = *std::max_element(_numbers.begin(), _numbers.end());
	return (static_cast<unsigned int>(max) - static_cast<unsigned int>(min));
}

unsigned int	Span::size(void) const
{
	return (_numbers.size());
}

unsigned int	Span::capacity(void) const
{
	return (_maxSize);
}

const char	*Span::FullException::what(void) const throw()
{
	return ("Span: no space left");
}

const char	*Span::NoSpanException::what(void) const throw()
{
	return ("Span: not enough numbers to find a span");
}
