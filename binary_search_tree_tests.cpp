#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <cstring>
#include <vector>
#include <forward_list>
#include <list>

#include "binary_search_tree.hpp"

/* --------------------------------------------Definitions--------------------------------------------------- */
using value_type = int;

using size_type = std::size_t;

using difference_type = std::ptrdiff_t;

using allocator_type = std::allocator<value_type>;

using reference = value_type&;

using const_reference = const value_type&;

using pointer = std::allocator_traits<allocator_type>::pointer;

using const_pointer = std::allocator_traits<allocator_type>::const_pointer;

using binary_search_tree = adt::binary_search_tree<value_type, allocator_type>;

using iterator = binary_search_tree::iterator;

using reverse_iterator = binary_search_tree::reverse_iterator;

using const_iterator = binary_search_tree::const_iterator;

using const_reverse_iterator = binary_search_tree::const_reverse_iterator;

using node_type = binary_search_tree::node_type;

/* ---------------------------------------------Functions---------------------------------------------------- */


/* ---------------------------------------------Variables---------------------------------------------------- */
constexpr std::initializer_list<value_type> single_init = {101};

constexpr std::initializer_list<value_type> filled_init = {
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

constexpr std::initializer_list<value_type> empty_init = {};

constexpr size_type filled_size = filled_init.size();

constexpr std::array<value_type, filled_size> filled_preorder_matcher = {
	50,
	30,
	20,
	10,
	5,
	4,
	3,
	2,
	1,
	7,
	15,
	25,
	40,
	35, 
	32, 
	31, 
	33, 
	37, 
	36, 
	38, 
	45, 
	70, 
	60, 
	55, 
	57, 
	65, 
	62, 
	80, 
	75, 
	90, 
	85, 
	95, 
	98, 
	99, 
	100,
	101
};

constexpr std::array<value_type, filled_size> filled_inorder_matcher = {
	1, 
	2, 
	3, 
	4, 
	5, 
	7, 
	10, 
	15, 
	20, 
	25, 
	30, 
	31, 
	32, 
	33, 
	35, 
	36, 
	37, 
	38, 
	40, 
	45, 
	50, 
	55, 
	57, 
	60, 
	62, 
	65, 
	70, 
	75, 
	80, 
	85, 
	90, 
	95, 
	98, 
	99, 
	100, 
	101
};

constexpr std::array<value_type, filled_size> filled_postorder_matcher = {
	1, 
	2, 
	3, 
	4, 
	7, 
	5, 
	15, 
	10, 
	25, 
	20, 
	31, 
	33, 
	32, 
	36, 
	38, 
	37, 
	35, 
	45, 
	40, 
	30, 
	57, 
	55, 
	62, 
	65, 
	60, 
	75, 
	85, 
	101, 
	100, 
	99, 
	98, 
	95, 
	90, 
	80, 
	70, 
	50
};

constexpr std::array<value_type, 0> empty_matcher = {};

constexpr value_type insertion_value = 0;

constexpr size_type insertion_size = filled_size + 1;

binary_search_tree bst_single = single_init;

binary_search_tree bst_filled = filled_init;

binary_search_tree bst_empty = empty_init;

const_iterator bst_cit;

iterator bst_it;

const_reverse_iterator bst_crit;

reverse_iterator bst_rit;

/* --------------------------------Constant Iterator Constructors Tests-------------------------------------- */
TEST(binary_search_tree__const_iterator__constructors, default_constructor) {
	adt::binary_search_tree<int>::const_iterator cit;
	
	EXPECT_EQ(cit.get_traversal(), adt::bst_traversals::inorder);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__constructors, nullptr_constructor) {
	adt::binary_search_tree<int>::const_iterator cit(nullptr);

	EXPECT_EQ(cit.get_traversal(), adt::bst_traversals::inorder);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__constructors, bst_constructor) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_EQ(cit.get_traversal(), adt::bst_traversals::inorder);

	EXPECT_NE(cit, nullptr);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);
	EXPECT_NO_THROW(cit++);

	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__constructors, traversal_constructor__preorder) {
	adt::binary_search_tree<int>::const_iterator cit(adt::bst_traversals::preorder);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
	EXPECT_EQ(cit.get_traversal(), adt::bst_traversals::preorder);
}

TEST(binary_search_tree__const_iterator__constructors, traversal_constructor__inorder) {
	adt::binary_search_tree<int>::const_iterator cit(adt::bst_traversals::inorder);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
	EXPECT_EQ(cit.get_traversal(), adt::bst_traversals::inorder);
}

TEST(binary_search_tree__const_iterator__constructors, traversal_constructor__postorder) {
	adt::binary_search_tree<int>::const_iterator cit(adt::bst_traversals::postorder);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
	EXPECT_EQ(cit.get_traversal(), adt::bst_traversals::postorder);
}

TEST(binary_search_tree__const_iterator__constructors, bst_and_traversal_constructor__preorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);

	EXPECT_NE(cit, nullptr);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 100);

	EXPECT_EQ(cit.get_traversal(), adt::bst_traversals::preorder);
}

TEST(binary_search_tree__const_iterator__constructors, bst_and_traversal_constructor__inorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);

	EXPECT_NE(cit, nullptr);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 10);

	EXPECT_EQ(cit.get_traversal(), adt::bst_traversals::inorder);
}

TEST(binary_search_tree__const_iterator__constructors, bst_and_traversal_constructor__postorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);

	EXPECT_NE(cit, nullptr);
	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 10);

	EXPECT_EQ(cit.get_traversal(), adt::bst_traversals::postorder);
}

/* -----------------------------Constant Iterator Overloaded Operators Tests--------------------------------- */
TEST(binary_search_tree__const_iterator__operators, dereference_operator__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst);

	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, dereference_operator__filled_bst) {
	adt::binary_search_tree<int> bst = {1};
	adt::binary_search_tree<int>::const_iterator cit(bst);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 1);
}

TEST(binary_search_tree__const_iterator__operators, arrow_operator__empty_bst) {
	adt::binary_search_tree<std::string> bst;
	adt::binary_search_tree<std::string>::const_iterator cit(bst);

	EXPECT_THROW(static_cast<void>(cit->c_str()), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, arrow_operator__filled_bst) {
	adt::binary_search_tree<std::string> bst = {std::string("hello world")};
	adt::binary_search_tree<std::string>::const_iterator cit(bst);
	const char* value;

	EXPECT_NO_THROW(value = cit->c_str());
	EXPECT_EQ(std::strncmp(value, "hello world", std::strlen(value)), 0);
}

TEST(binary_search_tree__const_iterator__operators, increment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);
	
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, increment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);
	
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, increment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);
	
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, increment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit++);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, increment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit++);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, increment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit++);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, increment_operator__preorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::preorder);
	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_cit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit++);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, increment_operator__inorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::inorder);
	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_cit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit++);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, increment_operator__postorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::postorder);
	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_cit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit++);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit++, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(static_cast<void>(cit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(static_cast<void>(cit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(static_cast<void>(cit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(cit + 0), 101);

	EXPECT_NO_THROW(cit = cit + 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(cit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(cit + 0), 101);

	EXPECT_NO_THROW(cit = cit + 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(cit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(cit + 0), 101);

	EXPECT_NO_THROW(cit = cit + 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(cit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_operator__preorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::preorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_cit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit = bst_cit + 1);
	};

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_cit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_operator__inorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::inorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_cit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit = bst_cit + 1);
	};

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_cit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_operator__postorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::postorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_cit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit = bst_cit + 1);
	};

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_cit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_assignment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(cit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_assignment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(cit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_assignment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(cit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_assignment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_NO_THROW(cit += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit += 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_assignment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_NO_THROW(cit += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit += 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_assignment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_NO_THROW(cit += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit += 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_assignment_operator__preorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::preorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_cit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit += 1);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_assignment_operator__inorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::inorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_cit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit += 1);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, addition_assignment_operator__postorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::postorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_cit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit += 1);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, decrement_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);
	
	EXPECT_THROW(cit--, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, decrement_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);
	
	EXPECT_THROW(cit--, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, decrement_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);
	
	EXPECT_THROW(cit--, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, decrement_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit--);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit--, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, decrement_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit--);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit--, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, decrement_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit--);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit--, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, decrement_operator__preorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_cit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit--);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit--, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, decrement_operator__inorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::inorder) + (filled_size - 1);
	
	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_cit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit--);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit--, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, decrement_operator__postorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::postorder) + (filled_size - 1);
	
	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_cit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit--);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit--, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(static_cast<void>(cit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(static_cast<void>(cit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(static_cast<void>(cit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(cit - 0), 101);

	EXPECT_NO_THROW(cit = cit - 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(cit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(cit - 0), 101);

	EXPECT_NO_THROW(cit = cit - 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(cit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(cit - 0), 101);

	EXPECT_NO_THROW(cit = cit - 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(cit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_operator__preorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_cit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit = bst_cit - 1);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_cit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_operator__inorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::inorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_cit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit = bst_cit - 1);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_cit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_operator__postorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::postorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_cit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit = bst_cit - 1);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_cit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_assignment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(cit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_assignment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(cit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_assignment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(cit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_assignment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_NO_THROW(cit -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit += 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_assignment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_NO_THROW(cit -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit -= 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_assignment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *cit);
	EXPECT_NO_THROW(cit -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(cit -= 1);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_assignment_operator__preorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_cit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit -= 1);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_assignment_operator__inorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::inorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_cit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit -= 1);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_iterator__operators, subtraction_assignment_operator__postorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::postorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_cit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_cit -= 1);
	}

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
	EXPECT_THROW(bst_cit -= 1, std::runtime_error);
}

/* --------------------------------------Iterator Constructors Tests----------------------------------------- */
TEST(binary_search_tree__iterator__constructors, default_constructor) {
	adt::binary_search_tree<int>::iterator it;

	EXPECT_EQ(it.get_traversal(), adt::bst_traversals::inorder);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__constructors, nullptr_constructor) {
	adt::binary_search_tree<int>::iterator it(nullptr);

	EXPECT_EQ(it.get_traversal(), adt::bst_traversals::inorder);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__constructors, bst_constructor) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_EQ(it.get_traversal(), adt::bst_traversals::inorder);

	EXPECT_NE(it, nullptr);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);
	EXPECT_NO_THROW(it++);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__constructors, traversal_constructor__preorder) {
	adt::binary_search_tree<int>::iterator it(adt::bst_traversals::preorder);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
	EXPECT_EQ(it.get_traversal(), adt::bst_traversals::preorder);
}

TEST(binary_search_tree__iterator__constructors, traversal_constructor__inorder) {
	adt::binary_search_tree<int>::iterator it(adt::bst_traversals::inorder);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
	EXPECT_EQ(it.get_traversal(), adt::bst_traversals::inorder);
}

TEST(binary_search_tree__iterator__constructors, traversal_constructor__postorder) {
	adt::binary_search_tree<int>::iterator it(adt::bst_traversals::postorder);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
	EXPECT_EQ(it.get_traversal(), adt::bst_traversals::postorder);
}

TEST(binary_search_tree__iterator__constructors, bst_and_traversal_constructor__preorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);

	EXPECT_NE(it, nullptr);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 100);

	EXPECT_EQ(it.get_traversal(), adt::bst_traversals::preorder);
}

TEST(binary_search_tree__iterator__constructors, bst_and_traversal_constructor__inorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);

	EXPECT_NE(it, nullptr);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 10);

	EXPECT_EQ(it.get_traversal(), adt::bst_traversals::inorder);
}

TEST(binary_search_tree__iterator__constructors, bst_and_traversal_constructor__postorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);

	EXPECT_NE(it, nullptr);
	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 10);

	EXPECT_EQ(it.get_traversal(), adt::bst_traversals::postorder);
}

/* ----------------------------------Iterator Overloaded Operators Tests------------------------------------- */
TEST(binary_search_tree__iterator__operators, dereference_operator__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst);

	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, dereference_operator__filled_bst) {
	adt::binary_search_tree<int> bst = {1};
	adt::binary_search_tree<int>::iterator it(bst);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 1);
}

TEST(binary_search_tree__iterator__operators, arrow_operator__empty_bst) {
	adt::binary_search_tree<std::string> bst;
	adt::binary_search_tree<std::string>::iterator it(bst);

	EXPECT_THROW(static_cast<void>(it->c_str()), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, arrow_operator__filled_bst) {
	adt::binary_search_tree<std::string> bst = {std::string("hello world")};
	adt::binary_search_tree<std::string>::iterator it(bst);
	const char* value;

	EXPECT_NO_THROW(value = it->c_str());
	EXPECT_EQ(std::strncmp(value, "hello world", std::strlen(value)), 0);
}

TEST(binary_search_tree__iterator__operators, increment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);
	
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, increment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);
	
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, increment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);
	
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, increment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it++);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, increment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it++);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, increment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it++);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, increment_operator__preorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::preorder);
	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_it, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_it++);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, increment_operator__inorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::inorder);
	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_it, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_it++);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, increment_operator__postorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::postorder);
	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_it, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_it++);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it++, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(static_cast<void>(it + 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(static_cast<void>(it + 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(static_cast<void>(it + 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(it + 0), 101);

	EXPECT_NO_THROW(it = it + 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(it + 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(it + 0), 101);

	EXPECT_NO_THROW(it = it + 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(it + 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(it + 0), 101);

	EXPECT_NO_THROW(it = it + 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(it + 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_operator__preorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::preorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_it, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_it = bst_it + 1);
	};

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_it + 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_operator__inorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::inorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_it, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_it = bst_it + 1);
	};

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_it + 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_operator__postorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::postorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_it, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_it = bst_it + 1);
	};

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_it + 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_assignment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(it += 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_assignment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(it += 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_assignment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(it += 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_assignment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_NO_THROW(it += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it += 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it += 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_assignment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_NO_THROW(it += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it += 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it += 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_assignment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_NO_THROW(it += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it += 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it += 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_assignment_operator__preorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::preorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_it, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_it += 1);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it += 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_assignment_operator__inorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::inorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_it, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_it += 1);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it += 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, addition_assignment_operator__postorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::postorder);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_it, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_it += 1);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it += 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, decrement_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);
	
	EXPECT_THROW(it--, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, decrement_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);
	
	EXPECT_THROW(it--, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, decrement_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);
	
	EXPECT_THROW(it--, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, decrement_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it--);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it--, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, decrement_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it--);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it--, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, decrement_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it--);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it--, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, decrement_operator__preorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_it, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_it--);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it--, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, decrement_operator__inorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::inorder) + (filled_size - 1);
	
	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_it, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_it--);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it--, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, decrement_operator__postorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::postorder) + (filled_size - 1);
	
	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_it, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_it--);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it--, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(static_cast<void>(it - 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(static_cast<void>(it - 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(static_cast<void>(it - 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(it - 0), 101);

	EXPECT_NO_THROW(it = it - 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(it - 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(it - 0), 101);

	EXPECT_NO_THROW(it = it - 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(it - 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(it - 0), 101);

	EXPECT_NO_THROW(it = it - 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(it - 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_operator__preorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_it, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_it = bst_it - 1);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_it - 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_operator__inorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::inorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_it, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_it = bst_it - 1);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_it - 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_operator__postorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::postorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_it, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_it = bst_it - 1);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_it - 1), std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_assignment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(it -= 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_assignment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(it -= 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_assignment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(it -= 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_assignment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_NO_THROW(it -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it += 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it -= 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_assignment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_NO_THROW(it -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it -= 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it -= 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_assignment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *it);
	EXPECT_NO_THROW(it -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(it -= 1);
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
	EXPECT_THROW(it -= 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_assignment_operator__preorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_it, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_it -= 1);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it -= 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_assignment_operator__inorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::inorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_it, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_it -= 1);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it -= 1, std::runtime_error);
}

TEST(binary_search_tree__iterator__operators, subtraction_assignment_operator__postorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::postorder) + (filled_size - 1);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_it, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_it -= 1);
	}

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
	EXPECT_THROW(bst_it -= 1, std::runtime_error);
}

/* -----------------------------Constant Reverse Iterator Constructors Tests--------------------------------- */
TEST(binary_search_tree__const_reverse_iterator__constructors, default_constructor) {
	adt::binary_search_tree<int>::const_reverse_iterator crit;

	EXPECT_EQ(crit.get_traversal(), adt::bst_traversals::inorder);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__constructors, nullptr_constructor) {
	adt::binary_search_tree<int>::const_reverse_iterator crit(nullptr);

	EXPECT_EQ(crit.get_traversal(), adt::bst_traversals::inorder);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__constructors, bst_constructor) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_EQ(crit.get_traversal(), adt::bst_traversals::inorder);

	EXPECT_NE(crit, nullptr);
	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);
	EXPECT_NO_THROW(crit++);

	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__constructors, traversal_constructor__preorder) {
	adt::binary_search_tree<int>::const_reverse_iterator crit(adt::bst_traversals::preorder);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit++, std::runtime_error);
	EXPECT_EQ(crit.get_traversal(), adt::bst_traversals::preorder);
}

TEST(binary_search_tree__const_reverse_iterator__constructors, traversal_constructor__inorder) {
	adt::binary_search_tree<int>::const_reverse_iterator crit(adt::bst_traversals::inorder);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit++, std::runtime_error);
	EXPECT_EQ(crit.get_traversal(), adt::bst_traversals::inorder);
}

