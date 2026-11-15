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
		unsigned int	shortestSpan(void) const;
		unsigned int	longestSpan(void) const;
		unsigned int	size(void) const;
		unsigned int	capacity(void) const;

		// Iterator araligiyla tek seferde ekleme (member function template).
		template <typename Iterator>
		void	addRange(Iterator begin, Iterator end)
		{
			// Stage one pass: input iterators cannot be traversed twice.
			std::vector<int> pending;
			std::vector<int>::size_type remaining = _maxSize - _numbers.size();
			for (; begin != end; ++begin)
			{
				if (pending.size() == remaining)
					throw FullException();
				pending.push_back(*begin);
			}
			_numbers.insert(_numbers.end(), pending.begin(), pending.end());
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
