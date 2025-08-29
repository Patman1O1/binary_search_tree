//
// Created by Patrick Thomas on 07/04/2025
//

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <cstddef>
#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <ranges>
#include <compare>
#include <concepts>
#include <unordered_map> // FOR TESTING - REMOVE WHEN FINISHED

#include "binary_tree.hpp"


namespace adt {

    enum class bst_traversals { preorder, inorder, postorder };

    template<class T, class Allocator = std::allocator<T>>
    class binary_search_tree : public binary_tree<T, Allocator> {
    public:
        /* ----------------------------------------------Definitions------------------------------------------------ */
        using value_type = typename binary_tree<T, Allocator>::value_type;

        using allocator_type = typename binary_tree<T, Allocator>::allocator_type;

        using size_type = typename binary_tree<T, Allocator>::size_type;

        using difference_type = typename binary_tree<T, Allocator>::difference_type;

        using reference = typename binary_tree<T, Allocator>::reference;

        using const_reference = typename binary_tree<T, Allocator>::const_reference;

        using pointer = typename binary_tree<T, Allocator>::pointer;

        using const_pointer = typename binary_tree<T, Allocator>::const_pointer;

    protected:
        /* ----------------------------------------------Definitions------------------------------------------------ */
        using _Node = binary_tree<T, Allocator>::_Node;

        using _NodeAllocator = typename binary_tree<T, Allocator>::_NodeAllocator;

        using allocator_traits = typename binary_tree<T, Allocator>::allocator_traits;

        using node_allocator_traits = typename binary_tree<T, Allocator>::node_allocator_traits;

        /* ------------------------------------------------Fields--------------------------------------------------- */
        _Node* min_node;

        _Node* max_node;

        /* ------------------------------------------------Methods-------------------------------------------------- */
        static constexpr _Node* _find_target(const_reference value, _Node* curr) noexcept {
            // For each node in the BST that does not contain `value`...
            while (curr != nullptr && curr->value != value) {
                // If the current node's left child has a value larger than `value` or
                // the current node's right child has a value smaller than `value`...
                if ((curr->parent != nullptr) && 
                    ((curr == curr->parent->left && curr->parent->value < value) ||
                    (curr == curr->parent->right && curr->parent->value > value))) {
                    // Traverse back up the BST
                    curr = curr->parent;
                } else if (value < curr->value) {
                    // Otherwise, if `value` is less than the current node's value, then
                    // visit the current node's left child
                    curr = curr->left;
                } else if (value > curr->value) {
                    // Otherwise, if `value` is greater than the current node's value,
                    // then visit the current node's right child
                    curr = curr->right;
                }
            }

            return curr;
        }

        static constexpr _Node* _find_min(_Node* node) noexcept {
            if (node == nullptr) {
                return nullptr;
            }

            while (node->left != nullptr) {
                node = node->left;
            }

            return node;
        }

        static constexpr _Node* _find_max(_Node* node) noexcept {
            if (node == nullptr) {
                return nullptr;
            }

            while (node->right != nullptr) {
                node = node->right;
            }

            return node;
        }