TEST(binary_search_tree__const_reverse_iterator__constructors, traversal_constructor__postorder) {
	adt::binary_search_tree<int>::const_reverse_iterator crit(adt::bst_traversals::postorder);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit++, std::runtime_error);
	EXPECT_EQ(crit.get_traversal(), adt::bst_traversals::postorder);
}

TEST(binary_search_tree__const_reverse_iterator__constructors, bst_and_traversal_constructor__preorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);

	EXPECT_NE(crit, nullptr);
	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 300);

	EXPECT_EQ(crit.get_traversal(), adt::bst_traversals::preorder);
}

TEST(binary_search_tree__const_reverse_iterator__constructors, bst_and_traversal_constructor__inorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);

	EXPECT_NE(crit, nullptr);
	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 300);

	EXPECT_EQ(crit.get_traversal(), adt::bst_traversals::inorder);
}

TEST(binary_search_tree__const_reverse_iterator__constructors, bst_and_traversal_constructor__postorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);

	EXPECT_NE(crit, nullptr);
	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 100);

	EXPECT_EQ(crit.get_traversal(), adt::bst_traversals::postorder);
}

/* -------------------------Constant Reverse Iterator Overloaded Operators Tests----------------------------- */
TEST(binary_search_tree__const_reverse_iterator__operators, increment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);
	
	EXPECT_THROW(crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, increment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);
	
	EXPECT_THROW(crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, increment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);
	
	EXPECT_THROW(crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, increment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit++);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, increment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit++);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, increment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit++);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, increment_operator__preorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::preorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_crit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit++);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, increment_operator__inorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::inorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_crit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit++);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, increment_operator__postorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::postorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_crit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit++);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit++, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(static_cast<void>(crit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(static_cast<void>(crit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(static_cast<void>(crit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(crit + 0), 101);

	EXPECT_NO_THROW(crit = crit + 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(crit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(crit + 0), 101);

	EXPECT_NO_THROW(crit = crit + 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(crit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(crit + 0), 101);

	EXPECT_NO_THROW(crit = crit + 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(crit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_operator__preorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::preorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_crit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit = bst_crit + 1);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_crit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_operator__inorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::inorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_crit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit = bst_crit + 1);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_crit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_operator__postorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::postorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_crit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit = bst_crit + 1);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_crit + 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_assignment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(crit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_assignment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(crit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_assignment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(crit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_assignment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_NO_THROW(crit += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit += 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_assignment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_NO_THROW(crit += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit += 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_assignment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_NO_THROW(crit += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit += 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_assignment_operator__preorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::preorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_crit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit += 1);
	};

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_assignment_operator__inorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::inorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_crit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit += 1);
	};

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, addition_assignment_operator__postorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::postorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_crit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit += 1);
	};

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit += 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, decrement_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);
	
	EXPECT_THROW(crit--, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, decrement_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);
	
	EXPECT_THROW(crit--, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, decrement_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);
	
	EXPECT_THROW(crit--, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, decrement_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit--);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit--, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, decrement_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit--);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit--, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, decrement_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit--);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit--, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, decrement_operator__preorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_crit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit--);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit--, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, decrement_operator__inorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::inorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_crit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit--);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit--, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, decrement_operator__postorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::postorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_crit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit--);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit--, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(static_cast<void>(crit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(static_cast<void>(crit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(static_cast<void>(crit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(crit - 0), 101);

	EXPECT_NO_THROW(crit = crit - 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(crit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(crit - 0), 101);

	EXPECT_NO_THROW(crit = crit - 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(crit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(crit - 0), 101);

	EXPECT_NO_THROW(crit = crit - 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(crit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_operator__preorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_crit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit = bst_crit - 1);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_crit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_operator__inorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::inorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_crit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit = bst_crit - 1);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_crit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_operator__postorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::postorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_crit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit = bst_crit - 1);
	}

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_crit - 1), std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_assignment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(crit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_assignment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(crit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_assignment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(crit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_assignment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_NO_THROW(crit -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit += 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_assignment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_NO_THROW(crit -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit -= 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_assignment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *crit);
	EXPECT_NO_THROW(crit -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(crit -= 1);
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
	EXPECT_THROW(crit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_assignment_operator__preorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_crit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit -= 1);
	};

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_assignment_operator__inorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::inorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_crit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit -= 1);
	};

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit -= 1, std::runtime_error);
}

TEST(binary_search_tree__const_reverse_iterator__operators, subtraction_assignment_operator__postorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::postorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_crit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_crit -= 1);
	};

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
	EXPECT_THROW(bst_crit -= 1, std::runtime_error);
}

/* ---------------------------------Reverse Iterator Constructors Tests-------------------------------------- */
TEST(binary_search_tree__reverse_iterator__constructors, default_constructor) {
	adt::binary_search_tree<int>::reverse_iterator rit;

	EXPECT_EQ(rit.get_traversal(), adt::bst_traversals::inorder);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__constructors, nullptr_constructor) {
	adt::binary_search_tree<int>::reverse_iterator rit(nullptr);

	EXPECT_EQ(rit.get_traversal(), adt::bst_traversals::inorder);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__constructors, bst_constructor) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_EQ(rit.get_traversal(), adt::bst_traversals::inorder);

	EXPECT_NE(rit, nullptr);
	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);
	EXPECT_NO_THROW(rit++);

	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__constructors, traversal_constructor__preorder) {
	adt::binary_search_tree<int>::reverse_iterator rit(adt::bst_traversals::preorder);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit++, std::runtime_error);
	EXPECT_EQ(rit.get_traversal(), adt::bst_traversals::preorder);
}

TEST(binary_search_tree__reverse_iterator__constructors, traversal_constructor__inorder) {
	adt::binary_search_tree<int>::reverse_iterator rit(adt::bst_traversals::inorder);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit++, std::runtime_error);
	EXPECT_EQ(rit.get_traversal(), adt::bst_traversals::inorder);
}

TEST(binary_search_tree__reverse_iterator__constructors, traversal_constructor__postorder) {
	adt::binary_search_tree<int>::reverse_iterator rit(adt::bst_traversals::postorder);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit++, std::runtime_error);
	EXPECT_EQ(rit.get_traversal(), adt::bst_traversals::postorder);
}

TEST(binary_search_tree__reverse_iterator__constructors, bst_and_traversal_constructor__preorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);

	EXPECT_NE(rit, nullptr);
	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 300);

	EXPECT_EQ(rit.get_traversal(), adt::bst_traversals::preorder);
}

TEST(binary_search_tree__reverse_iterator__constructors, bst_and_traversal_constructor__inorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);

	EXPECT_NE(rit, nullptr);
	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 300);

	EXPECT_EQ(rit.get_traversal(), adt::bst_traversals::inorder);
}

TEST(binary_search_tree__reverse_iterator__constructors, bst_and_traversal_constructor__postorder) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);

	EXPECT_NE(rit, nullptr);
	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 100);

	EXPECT_EQ(rit.get_traversal(), adt::bst_traversals::postorder);
}

/* -----------------------------Reverse Iterator Overloaded Operators Tests---------------------------------- */
TEST(binary_search_tree__reverse_iterator__operators, increment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);
	
	EXPECT_THROW(rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, increment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);
	
	EXPECT_THROW(rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, increment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);
	
	EXPECT_THROW(rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, increment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit++);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, increment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit++);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, increment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit++);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, increment_operator__preorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::preorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_rit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit++);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, increment_operator__inorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::inorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_rit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit++);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, increment_operator__postorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::postorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_rit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit++);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit++, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(static_cast<void>(rit + 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(static_cast<void>(rit + 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(static_cast<void>(rit + 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(rit + 0), 101);

	EXPECT_NO_THROW(rit = rit + 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(rit + 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(rit + 0), 101);

	EXPECT_NO_THROW(rit = rit + 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(rit + 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(rit + 0), 101);

	EXPECT_NO_THROW(rit = rit + 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(rit + 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_operator__preorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::preorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_rit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit = bst_rit + 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_rit + 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_operator__inorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::inorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_rit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit = bst_rit + 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_rit + 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_operator__postorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::postorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_rit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit = bst_rit + 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_rit + 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_assignment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(rit += 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_assignment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(rit += 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_assignment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(rit += 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_assignment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_NO_THROW(rit += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit += 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit += 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_assignment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_NO_THROW(rit += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit += 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit += 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_assignment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_NO_THROW(rit += 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit += 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit += 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_assignment_operator__preorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::preorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_rit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit += 1);
	};

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit += 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_assignment_operator__inorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::inorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_rit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit += 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit += 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, addition_assignment_operator__postorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::postorder);

	for (difference_type i = filled_size - 1; i >= 0; i--) {
		EXPECT_EQ(*bst_rit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit += 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit += 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, decrement_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);
	
	EXPECT_THROW(rit--, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, decrement_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);
	
	EXPECT_THROW(rit--, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, decrement_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);
	
	EXPECT_THROW(rit--, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, decrement_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit--);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit--, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, decrement_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit--);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit--, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, decrement_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit--);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit--, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, decrement_operator__preorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_rit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit--);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit--, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, decrement_operator__inorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::inorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_rit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit--);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit--, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, decrement_operator__postorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::postorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_rit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit--);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit--, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(static_cast<void>(rit - 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(static_cast<void>(rit - 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(static_cast<void>(rit - 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(rit - 0), 101);

	EXPECT_NO_THROW(rit = rit - 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(rit - 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(rit - 0), 101);

	EXPECT_NO_THROW(rit = rit - 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(rit - 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(*(rit - 0), 101);

	EXPECT_NO_THROW(rit = rit - 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(rit - 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_operator__preorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_rit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit = bst_rit - 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_rit - 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_operator__inorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::inorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_rit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit = bst_rit - 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_rit - 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_operator__postorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::postorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_rit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit = bst_rit - 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(static_cast<void>(bst_rit - 1), std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_assignment_operator__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);

	EXPECT_THROW(rit -= 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_assignment_operator__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);

	EXPECT_THROW(rit -= 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_assignment_operator__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);

	EXPECT_THROW(rit -= 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_assignment_operator__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::preorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_NO_THROW(rit -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit += 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit -= 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_assignment_operator__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::inorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_NO_THROW(rit -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit -= 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit -= 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_assignment_operator__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit(bst, adt::bst_traversals::postorder);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *rit);
	EXPECT_NO_THROW(rit -= 0);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(rit -= 1);
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
	EXPECT_THROW(rit -= 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_assignment_operator__preorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::preorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_rit, filled_preorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit -= 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit -= 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_assignment_operator__inorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::inorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_rit, filled_inorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit -= 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit -= 1, std::runtime_error);
}

TEST(binary_search_tree__reverse_iterator__operators, subtraction_assignment_operator__postorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::postorder) + (filled_size - 1);

	for (std::size_t i = 0; i < filled_size; i++) {
		EXPECT_EQ(*bst_rit, filled_postorder_matcher[i]);
		EXPECT_NO_THROW(bst_rit -= 1);
	}

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
	EXPECT_THROW(bst_rit -= 1, std::runtime_error);
}

/* --------------------------------------Node Type Constructors Tests---------------------------------------- */
TEST(binary_search_tree__node_type__constructors, default_constructor) {
	adt::binary_search_tree<int>::node_type node;

	EXPECT_EQ(node, nullptr);
}

TEST(binary_search_tree__node_type__constructors, const_iterator_constructor__nullptr_iterator) {
	adt::binary_search_tree<int>::const_iterator pos;
	adt::binary_search_tree<int>::node_type node(pos);

	EXPECT_EQ(node, nullptr);
}

TEST(binary_search_tree__node_type__constructors, const_iterator_constructor__valid_iterator) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type node(pos);

	EXPECT_NE(node, nullptr);
}

TEST(binary_search_tree__node_type__constructors, nullptr_constructor) {
	adt::binary_search_tree<int>::node_type node(nullptr);

	EXPECT_EQ(node, nullptr);
}

TEST(binary_search_tree__node_type__constructors, copy_constructor) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type src_node(pos), dst_node(src_node);
	adt::binary_search_tree<int>::value_type src_val, dst_val;

	EXPECT_NO_THROW(src_val = *src_node);
	EXPECT_NO_THROW(dst_val = *dst_node);

	EXPECT_EQ(src_val, dst_val);
}

TEST(binary_search_tree__node_type__constructors, move_constructor__empty) {
	adt::binary_search_tree<int>::node_type src, dst = std::move(src);

	EXPECT_EQ(src, nullptr);
	EXPECT_EQ(dst, nullptr);
}

TEST(binary_search_tree__node_type__constructors, move_constructor__filled) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type src(pos);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *src);
	EXPECT_EQ(value, 101);

	adt::binary_search_tree<int>::node_type dst = std::move(src);
	
	EXPECT_EQ(src, nullptr);
	EXPECT_NO_THROW(value = *dst);
	EXPECT_EQ(value, 101);
}

/* --------------------------------------Node Type Destructor Tests----------------------------------------- */
TEST(binary_search_tree__node_type__destructor, destructor) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type node(pos);

	node.~node_type();

	EXPECT_EQ(node, nullptr);
}

/* ----------------------------------Node Type Overloaded Operators Tests------------------------------------ */
TEST(binary_search_tree__node_type__operators, assignment_operator__node_type__empty_to_empty) {
	adt::binary_search_tree<int>::node_type src, dst;

	EXPECT_NO_THROW(dst = src);
	EXPECT_EQ(src, nullptr);
	EXPECT_EQ(dst, nullptr);
}

TEST(binary_search_tree__node_type__operators, assignment_operator__node_type__empty_to_filled) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type src(pos), dst;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *src);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(dst, nullptr);

	EXPECT_NO_THROW(dst = src);

	EXPECT_NO_THROW(value = *src);
	EXPECT_EQ(value, 101);
	EXPECT_NO_THROW(value = *dst);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__node_type__operators, assignment_operator__node_type__filled_to_filled) {
	adt::binary_search_tree<int> bst = {101, 69};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type src(pos), dst(pos + 1);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *src);
	EXPECT_EQ(value, 69);
	EXPECT_NO_THROW(value = *dst);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(dst = src);

	EXPECT_NO_THROW(value = *src);
	EXPECT_EQ(value, 69);
	EXPECT_NO_THROW(value = *dst);
	EXPECT_EQ(value, 69);
}

TEST(binary_search_tree__node_type__operators, assignment_operator__node_type__filled_to_empty) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type src, dst(pos);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_EQ(src, nullptr);
	EXPECT_NO_THROW(value = *dst);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(dst = src);

	EXPECT_EQ(src, nullptr);
	EXPECT_EQ(dst, nullptr);
}

TEST(binary_search_tree__node_type__operators, assignment_operator__nullptr__empty) {
	adt::binary_search_tree<int>::node_type node;

	EXPECT_NO_THROW(node = nullptr);
	EXPECT_EQ(node, nullptr);
}

TEST(binary_search_tree__node_type__operators, assignment_operator__nullptr__filled) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type node(pos);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *node);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(node = nullptr);

	EXPECT_EQ(node, nullptr);
}

TEST(binary_search_tree__node_type__operators, move_operator__empty_to_empty) {
	adt::binary_search_tree<int>::node_type src, dst;

	EXPECT_NO_THROW(dst = std::move(src));
	EXPECT_EQ(src, nullptr);
	EXPECT_EQ(dst, nullptr);
}

TEST(binary_search_tree__node_type__operators, move_operator__empty_to_filled) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type src(pos), dst;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *src);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(dst, nullptr);

	EXPECT_NO_THROW(dst = std::move(src));

	EXPECT_EQ(src, nullptr);
	EXPECT_EQ(value, 101);
	EXPECT_NO_THROW(value = *dst);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__node_type__operators, move_operator__filled_to_filled) {
	adt::binary_search_tree<int> bst = {101, 69};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type src(pos), dst(pos + 1);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *src);
	EXPECT_EQ(value, 69);
	EXPECT_NO_THROW(value = *dst);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(dst = std::move(src));

	EXPECT_EQ(src, nullptr);
	EXPECT_NO_THROW(value = *dst);
	EXPECT_EQ(value, 69);
}

TEST(binary_search_tree__node_type__operators, move_operator__filled_to_empty) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type src, dst(pos);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_EQ(src, nullptr);
	EXPECT_NO_THROW(value = *dst);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(dst = std::move(src));

	EXPECT_EQ(src, nullptr);
	EXPECT_EQ(dst, nullptr);
}

TEST(binary_search_tree__node_type__operators, dereference_operator__nullptr) {
	adt::binary_search_tree<int>::node_type node;

	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);
}

TEST(binary_search_tree__node_type__operators, dereference_operator__valid_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type node(pos);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *node);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__node_type__operators, arrow_operator__empty) {
	adt::binary_search_tree<std::string> bst;
	adt::binary_search_tree<std::string>::iterator it(bst);

	EXPECT_THROW(static_cast<void>(it->c_str()), std::runtime_error);
}

TEST(binary_search_tree__node_type__operators, arrow_operator__filled) {
	adt::binary_search_tree<std::string> bst = {std::string("hello world")};
	adt::binary_search_tree<std::string>::const_iterator pos(bst);
	adt::binary_search_tree<std::string>::node_type node(pos);
	const char* value;

	EXPECT_NO_THROW(value = node->c_str());
	EXPECT_EQ(std::strncmp(value, "hello world", std::strlen(value)), 0);
}

TEST(binary_search_tree__node_type__operators, bool_operator__empty) {
	adt::binary_search_tree<int>::node_type node;
	EXPECT_FALSE(static_cast<bool>(node));
}

TEST(binary_search_tree__node_type__operators, bool_operator__filled) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type node(pos);
	EXPECT_TRUE(static_cast<bool>(node));
}

