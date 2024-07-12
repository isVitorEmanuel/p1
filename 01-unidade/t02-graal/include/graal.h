/*!
 * Edite esse arquivo para incluir suas respostas.
 * @author Selan
 * @date April 6th, 2022.
 */

#include <algorithm>

#ifndef GRAAL_H
#define GRAAL_H

#include <utility>
using std::pair;

namespace graal {

/*!
 * Finds and returns a pair with the smallest and greatest elements in a range.
 *
 * @tparam Itr Iterator to the range.
 * @tparam Compare A regular comparison function.Comparison functor.
 *
 * @param first Pointer to the first element of the range we want to copy (inclusive).
 * @param last Pointer to the last element of the range we want to copy (exclusive).
 * @param cmp The comparison function that return true if the first element is *less* than the
 * second.
 *
 * @return A pair of the smallest and greatest elements.
 *
 */
template <typename Itr, typename Compare>
std::pair<Itr, Itr> minmax(Itr first, Itr last, Compare cmp) {
  
  /// Checks if the range is empty.
  if (first == last) {
    return {first, first};
  }

  /// Initializes the iterator variables
  Itr less = first;
  Itr larger = first;

  /// Iterates over the elements within the range [first, last).
  while (first != last) {
    
    /// Checks if 'first' points to an element smaller than the known one.
    if (cmp(*first, *less)) {
        less = first;
    }

    /// Checks if 'first' points to an element greater than the known one.
    if (!cmp(*first, *larger)){
        larger = first;
    }
    first++;
  }

  /// Returns the largest and smallest element of the container.
  return {less, larger};
}

/*!
 * Reverse the order the elements in range.
 *
 * @tparam BidirIt Iterator to the range.
 *
 * @param first Pointer to the first element of the range we want to reverse (inclusive).
 * @param last Pointer to the last element of the range we want to reverse (exclusive).
 *
 */
template <class BidirIt> 
void reverse(BidirIt first, BidirIt last) {

  /// Iterates over the container while first != last and --last.
  while (first != last && first != --last) {

    /// Swaps the value of last and first.
    std::swap(*first, *last);
    ++first; 
  }
}

/*!
 * Receives a range and copy the range values a new range.
 *
 * @tparam InputIt Iterator to the range.
 *
 * @param first Pointer to the first element of the range we want to copy (inclusive).
 * @param last Pointer to the last element of the range we want to copy (exclusive).
 * @param d_first Pointer to the new range we want to paste
 *
 * @return The pointer to the just past the last element.
 *
 */
template <class InputIt> 
InputIt copy(InputIt first, InputIt last, InputIt d_first) {

  /// Iterates over the container to be copied.
  while (first != last) {

    /// Copies the value from 'first' to 'd_first'
    *d_first = *first;

    /// Iterates the iterators of 'first' and 'd_first'.
    first++;
    d_first++; 
  }

  /// Return the iterator of d_first
  return d_first;
}

/*!
 * Find the first ocurrecy of especifed element that return true.
 *
 * @tparam InputIt Iterator to the range.
 * @tparam UnaryPredicate A predicate with a bool return value.
 *
 * @param first Pointer to the first element of the range we want to verify (inclusive).
 * @param last Pointer to the last element of the range we want to verify (exclusive).
 * @param p Predicate to be used in validation
 *
 * @return If one element is valid, return the element, otherwise return last.
 *
 */
template <class InputIt, class UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p) {
  
  /// Iterates over the container.
  while(first != last) {

    /// Checks if the predicate p is valid for *first, if it is, returns first.
    if(p(*first)) {
      return first;
      break;
    }
    first++;
  }

  /// Returns last if the predicate p is false for all values in the container.
  return last;
}

/*!
 * Verify if all elements are valid for the predicate.
 *
 * @tparam InputIt Iterator to the range.
 * @tparam UnaryPredicate A predicate with a bool return value.
 *
 * @param first Pointer to the first element of the range we want to verify (inclusive).
 * @param last Pointer to the last element of the range we want to verify (exclusive).
 * @param p Predicate to be used in validation
 *
 * @return Return true if all elements are valids, otherwise return false.
 *
 */
template <class InputIt, class UnaryPredicate>
bool all_of(InputIt first, InputIt last, UnaryPredicate p) {

  /// Iterates over the container
  while (first != last) {

    /// Checks if the predicate p is false for any value in the container, if so, returns false
    if(!p(*first)) {
      return false;
      break;
    }
    first++;
  }

  /// Returns true if for the predicate p all values of first are true
  return true; 
}

/*!
 * Verify if any element is valid for the predicate.
 *
 * @tparam InputIt Iterator to the range.
 * @tparam UnaryPredicate A predicate with a bool return value.
 *
 * @param first Pointer to the first element of the range we want to verify (inclusive).
 * @param last Pointer to the last element of the range we want to verify (exclusive).
 * @param p Predicate to be used in validation
 *
 * @return Return true if any element is valid, otherwise return false.
 *
 */
template <class InputIt, class UnaryPredicate>
bool any_of(InputIt first, InputIt last, UnaryPredicate p) {

  /// terates over the container
  while(first != last) {

    /// Checks if for any value of the container, p is true; if so, returns true
    if(p(*first)) {
      return true;
      break;
    }
    first++;
  }

  /// If p is not valid for any value of the container, returns false.
  return false;
}

