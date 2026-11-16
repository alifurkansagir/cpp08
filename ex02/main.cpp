#include <iostream>
#include <cassert>
#include <algorithm>
#include <list>
#include <vector>
#include <string>
#include "MutantStack.hpp"

static void	subjectMutantStack(void)
{
	MutantStack<int>	mstack;

	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	MutantStack<int>::iterator	it = mstack.begin();
	MutantStack<int>::iterator	ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int>	s(mstack);
	std::cout << "std::stack copy top: " << s.top() << ", size: " << s.size() << std::endl;
}

// Ayni test std::list ile: cikti birebir ayni olmali.
static void	subjectList(void)
{
	std::list<int>	lst;

	lst.push_back(5);
	lst.push_back(17);
	std::cout << lst.back() << std::endl;
	lst.pop_back();
	std::cout << lst.size() << std::endl;
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	std::list<int>::iterator	it = lst.begin();
	std::list<int>::iterator	ite = lst.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::list<int>	s(lst);
	std::cout << "std::stack copy top: " << s.back() << ", size: " << s.size() << std::endl;
}

static void	extraTests(void)
{
	MutantStack<std::string>	strs;
	strs.push("first");
	strs.push("second");
	strs.push("third");

	std::cout << "reverse (top -> bottom): ";
	for (MutantStack<std::string>::reverse_iterator it = strs.rbegin(); it != strs.rend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	// Iterator ile degistirme
	for (MutantStack<std::string>::iterator it = strs.begin(); it != strs.end(); ++it)
		*it += "!";

	// Kopya + const iterator
	MutantStack<std::string> const	copy(strs);
	strs.push("fourth");
	std::cout << "const copy: ";
	for (MutantStack<std::string>::const_iterator it = copy.begin(); it != copy.end(); ++it)
		std::cout << *it << " ";
	std::cout << "(size " << copy.size() << ", original size " << strs.size() << ")" << std::endl;

	// Assignment
	MutantStack<std::string>	assigned;
	assigned = strs;
	std::cout << "assigned top: " << assigned.top() << std::endl;

	// Farkli underlying container
	MutantStack<int, std::vector<int> >	vstack;
	for (int i = 0; i < 5; i++)
		vstack.push(i * 10);
	std::cout << "vector-based: ";
	for (MutantStack<int, std::vector<int> >::iterator it = vstack.begin(); it != vstack.end(); ++it)
		std::cout << *it << " ";
	std::cout << "| empty: " << (vstack.empty() ? "yes" : "no") << std::endl;
}

static void	regressionTests(void)
{
	MutantStack<int> stack;
	assert(stack.empty() && stack.begin() == stack.end());
	assert(stack.rbegin() == stack.rend());
	std::list<int> reference;
	for (int i = 0; i < 20; ++i)
	{
		stack.push(i - 10);
		reference.push_back(i - 10);
	}
	assert(std::equal(stack.begin(), stack.end(), reference.begin()));
	MutantStack<int> const copy(stack);
	assert(std::equal(copy.rbegin(), copy.rend(), reference.rbegin()));
	assert(std::equal(copy.begin(), copy.end(), reference.begin()));
	*stack.begin() = 500;
	assert(*copy.begin() == -10);
	MutantStack<int> assigned;
	assigned = stack;
	stack.pop();
	assert(assigned.size() == 20 && assigned.top() == 9);
	std::stack<int> base(assigned);
	assert(base.top() == assigned.top() && base.size() == assigned.size());
	while (!assigned.empty())
		assigned.pop();
	assert(assigned.begin() == assigned.end());
	assert(assigned.rbegin() == assigned.rend());
	MutantStack<int, std::list<int> > listStack;
	listStack.push(7);
	assert(*listStack.begin() == 7 && listStack.top() == 7);
	std::cout << "MutantStack regression tests passed" << std::endl;
}

int	main(void)
{
	regressionTests();
	std::cout << "=== MutantStack ===" << std::endl;
	subjectMutantStack();
	std::cout << "=== std::list ===" << std::endl;
	subjectList();
	std::cout << "=== extra ===" << std::endl;
	extraTests();
	return (0);
}