/* ----------------------------------------Node Type Methods Tests---------------------------------------------- */
TEST(binary_search_tree__node_type__methods, empty__empty_node) {
	adt::binary_search_tree<int>::node_type node;
	EXPECT_TRUE(node.empty());
}

TEST(binary_search_tree__node_type__methods, empty__filled_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type node(pos);
	EXPECT_FALSE(node.empty());
}

TEST(binary_search_tree__node_type__methods, value__nullptr) {
	adt::binary_search_tree<int>::node_type node;
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
}

TEST(binary_search_tree__node_type__methods, value__valid_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type node(pos);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = node.value());
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__node_type__methods, swap__nullptr_and_nullptr) {
	adt::binary_search_tree<int>::node_type node1, node2;

	EXPECT_EQ(node1, nullptr);
	EXPECT_EQ(node2, nullptr);

	EXPECT_NO_THROW(node1.swap(node2));

	EXPECT_EQ(node1, nullptr);
	EXPECT_EQ(node2, nullptr);
}

TEST(binary_search_tree__node_type__methods, swap__valid_node_and_nullptr) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type node1(pos), node2;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *node1);
	EXPECT_EQ(value, 101);
	EXPECT_EQ(node2, nullptr);

	EXPECT_NO_THROW(node1.swap(node2));

	EXPECT_EQ(node1, nullptr);
	EXPECT_NO_THROW(value = *node2);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__node_type__methods, swap__valid_node_and_valid_node) {
	adt::binary_search_tree<int> bst = {101, 69};
	adt::binary_search_tree<int>::const_iterator pos(bst);
	adt::binary_search_tree<int>::node_type node1(pos), node2(pos + 1);
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(value = *node1);
	EXPECT_EQ(value, 69);
	EXPECT_NO_THROW(value = *node2);
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(node1.swap(node2));

	EXPECT_NO_THROW(value = *node1);
	EXPECT_EQ(value, 101);
	EXPECT_NO_THROW(value = *node2);
	EXPECT_EQ(value, 69);
}

/* ----------------------------------Binary Search Tree Constructors Tests----------------------------------- */
TEST(binary_search_tree__constructors, default_constructor) {
	adt::binary_search_tree<int> bst;
	typename adt::binary_search_tree<int>::const_iterator cit = bst.cbegin();
	size_t size;

	EXPECT_NO_THROW(size = bst.size());
	EXPECT_EQ(size, 0);

	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
	EXPECT_THROW(cit++, std::runtime_error);
}

TEST(binary_search_tree__constructors, iterator_constructor__empty) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit = bst.cbegin();
	adt::binary_search_tree<int>::size_type size;

	EXPECT_NO_THROW(size = bst.size());
	EXPECT_EQ(size, 0);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__constructors, iterator_constructor__single) {
	std::initializer_list<int> matcher = {101};
	adt::binary_search_tree<int> bst(matcher.begin(), matcher.end());
	adt::binary_search_tree<int>::size_type size;

	EXPECT_NO_THROW(size = bst.size());
	EXPECT_EQ(size, 1);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__constructors, iterator_constructor__filled) {
	binary_search_tree bst(filled_init.begin(), filled_init.end());

	EXPECT_EQ(bst.size(), filled_size);
	EXPECT_EQ(bst, filled_inorder_matcher);
}

TEST(binary_search_tree__constructors, initializer_list_constructor__empty) {
	adt::binary_search_tree<int> bst = {};
	adt::binary_search_tree<int>::const_iterator cit = bst.cbegin();
	adt::binary_search_tree<int>::size_type size;

	EXPECT_NO_THROW(size = bst.size());
	EXPECT_EQ(size, 0);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__constructors, initializer_list_constructor__single) {
	std::initializer_list<int> matcher = {101};
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::size_type size;

	EXPECT_NO_THROW(size = bst.size());
	EXPECT_EQ(size, 1);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__constructors, initializer_list_constructor__filled) {
	binary_search_tree bst = filled_init;

	EXPECT_EQ(bst.size(), filled_size);
	EXPECT_EQ(bst, filled_inorder_matcher);
}

TEST(binary_search_tree__constructors, range_constructor__empty) {
	std::vector<int> vec;
	adt::binary_search_tree<int> bst(std::from_range, vec);
	adt::binary_search_tree<int>::const_iterator cit = bst.cbegin();
	adt::binary_search_tree<int>::size_type size;

	EXPECT_NO_THROW(size = bst.size());
	EXPECT_EQ(size, 0);
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__constructors, range_constructor__single) {
	std::vector<int> vec = {101};
	std::initializer_list<int> matcher = {101};
	adt::binary_search_tree<int> bst(std::from_range, vec);
	adt::binary_search_tree<int>::size_type size;

	EXPECT_NO_THROW(size = bst.size());
	EXPECT_EQ(size, 1);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__constructors, range_constructor__filled) {
	binary_search_tree bst(std::from_range, filled_init);

	EXPECT_EQ(bst.size(), filled_size);
	EXPECT_EQ(bst, filled_inorder_matcher);
}

TEST(binary_search_tree__constructors, copy_constructor__empty) {
	std::initializer_list<int> matcher = {};
	adt::binary_search_tree<int> src = {};
	adt::binary_search_tree<int> dst(src);
	adt::binary_search_tree<int>::size_type size;

	EXPECT_NO_THROW(size = dst.size());
	EXPECT_EQ(size, 0);
	EXPECT_EQ(src.size(), dst.size());

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__constructors, copy_constructor__single) {
	std::initializer_list<int> matcher = {101};
	adt::binary_search_tree<int> src = {101};
	adt::binary_search_tree<int> dst(src);
	adt::binary_search_tree<int>::size_type size;

	EXPECT_NO_THROW(size = dst.size());
	EXPECT_EQ(size, 1);
	EXPECT_EQ(src.size(), dst.size());

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__constructors, copy_constructor__filled) {
	binary_search_tree src(filled_init);
	binary_search_tree dst(src);

	EXPECT_EQ(src.size(), filled_size);
	EXPECT_EQ(dst.size(), filled_size);

	EXPECT_EQ(src, filled_inorder_matcher);
	EXPECT_EQ(dst, filled_inorder_matcher);
}

TEST(binary_search_tree__constructors, move_constructor__empty) {
	std::initializer_list<int> matcher = {};
	adt::binary_search_tree<int> src = {};
	adt::binary_search_tree<int>::size_type size;

	EXPECT_EQ(src, matcher);
	EXPECT_NO_THROW(size = src.size());
	EXPECT_EQ(size, 0);

	adt::binary_search_tree<int> dst = std::move(src);

	EXPECT_NO_THROW(size = src.size());
	EXPECT_EQ(size, 0);

	EXPECT_NO_THROW(size = dst.size());
	EXPECT_EQ(size, 0);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__constructors, move_constructor__single) {
	std::initializer_list<int> matcher = {101};
	adt::binary_search_tree<int> src = {101};
	adt::binary_search_tree<int>::size_type size;

	EXPECT_EQ(src, matcher);
	EXPECT_NO_THROW(size = src.size());
	EXPECT_EQ(size, 1);

	adt::binary_search_tree<int> dst = std::move(src);

	EXPECT_NO_THROW(size = src.size());
	EXPECT_EQ(size, 0);

	EXPECT_NO_THROW(size = dst.size());
	EXPECT_EQ(size, 1);

	EXPECT_EQ(src, std::initializer_list<int>({}));
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__constructors, move_constructor__filled) {
	binary_search_tree src = filled_init;

	EXPECT_EQ(src.size(), filled_size);
	EXPECT_EQ(src, filled_inorder_matcher);

	binary_search_tree dst = std::move(src);

	EXPECT_EQ(src.size(), 0);
	EXPECT_TRUE(src.empty());

	EXPECT_EQ(dst.size(), filled_size);
	EXPECT_EQ(dst, filled_inorder_matcher);
}

/* ----------------------------------Binary Search Tree Destructor Tests-------------------------------------- */
TEST(binary_search_tree__destructor, destructor__empty) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit;

	EXPECT_NO_THROW(bst.~binary_search_tree());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_NO_THROW(cit = bst.cbegin());
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__destructor, destructor__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit;

	EXPECT_NO_THROW(bst.~binary_search_tree());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_NO_THROW(cit = bst.cbegin());
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__destructor, destructor__filled) {
	binary_search_tree bst = filled_init;

	bst.~binary_search_tree();

	EXPECT_EQ(bst.size(), 0);
	EXPECT_TRUE(bst.empty());

	EXPECT_EQ(bst, empty_matcher);
}

/* -------------------------------Binary Search Tree Overloaded Operators Tests------------------------------ */
TEST(binary_search_tree__operators, assignment_operator__self_assignment) {
	std::initializer_list<int> matcher = {10, 20, 30, 100, 150, 200, 300};
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>& bst_ref = bst;

	bst_ref = bst;

	EXPECT_EQ(&bst_ref, &bst);

	EXPECT_EQ(bst_ref.size(), bst.size());

	EXPECT_EQ(bst, matcher);
	EXPECT_EQ(bst_ref, matcher);
}

TEST(binary_search_tree__operators, assignment_operator__empty_to_empty) {
	std::initializer_list<int> matcher = {};
	adt::binary_search_tree<int> src, dst;

	EXPECT_NE(&src, &dst);

	EXPECT_EQ(src.size(), 0);

	EXPECT_EQ(dst.size(), 0);

	EXPECT_NO_THROW(dst = src);

	EXPECT_EQ(src.size(), 0);
	EXPECT_EQ(dst.size(), 0);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__operators, assignment_operator__empty_to_filled) {
	std::initializer_list<int> matcher = {10, 20, 30, 100, 150, 200, 300};
	adt::binary_search_tree<int> src = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int> dst;

	EXPECT_NE(&src, &dst);

	EXPECT_EQ(src.size(), 7);
	EXPECT_EQ(dst.size(), 0);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, std::initializer_list<int>({}));

	EXPECT_NO_THROW(dst = src);

	EXPECT_EQ(src.size(), 7);
	EXPECT_EQ(dst.size(), 7);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__operators, assignment_operator__filled_to_filled) {
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5, 6, 7, 9};
	adt::binary_search_tree<int> src = {4, 2, 1, 3, 6, 5, 7, 0, 9};
	adt::binary_search_tree<int> dst = {100, 20, 10, 30, 200, 150, 300};

	EXPECT_NE(&src, &dst);

	EXPECT_EQ(src.size(), 9);
	EXPECT_EQ(dst.size(), 7);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, std::initializer_list<int>({10, 20, 30, 100, 150, 200, 300}));

	EXPECT_NO_THROW(dst = src);

	EXPECT_EQ(src.size(), 9);
	EXPECT_EQ(dst.size(), 9);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__operators, assignment_operator__filled_to_empty) {
	std::initializer_list<int> matcher = {};
	adt::binary_search_tree<int> src;
	adt::binary_search_tree<int> dst = {100, 20, 10, 30, 200, 150, 300};

	EXPECT_NE(&src, &dst);

	EXPECT_EQ(src.size(), 0);
	EXPECT_EQ(dst.size(), 7);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, std::initializer_list<int>({10, 20, 30, 100, 150, 200, 300}));

	EXPECT_NO_THROW(dst = src);

	EXPECT_EQ(src.size(), 0);
	EXPECT_EQ(dst.size(), 0);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__operators, move_operator__self_assignment) {
	std::initializer_list<int> matcher = {10, 20, 30, 100, 150, 200, 300};
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>& bst_ref = bst;

	bst_ref = std::move(bst);

	EXPECT_EQ(&bst_ref, &bst);

	EXPECT_EQ(bst_ref.size(), bst.size());

	EXPECT_EQ(bst, matcher);
	EXPECT_EQ(bst_ref, matcher);
}

TEST(binary_search_tree__operators, move_operator__empty_to_empty) {
	std::initializer_list<int> matcher = {};
	adt::binary_search_tree<int> src, dst;

	EXPECT_NE(&src, &dst);

	EXPECT_EQ(src.size(), 0);

	EXPECT_EQ(dst.size(), 0);

	EXPECT_NO_THROW(dst = std::move(src));

	EXPECT_EQ(src.size(), 0);
	EXPECT_EQ(dst.size(), 0);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__operators, move_operator__empty_to_filled) {
	std::initializer_list<int> matcher = {10, 20, 30, 100, 150, 200, 300};
	adt::binary_search_tree<int> src = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int> dst;

	EXPECT_NE(&src, &dst);

	EXPECT_EQ(src.size(), 7);
	EXPECT_EQ(dst.size(), 0);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, std::initializer_list<int>({}));

	EXPECT_NO_THROW(dst = std::move(src));

	EXPECT_EQ(src.size(), 0);
	EXPECT_EQ(dst.size(), 7);

	EXPECT_EQ(src, std::initializer_list<int>({}));
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__operators, move_operator__filled_to_filled) {
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5, 6, 7, 9};
	adt::binary_search_tree<int> src = {4, 2, 1, 3, 6, 5, 7, 0, 9};
	adt::binary_search_tree<int> dst = {100, 20, 10, 30, 200, 150, 300};

	EXPECT_EQ(src.size(), 9);
	EXPECT_EQ(dst.size(), 7);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, std::initializer_list<int>({10, 20, 30, 100, 150, 200, 300}));

	EXPECT_NO_THROW(dst = std::move(src));

	EXPECT_EQ(src.size(), 0);
	EXPECT_EQ(dst.size(), 9);

	EXPECT_EQ(src, std::initializer_list<int>({}));
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__operators, move_operator__filled_to_empty) {
	std::initializer_list<int> matcher = {};
	adt::binary_search_tree<int> src;
	adt::binary_search_tree<int> dst = {100, 20, 10, 30, 200, 150, 300};

	EXPECT_EQ(src.size(), 0);
	EXPECT_EQ(dst.size(), 7);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, std::initializer_list<int>({10, 20, 30, 100, 150, 200, 300}));

	EXPECT_NO_THROW(dst = src);

	EXPECT_EQ(src.size(), 0);
	EXPECT_EQ(dst.size(), 0);

	EXPECT_EQ(src, matcher);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__operators, equals_operator__bst__both_empty) {
	adt::binary_search_tree<int> lhs, rhs;

	EXPECT_NE(&lhs, &rhs);
	EXPECT_TRUE(lhs == rhs);
	EXPECT_EQ(lhs, rhs);
}

TEST(binary_search_tree__operators, equals_operator__bst__same_values) {
	adt::binary_search_tree<int> lhs = {100, 20, 30, 10, 200, 300, 150};
	adt::binary_search_tree<int> rhs = {100, 20, 10, 30, 200, 150, 300};

	EXPECT_NE(&lhs, &rhs);
	EXPECT_TRUE(lhs == rhs);
	EXPECT_EQ(lhs, rhs);
}