/*!
 * Verify if none element is valid for the predicate.
 *
 * @tparam InputIt Iterator to the range.
 * @tparam UnaryPredicate A predicate with a bool return value.
 *
 * @param first Pointer to the first element of the range we want to verify (inclusive).
 * @param last Pointer to the last element of the range we want to verify (exclusive).
 * @param p Predicate to be used in validation
 *
 * @return Return false if any element is valid, otherwise return true.
 *
 */
template <class InputIt, class UnaryPredicate>
bool none_of(InputIt first, InputIt last, UnaryPredicate p) {
  
  /// Iterates over the container.
  while(first != last){

    /// Checks if the predicate p is valid for any value of the container; if so, returns false.
    if(p(*first)) {
      return false;
      break;
    }
    first++;
  }

  /// If the predicate p is not valid for any value of the container, returns true.
  return true;
}

/*!
 * Check if containers are equals.
 *
 * @tparam InputIt1 Iterator to the first range.
 * @tparam InputIt2 Iterator to the second range.
 * @tparam Equal Predicate that validates equality.
 *
 * @param first1 Pointer to the first element of the first range we want to check (inclusive).
 * @param last1 Pointer to the last element of the first range we want to ckeck (exclusive).
 * @param first2 Pointer to the first element of the second range we want to check (inclusive).
 * @param eq Predicate to be used in equaldad
 *
 * @return Return false if any element is not equal, otherwise return true
 *
 */
template <class InputIt1, class InputIt2, class Equal>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, Equal eq) {

  /// Iterates over the container.
  while(first1 != last1) {
    
    /// Check if the values of the containers are different according to eq, if they are, return false
    if(!eq(*first1, *first2)) {
      return false;
      break;
    }

    /// Advance the iterators first1 and first2
    first1++;
    first2++;
  }

  /// If none of the values are different, return true.
  return true; 
}

/*!
 * Check if containers are equals.
 *
 * @tparam InputIt1 Iterator to the first range.
 * @tparam InputIt2 Iterator to the second range.
 * @tparam Equal Predicate that validates equality.
 *
 * @param first1 Pointer to the first element of the first range we want to check (inclusive).
 * @param last1 Pointer to the last element of the first range we want to ckeck (exclusive).
 * @param first2 Pointer to the first element of the second range we want to check (inclusive).
 * @param last2 Pointer to the last element of the second range we want to ckeck (exclusive).
 * @param eq Predicate to be used in equaldad
 *
 * @return Return false if any element is not equal, otherwise return true
 *
 */
template <class InputIt1, class InputIt2, class Equal>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Equal eq) {
  
  /// Iterates over both containers until last1 and last2.
  while (first1 != last1 && first1 != last2) {
    
    /// Checks if the elements of the two containers are different; if so, returns false.
    if(!eq(*first1, *first2)) {
      return false;
      break;
    }

    /// Iterates the iterators of each container.
    first1++;
    first2++;
  }
  
  /// If no element is different, returns true."
  return true; 
}

/*!
 * Leave only unique elements in the range.
 *
 * @tparam InputIt Iterator to the range.
 * @tparam Equal Predicate that validates equality.
 *
 * @param first1 Pointer to the first element of the first range we want to check (inclusive).
 * @param last1 Pointer to the last element of the first range we want to ckeck (exclusive).
 * @param eq Predicate to be used in equaldad
 *
 * @return Return the pointer to the address just past the last element of the range with unique elements.
 *
 */
template <class InputIt, class Equal> 
InputIt unique(InputIt first, InputIt last, Equal eq) {

  /// Declare the iterators for the slow and fast techniques.
  InputIt slow {first};
  InputIt fast {first};
  ++fast;

  bool repeatedElement;  /*!< Variable indicates whether the element is repeated or not. */

  /// Iterate over the container.
  while (fast != last) {  
    repeatedElement = false;

    /// Traverse the container with the elements already added and check if the fast element is already part of the container.
    for (InputIt value = first; value <= slow; ++value) {
      if (eq(*fast, *value)) {
        repeatedElement = true;
        break;
      }
    }

    /// If the element is not repeated, iterate the slow pointer and assign the element to it.
    if (!repeatedElement) {
      ++slow; 
      *slow = *fast;
    }

    /// Iterate the fast pointer.
    ++fast;
  }
  return slow;
}

/*!
 * Separate the range into elements that are valid according to a predicate and elements that are invalid.
 *
 * @tparam ForwardIt Iterator to the range.
 * @tparam UnaryPredicate A predicate with a bool return value.
 *
 * @param first1 Pointer to the first element of the first range we want to check (inclusive).
 * @param last1 Pointer to the last element of the first range we want to ckeck (exclusive).
 * @param p Predicate to be used in comparison.  
 *
 * @return Return the iterator to the beginning of the range for which predicate p return false .
 *
 */
template <class ForwardIt, class UnaryPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p) {

  /// Declare the iterators for the validity of each predicate.
  ForwardIt predTrue = first;
  ForwardIt predFalse = last - 1;

  /// Traverse the vector until the partition finishes
  while (true) {

    /// Search for an element where the predicate is false.
    while (predTrue <= predFalse && p(*predTrue)){
      ++predTrue;
    }

    /// Search for an element where the predicate is true.
    while (predTrue <= predFalse && !p(*predFalse)) {
      --predFalse;
    }

    /// Search for an element where the predicate is true.
    if (predTrue >= predFalse){
      break;
    }

    /// Swap the elements predTrue and predFalse.
    std::swap(*predTrue, *predFalse);
  }

  /// Return an iterator to the beginning of the second interval.
  return predTrue;
}

}  /// namespace graal.

#endif