        static constexpr _Node* _find_successor(_Node* node) noexcept {
            // If the node has NO right child...
            if (node->right == nullptr) {
                // Traverse up the BST until the inorder successor is found
                while (node->parent != nullptr && node == node->right) {
                    node = node->parent;
                }
                return node->parent;
            }

            // Otherwise, keep traversing the right node's left subtree 
            // until the leftmost leaf (inorder successor) is found
            node = node->right;
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        static constexpr _Node* _preorder_forward_traverse(_Node* node) noexcept {
            if (node == nullptr) {
                return nullptr;
            }

            // If the current node has a *left* child
            if (node->left != nullptr) {
                // Return the *left* child
                return node->left;
            }

            // If the current node has a *right* child
            if (node->right != nullptr) {
                // Return the *right* child
                return node->right;
            }

            // While the current node has a parent...
            while (node->parent != nullptr) {
                // If the current node's has a *right* sibling...
                if (node == node->parent->left && node->parent->right != nullptr) {
                    // Return the *right* sibling
                    return node->parent->right;
                }

                // Continue up the BST
                node = node->parent;
            }

            // Return nullptr to signify the end of the BST
            return nullptr;
        }

        static constexpr _Node* _inorder_forward_traverse(_Node* node) noexcept {
            if (node == nullptr) {
                return nullptr;
            }
            
            // If the current node has a *right* child...
            if (node->right != nullptr) {
                // Go to the *right* child's leftmost node
                node = node->right;
                while (node->left != nullptr) {
                    node = node->left;
                }
                return node;
            }
            
            // Otherwise, go up the BST from it's right subtree until we 
            // find a parent where we came from the left
            while (node->parent != nullptr && node == node->parent->right) {
                node = node->parent;
            }
            
            return node->parent;
        }
        
        static constexpr _Node* _postorder_forward_traverse(_Node* node) noexcept {
            if (node == nullptr) {
                return nullptr;
            }

            // If a *left* child has just been visited and that child has a *right* sibling...
            if (node->parent != nullptr && node == node->parent->left && node->parent->right != nullptr) {
                // Go to the *right* sibling's leftmost node
                node = node->parent->right;
                while (node->left != nullptr || node->right != nullptr) {
                    node = (node->left != nullptr) ? node->left : node->right;
                }
                return node;
            }
                
            // Otherwise, go up the BST after both subtrees have been visited
            return node->parent;
        }

        static constexpr _Node* _preorder_backward_traverse(_Node* node) noexcept {
            if (node == nullptr) {
                return nullptr;
            }

            // If the current node has a *left* sibling...
            if (node->parent != nullptr && node == node->parent->right && node->parent->left != nullptr) {
                node = node->parent->left;

                // While the current node has a child (left or right)...
                while (node->right != nullptr || node->left != nullptr) {
                    // Go to the current node's child
                    node = (node->right != nullptr) ? node->right : node->left;
                }
                return node;
            }

            return node->parent;
        }

        static constexpr _Node* _inorder_backward_traverse(_Node* node) noexcept {
            if (node == nullptr) {
                return nullptr;
            }
            
            // If the current node has a *left* child...
            if (node->left != nullptr) {
                // Go to the *left* child's rightmost node
                node = node->left;
                while (node->right != nullptr) {
                    node = node->right;
                }
                return node;
            }
            
            // Otherwise, go up the BST from it's left subtree until we 
            // find a parent where we came from the right
            while (node->parent != nullptr && node == node->parent->left) {
                node = node->parent;
            }
            
            return node->parent;
        }

        static constexpr _Node* _postorder_backward_traverse(_Node* node) noexcept {
            if (node == nullptr) {
                return nullptr;
            }

            // If the current node has a *right* child...
            if (node->right != nullptr) {
                // Return the *right* child
                return node->right;
            }

            // If the current node has a *left* child...
            if (node->left != nullptr) {
                // Return the *left* child
                return node->left;
            }

            // While the current has a parent...
            while (node->parent != nullptr) {
                // If the current node has *left* sibling...
                if (node == node->parent->right && node->parent->left != nullptr) {
                    // Return the *left* sibling
                    return node->parent->left;
                }

                // Go to the current node's parent
                node = node->parent;
            }
                
            // Otherwise, go up the BST after both subtrees have been visited
            return node->parent;
        }

        [[nodiscard]] constexpr _Node* _get_preorder_end_node() const noexcept {
            if (this->root == nullptr) {
                return nullptr;
            }

            // If the root node has a *right* subtree...
            if (this->root != this->max_node) {
                // Return the maximum node as the preorder end node
                return this->max_node;
            }

            // Otherwise, perform a reverse preorder traversal where 
            // the *right* node is visited before the *left* node
            _Node* curr = this->root;
            while (curr->left != nullptr || curr->right != nullptr) {
                // If the current node has a *left* child...
                if (curr->right == nullptr) {
                    // Visit the *left* child
                    curr = curr->left;
                    continue;
                }

                // Otherwise, visit the *right* child
                curr = curr->right;
            }

            // Return the preorder end node
            return curr;
        }

        [[nodiscard]] constexpr _Node* _get_postorder_start_node() const noexcept {
            if (this->root == nullptr) {
                return nullptr;
            }

            // If the root node has a *left* subtree
            if (this->root != this->min_node) {
                // Return the minimum node
                return this->min_node;
            }

            // Otherwise, perform a postorder traversal to find the postorder starting node
            _Node* curr = this->root;
            while (curr->left != nullptr || curr->right != nullptr) {
                // If the current node a *right* child...
                if (curr->left == nullptr) {
                    // Visit the *right* child
                    curr = curr->right;
                    continue;
                }

                // Otherwise, visit the *left* child
                curr = curr->left;
            }

            return curr;
        }

        constexpr void _transplant(_Node* const dst, _Node* const src) noexcept {
            // If the destination node is the root node...
            if (dst->parent == nullptr) {
                // Transplant the source node into the root node
                this->root = src;
            } else if (dst == dst->parent->left) {
                // Otherwise, if the destination node is a left child, then use it's parent
                // to transplant the source node
                dst->parent->left = src;
            } else {
                // Otherwise, if the destination node is a right child, then use it's parent
                // to transplant the source node
                dst->parent->right = src;
            }

            // Connect the source node to the destination node if the source node is not empty
            if (src != nullptr) {
                src->parent = dst->parent;
            }
        }

        constexpr std::pair<_Node*, bool> _insert(const_reference value, _Node** p_curr = nullptr) noexcept {
            _Node* prev = nullptr;

            // If the address of the current node points to nullptr...
            if (p_curr == nullptr || *p_curr == nullptr) {
                // Assign the address of the current node to the root node
                p_curr = &this->root;
            } else if (*p_curr != this->root) {
                // Otherwise, if the current node is not the root node, 
                // then assign `prev` to the current node's parent
                prev = (*p_curr)->parent;
            }

            // For each node in the BST...
            while (*p_curr != nullptr) {
                // If the current node is NOT the root node and the current node is a left child and 
                // has a parent with a value less than `value`, or the current node is a right child
                // and has a parent with a value greater than `value`...
                if ((*p_curr != this->root) && 
                    ((*p_curr == (*p_curr)->parent->left && (*p_curr)->parent->value < value) ||
                    (*p_curr == (*p_curr)->parent->right && (*p_curr)->parent->value > value))) {
                    // Traverse back up the BST
                    p_curr = &(*p_curr)->parent;
                } else if (value < (*p_curr)->value) {
                    // Otherwise, if `value` is less than the current node's value, then
                    // visit the current node's left child
                    prev = *p_curr;
                    p_curr = &(*p_curr)->left;
                } else if (value > (*p_curr)->value) {
                    // Otherwise, if `value` is greater than the current node's value,
                    // then visit the current node's right child
                    prev = *p_curr;
                    p_curr = &(*p_curr)->right;
                } else {
                    // Otherwise, return the current node and a boolean set to false
                    return std::make_pair(*p_curr, false);
                }
            }

            // Create a new node at the current node
            *p_curr = this->_construct_node(value, prev, nullptr, nullptr, 0);

            // If the node being inserted is the root...
            if (prev == nullptr) {
                // Point the minimum and maximum nodes to the current node
                this->min_node = this->max_node = *p_curr;
            } else if (value < this->min_node->value) {
                // Otherwise, if `value` is less than the current minimum value in the BST,
                // then point the minimum node to the current node
                this->min_node = *p_curr;
            } else if (value > this->max_node->value) {
                // Otherwise, if `value` is greater than the current maximum value in the BST 
                // (i.e `inorder_end`'s value), then point the maximum node to the current
                // node
                this->max_node = *p_curr;
            }

            // Update the BST size
            this->sz++;

            return std::make_pair(*p_curr, true);
        }

        constexpr _Node* _remove(_Node*& target) noexcept {
            if (target == nullptr) {
                return nullptr;
            }

            _Node* successor;

            if (target->left != nullptr) {
                if (target->right != nullptr) { // Case 1: Both Children
                    // Find inorder successor to the current node's right child
                    _Node* replacement = _find_min(target->right);

                    // Find the inorder successor to the replacement node
                    successor = _find_successor(replacement);

                    // If the current node's right child is not the replacement node...
                    if (target != replacement->parent) {
                        // Move the current node to the replacement's right child
                        this->_transplant(replacement, replacement->right);
                        replacement->right = target->right;
                        replacement->right->parent = replacement;
                    }
                    
                    this->_transplant(target, replacement);
                    replacement->left = target->left;
                    replacement->left->parent = replacement;
                } else { // Case 2: Single Child (Left)
                    // Find the inorder successor to the current node
                    successor = _find_successor(target);

                    // Transplant the current node's left child into itself
                    this->_transplant(target, target->left);
                }
            } else { 
                if (target->right != nullptr) { // Case 3: Single Child (Right)
                    // Find the inorder successor to the current node
                    successor = _find_successor(target);

                    // Transplant the current node's right child into itself
                    this->_transplant(target, target->right);
                } else { // Case 4: No Children
                    // Find the inorder successor to the current node
                    successor = _find_successor(target);

                    // Transplant nullptr into the current node
                    this->_transplant(target, nullptr);
                }
            }

            /* Need to optimize this */
            this->min_node = this->_find_min(this->root);
            this->max_node = this->_find_max(this->root);

            this->sz--;

            return successor;
        }

        constexpr _Node* _erase(_Node* target) noexcept {
            _Node* successor = this->_remove(target);
            this->_destroy_node(target);

            return successor;
        }

        constexpr void _clear() noexcept {
            _Node* curr = this->root;

            while (curr != nullptr) {
                // If the current node is a leaf...
                if (curr->left == nullptr && curr->right == nullptr) {
                    // Delete the current node and point it's address to it's parent node
                    curr = this->_destroy_node(curr);
                } else if (curr->left != nullptr) {
                    // Otherwise, if the current node has a left child, then visit the left child
                    curr = curr->left;
                } else {
                    // Otherwise, visit the right child
                    curr = curr->right;
                }
            }

            this->root = this->min_node = this->max_node = nullptr;
            this->sz = 0;
        }

        constexpr _Node* _copy(_Node* dst_node, _Node* dst_parent, const _Node* src_node, 
                               const binary_search_tree& src) noexcept {
            // Base case
            if (src_node == nullptr) {
                return nullptr;
            }

            // Copy the current node from the source BST
            dst_node = this->_construct_node(src_node->value, dst_parent, nullptr, nullptr, src_node->height);

            // If the current node from the source BST is in the only node...
            if (src_node->parent == nullptr && src_node->left == nullptr && src_node->right == nullptr) {
                // Point the destination BST's  minimum and maximum nodes to that node's copy
                // (i.e. `dst_node`)
                this->min_node = this->max_node = dst_node;
            } else if (src_node == src.max_node) {
                // Otherwise, if the current node from the source BST is the maximum node,
                // then point the destination BST's maximum node to that node's copy
                // (i.e. `dst_node`)
                this->max_node = dst_node;
            } else if (src_node == src.min_node) {
                // Otherwise, if the current node from the source BST is the minimum node,
                // then point the destination BST's minimum node to that node's copy
                // (i.e. `dst_node`)
                this->min_node = dst_node;
            }
           
            // Continue copying the rest of the source BST
            dst_node->left = this->_copy(dst_node->left, dst_node, src_node->left, src);
            dst_node->right = this->_copy(dst_node->right, dst_node, src_node->right, src);

            return dst_node;
        }

        constexpr void _move(binary_search_tree& other) noexcept {
            // If the other BST is empty...
            if (other.root == nullptr) {
                // Point this BST's root, min, and max nodes to nullptr and set the size to 0
                this->root = this->min_node = this->max_node = nullptr;
                this->sz = 0;
                return;
            }

            // Otherwise...

            // Move the root
            this->root = other.root;
            other.root = nullptr;

            // Move the min node
            this->min_node = other.min_node;
            other.min_node = nullptr;

            // Move the max node
            this->max_node = other.max_node;
            other.max_node = nullptr;

            // Update the size
            this->sz = other.sz;
            other.sz = 0;
        }

        constexpr void _merge(binary_search_tree& other) noexcept {
            while (other.root != nullptr) {
                this->_insert(other.root->value);
                other._erase(other.root);
            }
        }

        // FOR TESTING - REMOVE WHEN FINISHED
        constexpr void _print_adjacent_list(_Node* curr) const noexcept {
            if (curr == nullptr) {
                return;
            }

            std::cout << curr->value << " -> {";
            if (curr->left != nullptr) {
                std::cout << curr->left->value;
                if (curr->right != nullptr) {
                    std::cout << ", " << curr->right->value;
                } else {
                    std::cout << ", null";
                }
            } else {
                if (curr->right != nullptr) {
                    std::cout << "null, " << curr->right->value;
                } else {
                    std::cout << "null, null";
                }
            }
            std::cout << "}\n";

            this->_print_adjacent_list(curr->left);
            this->_print_adjacent_list(curr->right);
        } 

    public:
        /* -------------------------------------------Constant Iterator--------------------------------------------- */
        class const_iterator : public binary_tree<T, Allocator>::const_iterator {
        private:
            /* --------------------------------------------Friends-------------------------------------------------- */
            friend class binary_search_tree;

        protected:
            /* ---------------------------------------------Fields-------------------------------------------------- */
            bst_traversals traversal;

            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr const_iterator(const _Node* const& node) noexcept 
                : binary_tree<T, Allocator>::const_iterator(node) {}

        public:
            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr const_iterator() noexcept : binary_tree<T, Allocator>::const_iterator() {
                this->traversal = bst_traversals::inorder;
            }
            
            constexpr explicit const_iterator(std::nullptr_t) noexcept 
                : binary_tree<T, Allocator>::const_iterator(nullptr) { this->traversal = bst_traversals::inorder; }

            constexpr explicit const_iterator(const binary_search_tree& tree) noexcept 
                : binary_tree<T, Allocator>::const_iterator(tree.min_node) {
                this->traversal = bst_traversals::inorder;
            }

            constexpr explicit const_iterator(bst_traversals traversal) noexcept 
                : binary_tree<T, Allocator>::const_iterator() { this->traversal = traversal; }

            constexpr const_iterator(const binary_search_tree& tree, bst_traversals traversal) noexcept 
                : binary_tree<T, Allocator>::const_iterator(tree) {
                this->traversal = traversal;

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = tree.root;
                        break;
                    case bst_traversals::inorder:
                        this->node = tree.min_node;
                        break;
                    case bst_traversals::postorder:
                        this->node = const_cast<_Node*>(tree._get_postorder_start_node());
                        break;
                }
            }
            
            constexpr const_iterator(const const_iterator& other) noexcept
                : binary_tree<T, Allocator>::const_iterator(other) { this->traversal = other.traversal; }

            constexpr const_iterator(const_iterator&& other) noexcept 
                : binary_tree<T, Allocator>::const_iterator(other) { this->traversal = other.traversal; }

            /* -------------------------------------------Destructor------------------------------------------------ */
            constexpr ~const_iterator() noexcept = default;

            /* ---------------------------------------Overloaded Operators------------------------------------------ */
            constexpr const_iterator& operator=(const const_iterator&) noexcept = default;

            constexpr const_iterator& operator=(const_iterator&&) noexcept = default;

            constexpr const_iterator& operator=(std::nullptr_t) noexcept {
                this->node = nullptr;
                return *this;
            }

            [[nodiscard]] constexpr bool operator==(const const_iterator& rhs) const noexcept {
                return this->node == rhs.node;
            }

            [[nodiscard]] constexpr bool operator==(const_iterator&& rhs) const noexcept {
                return this->node == rhs.node;
            }

            [[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return this->node == nullptr; }

            [[nodiscard]] constexpr auto operator<=>(const const_iterator& rhs) const noexcept {
                return this->node <=> rhs.node;
            }

            [[nodiscard]] constexpr auto operator<=>(const_iterator&& rhs) const noexcept {
                return this->node <=> rhs.node;
            }

            [[nodiscard]] constexpr auto operator<=>(std::nullptr_t) const noexcept { return this->node <=> nullptr; }

            const_iterator& operator++() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = _preorder_forward_traverse(const_cast<_Node*>(this->node));
                        break;
                    
                    case bst_traversals::inorder:
                        this->node = _inorder_forward_traverse(const_cast<_Node*>(this->node));
                        break;

                    case bst_traversals::postorder:
                        this->node = _postorder_forward_traverse(const_cast<_Node*>(this->node));
                        break;
                }

                return *this;
            }