TEST(binary_search_tree__operators, equals_operator__bst__different_values) {
	adt::binary_search_tree<int> lhs = {25, 20, 10, 22, 5, 12, 1, 8, 15};
	adt::binary_search_tree<int> rhs = {25, 36, 30, 28, 40, 38, 48, 45, 50};

	EXPECT_NE(&lhs, &rhs);
	EXPECT_FALSE(lhs == rhs);
	EXPECT_NE(lhs, rhs);
}

TEST(binary_search_tree__operators, equals_operator__ranges__both_empty) {
	adt::binary_search_tree<int> lhs;
	std::vector<int> rhs;

	EXPECT_NE(static_cast<void*>(&lhs), static_cast<void*>(&rhs));
	EXPECT_TRUE(lhs == rhs);
	EXPECT_EQ(lhs, rhs);
}

TEST(binary_search_tree__operators, equals_operator__ranges__same_values) {
	adt::binary_search_tree<int> lhs = {100, 20, 30, 10, 200, 300, 150};
	std::vector<int> rhs = {10, 20, 30, 100, 150, 200, 300};

	EXPECT_NE(static_cast<void*>(&lhs), static_cast<void*>(&rhs));
	EXPECT_TRUE(lhs == rhs);
	EXPECT_EQ(lhs, rhs);
}

TEST(binary_search_tree__operators, equals_operator__ranges__different_values) {
	adt::binary_search_tree<int> lhs = {25, 20, 10, 22, 5, 12, 1, 8, 15};
	std::vector<int> rhs = {25, 36, 30, 28, 40, 38, 48, 45, 50};

	EXPECT_NE(static_cast<void*>(&lhs), static_cast<void*>(&rhs));
	EXPECT_FALSE(lhs == rhs);
	EXPECT_NE(lhs, rhs);
}

/* -----------------------------------Binary Search Tree Methods Tests--------------------------------------- */
TEST(binary_search_tree__methods, cbegin__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit;

	EXPECT_NO_THROW(cit = bst.cbegin(adt::bst_traversals::preorder));
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__methods, cbegin__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit;

	EXPECT_NO_THROW(cit = bst.cbegin(adt::bst_traversals::inorder));
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__methods, cbegin__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit;

	EXPECT_NO_THROW(cit = bst.cbegin(adt::bst_traversals::postorder));
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__methods, cbegin__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(cit = bst.cbegin(adt::bst_traversals::preorder));
	EXPECT_NE(cit, nullptr);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, cbegin__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(cit = bst.cbegin(adt::bst_traversals::inorder));
	EXPECT_NE(cit, nullptr);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, cbegin__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(cit = bst.cbegin(adt::bst_traversals::postorder));
	EXPECT_NE(cit, nullptr);

	EXPECT_NO_THROW(value = *cit);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, cbegin__preorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::preorder);

	EXPECT_NE(bst_cit, nullptr);
	EXPECT_EQ(*bst_cit, filled_preorder_matcher[0]);
}

TEST(binary_search_tree__methods, cbegin__inorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::inorder);

	EXPECT_NE(bst_cit, nullptr);
	EXPECT_EQ(*bst_cit, filled_inorder_matcher[0]);
}

TEST(binary_search_tree__methods, cbegin__postorder__filled_bst) {
	bst_cit = bst_filled.cbegin(adt::bst_traversals::postorder);

	EXPECT_NE(bst_cit, nullptr);
	EXPECT_EQ(*bst_cit, filled_postorder_matcher[0]);
}

TEST(binary_search_tree__methods, begin__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it;

	EXPECT_NO_THROW(it = bst.begin(adt::bst_traversals::preorder));
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, begin__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it;

	EXPECT_NO_THROW(it = bst.begin(adt::bst_traversals::inorder));
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, begin__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it;

	EXPECT_NO_THROW(it = bst.begin(adt::bst_traversals::postorder));
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, begin__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(it = bst.begin(adt::bst_traversals::preorder));
	EXPECT_NE(it, nullptr);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, begin__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(it = bst.begin(adt::bst_traversals::inorder));
	EXPECT_NE(it, nullptr);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, begin__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(it = bst.begin(adt::bst_traversals::postorder));
	EXPECT_NE(it, nullptr);

	EXPECT_NO_THROW(value = *it);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, begin__preorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::preorder);

	EXPECT_NE(bst_it, nullptr);
	EXPECT_EQ(*bst_it, filled_preorder_matcher[0]);
}

TEST(binary_search_tree__methods, begin__inorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::inorder);

	EXPECT_NE(bst_it, nullptr);
	EXPECT_EQ(*bst_it, filled_inorder_matcher[0]);
}

TEST(binary_search_tree__methods, begin__postorder__filled_bst) {
	bst_it = bst_filled.begin(adt::bst_traversals::postorder);

	EXPECT_NE(bst_it, nullptr);
	EXPECT_EQ(*bst_it, filled_postorder_matcher[0]);
}

TEST(binary_search_tree__methods, crbegin__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit;

	EXPECT_NO_THROW(crit = bst.crbegin(adt::bst_traversals::preorder));
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
}

TEST(binary_search_tree__methods, crbegin__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit;

	EXPECT_NO_THROW(crit = bst.crbegin(adt::bst_traversals::inorder));
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
}

TEST(binary_search_tree__methods, crbegin__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit;

	EXPECT_NO_THROW(crit = bst.crbegin(adt::bst_traversals::postorder));
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
}

TEST(binary_search_tree__methods, crbegin__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(crit = bst.crbegin(adt::bst_traversals::preorder));
	EXPECT_NE(crit, nullptr);

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, crbegin__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(crit = bst.crbegin(adt::bst_traversals::inorder));
	EXPECT_NE(crit, nullptr);

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, crbegin__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(crit = bst.crbegin(adt::bst_traversals::postorder));
	EXPECT_NE(crit, nullptr);

	EXPECT_NO_THROW(value = *crit);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, crbegin__preorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::preorder);

	EXPECT_NE(bst_crit, nullptr);
	EXPECT_EQ(*bst_crit, filled_preorder_matcher[filled_size - 1]);
}

TEST(binary_search_tree__methods, crbegin__inorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::inorder);

	EXPECT_NE(bst_crit, nullptr);
	EXPECT_EQ(*bst_crit, filled_inorder_matcher[filled_size - 1]);
}

TEST(binary_search_tree__methods, crbegin__postorder__filled_bst) {
	bst_crit = bst_filled.crbegin(adt::bst_traversals::postorder);

	EXPECT_NE(bst_crit, nullptr);
	EXPECT_EQ(*bst_crit, filled_postorder_matcher[filled_size - 1]);
}

TEST(binary_search_tree__methods, rbegin__preorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit;

	EXPECT_NO_THROW(rit = bst.rbegin(adt::bst_traversals::preorder));
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
}

TEST(binary_search_tree__methods, rbegin__inorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit;

	EXPECT_NO_THROW(rit = bst.rbegin(adt::bst_traversals::inorder));
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
}

TEST(binary_search_tree__methods, rbegin__postorder__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit;

	EXPECT_NO_THROW(rit = bst.rbegin(adt::bst_traversals::postorder));
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
}

TEST(binary_search_tree__methods, rbegin__preorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(rit = bst.rbegin(adt::bst_traversals::preorder));
	EXPECT_NE(rit, nullptr);

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, rbegin__inorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(rit = bst.rbegin(adt::bst_traversals::inorder));
	EXPECT_NE(rit, nullptr);

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, rbegin__postorder__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit;
	adt::binary_search_tree<int>::value_type value;

	EXPECT_NO_THROW(rit = bst.rbegin(adt::bst_traversals::postorder));
	EXPECT_NE(rit, nullptr);

	EXPECT_NO_THROW(value = *rit);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, rbegin__preorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::preorder);

	EXPECT_NE(bst_rit, nullptr);
	EXPECT_EQ(*bst_rit, filled_preorder_matcher[filled_size - 1]);
}

TEST(binary_search_tree__methods, rbegin__inorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::inorder);

	EXPECT_NE(bst_rit, nullptr);
	EXPECT_EQ(*bst_rit, filled_inorder_matcher[filled_size - 1]);
}

TEST(binary_search_tree__methods, rbegin__postorder__filled_bst) {
	bst_rit = bst_filled.rbegin(adt::bst_traversals::postorder);

	EXPECT_NE(bst_rit, nullptr);
	EXPECT_EQ(*bst_rit, filled_postorder_matcher[filled_size - 1]);
}

TEST(binary_search_tree__methods, cend__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit;

	EXPECT_NO_THROW(cit = bst.cend());
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__methods, cend__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit;

	EXPECT_NO_THROW(cit = bst.cend());
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__methods, cend__filled_bst) {
	bst_cit = bst_filled.cend();

	EXPECT_EQ(bst_cit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_cit), std::runtime_error);
}

TEST(binary_search_tree__methods, end__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it;

	EXPECT_NO_THROW(it = bst.end());
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, end__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it;

	EXPECT_NO_THROW(it = bst.end());
	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, end__filled_bst) {
	bst_it = bst_filled.end();

	EXPECT_EQ(bst_it, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_it), std::runtime_error);
}

TEST(binary_search_tree__methods, crend__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reverse_iterator crit;

	EXPECT_NO_THROW(crit = bst.crend());
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
}

TEST(binary_search_tree__methods, crend__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reverse_iterator crit;
	
	EXPECT_NO_THROW(crit = bst.crend());
	EXPECT_EQ(crit, nullptr);
	EXPECT_THROW(static_cast<void>(*crit), std::runtime_error);
}

TEST(binary_search_tree__methods, crend__filled_bst) {
	bst_crit = bst_filled.crend();

	EXPECT_EQ(bst_crit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_crit), std::runtime_error);
}

TEST(binary_search_tree__methods, rend__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::reverse_iterator rit;

	EXPECT_NO_THROW(rit = bst.rend());
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
}

TEST(binary_search_tree__methods, rend__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::reverse_iterator rit;

	EXPECT_NO_THROW(rit = bst.rend());
	EXPECT_EQ(rit, nullptr);
	EXPECT_THROW(static_cast<void>(*rit), std::runtime_error);
}

TEST(binary_search_tree__methods, rend__filled_bst) {
	bst_rit = bst_filled.rend();

	EXPECT_EQ(bst_rit, nullptr);
	EXPECT_THROW(static_cast<void>(*bst_rit), std::runtime_error);
}

TEST(binary_search_tree__methods, get_root__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::node_type root = bst.get_root();

	EXPECT_TRUE(root.empty());
	EXPECT_EQ(root, nullptr);
	
	EXPECT_THROW(static_cast<void>(root.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*root), std::runtime_error);
}

TEST(binary_search_tree__methods, get_root__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::node_type root = bst.get_root();
	adt::binary_search_tree<int>::value_type value;

	EXPECT_FALSE(root.empty());
	EXPECT_NE(root, nullptr);
	
	EXPECT_NO_THROW(value = root.value());
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(value = *root);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, get_root__filled_bst) {
	node_type root = bst_filled.get_root();

	EXPECT_NE(root, nullptr);
	EXPECT_FALSE(root.empty());

	EXPECT_EQ(*root, filled_preorder_matcher[0]);
	EXPECT_EQ(root.value(), filled_preorder_matcher[0]);
}

TEST(binary_search_tree__methods, get_min__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::node_type min = bst.get_min();

	EXPECT_TRUE(min.empty());
	EXPECT_EQ(min, nullptr);

	EXPECT_THROW(static_cast<void>(min.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*min), std::runtime_error);
}

TEST(binary_search_tree__methods, get_min__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::node_type min = bst.get_min();
	adt::binary_search_tree<int>::value_type value;

	EXPECT_FALSE(min.empty());
	EXPECT_NE(min, nullptr);
	
	EXPECT_NO_THROW(value = min.value());
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(value = *min);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, get_min__filled_bst) {
	node_type min = bst_filled.get_min();

	EXPECT_NE(min, nullptr);
	EXPECT_FALSE(min.empty());

	EXPECT_EQ(*min, filled_inorder_matcher[0]);
	EXPECT_EQ(min.value(), filled_inorder_matcher[0]);
}

TEST(binary_search_tree__methods, get_max__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::node_type max = bst.get_max();

	EXPECT_TRUE(max.empty());
	EXPECT_EQ(max, nullptr);

	EXPECT_THROW(static_cast<void>(max.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*max), std::runtime_error);
}

TEST(binary_search_tree__methods, get_max__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::node_type max = bst.get_max();
	adt::binary_search_tree<int>::value_type value;

	EXPECT_FALSE(max.empty());
	EXPECT_NE(max, nullptr);
	
	EXPECT_NO_THROW(value = max.value());
	EXPECT_EQ(value, 101);

	EXPECT_NO_THROW(value = *max);
	EXPECT_EQ(value, 101);
}

TEST(binary_search_tree__methods, get_max__filled_bst) {
	node_type max = bst_filled.get_max();

	EXPECT_NE(max, nullptr);
	EXPECT_FALSE(max.empty());

	EXPECT_EQ(*max, filled_inorder_matcher[filled_size - 1]);
	EXPECT_EQ(max.value(), filled_inorder_matcher[filled_size - 1]);
}

TEST(binary_search_tree__methods, clear__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_iterator cit;

	bst.clear();

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_NO_THROW(cit = bst.cbegin());
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__methods, clear__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_iterator cit;

	bst.clear();

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_NO_THROW(cit = bst.cbegin());
	EXPECT_EQ(cit, nullptr);
	EXPECT_THROW(static_cast<void>(*cit), std::runtime_error);
}

TEST(binary_search_tree__methods, clear__filled_bst) {
	binary_search_tree bst = filled_init;

	bst.clear();

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_EQ(bst, empty_matcher);
	
	EXPECT_THROW(static_cast<void>(*bst.begin()), std::runtime_error);
}

TEST(binary_search_tree__methods, insert__lref__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reference lref = 101;
	std::initializer_list<int> matcher = {101};

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_EQ(*pair.first, 101);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref__single_node__left_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reference lref = 102;
	std::initializer_list<int> matcher = {101, 102};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(bst, matcher);
	EXPECT_EQ(*pair.first, 102);
	EXPECT_TRUE(pair.second);
}

TEST(binary_search_tree__methods, insert__lref__single_node__right_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reference lref = 100;
	std::initializer_list<int> matcher = {100, 101};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(*pair.first, 100);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::const_reference lref = 0;
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*pair.first, 0);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::const_reference lref = 6;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*pair.first, 6);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	adt::binary_search_tree<int>::const_reference lref = 11;
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 15, 20, 22, 25};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*pair.first, 11);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::const_reference lref = 29;
	std::initializer_list<int> matcher = {25, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*pair.first, 29);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::const_reference lref = 29;
	std::initializer_list<int> matcher = {10, 20, 29, 30, 100, 150, 200, 300};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 7);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 8);

	EXPECT_EQ(*pair.first, 29);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref__filled_bst) {
	binary_search_tree bst = filled_init;
	const_reference lref = insertion_value;

	std::pair<iterator, bool> pair = bst.insert(lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), insertion_size);



	EXPECT_EQ(*pair.first, 29);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}


TEST(binary_search_tree__methods, insert__lref__failed_insertion) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reference lref = 101;
	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(lref);

	EXPECT_FALSE(pair.second);
	EXPECT_EQ(*pair.first, 101);
}

TEST(binary_search_tree__methods, insert__rref__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::value_type&& rref = 101;

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_EQ(*pair.first, 101);
	EXPECT_TRUE(pair.second);
}

TEST(binary_search_tree__methods, insert__rref__single_node__left_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type&& rref = 102;
	std::initializer_list<int> matcher = {101, 102};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(bst, matcher);
	EXPECT_EQ(*pair.first, 102);
	EXPECT_TRUE(pair.second);
}

TEST(binary_search_tree__methods, insert__rref__single_node__right_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type&& rref = 100;
	std::initializer_list<int> matcher = {100, 101};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(*pair.first, 100);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::value_type&& rref = 0;
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*pair.first, 0);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::value_type&& rref = 6;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*pair.first, 6);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	adt::binary_search_tree<int>::value_type&& rref = 11;
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 15, 20, 22, 25};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*pair.first, 11);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::value_type&& rref = 29;
	std::initializer_list<int> matcher = {25, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(rref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*pair.first, 29);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type&& rref = 29;
	std::initializer_list<int> matcher = {10, 20, 29, 30, 100, 150, 200, 300};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 7);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 8);

	EXPECT_EQ(*pair.first, 29);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref__failed_insertion) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type&& rref = 101;
	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.insert(std::forward<int>(rref));

	EXPECT_FALSE(pair.second);
	EXPECT_EQ(*pair.first, 101);
}

