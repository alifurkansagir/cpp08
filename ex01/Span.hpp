#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <stdexcept>
# include <iterator>

class Span
{
	private:
		unsigned int		_maxSize;
		std::vector<int>	_numbers;

		Span(void);

	public:
		Span(unsigned int n);
		Span(Span const &other);
		Span	&operator=(Span const &other);
		~Span(void);

		void			addNumber(int number);
		long			shortestSpan(void) const;
		long			longestSpan(void) const;
		unsigned int	size(void) const;
		unsigned int	capacity(void) const;

		// Iterator araligiyla tek seferde ekleme (member function template).
		template <typename Iterator>
		void	addRange(Iterator begin, Iterator end)
		{
			unsigned long	count = std::distance(begin, end);

			if (_numbers.size() + count > _maxSize)
				throw FullException();
			_numbers.insert(_numbers.end(), begin, end);
		}

		class FullException : public std::exception
		{
			public:
				virtual const char	*what(void) const throw();
		};

		class NoSpanException : public std::exception
		{
			public:
				virtual const char	*what(void) const throw();
		};
};

#endif
