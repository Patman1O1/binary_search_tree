#include <iostream>
#include <vector>
#include <set>
#include <concepts>
#include <cstring>
#include <forward_list>
#include <list>

#include "binary_search_tree.hpp"


using value_type = int;
using allocator_type = std::allocator<value_type>;

constexpr std::initializer_list<value_type> balanced = {100, 20, 10, 30, 200, 150, 300};
constexpr std::initializer_list<value_type> left_linked_list = {5, 4, 3, 2, 1};
constexpr std::initializer_list<value_type> right_linked_list = {1, 2, 3, 4, 5};
constexpr std::initializer_list<value_type> left_skewed = {25, 20, 10, 22, 5, 12, 1, 8, 15};
constexpr std::initializer_list<value_type> right_skewed = {25, 36, 30, 28, 40, 38, 48, 45, 50};
constexpr std::initializer_list<value_type> filled = {
    50,
    30,
    70,
    20,
    40,
    60,
    80,
    10,
    25,
    35,
    45,
    55,
    65,
    75,
    90,
    15,
    32,
    37,
    57,
    62,
    85,
    95,
    5,
    98,
    7,
	4,
	3,
	2,
	1,
	99,
	100,
	101,
	31,
	33,
	36,
	38
};
constexpr std::initializer_list<value_type> single = {101};
constexpr std::initializer_list<value_type> empty;

template<class T>
concept bst_iterator = std::same_as<T, typename adt::binary_search_tree<value_type, allocator_type>::const_iterator> ||
					   std::same_as<T, typename adt::binary_search_tree<value_type, allocator_type>::iterator> ||
					   std::same_as<T, typename adt::binary_search_tree<value_type, allocator_type>::const_reverse_iterator> ||
					   std::same_as<T, typename adt::binary_search_tree<value_type, allocator_type>::reverse_iterator>;

template<class T>
concept set_iterator = std::same_as<T, typename std::set<value_type, allocator_type>::const_iterator> ||
					   std::same_as<T, typename std::set<value_type, allocator_type>::iterator> ||
					   std::same_as<T, typename std::set<value_type, allocator_type>::const_reverse_iterator> ||
					   std::same_as<T, typename std::set<value_type, allocator_type>::reverse_iterator>;

template<std::input_iterator Iterator>
std::ostream& operator<<(std::ostream& os, std::pair<Iterator, Iterator> range);

int set(int argc, char** argv, const std::initializer_list<value_type>& values);

int binary_search_tree(int argc, char** argv, const std::initializer_list<value_type>& values);

constexpr std::vector<std::vector<value_type>> create_matchers(const std::initializer_list<value_type>& values) noexcept;

int main(int argc, char* argv[]) {
	const std::initializer_list<value_type>& values = filled;

	if (argc > 1) {
		if (argv[1][0] == 'b') {
			return binary_search_tree(argc, argv, values);
		} else if (argv[1][0] == 's') {
			return set(argc, argv, values);
		}
	}

	char choice;
	std::cout << "Options\nb = bst\ns = set\nEnter choice: ";
	std::cin >> choice;
	std::cout << '\n';

	if (choice == 'b') {
		return binary_search_tree(argc, argv, values);
	} else if (choice == 's') {
		return set(argc, argv, values);
	} else {
		std::cout << "Invalid option: " << choice << "\nTerminating\n";
		return 1;
	}
}

template<std::input_iterator Iterator>
std::ostream& operator<<(std::ostream& os, std::pair<Iterator, Iterator> range) {
	if (std::distance(range.first, range.second) <= 0) {
		os << "{}";
		return os;
	}

	os << "{ ";
	for (Iterator it = range.first; it != range.second; it++) {
		os << *it << ", ";
	}
	os << '}';

	return os;
}

int set(int argc, char** argv, const std::initializer_list<value_type>& values) {
	try {
		std::set<value_type> set = values;
		std::pair<std::set<value_type>::iterator, std::set<value_type>::iterator> pair;

		pair = set.equal_range(-1);

		std::cout << "First: " << *pair.first << "\nSecond: " << *pair.second << std::endl;

		return 0;
	} catch (std::runtime_error e) {
		std::cout << e.what() << "\nTerminating...\n";
		return 1;
	} catch (std::invalid_argument e) {
		std::cout << e.what() << "\nTerminating...\n";
		return 1; 
	} catch (...) {
		std::cout << "Unknown error encountered\nTerminating...\n";
		return 1;
	}
}

int binary_search_tree(int argc, char** argv, const std::initializer_list<value_type>& values) {
	try {
		adt::binary_search_tree<value_type> bst = values;
		adt::binary_search_tree<value_type>::iterator bst_it;
		std::list<value_type> values_matcher(values.begin(), values.end());
		std::size_t size_matcher = values.size();

		std::cout << std::make_pair(bst.begin(), bst.end()) << std::endl;

		return 0;
	} catch (std::runtime_error e) {
		std::cout << e.what() << "\nTerminating...\n";
		return 1;
	} catch (std::invalid_argument e) {
		std::cout << e.what() << "\nTerminating...\n";
		return 1; 
	} catch (...) {
		std::cout << "Unknown error encountered\nTerminating...\n";
		return 1;
	}
}

constexpr std::vector<std::vector<value_type>> create_matchers(const std::initializer_list<value_type>& values) noexcept {
	std::vector<std::vector<value_type>> matchers;
	std::size_t matchers_size = values.size() - 1;

    matchers.reserve(matchers_size);
    for (std::size_t i = 0; i < matchers_size; i++) {
        matchers.emplace_back(values.begin() + i, values.end());
    }

	return matchers;
}