TEST(binary_search_tree__methods, insert__lref_and_iterator__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reference lref = 101;
	adt::binary_search_tree<int>::iterator pos = bst.begin();

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_EQ(*it, 101);
}

TEST(binary_search_tree__methods, insert__lref_and_iterator__single_node__left_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reference lref = 102;
	adt::binary_search_tree<int>::iterator pos = bst.begin();
	std::initializer_list<int> matcher = {101, 102};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	adt::binary_search_tree<int>::iterator it =  bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(bst, matcher);
	EXPECT_EQ(*it, 102);
}

TEST(binary_search_tree__methods, insert__lref_and_iterator__single_node__right_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reference lref = 100;
	adt::binary_search_tree<int>::iterator pos = bst.begin();
	std::initializer_list<int> matcher = {100, 101};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(*it, 100);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_iterator__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::const_reference lref = 0;
	adt::binary_search_tree<int>::iterator pos = bst.begin() + 4;
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*it, 0);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_iterator__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::const_reference lref = 6;
	adt::binary_search_tree<int>::iterator pos = bst.begin() + 4;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*it, 6);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_iterator__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	adt::binary_search_tree<int>::const_reference lref = 11;
	adt::binary_search_tree<int>::iterator pos = bst.begin() + 8;
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 15, 20, 22, 25};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*it, 11);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_iterator__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::const_reference lref = 29;
	adt::binary_search_tree<int>::iterator pos = bst.begin() + 8;
	std::initializer_list<int> matcher = {25, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*it, 29);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_iterator__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::const_reference lref = 29;
	adt::binary_search_tree<int>::iterator pos = bst.begin() + 6;
	std::initializer_list<int> matcher = {10, 20, 29, 30, 100, 150, 200, 300};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 7);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 8);

	EXPECT_EQ(*it, 29);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_iterator__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::value_type&& rref = 101;
	adt::binary_search_tree<int>::iterator pos = bst.begin();

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_EQ(*it, 101);
}

TEST(binary_search_tree__methods, insert__rref_and_iterator__single_node__left_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type&& rref = 102;
	adt::binary_search_tree<int>::iterator pos = bst.begin();
	std::initializer_list<int> matcher = {101, 102};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(bst, matcher);
	EXPECT_EQ(*it, 102);
}

TEST(binary_search_tree__methods, insert__rref_and_iterator__single_node__right_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type&& rref = 100;
	adt::binary_search_tree<int>::iterator pos = bst.begin();
	std::initializer_list<int> matcher = {100, 101};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(*it, 100);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_iterator__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::value_type&& rref = 0;
	adt::binary_search_tree<int>::iterator pos = bst.begin();
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*it, 0);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_iterator__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::value_type&& rref = 6;
	adt::binary_search_tree<int>::iterator pos = bst.begin() + 4;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*it, 6);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_iterator__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	adt::binary_search_tree<int>::value_type&& rref = 11;
	adt::binary_search_tree<int>::iterator pos = bst.begin() + 8;
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 15, 20, 22, 25};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*it, 11);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_iterator__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::value_type&& rref = 29;
	adt::binary_search_tree<int>::iterator pos = bst.begin() + 8;
	std::initializer_list<int> matcher = {25, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*it, 29);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_iterator__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type&& rref = 29;
	adt::binary_search_tree<int>::iterator pos = bst.begin() + 6;
	std::initializer_list<int> matcher = {10, 20, 29, 30, 100, 150, 200, 300};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 7);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 8);

	EXPECT_EQ(*it, 29);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_const_iterator__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::const_reference lref = 101;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_EQ(*it, 101);
}

TEST(binary_search_tree__methods, insert__lref_and_const_iterator__single_node__left_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reference lref = 102;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();
	std::initializer_list<int> matcher = {101, 102};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(bst, matcher);
	EXPECT_EQ(*it, 102);
}

TEST(binary_search_tree__methods, insert__lref_and_const_iterator__single_node__right_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::const_reference lref = 100;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();
	std::initializer_list<int> matcher = {100, 101};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(*it, 100);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_const_iterator__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::const_reference lref = 0;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 4;
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*it, 0);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_const_iterator__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::const_reference lref = 6;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 4;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*it, 6);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_const_iterator__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	adt::binary_search_tree<int>::const_reference lref = 11;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 8;
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 15, 20, 22, 25};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*it, 11);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_const_iterator__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::const_reference lref = 29;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 8;
	std::initializer_list<int> matcher = {25, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*it, 29);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__lref_and_const_iterator__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::const_reference lref = 29;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 6;
	std::initializer_list<int> matcher = {10, 20, 29, 30, 100, 150, 200, 300};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 7);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, lref);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 8);

	EXPECT_EQ(*it, 29);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_const_iterator__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::value_type&& rref = 101;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_EQ(*it, 101);
}

TEST(binary_search_tree__methods, insert__rref_and_const_iterator__single_node__left_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type&& rref = 102;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();
	std::initializer_list<int> matcher = {101, 102};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(bst, matcher);
	EXPECT_EQ(*it, 102);
}

TEST(binary_search_tree__methods, insert__rref_and_const_iterator__single_node__right_insert) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type&& rref = 100;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();
	std::initializer_list<int> matcher = {100, 101};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(*it, 100);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_const_iterator__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::value_type&& rref = 0;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*it, 0);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_const_iterator__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::value_type&& rref = 6;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 4;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*it, 6);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_const_iterator__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	adt::binary_search_tree<int>::value_type&& rref = 11;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 8;
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 15, 20, 22, 25};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*it, 11);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_const_iterator__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::value_type&& rref = 29;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 8;
	std::initializer_list<int> matcher = {25, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*it, 29);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__rref_and_const_iterator__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type&& rref = 29;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 6;
	std::initializer_list<int> matcher = {10, 20, 29, 30, 100, 150, 200, 300};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 7);

	adt::binary_search_tree<int>::iterator it = bst.insert(pos, std::forward<int>(rref));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 8);

	EXPECT_EQ(*it, 29);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__iterators__valid_iterators) {
	adt::binary_search_tree<int> bst;
	std::vector<int> vec = {100, 20, 10, 30, 200, 150, 300};
	std::initializer_list<int> matcher = {10, 20, 30, 100, 150, 200, 300};
	
	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	bst.insert(vec.begin(), vec.end());

	EXPECT_FALSE(vec.empty());
	EXPECT_EQ(bst.size(), 7);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__initializer_list__empty_bst) {
	adt::binary_search_tree<int> bst;
	std::initializer_list<int> values;
	std::initializer_list<int> matcher;

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	bst.insert(values);

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__initializer_list__single_node) {
	adt::binary_search_tree<int> bst;
	std::initializer_list<int> values = {101};
	std::initializer_list<int> matcher = {101};
	
	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	bst.insert(values);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__initializer_list__left_linked_list) {
	adt::binary_search_tree<int> bst;
	std::initializer_list<int> values = {5, 4, 3, 2, 1};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	bst.insert(values);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__initializer_list__right_linked_list) {
	adt::binary_search_tree<int> bst;
	std::initializer_list<int> values = {1, 2, 3, 4, 5};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5};

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	bst.insert(values);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__initializer_list__left_skewed_bst) {
	adt::binary_search_tree<int> bst;
	std::initializer_list<int> values = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	std::initializer_list<int> matcher = {1, 5, 8, 10, 12, 15, 20, 22, 25};

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	bst.insert(values);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__initializer_list__right_skewed_bst) {
	adt::binary_search_tree<int> bst;
	std::initializer_list<int> values = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	std::initializer_list<int> matcher = {25, 28, 30, 36, 38, 40, 45, 48, 50};

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	bst.insert(values);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__initializer_list__balanced_bst) {
	adt::binary_search_tree<int> bst;
	std::initializer_list<int> values = {100, 20, 10, 30, 200, 150, 300};
	std::initializer_list<int> matcher = {10, 20, 30, 100, 150, 200, 300};

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	bst.insert(values);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 7);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle__empty_bst) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {101};
	bst_t dst;
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {101};

	bst_t::insert_return_type<bst_t::iterator, bst_t::node_type> insert_return_value = dst.insert(
		std::forward<bst_t::node_type>(node)
	);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_TRUE(insert_return_value.inserted);
	EXPECT_TRUE(insert_return_value.node.empty());
	EXPECT_THROW(static_cast<void>(*insert_return_value.node), std::runtime_error);

	EXPECT_NE(insert_return_value.position, nullptr);
	EXPECT_EQ(*insert_return_value.position, 101);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 1);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle__single_node__left_insert) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {102};
	bst_t dst = {101};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {101, 102};

	bst_t::insert_return_type<bst_t::iterator, bst_t::node_type> insert_return_value = dst.insert(
		std::forward<bst_t::node_type>(node)
	);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_TRUE(insert_return_value.inserted);
	EXPECT_TRUE(insert_return_value.node.empty());
	EXPECT_THROW(static_cast<void>(*insert_return_value.node), std::runtime_error);

	EXPECT_NE(insert_return_value.position, nullptr);
	EXPECT_EQ(*insert_return_value.position, 102);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 2);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle__single_node__right_insert) {
	adt::binary_search_tree<int> bst = {101};
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {100};
	bst_t dst = {101};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {100, 101};

	bst_t::insert_return_type<bst_t::iterator, bst_t::node_type> insert_return_value = dst.insert(
		std::forward<bst_t::node_type>(node)
	);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_TRUE(insert_return_value.inserted);
	EXPECT_TRUE(insert_return_value.node.empty());
	EXPECT_THROW(static_cast<void>(*insert_return_value.node), std::runtime_error);

	EXPECT_NE(insert_return_value.position, nullptr);
	EXPECT_EQ(*insert_return_value.position, 100);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 2);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle__left_linked_list) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {0};
	bst_t dst = {5, 4, 3, 2, 1};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5};

	bst_t::insert_return_type<bst_t::iterator, bst_t::node_type> insert_return_value = dst.insert(
		std::forward<bst_t::node_type>(node)
	);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_TRUE(insert_return_value.inserted);
	EXPECT_TRUE(insert_return_value.node.empty());
	EXPECT_THROW(static_cast<void>(*insert_return_value.node), std::runtime_error);

	EXPECT_NE(insert_return_value.position, nullptr);
	EXPECT_EQ(*insert_return_value.position, 0);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 6);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle__right_linked_list) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {6};
	bst_t dst = {1, 2, 3, 4, 5};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	bst_t::insert_return_type<bst_t::iterator, bst_t::node_type> insert_return_value = dst.insert(
		std::forward<bst_t::node_type>(node)
	);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_TRUE(insert_return_value.inserted);
	EXPECT_TRUE(insert_return_value.node.empty());
	EXPECT_THROW(static_cast<void>(*insert_return_value.node), std::runtime_error);

	EXPECT_NE(insert_return_value.position, nullptr);
	EXPECT_EQ(*insert_return_value.position, 6);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 6);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle__left_skewed_bst) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {11};
	bst_t dst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 15, 20, 22, 25};

	bst_t::insert_return_type<bst_t::iterator, bst_t::node_type> insert_return_value = dst.insert(
		std::forward<bst_t::node_type>(node)
	);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_TRUE(insert_return_value.inserted);
	EXPECT_TRUE(insert_return_value.node.empty());
	EXPECT_THROW(static_cast<void>(*insert_return_value.node), std::runtime_error);

	EXPECT_NE(insert_return_value.position, nullptr);
	EXPECT_EQ(*insert_return_value.position, 11);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 10);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle__right_skewed_bst) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {29};
	bst_t dst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {25, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	bst_t::insert_return_type<bst_t::iterator, bst_t::node_type> insert_return_value = dst.insert(
		std::forward<bst_t::node_type>(node)
	);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_TRUE(insert_return_value.inserted);
	EXPECT_TRUE(insert_return_value.node.empty());
	EXPECT_THROW(static_cast<void>(*insert_return_value.node), std::runtime_error);

	EXPECT_NE(insert_return_value.position, nullptr);
	EXPECT_EQ(*insert_return_value.position, 29);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 10);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle__balanced_bst) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {29};
	bst_t dst = {100, 20, 10, 30, 200, 150, 300};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {10, 20, 29, 30, 100, 150, 200, 300};

	bst_t::insert_return_type<bst_t::iterator, bst_t::node_type> insert_return_value = dst.insert(
		std::forward<bst_t::node_type>(node)
	);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_TRUE(insert_return_value.inserted);
	
	EXPECT_TRUE(insert_return_value.node.empty());
	EXPECT_THROW(static_cast<void>(*insert_return_value.node), std::runtime_error);

	EXPECT_NE(insert_return_value.position, nullptr);
	EXPECT_EQ(*insert_return_value.position, 29);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 8);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle__failed_insertion) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {101};
	bst_t dst = {101};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {101};

	EXPECT_FALSE(src.empty());
	EXPECT_EQ(src.size(), 1);
	EXPECT_EQ(src, matcher);

	bst_t::insert_return_type<bst_t::iterator, bst_t::node_type> insert_return_value = dst.insert(
		std::forward<bst_t::node_type>(node)
	);

	EXPECT_FALSE(node.empty());
	EXPECT_NE(node, nullptr);
	EXPECT_EQ(node.value(), 101);
	EXPECT_EQ(*node, 101);

	EXPECT_FALSE(insert_return_value.inserted);

	EXPECT_FALSE(insert_return_value.node.empty());
	EXPECT_EQ(*insert_return_value.node, 101);

	EXPECT_NE(insert_return_value.position, nullptr);
	EXPECT_EQ(*insert_return_value.position, 101);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 1);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle_and_const_iterator__single_node__left_insert) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {102};
	bst_t dst = {101};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {101, 102};

	bst_t::iterator it = dst.insert(dst.cbegin(), std::forward<bst_t::node_type>(node));

	EXPECT_NE(it, nullptr);
	EXPECT_EQ(*it, 102);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 2);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle_and_const_iterator__single_node__right_insert) {
	adt::binary_search_tree<int> bst = {101};
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {100};
	bst_t dst = {101};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {100, 101};

	bst_t::iterator it = dst.insert(dst.cbegin(), std::forward<bst_t::node_type>(node));

	EXPECT_NE(it, nullptr);
	EXPECT_EQ(*it, 100);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 2);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle_and_const_iterator__left_linked_list) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {0};
	bst_t dst = {5, 4, 3, 2, 1};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5};

	bst_t::iterator it = dst.insert(dst.cbegin() + 4, std::forward<bst_t::node_type>(node));

	EXPECT_NE(it, nullptr);
	EXPECT_EQ(*it, 0);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 6);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle_and_const_iterator__right_linked_list) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {6};
	bst_t dst = {1, 2, 3, 4, 5};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	bst_t::iterator it = dst.insert(dst.cbegin() + 4, std::forward<bst_t::node_type>(node));

	EXPECT_NE(it, nullptr);
	EXPECT_EQ(*it, 6);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 6);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle_and_const_iterator__left_skewed_bst) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {11};
	bst_t dst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 15, 20, 22, 25};

	bst_t::iterator it = dst.insert(dst.cbegin() + 3, std::forward<bst_t::node_type>(node));

	EXPECT_NE(it, nullptr);
	EXPECT_EQ(*it, 11);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 10);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle_and_const_iterator__right_skewed_bst) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {29};
	bst_t dst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {25, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	bst_t::iterator it = dst.insert(dst.cbegin() + 3, std::forward<bst_t::node_type>(node));

	EXPECT_NE(it, nullptr);
	EXPECT_EQ(*it, 29);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 10);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle_and_const_iterator__balanced_bst) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {29};
	bst_t dst = {100, 20, 10, 30, 200, 150, 300};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {10, 20, 29, 30, 100, 150, 200, 300};

	bst_t::iterator it = dst.insert(dst.cbegin() + 3, std::forward<bst_t::node_type>(node));

	EXPECT_NE(it, nullptr);
	EXPECT_EQ(*it, 29);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 8);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert__node_handle_and_const_iterator__failed_insertion) {
	typedef adt::binary_search_tree<int> bst_t;

	bst_t src = {101};
	bst_t dst = {101};
	bst_t::node_type node(src.cbegin());
	std::initializer_list<int> matcher = {101};

	bst_t::iterator it = dst.insert(dst.cbegin(), std::forward<bst_t::node_type>(node));

	EXPECT_NE(it, nullptr);
	EXPECT_EQ(*it, 101);

	EXPECT_FALSE(node.empty());
	EXPECT_NE(node, nullptr);
	EXPECT_EQ(node.value(), 101);
	EXPECT_EQ(*node, 101);

	EXPECT_FALSE(src.empty());
	EXPECT_EQ(src.size(), 1);
	EXPECT_EQ(src, matcher);

	EXPECT_FALSE(dst.empty());
	EXPECT_EQ(dst.size(), 1);
	EXPECT_EQ(dst, matcher);
}

