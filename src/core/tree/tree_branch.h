/*
 * Copyright (C) 2018 Emmanuel Durand
 *
 * This file is part of Splash.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Splash is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Splash.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * @tree_branch.h
 * The Branch class, fixed on a tree Root
 */

#ifndef SPLASH_TREE_BRANCH_H
#define SPLASH_TREE_BRANCH_H

#include <chrono>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "./config.h"

namespace Splash
{

namespace Tree
{

class Root;
class Leaf;

/*************/
/**
 * Tree::Branch class, which can hold other Branches and Leafs
 */
class Branch
{
    friend Root;

  public:
    /**
     * Constructor
     */
    explicit Branch(const std::string& name, Branch* parent = nullptr);

    /**
     * Compare the equality of two branches
     * \param rhs Other branch to compare to
     * \return Return true if branches are identical
     */
    bool operator==(const Branch& rhs) const;
    bool operator!=(const Branch& rhs) const { return !operator==(rhs); }

    /**
     * Add a new branch
     * \param branch Branch to add
     * \return Return false if a branch with the same name already exists
     */
    bool addBranch(std::unique_ptr<Branch>&& branch);

    /**
     * Add a new leaf
     * \param leaf Leaf to add
     * \return Return false if a leaf with the same name already exists
     */
    bool addLeaf(std::unique_ptr<Leaf>&& leaf);

    /**
     * Get the branch by its name
     * \param path Path to a subbranch
     * \return Return a pointer to the branch, or nullptr
     */
    Branch* getBranch(const std::string& path);

    /**
     * Get the list of branches connected to this branch
     * \return Return the list of branches
     */
    std::list<std::string> getBranchList() const;

    /**
     * Get the leaf by its name
     * \param name Leaf name
     * \return Return a pointer to the leaf, or nullptr
     */
    Leaf* getLeaf(const std::string& path);

    /**
     * Get the list of leaves connected to this branch
     * \return Return the list of leaves
     */
    std::list<std::string> getLeafList() const;

    /**
     * Get the list of leaves for this branch
     * \return Return the list of leaf names
     */
    std::list<std::string> getLeafNames() const;

    /**
     * Get the branch name
     * \return Return the name
     */
    std::string getName() const { return _name; }

    /**
     * Check whether a given subbranch exists
     * \return Return true if the subbranch exists
     */
    bool hasBranch(const std::string& name) const { return _branches.find(name) != _branches.end(); }

    /**
     * Check whether a given leaf exists
     * \return Return true if the leaf exists
     */
    bool hasLeaf(const std::string& name) const { return _leaves.find(name) != _leaves.end(); }

    /**
     * Get the full path for this branch
     * \return Return the full path
     */
    std::string getPath() const;

    /**
     * Return a string describing the branch
     * \param indent Indent for this branch
     * \return Return the tree as a string
     */
    std::string print(int indent) const;

    /**
     * Remove a branch given its name
     * \param name Branch name
     * \return Return true if the branch has been removed
     */
    bool removeBranch(std::string name);

    /**
     * Remove a leaf given its name
     * \param name Leaf name
     * \return Return true if the leaf has been removed
     */
    bool removeLeaf(std::string name);

    /**
     * Set this branch parent
     * \param parent Parent branch
     */
    void setParent(Branch* parent) { _parentBranch = parent; }

  private:
    std::string _name{"branch"};
    std::unordered_map<std::string, std::unique_ptr<Branch>> _branches{};
    std::unordered_map<std::string, std::unique_ptr<Leaf>> _leaves{};
    Branch* _parentBranch{nullptr};
};

} // namespace Tree
} // namespace Splash

#endif // SPLASH_TREE_BRANCH_H