            const_iterator operator++(int) {
                const_iterator temp = *this;
                ++(*this);
                return temp;
            }

            const_iterator operator+(size_type n) {
                const_iterator result(*this);

                // Return the iterator at it's current position if n is 0
                if (n == 0) {
                    return result;
                }

                switch (result.traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _preorder_forward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _inorder_forward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _postorder_forward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                }

                return result;
            }

            const_iterator& operator+=(size_type n) {
                // Return the iterator at the current position if n is 0
                if (n == 0) {
                    return *this;
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _preorder_forward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _inorder_forward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _postorder_forward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                }

                return *this;
            }

            const_iterator& operator--() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = binary_search_tree::_preorder_backward_traverse(const_cast<_Node*>(this->node));
                        break;
                    
                    case bst_traversals::inorder:
                        this->node = binary_search_tree::_inorder_backward_traverse(const_cast<_Node*>(this->node));
                        break;

                    case bst_traversals::postorder:
                        this->node = binary_search_tree::_postorder_backward_traverse(const_cast<_Node*>(this->node));
                        break;
                }

                return *this;
            }

            const_iterator operator--(int) {
                const_iterator temp = *this;
                --(*this);
                return temp;
            }

            const_iterator operator-(size_type n) {
                const_iterator result(*this);

                // Return the iterator at it's current position if n is 0
                if (n == 0) {
                    return result;
                }

                switch (result.traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _preorder_backward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _inorder_backward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _postorder_backward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                }

                return result;
            }

            const_iterator& operator-=(size_type n) {
                // Return the iterator at the current position if n is 0
                if (n == 0) {
                    return *this;
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _preorder_backward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _inorder_backward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _postorder_backward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                }

                return *this;
            }

            /* ---------------------------------------------Methods------------------------------------------------- */
            [[nodiscard]] constexpr bst_traversals get_traversal() const noexcept { return this->traversal; }

        };

        /* -----------------------------------------------Iterator-------------------------------------------------- */
        class iterator : public binary_tree<T, Allocator>::iterator {
        private:
            /* --------------------------------------------Friends-------------------------------------------------- */
            friend class binary_search_tree;

        protected:
            /* ---------------------------------------------Fields-------------------------------------------------- */
            bst_traversals traversal;

            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr iterator(_Node* const& node) noexcept : binary_tree<T, Allocator>::iterator(node) {}

        public:
            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr iterator() noexcept : binary_tree<T, Allocator>::iterator() {
                this->traversal = bst_traversals::inorder;
            }

            constexpr explicit iterator(std::nullptr_t) noexcept : binary_tree<T, Allocator>::iterator(nullptr) {
                this->traversal = bst_traversals::inorder;
            }

            constexpr explicit iterator(const binary_search_tree& tree) noexcept 
                : binary_tree<T, Allocator>::iterator(tree.min_node) {
                this->traversal = bst_traversals::inorder;
            }

            constexpr explicit iterator(bst_traversals traversal) noexcept : binary_tree<T, Allocator>::iterator() {
                this->traversal = traversal;
            }

            constexpr iterator(const binary_search_tree& tree, bst_traversals traversal) noexcept 
                : binary_tree<T, Allocator>::iterator(tree.min_node) {
                this->traversal = traversal;
                
                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = tree.root;
                        break;
                    case bst_traversals::inorder:
                        this->node = tree.min_node;
                        break;
                    case bst_traversals::postorder:
                        this->node = tree._get_postorder_start_node();
                        break;
                }
            }
            
            constexpr iterator(const iterator& other) noexcept : binary_tree<T, Allocator>::iterator(other) {
                this->traversal = other.traversal;
            }

            constexpr iterator(iterator&& other) noexcept : binary_tree<T, Allocator>::iterator(other) {
                this->traversal = other.traversal;
            }

            /* -------------------------------------------Destructor------------------------------------------------ */
            constexpr ~iterator() noexcept = default;

            /* ---------------------------------------Overloaded Operators------------------------------------------ */
            constexpr iterator& operator=(const iterator&) noexcept = default;

            constexpr iterator& operator=(iterator&&) noexcept = default;

            constexpr iterator& operator=(std::nullptr_t) noexcept {
                this->node = nullptr;
                return *this;
            }

            [[nodiscard]] constexpr bool operator==(const iterator& rhs) const noexcept {
                return this->node == rhs.node;
            }

            [[nodiscard]] constexpr bool operator==(iterator&& rhs) const noexcept { return this->node == rhs.node; }

            [[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return this->node == nullptr; }

            [[nodiscard]] constexpr auto operator<=>(const iterator& rhs) const noexcept {
                return this->node <=> rhs.node;
            }

            [[nodiscard]] constexpr auto operator<=>(iterator&& rhs) const noexcept {return this->node <=> rhs.node; }

            [[nodiscard]] constexpr auto operator<=>(std::nullptr_t) const noexcept { return this->node <=> nullptr; }

            iterator& operator++() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = _preorder_forward_traverse(this->node);
                        break;
                    
                    case bst_traversals::inorder:
                        this->node = _inorder_forward_traverse(this->node);
                        break;

                    case bst_traversals::postorder:
                        this->node = _postorder_forward_traverse(this->node);
                        break;
                }

                return *this;
            }

            iterator operator++(int) {
                iterator temp = *this;
                ++(*this);
                return temp;
            }

            iterator operator+(size_type n) {
                iterator result(*this);

                // Return the iterator at it's current position if n is 0
                if (n == 0) {
                    return result;
                }

                switch (result.traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _preorder_forward_traverse(result.node);
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _inorder_forward_traverse(result.node);
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _postorder_forward_traverse(result.node);
                        }
                        break;
                }

                return result;
            }

            iterator& operator+=(size_type n) {
                // Return the iterator at the current position if n is 0
                if (n == 0) {
                    return *this;
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _preorder_forward_traverse(this->node);
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _inorder_forward_traverse(this->node);
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _postorder_forward_traverse(this->node);
                        }
                        break;
                }

                return *this;
            }

            iterator& operator--() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = _preorder_backward_traverse(this->node);
                        break;
                    
                    case bst_traversals::inorder:
                        this->node = _inorder_backward_traverse(this->node);
                        break;

                    case bst_traversals::postorder:
                        this->node = _postorder_backward_traverse(this->node);
                        break;
                }

                return *this;
            }

            iterator operator--(int) {
                iterator temp = *this;
                --(*this);
                return temp;
            }

            iterator operator-(size_type n) {
                iterator result(*this);

                // Return the iterator at it's current position if n is 0
                if (n == 0) {
                    return result;
                }

                switch (result.traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _preorder_backward_traverse(result.node);
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _inorder_backward_traverse(result.node);
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _postorder_backward_traverse(result.node);
                        }
                        break;
                }

                return result;
            }

            iterator& operator-=(size_type n) {
                // Return the iterator at the current position if n is 0
                if (n == 0) {
                    return *this;
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _preorder_backward_traverse(this->node);
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _inorder_backward_traverse(this->node);
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _postorder_backward_traverse(this->node);
                        }
                        break;
                }

                return *this;
            }
            
            [[nodiscard]] constexpr operator const_iterator() const noexcept {
                return const_iterator(this->node);
            }

            /* ---------------------------------------------Methods------------------------------------------------- */
            [[nodiscard]] constexpr bst_traversals get_traversal() const noexcept { return this->traversal; }
        
        };

        /* ---------------------------------------Constant Reverse Iterator----------------------------------------- */
        class const_reverse_iterator : public binary_tree<T, Allocator>::const_reverse_iterator {
        private:
            /* --------------------------------------------Friends-------------------------------------------------- */
            friend class binary_search_tree;

        protected:
            /* ---------------------------------------------Fields-------------------------------------------------- */
            bst_traversals traversal;

            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr const_reverse_iterator(const _Node* const& node) noexcept 
                : binary_tree<T, Allocator>::const_reverse_iterator(node) {}

        public:
            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr const_reverse_iterator() noexcept : binary_tree<T, Allocator>::const_reverse_iterator() {
                this->traversal = bst_traversals::inorder;
            }

            constexpr explicit const_reverse_iterator(std::nullptr_t) noexcept 
                : binary_tree<T, Allocator>::const_reverse_iterator(nullptr) {
                this->traversal = bst_traversals::inorder;
            }

            constexpr explicit const_reverse_iterator(const binary_search_tree& tree) noexcept
                : binary_tree<T, Allocator>::const_reverse_iterator(tree.max_node) {
                this->traversal = bst_traversals::inorder;
            }

            constexpr explicit const_reverse_iterator(bst_traversals traversal) noexcept 
                : binary_tree<T, Allocator>::const_reverse_iterator() { this->traversal = traversal; }

            constexpr const_reverse_iterator(const binary_search_tree& tree, bst_traversals traversal) noexcept
                : binary_tree<T, Allocator>::const_reverse_iterator(tree) {
                this->traversal = traversal;

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = tree._get_preorder_end_node();
                        break;

                    case bst_traversals::inorder:
                        this->node = tree.max_node;
                        break;

                    case bst_traversals::postorder:
                        this->node = tree.root;
                        break;
                }
            }
            
            constexpr const_reverse_iterator(const const_reverse_iterator& other) noexcept
                : binary_tree<T, Allocator>::const_reverse_iterator(other) { this->traversal = other.traversal; }

            constexpr const_reverse_iterator(const_reverse_iterator&& other) noexcept
                : binary_tree<T, Allocator>::const_reverse_iterator(other) { this->traversal = other.traversal; }

            /* ------------------------------------------Destructor------------------------------------------------- */
            constexpr ~const_reverse_iterator() noexcept = default;

            /* -------------------------------------Overloaded Operators-------------------------------------------- */
            constexpr const_reverse_iterator& operator=(const const_reverse_iterator&) noexcept = default;

            constexpr const_reverse_iterator& operator=(const_reverse_iterator&&) noexcept = default;

            constexpr const_reverse_iterator& operator=(std::nullptr_t) noexcept {
                this->node = nullptr;
                return *this;
            }

            [[nodiscard]] constexpr bool operator==(const const_reverse_iterator&) const noexcept = default;

            [[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return this->node == nullptr; }

            [[nodiscard]] constexpr auto operator<=>(const const_reverse_iterator&) const noexcept = default;

            [[nodiscard]] constexpr auto operator<=>(std::nullptr_t) const noexcept { return this->node <=> nullptr; }

            const_reverse_iterator& operator++() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = _preorder_backward_traverse(const_cast<_Node*>(this->node));
                        break;
                    
                    case bst_traversals::inorder:
                        this->node = _inorder_backward_traverse(const_cast<_Node*>(this->node));
                        break;

                    case bst_traversals::postorder:
                        this->node = _postorder_backward_traverse(const_cast<_Node*>(this->node));
                        break;
                }

                return *this;
            }

            const_reverse_iterator operator++(int) {
                const_reverse_iterator temp = *this;
                ++(*this);
                return temp;
            }

            const_reverse_iterator operator+(size_type n) {
                const_reverse_iterator result(*this);

                // Return the iterator at it's current position if n is 0
                if (n == 0) {
                    return result;
                }

                switch (result.traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _preorder_backward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _inorder_backward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _postorder_backward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                }

                return result;
            }

            const_reverse_iterator& operator+=(size_type n) {
                // Return the iterator at the current position if n is 0
                if (n == 0) {
                    return *this;
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _preorder_backward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _inorder_backward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _postorder_backward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                }

                return *this;
            }

            const_reverse_iterator& operator--() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = _preorder_forward_traverse(const_cast<_Node*>(this->node));
                        break;
                    
                    case bst_traversals::inorder:
                        this->node = _inorder_forward_traverse(const_cast<_Node*>(this->node));
                        break;

                    case bst_traversals::postorder:
                        this->node = _postorder_forward_traverse(const_cast<_Node*>(this->node));
                        break;
                }

                return *this;
            }

            const_reverse_iterator operator--(int) {
                const_reverse_iterator temp = *this;
                --(*this);
                return temp;
            }

            const_reverse_iterator operator-(size_type n) {
                const_reverse_iterator result(*this);

                // Return the iterator at it's current position if n is 0
                if (n == 0) {
                    return result;
                }

                switch (result.traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _preorder_forward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _inorder_forward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _postorder_forward_traverse(const_cast<_Node*>(result.node));
                        }
                        break;
                }

                return result;
            }

            const_reverse_iterator& operator-=(size_type n) {
                // Return the iterator at the current position if n is 0
                if (n == 0) {
                    return *this;
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _preorder_forward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _inorder_forward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _postorder_forward_traverse(const_cast<_Node*>(this->node));
                        }
                        break;
                }

                return *this;
            }
            
            /* ---------------------------------------------Methods------------------------------------------------- */
            [[nodiscard]] constexpr bst_traversals get_traversal() const noexcept { return this->traversal; }
        
        };

        /* -------------------------------------------Reverse Iterator---------------------------------------------- */
        class reverse_iterator : public binary_tree<T, Allocator>::reverse_iterator {
        private:
            /* --------------------------------------------Friends-------------------------------------------------- */
            friend class binary_search_tree;

        protected:
            /* --------------------------------------------Fields--------------------------------------------------- */
            bst_traversals traversal;

            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr reverse_iterator(_Node* const& node) noexcept 
                : binary_tree<T, Allocator>::reverse_iterator(node) {}

        public:
            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr reverse_iterator() noexcept : binary_tree<T, Allocator>::reverse_iterator() {
                this->traversal = bst_traversals::inorder;
            }

            constexpr explicit reverse_iterator(std::nullptr_t) noexcept
                : binary_tree<T, Allocator>::reverse_iterator(nullptr) { this->traversal = bst_traversals::inorder; }

            constexpr explicit reverse_iterator(const binary_search_tree& tree) noexcept
                : binary_tree<T, Allocator>::reverse_iterator(tree.max_node) {
                    this->traversal = bst_traversals::inorder;
                }

            constexpr explicit reverse_iterator(bst_traversals traversal) noexcept
                : binary_tree<T, Allocator>::reverse_iterator() { this->traversal = traversal; }

            constexpr reverse_iterator(const binary_search_tree& tree, bst_traversals traversal) noexcept
                : binary_tree<T, Allocator>::reverse_iterator(tree) {
		        this->traversal = traversal;

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = tree._get_preorder_end_node();
                        break;

                    case bst_traversals::inorder:
                        this->node = tree.max_node;
                        break;

                    case bst_traversals::postorder:
                        this->node = tree.root;
                        break;
                }
            }
            
            constexpr reverse_iterator(const reverse_iterator& other) noexcept 
                : binary_tree<T, Allocator>::reverse_iterator(other) { this->traversal = other.traversal; }

            constexpr reverse_iterator(reverse_iterator&& other) noexcept
                : binary_tree<T, Allocator>::reverse_iterator(other) { this->traversal = other.traversal; }

            /* ------------------------------------------Destructor------------------------------------------------- */
            constexpr ~reverse_iterator() noexcept = default;

            /* -------------------------------------Overloaded Operators-------------------------------------------- */
            constexpr reverse_iterator& operator=(const reverse_iterator&) noexcept = default;

            constexpr reverse_iterator& operator=(reverse_iterator&&) noexcept = default;

            constexpr reverse_iterator& operator=(std::nullptr_t) noexcept {
                this->node = nullptr;
                return *this;
            }

            [[nodiscard]] constexpr bool operator==(const reverse_iterator&) const noexcept = default;

            [[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return this->node == nullptr; }

            [[nodiscard]] constexpr auto operator<=>(const reverse_iterator&) const noexcept = default;

            [[nodiscard]] constexpr auto operator<=>(std::nullptr_t) const noexcept { return this->node <=> nullptr; }

            reverse_iterator& operator++() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = _preorder_backward_traverse(this->node);
                        break;
                    
                    case bst_traversals::inorder:
                        this->node = _inorder_backward_traverse(this->node);
                        break;

                    case bst_traversals::postorder:
                        this->node = _postorder_backward_traverse(this->node);
                        break;
                }

                return *this;
            }

            reverse_iterator operator++(int) {
                reverse_iterator temp = *this;
                ++(*this);
                return temp;
            }

            reverse_iterator operator+(size_type n) {
                reverse_iterator result(*this);

                // Return the iterator at it's current position if n is 0
                if (n == 0) {
                    return result;
                }

                switch (result.traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _preorder_backward_traverse(result.node);
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _inorder_backward_traverse(result.node);
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _postorder_backward_traverse(result.node);
                        }
                        break;
                }

                return result;
            }

            reverse_iterator& operator+=(size_type n) {
                // Return the iterator at the current position if n is 0
                if (n == 0) {
                    return *this;
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _preorder_backward_traverse(this->node);
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _inorder_backward_traverse(this->node);
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _postorder_backward_traverse(this->node);
                        }
                        break;
                }

                return *this;
            }

            reverse_iterator& operator--() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        this->node = _preorder_forward_traverse(this->node);
                        break;
                    
                    case bst_traversals::inorder:
                        this->node = _inorder_forward_traverse(this->node);
                        break;

                    case bst_traversals::postorder:
                        this->node = _postorder_forward_traverse(this->node);
                        break;
                }

                return *this;
            }

            reverse_iterator operator--(int) {
                reverse_iterator temp = *this;
                --(*this);
                return temp;
            }

            reverse_iterator operator-(size_type n) {
                reverse_iterator result(*this);

                // Return the iterator at it's current position if n is 0
                if (n == 0) {
                    return result;
                }

                switch (result.traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _preorder_forward_traverse(result.node);
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _inorder_forward_traverse(result.node);
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (result.node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            result.node = _postorder_forward_traverse(result.node);
                        }
                        break;
                }

                return result;
            }

            reverse_iterator& operator-=(size_type n) {
                // Return the iterator at the current position if n is 0
                if (n == 0) {
                    return *this;
                }

                switch (this->traversal) {
                    case bst_traversals::preorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _preorder_forward_traverse(this->node);
                        }
                        break;
                    case bst_traversals::inorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _inorder_forward_traverse(this->node);
                        }
                        break;
                    case bst_traversals::postorder:
                        for (size_type i = 0; i < n; i++) {
                            if (this->node == nullptr) {
                                throw std::runtime_error("segmentation fault");
                            }
                            this->node = _postorder_forward_traverse(this->node);
                        }
                        break;
                }

                return *this;
            }
        
            [[nodiscard]] constexpr operator const_reverse_iterator() const noexcept {
                return const_reverse_iterator(std::forward<_Node*>(this->node));
            }

            /* ---------------------------------------------Methods------------------------------------------------- */
            [[nodiscard]] constexpr bst_traversals get_traversal() const noexcept { return this->traversal; }
        
        };

        /* ----------------------------------------------Node Type-------------------------------------------------- */
        class node_type : public binary_tree<T, Allocator>::node_type {
        private:
            /* --------------------------------------------Friends-------------------------------------------------- */
            friend class binary_search_tree;
        
        protected:
            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr node_type(const _Node* node) noexcept {
                if (node == nullptr) {
                    this->node = nullptr;
                    return;
                }
                this->_construct(node);
            }
            
        public:
            /* -----------------------------------------Definitions------------------------------------------------- */
            using allocator_type = typename binary_tree<T, Allocator>::node_type::allocator_type;

            /* -----------------------------------------Constructors------------------------------------------------ */
            constexpr node_type() noexcept : binary_tree<T, Allocator>::node_type() {}

            constexpr node_type(std::nullptr_t) noexcept : binary_tree<T, Allocator>::node_type(nullptr) {}

            constexpr node_type(const node_type& other) noexcept : binary_tree<T, Allocator>::node_type(other) {}

            constexpr node_type(node_type&& other) noexcept 
                : binary_tree<T, Allocator>::node_type(std::forward<node_type>(other)) {}

            constexpr explicit node_type(const_iterator pos) noexcept {
                if (pos.node == nullptr) {
                    this->node = nullptr;
                    return;
                }

                this->_construct(pos.node);
            }

            /* -------------------------------------------Destructor------------------------------------------------ */
            constexpr ~node_type() noexcept = default;

            /* ---------------------------------------Overloaded Operators------------------------------------------ */
            constexpr node_type& operator=(const node_type&) noexcept = default;

            constexpr node_type& operator=(node_type&&) noexcept = default;

            constexpr node_type& operator=(const_iterator pos) noexcept {
                this->_destroy();
                if (pos.node == nullptr) {
                    this->node = nullptr;
                    return *this;
                }

                this->node = pos.node;
                return *this;
            }

            constexpr node_type& operator=(std::nullptr_t) noexcept {
                this->_destroy();
                this->node = nullptr;
                return *this;
            }

            [[nodiscard]] constexpr bool operator==(const node_type&) const noexcept = default;

            [[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return this->node == nullptr; }

            [[nodiscard]] constexpr auto operator<=>(const node_type&) const noexcept = default;

            [[nodiscard]] constexpr auto operator<=>(std::nullptr_t) const noexcept {
                return this->node <=> nullptr;
            }

        };

        /* ------------------------------------------Insert Return Type--------------------------------------------- */
        template<std::input_iterator InputIt = iterator, class NodeType = node_type>
        struct insert_return_type : binary_tree<T, Allocator>::template insert_return_type<InputIt, NodeType> {
            /* -----------------------------------------Constructors------------------------------------------------ */
            constexpr insert_return_type() noexcept
                : binary_tree<T, Allocator>::template insert_return_type<InputIt, NodeType>() {}

            constexpr insert_return_type(InputIt position, bool inserted, NodeType node) noexcept
                : binary_tree<T, Allocator>::template insert_return_type<InputIt, NodeType>(position, inserted, node) {}

            constexpr insert_return_type(const insert_return_type&) noexcept = default;

            constexpr insert_return_type(insert_return_type&&) noexcept = default;

            /* ------------------------------------------Destructor------------------------------------------------- */
            constexpr ~insert_return_type() noexcept = default;

            /* -------------------------------------Overloaded Operators-------------------------------------------- */
            constexpr insert_return_type& operator=(const insert_return_type&) noexcept = default;

            constexpr insert_return_type& operator=(insert_return_type&&) noexcept = default;

            [[nodiscard]] constexpr bool operator==(const insert_return_type&) const noexcept = default;

            [[nodiscard]] constexpr auto operator<=>(const insert_return_type&) const noexcept = default;
        };

        /* ---------------------------------------------Constructors------------------------------------------------ */
        constexpr binary_search_tree() noexcept : binary_tree<T, Allocator>() {
            this->min_node = this->max_node = nullptr;
        }

        constexpr explicit binary_search_tree(const allocator_type& allocator) noexcept 
            : binary_tree<T, Allocator>(allocator) { this->min_node = this->max_node = nullptr; }

        template<std::input_iterator InputIt>
        constexpr binary_search_tree(InputIt first, InputIt last) noexcept : binary_tree<T, Allocator>() {
            this->min_node = this->max_node = nullptr;

            // Create an empty tree if `last` is not reachable from `first`
            if (std::distance(first, last) <= 0) {
                return;
            }

            for (InputIt it = first; it != last; ++it) {
                this->_insert(*it);
            }
        }

        template<std::input_iterator InputIt>
        constexpr binary_search_tree(InputIt first, InputIt last, const allocator_type& allocator) noexcept 
            : binary_tree<T, Allocator>(allocator) { this->binary_search_tree(first, last); }

        constexpr binary_search_tree(std::initializer_list<value_type> values) noexcept 
            : binary_tree<T, Allocator>() {
            this->min_node = this->max_node = nullptr;

            for (value_type value : values) {
                this->_insert(value);
            }
        }

        constexpr binary_search_tree(std::initializer_list<value_type> values, const allocator_type& allocator) 
            noexcept : binary_tree<T, Allocator>(allocator) { this->binary_search_tree(values); }
        
        template<class R>
        constexpr binary_search_tree(std::from_range_t, R&& range) noexcept 
            requires(std::assignable_from<reference, std::ranges::range_reference_t<R>> && 
                     std::ranges::input_range<R>) : binary_tree<T, Allocator>() {
            this->root = this->min_node = this->max_node = nullptr;

            for (value_type value : range) {
                this->_insert(value);
            }
        }

        template<class R>
        constexpr binary_search_tree(std::from_range_t, R&& range, const allocator_type& allocator) noexcept
            requires(std::assignable_from<reference, std::ranges::range_reference_t<R>> && 
                     std::ranges::input_range<R>) : binary_tree<T, Allocator>(allocator) {
            this->binary_search_tree(std::from_range, range);
        }

        constexpr binary_search_tree(const binary_search_tree& other) noexcept : binary_tree<T, Allocator>() {
            this->min_node = this->max_node = nullptr;
            this->root = this->_copy(this->root, nullptr, other.root, other);
            this->sz = other.sz;
        }

        constexpr binary_search_tree(const binary_search_tree& other, const allocator_type& allocator) noexcept 
            : binary_tree<T, Allocator>(allocator) { this->binary_search_tree(other); }

        constexpr binary_search_tree(binary_search_tree&& other) noexcept 
            : binary_tree<T, Allocator>() { this->_move(other); }

        constexpr binary_search_tree(binary_search_tree&& other, const allocator_type& allocator)
            : binary_tree<T, Allocator>(allocator) { this->binary_search_tree(other); }

        /* -----------------------------------------------Destructor------------------------------------------------ */
        constexpr virtual ~binary_search_tree() noexcept override { this->_clear(); }

        /* ------------------------------------------Overloaded Operators------------------------------------------- */
        constexpr binary_search_tree& operator=(const binary_search_tree& rhs) noexcept {
            // Protect against self-assignment
            if (this == &rhs) {
                return *this;
            }

            this->_clear();
            this->root = this->_copy(this->root, nullptr, rhs.root, rhs);
            this->sz = rhs.sz;

            return *this;
        }

        constexpr binary_search_tree& operator=(binary_search_tree&& rhs) noexcept {
            // Protect against self-movement
            if (this == &rhs) {
                return *this;
            }

            this->_clear();
            this->_move(rhs);

            return *this;
        }
        
        // Need to write tests
        constexpr binary_search_tree& operator=(std::initializer_list<value_type> rhs) noexcept {
            this->_clear();
            
            for (typename std::initializer_list<value_type>::iterator it = rhs.begin(); it != rhs.end(); it++) {
                this->_insert(*it);
            }
            
            return *this;
        }

        [[nodiscard]] constexpr bool operator==(const binary_search_tree& rhs) const noexcept {
            return std::equal(this->begin(), this->end(), rhs.begin(), rhs.end());
        }

        template<class R>
        [[nodiscard]] constexpr bool operator==(R&& rhs) const noexcept
            requires(std::convertible_to<std::ranges::range_reference_t<R>, value_type> && 
                     std::ranges::input_range<R> && !std::is_same_v<std::remove_cvref_t<R>, binary_search_tree>) {
            return std::equal(this->begin(), this->end(), std::ranges::begin(rhs), std::ranges::end(rhs));
        }

        [[nodiscard]] constexpr auto operator<=>(const binary_search_tree& rhs) const noexcept 
            requires(std::three_way_comparable<value_type>) {
            // Compare this BST's size with the other BST's size
            if (size_type cmp = this->sz <=> rhs.sz; cmp != 0) {
                return cmp;
            }

            // If comparing the sizes fails, then lexicographically compare this BST's elements
            // with the other BST's elements
            return std::lexicographical_compare_three_way(this->begin(), this->end(), rhs.begin(), rhs.end());
        }

        template<class R>
        [[nodiscard]] constexpr auto operator<=>(R&& rhs) const noexcept 
            requires(std::convertible_to<std::ranges::range_reference_t<R>, value_type> && 
                     std::ranges::input_range<R> && !std::is_same_v<std::remove_cvref_t<R>, binary_search_tree> &&
                     std::three_way_comparable<value_type>) {
            // Compare this BST's size with the other BST's size
            if (size_type cmp = this->sz <=> rhs.sz; cmp != 0) {
                return cmp;
            }

            // If comparing the sizes fails, then lexicographically compare this BST's elements
            // with the other BST's elements
            return std::lexicographical_compare_three_way(
                this->begin(), this->end(), std::ranges::begin(rhs), std::ranges::end(rhs)
            );
        }

        /* ------------------------------------------------Methods-------------------------------------------------- */
        [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return const_iterator(*this); }

        [[nodiscard]] constexpr const_iterator cbegin(bst_traversals traversal) const noexcept {
            return const_iterator(*this, traversal);
        }

        [[nodiscard]] constexpr const_iterator cend() const noexcept { return const_iterator(nullptr); }

        [[nodiscard]] constexpr iterator begin() const noexcept { return iterator(*this); }

        [[nodiscard]] constexpr iterator begin(bst_traversals traversal) const noexcept {
            return iterator(*this, traversal);
        }

        [[nodiscard]] constexpr iterator end() const noexcept { return iterator(nullptr); }

        [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept {
            return const_reverse_iterator(*this);
        }

        [[nodiscard]] constexpr const_reverse_iterator crbegin(bst_traversals traversal) const noexcept {
            return const_reverse_iterator(*this, traversal);
        }

        [[nodiscard]] constexpr const_reverse_iterator crend() const noexcept {
            return const_reverse_iterator(nullptr);
        }

        [[nodiscard]] constexpr reverse_iterator rbegin() const noexcept { return reverse_iterator(*this); }

        [[nodiscard]] constexpr reverse_iterator rbegin(bst_traversals traversal) const noexcept {
            return reverse_iterator(*this, traversal);
        }

        [[nodiscard]] constexpr reverse_iterator rend() const noexcept { return reverse_iterator(nullptr); }

        [[nodiscard]] constexpr node_type get_root() const noexcept { return node_type(this->root); }

        [[nodiscard]] constexpr node_type get_min() const noexcept { return node_type(this->min_node); }

        [[nodiscard]] constexpr node_type get_max() const noexcept { return node_type(this->max_node); }

        constexpr virtual void clear() noexcept override { this->_clear(); }

        constexpr std::pair<iterator, bool> insert(const_reference value) noexcept
            requires(std::is_copy_constructible_v<value_type>) {
            std::pair<_Node*, bool> pair = this->_insert(value);
            return std::make_pair(iterator(pair.first), pair.second);
        }

        constexpr std::pair<iterator, bool> insert(value_type&& value) noexcept
            requires(std::is_move_constructible_v<value_type>) {
            std::pair<_Node*, bool> pair = this->_insert(value);
            return std::make_pair(iterator(pair.first), pair.second);
        }

        constexpr iterator insert(iterator pos, const_reference value) noexcept
            requires(std::is_copy_constructible_v<value_type> && !std::is_same_v<iterator, const_iterator>) {
        
            _Node* pos_node = const_cast<_Node*>(pos.node);
            return iterator(this->_insert(value, &pos_node).first);
        }

        constexpr iterator insert(iterator pos, value_type&& value) noexcept
            requires(std::is_move_constructible_v<value_type> && !std::is_same_v<iterator, const_iterator>) {
            _Node* pos_node = const_cast<_Node*>(pos.node);
            return iterator(this->_insert(value, &pos_node).first);
        }

        constexpr iterator insert(const_iterator pos, const_reference value) noexcept
            requires(std::is_copy_constructible_v<value_type>) {
            _Node* pos_node = const_cast<_Node*>(pos.node);
            return iterator(this->_insert(value, &pos_node).first);
        }

        constexpr iterator insert(const_iterator pos, value_type&& value) noexcept
            requires(std::is_move_constructible_v<value_type>) {
            _Node* pos_node = const_cast<_Node*>(pos.node);
            return iterator(this->_insert(value, &pos_node).first);
        }

        template<std::input_iterator InputIt>
        constexpr void insert(InputIt first, InputIt last) noexcept {
            // If `last` is not reachable from `first`...
            if (std::distance(first, last) <= 0) {
                // Do nothing
                return;
            }

            for (InputIt it = first; it != last; ++it) {
                this->_insert(*it);
            }
        }

        constexpr virtual void insert(std::initializer_list<value_type> values) noexcept override {
            for (value_type value : values) {
                this->_insert(value);
            }
        }

        constexpr insert_return_type<iterator, node_type> insert(node_type&& node) noexcept {
            // If the node handle has a node pointing to nullptr...
            if (node.empty()) {
                // Do NOT insert anything and return a default insert_return_type value
                return insert_return_type();
            }

            // Otherwise, attempt to insert the node into the BST
            std::pair<_Node*, bool> pair = this->_insert(node.node->value);

            // If the node was successfully inserted...
            if (pair.second) {
                // Destroy the node handle's copy of the inserted node
                node._destroy();
            }

            return insert_return_type(iterator(std::forward<_Node*>(pair.first)), pair.second, node);
        }

        constexpr iterator insert(const_iterator pos, node_type&& node) noexcept {
            // If the iterator is not at a valid position within the BST or 
            // the node handle does not contain a valid node...
            if (pos.node == nullptr || node.empty()) {
                // Return a non-constant iterator at nullptr and a false boolean value 
                // indicating nothing was inserted
                return iterator(nullptr);
            }

            // Attempt to insert the node_handle's node into the BST at the current position
            _Node* pos_node = const_cast<_Node*>(pos.node);
            std::pair pair = this->_insert(node.node->value, &pos_node);

            // If the node was successfully inserted...
            if (pair.second) {
                // Destroy the node handle's copy of the inserted node
                node._destroy();
            }
            
            return iterator(pair.first);
	    }

        template<class R>
        constexpr void insert_range(R&& range) noexcept
            requires(std::assignable_from<reference, std::ranges::range_reference_t<R>> && 
                     std::ranges::input_range<R>) {
            for (value_type value : range) {
                this->_insert(value);
            }
        }

        template<class... Args>
        constexpr std::pair<iterator, bool> emplace(Args... args) noexcept 
            requires(std::is_constructible_v<value_type, Args...>) {
            std::pair<_Node*, bool> pair = this->_insert(value_type(std::forward<Args>(args)...));
            return std::make_pair(iterator(pair.first), pair.second);
        }

        template<class... Args>
        constexpr iterator emplace_hint(const_iterator pos, Args... args) noexcept
            requires(std::is_constructible_v<value_type, Args...>) {
            // If the iterator is not in a valid position within the BST...
            if (pos.node == nullptr) {
                // Emplace the arguments starting at the root node
                return this->emplace(std::forward<value_type>(args)...).first;
            }

            // Otherwise, emplace the arguments at the iterator's position or as near as possible to it
            _Node* pos_node = const_cast<_Node*>(pos.node);
            return iterator(this->_insert(std::forward<value_type>(args)..., &pos_node).first);
        }

        constexpr iterator erase(iterator pos) noexcept
            requires(!std::is_same_v<iterator, const_iterator>) {
            return iterator(this->_erase(pos.node));
        }

        constexpr iterator erase(const_iterator pos) noexcept {
            return iterator(this->_erase(const_cast<_Node*>(pos.node)));
        }

        iterator erase(iterator start, iterator end)
            requires(!std::is_same_v<iterator, const_iterator>) {
            if (std::distance(start, end) <= 0 || this->sz == 1) {
                throw std::invalid_argument("adt::binary_search_tree::erase() error: \"end\" must be reachable from \"start\"");
            }

            iterator it = start;
            while (it.node != end.node) {
                it.node = this->_erase(it.node);
            }
            
            return it;
        }

        iterator erase(const_iterator start, const_iterator end) {
            if (std::distance(start, end) <= 0 || this->sz == 1) {
                throw std::invalid_argument("adt::binary_search_tree::erase() error: \"end\" must be reachable from \"start\"");
            }

            _Node* it_node = const_cast<_Node*>(start.node);
            while (it_node != end.node) {
                it_node = this->_erase(it_node);
            }
            
            return iterator(it_node);
        }

        constexpr void swap(binary_search_tree& other) noexcept {
            if (this->root == nullptr && other.root == nullptr) {
                return;
            }

            if (this == &other) {
                return;
            }

            _Node* temp_node;
            size_type temp_sz = this->sz;
            this->sz = other.sz;
            other.sz = temp_sz;

            temp_node = this->root;
            this->root = other.root;
            other.root = temp_node;

            temp_node = this->min_node;
            this->min_node = other.min_node;
            other.min_node = temp_node;

            temp_node = this->max_node;
            this->max_node = other.max_node;
            other.max_node = temp_node;
        }

        constexpr node_type extract(const_iterator pos) noexcept {
            node_type node_handle;
            if (pos.node == nullptr) {
                return node_handle;
            }

            node_handle.node = const_cast<_Node*>(pos.node);
            this->_remove(node_handle.node);
            return node_handle;
        }

        constexpr void merge(binary_search_tree& source) noexcept { this->_merge(source); }

        constexpr void merge(binary_search_tree&& source) noexcept {this->_merge(source); }

        // TO-TEST
        constexpr iterator find(const_reference value) noexcept
            requires(std::is_copy_constructible_v<value_type>) {
            iterator it = this->begin();
            while (it != this->end() && it.node->value != value) {
                it++;
            }

            return it;
        }

        // TO-TEST
        [[nodiscard]] constexpr const_iterator find(const_reference value) const noexcept
            requires(std::is_copy_constructible_v<value_type>) {
            const_iterator cit = this->cbegin();
            while (cit != this->cend() && cit.node->value != value) {
                cit++;
            }

            return cit;
        }

        // TO-TEST
        [[nodiscard]] constexpr virtual bool contains(const_reference value) const noexcept override {
            return this->find(value) != this->end();
        }

        // TO-DO
        constexpr std::pair<iterator, iterator> equal_range(const_reference value) noexcept
            requires(std::is_copy_constructible_v<value_type>);

        // TO-DO
        [[nodiscard]] constexpr std::pair<const_iterator, const_iterator> equal_range(const_reference value) const noexcept
            requires(std::is_copy_constructible_v<value_type>);
        
        // TO-DO
        constexpr iterator lower_bound(const_reference value) noexcept
            requires(std::is_copy_constructible_v<value_type>);

        // TO-DO
        [[nodiscard]] constexpr const_iterator lower_bound(const_reference value) const noexcept
            requires(std::is_copy_constructible_v<value_type>);

        // TO-DO
        constexpr iterator upper_bound(const_reference value) noexcept
            requires(std::is_copy_constructible_v<value_type>);

        // TO-DO
        [[nodiscard]] constexpr const_iterator upper_bound(const_reference value) const noexcept
            requires(std::is_copy_constructible_v<value_type>);

        // FOR TESTING - REMOVE WHEN FINISHED
        constexpr void print_adjacent_list() const noexcept {
            this->_print_adjacent_list(this->root);
        }

    };

    

} // adt

namespace std {

    // TO-TEST
    template<class T, class Allocator>
    constexpr void swap(adt::binary_search_tree<T, Allocator>& lhs, adt::binary_search_tree<T, Allocator>& rhs) noexcept {
        lhs.swap(rhs);
    }

    // TO-TEST
    template<class T, class Allocator, class Predicate>
    constexpr typename adt::binary_search_tree<T, Allocator>::size_type erase_if(adt::binary_search_tree<T, Allocator>& bst, 
                                                                                 Predicate pred) noexcept
        requires(std::predicate<Predicate, T>) {
        typename adt::binary_search_tree<T, Allocator>::size_type erase_count = 0;

        
    }


} // std


#endif // BINARY_SEARCH_TREE_HPP