TEST(binary_search_tree__methods, insert_range__empty_bst) {
	adt::binary_search_tree<int> bst;
	std::vector<int> vec = {101};
	std::initializer_list<int> matcher = {101};

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	bst.insert_range(vec);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert_range__single_node__left_insert) {
	adt::binary_search_tree<int> bst = {101};
	std::vector<int> vec = {102, 103, 104};
	std::initializer_list<int> matcher = {101, 102, 103, 104};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	bst.insert_range(vec);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 4);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert_range__single_node__right_insert) {
	adt::binary_search_tree<int> bst = {101};
	std::vector<int> vec = {98, 99, 100};
	std::initializer_list<int> matcher = {98, 99, 100, 101};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	bst.insert_range(vec);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 4);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert_range__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	std::vector<int> vec = {-2, -1, 0};
	std::initializer_list<int> matcher = {-2, -1, 0, 1, 2, 3, 4, 5};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	bst.insert_range(vec);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 8);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert_range__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	std::vector<int> vec = {6, 7, 8};
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6, 7, 8};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	bst.insert_range(vec);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 8);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert_range__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	std::vector<int> vec = {11, 13, 16};
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 13, 15, 16, 20, 22, 25};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	bst.insert_range(vec);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 12);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert_range__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	std::vector<int> vec = {26, 27, 29};
	std::initializer_list<int> matcher = {25, 26, 27, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	bst.insert_range(vec);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 12);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, insert_range__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	std::vector<int> vec = {29, 31, 32};
	std::initializer_list<int> matcher = {10, 20, 29, 30, 31, 32, 100, 150, 200, 300};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 7);

	bst.insert_range(vec);

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::value_type value = 101;
	std::initializer_list<int> matcher = {101};

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.emplace(std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_EQ(*pair.first, 101);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace__single_node__left_emplace) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type value = 102;
	std::initializer_list<int> matcher = {101, 102};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.emplace(std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(bst, matcher);
	EXPECT_EQ(*pair.first, 102);
	EXPECT_TRUE(pair.second);
}

TEST(binary_search_tree__methods, emplace__single_node__right_emplace) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type value = 100;
	std::initializer_list<int> matcher = {100, 101};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.emplace(std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(*pair.first, 100);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::value_type value = 0;
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.emplace(std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*pair.first, 0);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::value_type value = 6;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.emplace(std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*pair.first, 6);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	adt::binary_search_tree<int>::value_type value = 11;
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 15, 20, 22, 25};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.emplace(std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*pair.first, 11);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::value_type value = 29;
	std::initializer_list<int> matcher = {25, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.emplace(std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*pair.first, 29);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value = 29;
	std::initializer_list<int> matcher = {10, 20, 29, 30, 100, 150, 200, 300};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 7);

	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.emplace(std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 8);

	EXPECT_EQ(*pair.first, 29);
	EXPECT_TRUE(pair.second);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace__failed_emplacement) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type value = 101;
	std::pair<adt::binary_search_tree<int>::iterator, bool> pair = bst.emplace(std::forward<int>(value));

	EXPECT_FALSE(pair.second);
	EXPECT_EQ(*pair.first, 101);
}

TEST(binary_search_tree__methods, emplace_hint__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::value_type value = 101;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	adt::binary_search_tree<int>::iterator it = bst.emplace_hint(pos, std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_EQ(*it, 101);
}

TEST(binary_search_tree__methods, emplace_hint__single_node__left_emplace) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type value = 102;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();
	std::initializer_list<int> matcher = {101, 102};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	adt::binary_search_tree<int>::iterator it = bst.emplace_hint(pos, std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(bst, matcher);
	EXPECT_EQ(*it, 102);
}

TEST(binary_search_tree__methods, emplace_hint__single_node__right_emplace) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::value_type value = 100;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();
	std::initializer_list<int> matcher = {100, 101};
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	adt::binary_search_tree<int>::iterator it = bst.emplace_hint(pos, std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 2);

	EXPECT_EQ(*it, 100);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace_hint__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::value_type value = 0;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin();
	std::initializer_list<int> matcher = {0, 1, 2, 3, 4, 5};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	adt::binary_search_tree<int>::iterator it = bst.emplace_hint(pos, std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*it, 0);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace_hint__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::value_type value = 6;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 4;
	std::initializer_list<int> matcher = {1, 2, 3, 4, 5, 6};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 5);

	adt::binary_search_tree<int>::iterator it = bst.emplace_hint(pos, std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 6);

	EXPECT_EQ(*it, 6);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace_hint__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	adt::binary_search_tree<int>::value_type value = 11;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 8;
	std::initializer_list<int> matcher = {1, 5, 8, 10, 11, 12, 15, 20, 22, 25};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	adt::binary_search_tree<int>::iterator it = bst.emplace_hint(pos, std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*it, 11);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace_hint__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::value_type value = 29;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 8;
	std::initializer_list<int> matcher = {25, 28, 29, 30, 36, 38, 40, 45, 48, 50};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 9);

	adt::binary_search_tree<int>::iterator it = bst.emplace_hint(pos, std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 10);

	EXPECT_EQ(*it, 29);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, emplace_hint__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::value_type value = 29;
	adt::binary_search_tree<int>::const_iterator pos = bst.cbegin() + 6;
	std::initializer_list<int> matcher = {10, 20, 29, 30, 100, 150, 200, 300};

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 7);

	adt::binary_search_tree<int>::iterator it = bst.emplace_hint(pos, std::forward<int>(value));

	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 8);

	EXPECT_EQ(*it, 29);
	EXPECT_EQ(bst, matcher);
}

TEST(binary_search_tree__methods, erase__single_iterator__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it;

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_NO_THROW(it = bst.erase(bst.begin()));

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_iterator__single_node) {
	adt::binary_search_tree<int> bst = {101};
	std::initializer_list<int> matcher;
	adt::binary_search_tree<int>::iterator it;
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_NO_THROW(it = bst.erase(bst.begin()));

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, matcher);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_iterator__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::iterator it;
	std::forward_list<int> values_matcher = {1, 2, 3, 4, 5};

	for (std::forward_list<int>::size_type size_matcher = 5; size_matcher > 0; size_matcher--) {
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst.size(), size_matcher);
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(it = bst.erase(bst.begin()));
		values_matcher.pop_front();
		
		if (bst.size() == 0) {
			break;
		}

		EXPECT_FALSE(it == nullptr);
		EXPECT_EQ(*it, values_matcher.front());
	}

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, values_matcher);

	EXPECT_TRUE(it == nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_iterator__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::iterator it;
	std::forward_list<int> values_matcher = {1, 2, 3, 4, 5};

	for (std::forward_list<int>::size_type size_matcher = 5; size_matcher > 0; size_matcher--) {
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst.size(), size_matcher);
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(it = bst.erase(bst.begin()));
		values_matcher.pop_front();

		if (bst.size() == 0) {
			break;
		}

		EXPECT_FALSE(it == nullptr);
		EXPECT_EQ(*it, values_matcher.front());
	}

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, values_matcher);

	EXPECT_TRUE(it == nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_iterator__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	adt::binary_search_tree<int>::iterator it;
	std::forward_list<int> values_matcher = {1, 5, 8, 10, 12, 15, 20, 22, 25};

	for (std::forward_list<int>::size_type size_matcher = 9; size_matcher > 0; size_matcher--) {
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst.size(), size_matcher);
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(it = bst.erase(bst.begin()));
		values_matcher.pop_front();

		if (bst.size() == 0) {
			break;
		}

		EXPECT_NE(it, nullptr);
		EXPECT_EQ(*it, values_matcher.front());
	}

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, values_matcher);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_iterator__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::iterator it;
	std::forward_list<int> values_matcher = {25, 28, 30, 36, 38, 40, 45, 48, 50};

	for (std::forward_list<int>::size_type size_matcher = 9; size_matcher > 0; size_matcher--) {
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst.size(), size_matcher);
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(it = bst.erase(bst.begin()));
		values_matcher.pop_front();

		if (bst.size() == 0) {
			break;
		}

		EXPECT_NE(it, nullptr);
		EXPECT_EQ(*it, values_matcher.front());
	}

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, values_matcher);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_iterator__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::iterator it;
	std::forward_list<int> values_matcher = {10, 20, 30, 100, 150, 200, 300};

	for (std::forward_list<int>::size_type size_matcher = 7; size_matcher > 0; size_matcher--) {
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst.size(), size_matcher);
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(it = bst.erase(bst.begin()));
		values_matcher.pop_front();

		if (bst.size() == 0) {
			break;
		}

		EXPECT_NE(it, nullptr);
		EXPECT_EQ(*it, values_matcher.front());
	}

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, values_matcher);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_const_iterator__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::iterator it;

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_NO_THROW(it = bst.erase(bst.cbegin()));

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_const_iterator__single_node) {
	adt::binary_search_tree<int> bst = {101};
	std::initializer_list<int> matcher;
	adt::binary_search_tree<int>::iterator it;
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_NO_THROW(it = bst.erase(bst.cbegin()));

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, matcher);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_const_iterator__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::iterator it;
	std::forward_list<int> values_matcher = {1, 2, 3, 4, 5};

	for (std::forward_list<int>::size_type size_matcher = 5; size_matcher > 0; size_matcher--) {
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst.size(), size_matcher);
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(it = bst.erase(bst.cbegin()));
		values_matcher.pop_front();

		if (bst.size() == 0) {
			break;
		}

		EXPECT_NE(it, nullptr);
		EXPECT_EQ(*it, values_matcher.front());
	}

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, values_matcher);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_const_iterator__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::iterator it;
	std::forward_list<int> values_matcher = {1, 2, 3, 4, 5};

	for (std::forward_list<int>::size_type size_matcher = 5; size_matcher > 0; size_matcher--) {
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst.size(), size_matcher);
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(it = bst.erase(bst.cbegin()));
		values_matcher.pop_front();

		if (bst.size() == 0) {
			break;
		}

		EXPECT_NE(it, nullptr);
		EXPECT_EQ(*it, values_matcher.front());
	}

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, values_matcher);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_const_iterator__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 5, 1, 8, 12, 15, 22};
	adt::binary_search_tree<int>::iterator it;
	std::forward_list<int> values_matcher = {1, 5, 8, 10, 12, 15, 20, 22, 25};

	for (std::forward_list<int>::size_type size_matcher = 9; size_matcher > 0; size_matcher--) {
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst.size(), size_matcher);
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(it = bst.erase(bst.cbegin()));
		values_matcher.pop_front();

		if (bst.size() == 0) {
			break;
		}

		EXPECT_NE(it, nullptr);
		EXPECT_EQ(*it, values_matcher.front());
	}

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, values_matcher);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_const_iterator__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::iterator it;
	std::forward_list<int> values_matcher = {25, 28, 30, 36, 38, 40, 45, 48, 50};

	for (std::forward_list<int>::size_type size_matcher = 9; size_matcher > 0; size_matcher--) {
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst.size(), size_matcher);
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(it = bst.erase(bst.cbegin()));
		values_matcher.pop_front();

		if (bst.size() == 0) {
			break;
		}

		EXPECT_NE(it, nullptr);
		EXPECT_EQ(*it, values_matcher.front());
	}

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, values_matcher);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__single_const_iterator__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::iterator it;
	std::forward_list<int> values_matcher = {10, 20, 30, 100, 150, 200, 300};

	for (std::forward_list<int>::size_type size_matcher = 7; size_matcher > 0; size_matcher--) {
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst.size(), size_matcher);
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(it = bst.erase(bst.cbegin()));
		values_matcher.pop_front();

		if (bst.size() == 0) {
			break;
		}

		EXPECT_NE(it, nullptr);
		EXPECT_EQ(*it, values_matcher.front());
	}

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, values_matcher);

	EXPECT_EQ(it, nullptr);
	EXPECT_THROW(static_cast<void>(*it), std::runtime_error);
}

TEST(binary_search_tree__methods, erase__iterator_range__empty_bst) {
	adt::binary_search_tree<int> bst;

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_THROW(static_cast<void>(bst.erase(bst.begin(), bst.end())), std::invalid_argument);
}

TEST(binary_search_tree__methods, erase__iterator_range__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it;
	
	EXPECT_THROW(static_cast<void>(it = bst.erase(bst.begin(), bst.end())), std::invalid_argument);
}

TEST(binary_search_tree__methods, erase__iterator_range__left_linked_list) {
    std::initializer_list<int> values = {5, 4, 3, 2, 1};
    adt::binary_search_tree<int> bst = values;
    adt::binary_search_tree<int>::iterator it;
    
    // Expected remaining elements after erasing [begin, begin+i)
    std::vector<std::vector<int>> matchers = {
        {1, 2, 3, 4, 5}, // erase nothing: [begin, begin) 
        {2, 3, 4, 5},    // erase first 1 element: erase(1)
        {3, 4, 5},       // erase first 2 elements: erase(1,2)
        {4, 5},          // erase first 3 elements: erase(1,2,3)
        {5},             // erase first 4 elements: erase(1,2,3,4)
    };
    
    for (std::size_t i = 0; i <= values.size(); i++) {
        EXPECT_FALSE(bst.empty());
        EXPECT_EQ(bst.size(), matchers[i].size());

        // Get iterator to position i by advancing from begin
		auto begin_it = bst.begin();
        auto end_it = bst.begin();
        std::advance(end_it, i);

		if (std::distance(begin_it, end_it) <= 0) {
			EXPECT_THROW(it = bst.erase(begin_it, end_it), std::invalid_argument);
			break;
		}
        
        if (i < values.size()) {
            EXPECT_NO_THROW(it = bst.erase(begin_it, end_it));
            EXPECT_NE(it, bst.end());
            EXPECT_EQ(*it, matchers[i][0]);
        }
        
        // Verify remaining elements
        std::vector<int> remaining(bst.begin(), bst.end());
        EXPECT_EQ(remaining, matchers[i]);
        
        // Reset
        bst = values;
    }
    
    // Test erasing all elements
    EXPECT_NO_THROW(it = bst.erase(bst.begin(), bst.end()));
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
    EXPECT_EQ(it, bst.end());
}

TEST(binary_search_tree__methods, erase__iterator_range__right_linked_list) {
    std::initializer_list<int> values = {1, 2, 3, 4, 5};
    adt::binary_search_tree<int> bst = values;
    adt::binary_search_tree<int>::iterator it;
    
    // Expected remaining elements after erasing [begin, begin+i)
    std::vector<std::vector<int>> matchers = {
        {1, 2, 3, 4, 5}, // erase nothing
        {2, 3, 4, 5},    // erase first 1 element
        {3, 4, 5},       // erase first 2 elements
        {4, 5},          // erase first 3 elements
        {5},             // erase first 4 elements
    };
    
    for (std::size_t i = 0; i <= values.size(); i++) {
        EXPECT_FALSE(bst.empty());
        EXPECT_EQ(bst.size(), matchers[i].size());
        
        // Get iterator to position i
		auto begin_it = bst.begin();
        auto end_it = bst.begin();
        std::advance(end_it, i);

		if (std::distance(begin_it, end_it) <= 0) {
			EXPECT_THROW(it = bst.erase(begin_it, end_it), std::invalid_argument);
			break;
		}
        
        if (i < values.size()) {
            EXPECT_NO_THROW(it = bst.erase(begin_it, end_it));
            EXPECT_NE(it, bst.end());
            EXPECT_EQ(*it, matchers[i][0]);
        }
        
        // Verify remaining elements
        std::vector<int> remaining(bst.begin(), bst.end());
        EXPECT_EQ(remaining, matchers[i]);
        
        // Reset
        bst = values;
    }
    
    // Test erasing all elements
    EXPECT_NO_THROW(it = bst.erase(bst.begin(), bst.end()));
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
    EXPECT_EQ(it, bst.end());
}

