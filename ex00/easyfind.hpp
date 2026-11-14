#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <stdexcept>

// T bir int container'i olmali (vector, list, deque...).
// Bulursa ilk eslesmenin iterator'unu doner, bulamazsa exception atar.
template <typename T>
typename T::iterator		easyfind(T &container, int value);

template <typename T>
typename T::const_iterator	easyfind(T const &container, int value);

# include "easyfind.tpp"

#endif