TEST(binary_search_tree__methods, erase__iterator_range__left_skewed_bst) {
    std::initializer_list<int> values = {25, 20, 10, 5, 1, 8, 12, 15, 22};
    adt::binary_search_tree<int> bst = values;
    adt::binary_search_tree<int>::iterator it;
    
    // BST in-order traversal: {1, 5, 8, 10, 12, 15, 20, 22, 25}
    // Expected remaining elements after erasing [begin, begin+i)
    std::vector<std::vector<int>> matchers = {
        {1, 5, 8, 10, 12, 15, 20, 22, 25}, // erase nothing
        {5, 8, 10, 12, 15, 20, 22, 25},    // erase first 1: erase(1)
        {8, 10, 12, 15, 20, 22, 25},       // erase first 2: erase(1,5)
        {10, 12, 15, 20, 22, 25},          // erase first 3: erase(1,5,8)
        {12, 15, 20, 22, 25},              // erase first 4: erase(1,5,8,10)
        {15, 20, 22, 25},                  // erase first 5: erase(1,5,8,10,12)
        {20, 22, 25},                      // erase first 6: erase(1,5,8,10,12,15)
        {22, 25},                          // erase first 7: erase(1,5,8,10,12,15,20)
        {25},                              // erase first 8: erase(1,5,8,10,12,15,20,22)
    };
    
    for (std::size_t i = 0; i <= values.size(); i++) {
        EXPECT_FALSE(bst.empty());
        EXPECT_EQ(bst.size(), matchers[i].size());
        
        // Get iterator to position i
		auto begin_it = bst.begin();
        auto end_it = bst.begin();
        std::advance(end_it, i);

		if (std::distance(begin_it, end_it) <= 0) {
			EXPECT_THROW(it = bst.erase(begin_it, end_it), std::invalid_argument);
			break;
		}
        
        if (i < values.size()) {
            EXPECT_NO_THROW(it = bst.erase(bst.begin(), end_it));
            EXPECT_NE(it, bst.end());
            EXPECT_EQ(*it, matchers[i][0]);
        }
        
        // Verify remaining elements
        std::vector<int> remaining(bst.begin(), bst.end());
        EXPECT_EQ(remaining, matchers[i]);
        
        // Reset
        bst = values;
    }
    
    // Test erasing all elements
    EXPECT_NO_THROW(it = bst.erase(bst.begin(), bst.end()));
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
    EXPECT_EQ(it, bst.end());
}

TEST(binary_search_tree__methods, erase__iterator_range__right_skewed_bst) {
    std::initializer_list<int> values = {25, 36, 30, 28, 40, 38, 48, 45, 50};
    adt::binary_search_tree<int> bst = values;
    adt::binary_search_tree<int>::iterator it;
    
    // BST in-order traversal: {25, 28, 30, 36, 38, 40, 45, 48, 50}
    // Expected remaining elements after erasing [begin, begin+i)
    std::vector<std::vector<int>> matchers = {
        {25, 28, 30, 36, 38, 40, 45, 48, 50}, // erase nothing
        {28, 30, 36, 38, 40, 45, 48, 50},     // erase first 1
        {30, 36, 38, 40, 45, 48, 50},         // erase first 2
        {36, 38, 40, 45, 48, 50},             // erase first 3
        {38, 40, 45, 48, 50},                 // erase first 4
        {40, 45, 48, 50},                     // erase first 5
        {45, 48, 50},                         // erase first 6
        {48, 50},                             // erase first 7
        {50},                                 // erase first 8
    };
    
    for (std::size_t i = 0; i <= values.size(); i++) {
        EXPECT_FALSE(bst.empty());
        EXPECT_EQ(bst.size(), matchers[i].size());
        
        // Get iterator to position i
		auto begin_it = bst.begin();
        auto end_it = bst.begin();
        std::advance(end_it, i);

		if (std::distance(begin_it, end_it) <= 0) {
			EXPECT_THROW(it = bst.erase(begin_it, end_it), std::invalid_argument);
			break;
		}
        
        if (i < values.size()) {
            EXPECT_NO_THROW(it = bst.erase(bst.begin(), end_it));
            EXPECT_NE(it, bst.end());
            EXPECT_EQ(*it, matchers[i][0]);
        }
        
        // Verify remaining elements
        std::vector<int> remaining(bst.begin(), bst.end());
        EXPECT_EQ(remaining, matchers[i]);
        
        // Reset
        bst = values;
    }
    
    // Test erasing all elements
    EXPECT_NO_THROW(it = bst.erase(bst.begin(), bst.end()));
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
    EXPECT_EQ(it, bst.end());
}

TEST(binary_search_tree__methods, erase__iterator_range__balanced_bst) {
    std::initializer_list<int> values = {100, 20, 10, 30, 200, 150, 300};
    adt::binary_search_tree<int> bst = values;
    adt::binary_search_tree<int>::iterator it;
    
    // BST in-order traversal: {10, 20, 30, 100, 150, 200, 300}
    // Expected remaining elements after erasing [begin, begin+i)
    std::vector<std::vector<int>> matchers = {
        {10, 20, 30, 100, 150, 200, 300}, // erase nothing
        {20, 30, 100, 150, 200, 300},     // erase first 1: erase(10)
        {30, 100, 150, 200, 300},         // erase first 2: erase(10,20)
        {100, 150, 200, 300},             // erase first 3: erase(10,20,30)
        {150, 200, 300},                  // erase first 4: erase(10,20,30,100)
        {200, 300},                       // erase first 5: erase(10,20,30,100,150)
        {300},                            // erase first 6: erase(10,20,30,100,150,200)
    };
    
    for (std::size_t i = 0; i <= values.size(); i++) {
        EXPECT_FALSE(bst.empty());
        EXPECT_EQ(bst.size(), matchers[i].size());
        
        // Get iterator to position i
		auto begin_it = bst.begin();
        auto end_it = bst.begin();
        std::advance(end_it, i);

		if (std::distance(begin_it, end_it) <= 0) {
			EXPECT_THROW(it = bst.erase(begin_it, end_it), std::invalid_argument);
			break;
		}
        
        if (i < values.size()) {
            EXPECT_NO_THROW(it = bst.erase(bst.begin(), end_it));
            EXPECT_NE(it, bst.end());
            EXPECT_EQ(*it, matchers[i][0]);
        }
        
        // Verify remaining elements
        std::vector<int> remaining(bst.begin(), bst.end());
        EXPECT_EQ(remaining, matchers[i]);
        
        // Reset
        bst = values;
    }
    
    // Test erasing all elements
    EXPECT_NO_THROW(it = bst.erase(bst.begin(), bst.end()));
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
    EXPECT_EQ(it, bst.end());
}

TEST(binary_search_tree__methods, erase__const_iterator_range__empty_bst) {
	adt::binary_search_tree<int> bst;

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_THROW(static_cast<void>(bst.erase(bst.cbegin(), bst.cend())), std::invalid_argument);
}

TEST(binary_search_tree__methods, erase__const_iterator_range__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::iterator it;
	
	EXPECT_THROW(static_cast<void>(it = bst.erase(bst.cbegin(), bst.cend())), std::invalid_argument);
}

TEST(binary_search_tree__methods, erase__const_iterator_range__left_linked_list) {
    std::initializer_list<int> values = {5, 4, 3, 2, 1};
    adt::binary_search_tree<int> bst = values;
    adt::binary_search_tree<int>::iterator it;
    
    // Expected remaining elements after erasing [begin, begin+i)
    std::vector<std::vector<int>> matchers = {
        {1, 2, 3, 4, 5}, // erase nothing: [begin, begin) 
        {2, 3, 4, 5},    // erase first 1 element: erase(1)
        {3, 4, 5},       // erase first 2 elements: erase(1,2)
        {4, 5},          // erase first 3 elements: erase(1,2,3)
        {5},             // erase first 4 elements: erase(1,2,3,4)
    };
    
    for (std::size_t i = 0; i <= values.size(); i++) {
        EXPECT_FALSE(bst.empty());
        EXPECT_EQ(bst.size(), matchers[i].size());

        // Get iterator to position i by advancing from begin
		auto begin_cit = bst.cbegin();
        auto end_cit = bst.cbegin();
        std::advance(end_cit, i);

		if (std::distance(begin_cit, end_cit) <= 0) {
			EXPECT_THROW(it = bst.erase(begin_cit, end_cit), std::invalid_argument);
			break;
		}
        
        if (i < values.size()) {
            EXPECT_NO_THROW(it = bst.erase(begin_cit, end_cit));
            EXPECT_NE(it, bst.end());
            EXPECT_EQ(*it, matchers[i][0]);
        }
        
        // Verify remaining elements
        std::vector<int> remaining(bst.begin(), bst.end());
        EXPECT_EQ(remaining, matchers[i]);
        
        // Reset
        bst = values;
    }
    
    // Test erasing all elements
    EXPECT_NO_THROW(it = bst.erase(bst.cbegin(), bst.cend()));
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
    EXPECT_EQ(it, bst.end());
}

TEST(binary_search_tree__methods, erase__const_iterator_range__right_linked_list) {
    std::initializer_list<int> values = {1, 2, 3, 4, 5};
    adt::binary_search_tree<int> bst = values;
    adt::binary_search_tree<int>::iterator it;
    
    // Expected remaining elements after erasing [begin, begin+i)
    std::vector<std::vector<int>> matchers = {
        {1, 2, 3, 4, 5}, // erase nothing
        {2, 3, 4, 5},    // erase first 1 element
        {3, 4, 5},       // erase first 2 elements
        {4, 5},          // erase first 3 elements
        {5},             // erase first 4 elements
    };
    
    for (std::size_t i = 0; i <= values.size(); i++) {
        EXPECT_FALSE(bst.empty());
        EXPECT_EQ(bst.size(), matchers[i].size());
        
        // Get iterator to position i
		auto begin_cit = bst.cbegin();
        auto end_cit = bst.cbegin();
        std::advance(end_cit, i);

		if (std::distance(begin_cit, end_cit) <= 0) {
			EXPECT_THROW(it = bst.erase(begin_cit, end_cit), std::invalid_argument);
			break;
		}
        
        if (i < values.size()) {
            EXPECT_NO_THROW(it = bst.erase(begin_cit, end_cit));
            EXPECT_NE(it, bst.end());
            EXPECT_EQ(*it, matchers[i][0]);
        }
        
        // Verify remaining elements
        std::vector<int> remaining(bst.begin(), bst.end());
        EXPECT_EQ(remaining, matchers[i]);
        
        // Reset
        bst = values;
    }
    
    // Test erasing all elements
    EXPECT_NO_THROW(it = bst.erase(bst.cbegin(), bst.cend()));
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
    EXPECT_EQ(it, bst.end());
}

TEST(binary_search_tree__methods, erase__const_iterator_range__left_skewed_bst) {
    std::initializer_list<int> values = {25, 20, 10, 5, 1, 8, 12, 15, 22};
    adt::binary_search_tree<int> bst = values;
    adt::binary_search_tree<int>::iterator it;
    
    // BST in-order traversal: {1, 5, 8, 10, 12, 15, 20, 22, 25}
    // Expected remaining elements after erasing [begin, begin+i)
    std::vector<std::vector<int>> matchers = {
        {1, 5, 8, 10, 12, 15, 20, 22, 25}, // erase nothing
        {5, 8, 10, 12, 15, 20, 22, 25},    // erase first 1: erase(1)
        {8, 10, 12, 15, 20, 22, 25},       // erase first 2: erase(1,5)
        {10, 12, 15, 20, 22, 25},          // erase first 3: erase(1,5,8)
        {12, 15, 20, 22, 25},              // erase first 4: erase(1,5,8,10)
        {15, 20, 22, 25},                  // erase first 5: erase(1,5,8,10,12)
        {20, 22, 25},                      // erase first 6: erase(1,5,8,10,12,15)
        {22, 25},                          // erase first 7: erase(1,5,8,10,12,15,20)
        {25},                              // erase first 8: erase(1,5,8,10,12,15,20,22)
    };
    
    for (std::size_t i = 0; i <= values.size(); i++) {
        EXPECT_FALSE(bst.empty());
        EXPECT_EQ(bst.size(), matchers[i].size());
        
        // Get iterator to position i
		auto begin_cit = bst.cbegin();
        auto end_cit = bst.cbegin();
        std::advance(end_cit, i);

		if (std::distance(begin_cit, end_cit) <= 0) {
			EXPECT_THROW(it = bst.erase(begin_cit, end_cit), std::invalid_argument);
			break;
		}
        
        if (i < values.size()) {
            EXPECT_NO_THROW(it = bst.erase(begin_cit, end_cit));
            EXPECT_NE(it, bst.end());
            EXPECT_EQ(*it, matchers[i][0]);
        }
        
        // Verify remaining elements
        std::vector<int> remaining(bst.begin(), bst.end());
        EXPECT_EQ(remaining, matchers[i]);
        
        // Reset
        bst = values;
    }
    
    // Test erasing all elements
    EXPECT_NO_THROW(it = bst.erase(bst.cbegin(), bst.cend()));
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
    EXPECT_EQ(it, bst.end());
}

TEST(binary_search_tree__methods, erase__const_iterator_range__right_skewed_bst) {
    std::initializer_list<int> values = {25, 36, 30, 28, 40, 38, 48, 45, 50};
    adt::binary_search_tree<int> bst = values;
    adt::binary_search_tree<int>::iterator it;
    
    // BST in-order traversal: {25, 28, 30, 36, 38, 40, 45, 48, 50}
    // Expected remaining elements after erasing [begin, begin+i)
    std::vector<std::vector<int>> matchers = {
        {25, 28, 30, 36, 38, 40, 45, 48, 50}, // erase nothing
        {28, 30, 36, 38, 40, 45, 48, 50},     // erase first 1
        {30, 36, 38, 40, 45, 48, 50},         // erase first 2
        {36, 38, 40, 45, 48, 50},             // erase first 3
        {38, 40, 45, 48, 50},                 // erase first 4
        {40, 45, 48, 50},                     // erase first 5
        {45, 48, 50},                         // erase first 6
        {48, 50},                             // erase first 7
        {50},                                 // erase first 8
    };
    
    for (std::size_t i = 0; i <= values.size(); i++) {
        EXPECT_FALSE(bst.empty());
        EXPECT_EQ(bst.size(), matchers[i].size());
        
        // Get iterator to position i
		auto begin_cit = bst.cbegin();
        auto end_cit = bst.cbegin();
        std::advance(end_cit, i);

		if (std::distance(begin_cit, end_cit) <= 0) {
			EXPECT_THROW(it = bst.erase(begin_cit, end_cit), std::invalid_argument);
			break;
		}
        
        if (i < values.size()) {
            EXPECT_NO_THROW(it = bst.erase(begin_cit, end_cit));
            EXPECT_NE(it, bst.end());
            EXPECT_EQ(*it, matchers[i][0]);
        }
        
        // Verify remaining elements
        std::vector<int> remaining(bst.begin(), bst.end());
        EXPECT_EQ(remaining, matchers[i]);
        
        // Reset
        bst = values;
    }
    
    // Test erasing all elements
    EXPECT_NO_THROW(it = bst.erase(bst.cbegin(), bst.cend()));
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
    EXPECT_EQ(it, bst.end());
}

TEST(binary_search_tree__methods, erase__const_iterator_range__balanced_bst) {
    std::initializer_list<int> values = {100, 20, 10, 30, 200, 150, 300};
    adt::binary_search_tree<int> bst = values;
    adt::binary_search_tree<int>::iterator it;
    
    // BST in-order traversal: {10, 20, 30, 100, 150, 200, 300}
    // Expected remaining elements after erasing [begin, begin+i)
    std::vector<std::vector<int>> matchers = {
        {10, 20, 30, 100, 150, 200, 300}, // erase nothing
        {20, 30, 100, 150, 200, 300},     // erase first 1: erase(10)
        {30, 100, 150, 200, 300},         // erase first 2: erase(10,20)
        {100, 150, 200, 300},             // erase first 3: erase(10,20,30)
        {150, 200, 300},                  // erase first 4: erase(10,20,30,100)
        {200, 300},                       // erase first 5: erase(10,20,30,100,150)
        {300},                            // erase first 6: erase(10,20,30,100,150,200)
    };
    
    for (std::size_t i = 0; i <= values.size(); i++) {
        EXPECT_FALSE(bst.empty());
        EXPECT_EQ(bst.size(), matchers[i].size());
        
        // Get iterator to position i
		auto begin_cit = bst.cbegin();
        auto end_cit = bst.cbegin();
        std::advance(end_cit, i);

		if (std::distance(begin_cit, end_cit) <= 0) {
			EXPECT_THROW(it = bst.erase(begin_cit, end_cit), std::invalid_argument);
			break;
		}
        
        if (i < values.size()) {
            EXPECT_NO_THROW(it = bst.erase(begin_cit, end_cit));
            EXPECT_NE(it, bst.end());
            EXPECT_EQ(*it, matchers[i][0]);
        }
        
        // Verify remaining elements
        std::vector<int> remaining(bst.begin(), bst.end());
        EXPECT_EQ(remaining, matchers[i]);
        
        // Reset
        bst = values;
    }
    
    // Test erasing all elements
    EXPECT_NO_THROW(it = bst.erase(bst.cbegin(), bst.cend()));
    EXPECT_TRUE(bst.empty());
    EXPECT_EQ(bst.size(), 0);
    EXPECT_EQ(it, bst.end());
}

TEST(binary_search_tree__methods, swap__empty_to_empty) {
	adt::binary_search_tree<int> bst1,
								 bst1_orig = bst1,
								 bst2,
								 bst2_orig = bst2;

	adt::binary_search_tree<int>* bst1_ptr = &bst1,
								* bst2_ptr = &bst2;
	
	bst1.swap(bst2);

	EXPECT_EQ(bst1_ptr, &bst1);
	EXPECT_EQ(bst2_ptr, &bst2);

	EXPECT_NE(&bst1, &bst2);

	EXPECT_EQ(bst1, bst2_orig);
	EXPECT_EQ(bst2, bst1_orig);

	EXPECT_EQ(bst1.size(), 0);
	EXPECT_TRUE(bst1.empty());

	EXPECT_EQ(bst2.size(), 0);
	EXPECT_TRUE(bst2.empty());

	EXPECT_EQ(bst1, std::initializer_list<int>());
	EXPECT_EQ(bst2, std::initializer_list<int>());
}

TEST(binary_search_tree__methods, swap__filled_to_empty) {
	adt::binary_search_tree<int> bst1 = {100, 20, 10, 30, 200, 150, 300},
								 bst1_orig = bst1,
								 bst2,
								 bst2_orig = bst2;

	adt::binary_search_tree<int>* bst1_ptr = &bst1,
								* bst2_ptr = &bst2;
	
	bst1.swap(bst2);

	EXPECT_EQ(bst1_ptr, &bst1);
	EXPECT_EQ(bst2_ptr, &bst2);

	EXPECT_NE(&bst1, &bst2);

	EXPECT_EQ(bst1, bst2_orig);
	EXPECT_EQ(bst2, bst1_orig);

	EXPECT_EQ(bst1.size(), 0);
	EXPECT_TRUE(bst1.empty());

	EXPECT_EQ(bst2.size(), 7);
	EXPECT_FALSE(bst2.empty());

	EXPECT_EQ(bst1, std::initializer_list<int>());
	EXPECT_EQ(bst2, std::initializer_list<int>({10, 20, 30, 100, 150, 200, 300}));
}

TEST(binary_search_tree__methods, swap__empty_to_filled) {
	adt::binary_search_tree<int> bst1,
								 bst1_orig = bst1,
								 bst2 = {25, 20, 10, 22, 5, 12, 1, 8, 15},
								 bst2_orig = bst2;

	adt::binary_search_tree<int>* bst1_ptr = &bst1,
								* bst2_ptr = &bst2;
	
	bst1.swap(bst2);

	EXPECT_EQ(bst1_ptr, &bst1);
	EXPECT_EQ(bst2_ptr, &bst2);

	EXPECT_NE(&bst1, &bst2);

	EXPECT_EQ(bst1, bst2_orig);
	EXPECT_EQ(bst2, bst1_orig);

	EXPECT_EQ(bst1.size(), 9);
	EXPECT_FALSE(bst1.empty());

	EXPECT_EQ(bst2.size(), 0);
	EXPECT_TRUE(bst2.empty());

	EXPECT_EQ(bst1, std::initializer_list<int>({1, 5, 8, 10, 12, 15, 20, 22, 25}));
	EXPECT_EQ(bst2, std::initializer_list<int>());
}

TEST(binary_search_tree__methods, swap__filled_to_filled) {
	adt::binary_search_tree<int> bst1 = {100, 20, 10, 30, 200, 150, 300},
								 bst1_orig = bst1,
								 bst2 = {25, 20, 10, 22, 5, 12, 1, 8, 15},
								 bst2_orig = bst2;

	adt::binary_search_tree<int>* bst1_ptr = &bst1,
								* bst2_ptr = &bst2;
	
	bst1.swap(bst2);

	EXPECT_EQ(bst1_ptr, &bst1);
	EXPECT_EQ(bst2_ptr, &bst2);

	EXPECT_NE(&bst1, &bst2);

	EXPECT_EQ(bst1, bst2_orig);
	EXPECT_EQ(bst2, bst1_orig);

	EXPECT_EQ(bst1.size(), 9);
	EXPECT_FALSE(bst1.empty());

	EXPECT_EQ(bst2.size(), 7);
	EXPECT_FALSE(bst2.empty());

	EXPECT_EQ(bst1, std::initializer_list<int>({1, 5, 8, 10, 12, 15, 20, 22, 25}));
	EXPECT_EQ(bst2, std::initializer_list<int>({10, 20, 30, 100, 150, 200, 300}));
}

TEST(binary_search_tree__methods, extract__empty_bst) {
	adt::binary_search_tree<int> bst;
	adt::binary_search_tree<int>::node_type node;

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_NO_THROW(node = bst.extract(bst.cbegin()));

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_EQ(node, nullptr);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	EXPECT_TRUE(node.empty());
	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
}

TEST(binary_search_tree__methods, extract__single_node) {
	adt::binary_search_tree<int> bst = {101};
	adt::binary_search_tree<int>::node_type node;
	std::initializer_list<int> matcher;
	
	EXPECT_FALSE(bst.empty());
	EXPECT_EQ(bst.size(), 1);

	EXPECT_NO_THROW(node = bst.extract(bst.cbegin()));

	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);
	EXPECT_EQ(bst, matcher);

	EXPECT_NE(node, nullptr);
	EXPECT_FALSE(node.empty());

	EXPECT_EQ(*node, 101);
	EXPECT_EQ(node.value(), 101);
}

TEST(binary_search_tree__methods, extract__left_linked_list) {
	adt::binary_search_tree<int> bst = {5, 4, 3, 2, 1};
	adt::binary_search_tree<int>::node_type node;
	std::list<adt::binary_search_tree<int>::node_type> nodes;
	std::forward_list<int> values_matcher = {1, 2, 3, 4, 5};
	constexpr std::size_t values_size = 5;

	for (std::size_t i = 0; i < values_size; i++) {
		if (bst.size() == 0) {
			break;
		}

		EXPECT_EQ(bst.size(), values_size - i);
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(node = bst.extract(bst.cbegin()));

		EXPECT_FALSE(node.empty());
		EXPECT_NE(node, nullptr);

		EXPECT_EQ(node.value(), values_matcher.front());
		EXPECT_EQ(*node, values_matcher.front());

		values_matcher.pop_front();
		nodes.push_back(node);
	}

	node = bst.extract(bst.cbegin());
	
	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);

	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	for (std::size_t i = 0; i < values_size; i++) {
		node = nodes.front();
		nodes.pop_front();
		
		static_cast<void>(bst.insert(std::forward<decltype(node)>(node)));
	}

	EXPECT_EQ(bst, std::initializer_list<int>({1, 2, 3, 4, 5}));
	EXPECT_EQ(bst.size(), values_size);
	EXPECT_FALSE(bst.empty());
}

TEST(binary_search_tree__methods, extract__right_linked_list) {
	adt::binary_search_tree<int> bst = {1, 2, 3, 4, 5};
	adt::binary_search_tree<int>::node_type node;
	std::list<adt::binary_search_tree<int>::node_type> nodes;
	std::forward_list<int> values_matcher = {1, 2, 3, 4, 5};
	constexpr std::size_t values_size = 5;

	for (std::size_t i = 0; i < values_size; i++) {
		if (bst.size() == 0) {
			break;
		}

		EXPECT_EQ(bst.size(), values_size - i);
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(node = bst.extract(bst.cbegin()));

		EXPECT_FALSE(node.empty());
		EXPECT_NE(node, nullptr);

		EXPECT_EQ(node.value(), values_matcher.front());
		EXPECT_EQ(*node, values_matcher.front());

		values_matcher.pop_front();
		nodes.push_back(node);
	}

	node = bst.extract(bst.cbegin());
	
	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);

	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	for (std::size_t i = 0; i < values_size; i++) {
		node = nodes.front();
		nodes.pop_front();
		
		static_cast<void>(bst.insert(std::forward<decltype(node)>(node)));
	}

	EXPECT_EQ(bst, std::initializer_list<int>({1, 2, 3, 4, 5}));
	EXPECT_EQ(bst.size(), values_size);
	EXPECT_FALSE(bst.empty());
}

TEST(binary_search_tree__methods, extract__left_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 20, 10, 22, 5, 12, 1, 8, 15};
	adt::binary_search_tree<int>::node_type node;
	std::list<adt::binary_search_tree<int>::node_type> nodes;
	std::forward_list<int> values_matcher = {1, 5, 8, 10, 12, 15, 20, 22, 25};
	constexpr std::size_t values_size = 9;

	for (std::size_t i = 0; i < values_size; i++) {
		if (bst.size() == 0) {
			break;
		}

		EXPECT_EQ(bst.size(), values_size - i);
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(node = bst.extract(bst.cbegin()));

		EXPECT_FALSE(node.empty());
		EXPECT_NE(node, nullptr);

		EXPECT_EQ(node.value(), values_matcher.front());
		EXPECT_EQ(*node, values_matcher.front());

		values_matcher.pop_front();
		nodes.push_back(node);
	}

	node = bst.extract(bst.cbegin());
	
	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);

	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	for (std::size_t i = 0; i < values_size; i++) {
		node = nodes.front();
		nodes.pop_front();
		
		static_cast<void>(bst.insert(std::forward<decltype(node)>(node)));
	}

	EXPECT_EQ(bst, std::initializer_list<int>({1, 5, 8, 10, 12, 15, 20, 22, 25}));
	EXPECT_EQ(bst.size(), values_size);
	EXPECT_FALSE(bst.empty());
}

TEST(binary_search_tree__methods, extract__right_skewed_bst) {
	adt::binary_search_tree<int> bst = {25, 36, 30, 28, 40, 38, 48, 45, 50};
	adt::binary_search_tree<int>::node_type node;
	std::list<adt::binary_search_tree<int>::node_type> nodes;
	std::forward_list<int> values_matcher = {25, 28, 30, 36, 38, 40, 45, 48, 50};
	constexpr std::size_t values_size = 9;

	for (std::size_t i = 0; i < values_size; i++) {
		if (bst.size() == 0) {
			break;
		}

		EXPECT_EQ(bst.size(), values_size - i);
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(node = bst.extract(bst.cbegin()));

		EXPECT_FALSE(node.empty());
		EXPECT_NE(node, nullptr);

		EXPECT_EQ(node.value(), values_matcher.front());
		EXPECT_EQ(*node, values_matcher.front());

		values_matcher.pop_front();
		nodes.push_back(node);
	}

	node = bst.extract(bst.cbegin());
	
	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);

	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	for (std::size_t i = 0; i < values_size; i++) {
		node = nodes.front();
		nodes.pop_front();
		
		static_cast<void>(bst.insert(std::forward<decltype(node)>(node)));
	}

	EXPECT_EQ(bst, std::initializer_list<int>({25, 28, 30, 36, 38, 40, 45, 48, 50}));
	EXPECT_EQ(bst.size(), values_size);
	EXPECT_FALSE(bst.empty());
}

TEST(binary_search_tree__methods, extract__balanced_bst) {
	adt::binary_search_tree<int> bst = {100, 20, 10, 30, 200, 150, 300};
	adt::binary_search_tree<int>::node_type node;
	std::list<adt::binary_search_tree<int>::node_type> nodes;
	std::forward_list<int> values_matcher = {10, 20, 30, 100, 150, 200, 300};
	constexpr std::size_t values_size = 7;

	for (std::size_t i = 0; i < values_size; i++) {
		if (bst.size() == 0) {
			break;
		}

		EXPECT_EQ(bst.size(), values_size - i);
		EXPECT_FALSE(bst.empty());
		EXPECT_EQ(bst, values_matcher);

		EXPECT_NO_THROW(node = bst.extract(bst.cbegin()));

		EXPECT_FALSE(node.empty());
		EXPECT_NE(node, nullptr);

		EXPECT_EQ(node.value(), values_matcher.front());
		EXPECT_EQ(*node, values_matcher.front());

		values_matcher.pop_front();
		nodes.push_back(node);
	}

	node = bst.extract(bst.cbegin());
	
	EXPECT_TRUE(bst.empty());
	EXPECT_EQ(bst.size(), 0);

	EXPECT_TRUE(node.empty());
	EXPECT_EQ(node, nullptr);

	EXPECT_THROW(static_cast<void>(node.value()), std::runtime_error);
	EXPECT_THROW(static_cast<void>(*node), std::runtime_error);

	for (std::size_t i = 0; i < values_size; i++) {
		node = nodes.front();
		nodes.pop_front();
		
		static_cast<void>(bst.insert(std::forward<decltype(node)>(node)));
	}

	EXPECT_EQ(bst, std::initializer_list<int>({10, 20, 30, 100, 150, 200, 300}));
	EXPECT_EQ(bst.size(), values_size);
	EXPECT_FALSE(bst.empty());
}

TEST(binary_search_tree__methods, merge__lref__empty_into_empty) {
	adt::binary_search_tree<int> dst, src;
	std::initializer_list<int> matcher;

	dst.merge(src);

	EXPECT_TRUE(dst.empty());
	EXPECT_TRUE(src.empty());

	EXPECT_EQ(dst.size(), 0);
	EXPECT_EQ(src.size(), 0);

	EXPECT_EQ(dst, matcher);
	EXPECT_EQ(src, matcher);
}

TEST(binary_search_tree__methods, merge__lref__empty_into_filled) {
	adt::binary_search_tree<int> dst, src = {100, 20, 10, 30, 200, 150, 300};
	std::initializer_list<int> matcher_dst = {10, 20, 30, 100, 150, 200, 300}, 
							   matcher_src;

	dst.merge(src);

	EXPECT_FALSE(dst.empty());
	EXPECT_TRUE(src.empty());

	EXPECT_EQ(dst.size(), 7);
	EXPECT_EQ(src.size(), 0);

	EXPECT_EQ(dst, matcher_dst);
	EXPECT_EQ(src, matcher_src);
}

TEST(binary_search_tree__methods, merge__lref__filled_into_filled) {
	adt::binary_search_tree<int> dst = {100, 20, 10, 30, 200, 150, 300},
								 src = {101, 21, 11, 31, 201, 151, 301};
	std::initializer_list<int> matcher_dst = {10, 11, 20, 21, 30, 31, 100, 101, 150, 151, 200, 201, 300, 301}, 
							   matcher_src;

	dst.merge(src);

	EXPECT_FALSE(dst.empty());
	EXPECT_TRUE(src.empty());

	EXPECT_EQ(dst.size(), 14);
	EXPECT_EQ(src.size(), 0);

	EXPECT_EQ(dst, matcher_dst);
	EXPECT_EQ(src, matcher_src);
}

TEST(binary_search_tree__methods, merge__rref__empty_into_empty) {
	adt::binary_search_tree<int> dst, src;
	std::initializer_list<int> matcher;

	dst.merge(std::forward<adt::binary_search_tree<int>>(src));

	EXPECT_TRUE(dst.empty());
	EXPECT_TRUE(src.empty());

	EXPECT_EQ(dst.size(), 0);
	EXPECT_EQ(src.size(), 0);

	EXPECT_EQ(dst, matcher);
	EXPECT_EQ(src, matcher);
}

TEST(binary_search_tree__methods, merge__rref__empty_into_filled) {
	adt::binary_search_tree<int> dst, 
								&& src = {100, 20, 10, 30, 200, 150, 300};
	std::initializer_list<int> matcher_dst = {10, 20, 30, 100, 150, 200, 300}, 
							   matcher_src;

	dst.merge(std::forward<adt::binary_search_tree<int>>(src));

	EXPECT_FALSE(dst.empty());
	EXPECT_TRUE(src.empty());

	EXPECT_EQ(dst.size(), 7);
	EXPECT_EQ(src.size(), 0);

	EXPECT_EQ(dst, matcher_dst);
	EXPECT_EQ(src, matcher_src);
}

TEST(binary_search_tree__methods, merge__rref__filled_into_filled) {
	adt::binary_search_tree<int> dst = {100, 20, 10, 30, 200, 150, 300},
								&& src = {101, 21, 11, 31, 201, 151, 301};
	std::initializer_list<int> matcher_dst = {10, 11, 20, 21, 30, 31, 100, 101, 150, 151, 200, 201, 300, 301}, 
							   matcher_src;

	dst.merge(std::forward<adt::binary_search_tree<int>>(src));

	EXPECT_FALSE(dst.empty());
	EXPECT_TRUE(src.empty());

	EXPECT_EQ(dst.size(), 14);
	EXPECT_EQ(src.size(), 0);

	EXPECT_EQ(dst, matcher_dst);
	EXPECT_EQ(src, matcher_src);
}
