#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <algorithm>        // std::copy, std::equal, std::fill
#include <cassert>          // assert()
#include <cstddef>          // std::size_t
#include <exception>        // std::out_of_range
#include <initializer_list> // std::initializer_list
#include <iostream>         // std::cout, std::endl
#include <iterator> // std::advance, std::begin(), std::end(), std::ostream_iterator
#include <limits> // std::numeric_limits<T>
#include <memory> // std::unique_ptr

/// Sequence container namespace.
namespace sc {
/// Implements tha infrastructure to support a bidirectional iterator.
template <class T> class MyForwardIterator {
public:
  using iterator = MyForwardIterator; //!< Alias to iterator.
  // Below we have the iterator_traits common interface
  using difference_type = std::ptrdiff_t;  //!< Difference type used to calculated distance between iterators.
  using value_type = T; //!< Value type the iterator points to.
  using pointer = T*;   //!< Pointer to the value type.
  using reference = T&; //!< Reference to the value type.
  using const_reference = const T&; //!< Reference to the value type.
  using iterator_category = std::bidirectional_iterator_tag; //!< Iterator category.

  /*! Create an iterator around a raw pointer.
   * \param pt_ raw pointer to the container.
   */
  explicit MyForwardIterator(pointer pt = nullptr) : m_ptr(pt) { /* empty */
  }

  /// Access the content the iterator points to.
  reference operator*() const {
    assert(m_ptr != nullptr);
    return *m_ptr;
  }

  /// Overloaded `->` operator.
  pointer operator->() const {
    assert(m_ptr != nullptr);
    return m_ptr;
  }

  /// Assignment operator.
  iterator &operator=(const iterator &) = default;
  /// Copy constructor.
  MyForwardIterator(const iterator &) = default;

  /// Pre-increment operator.
  iterator operator++() {
    m_ptr++;
    return *this;
  }

  /// Post-increment operator.
  iterator operator++(int) {
    iterator dummy(*this);
    m_ptr++;
    return dummy;
  }

  /// Pre-decrement operator.
  iterator operator--() {
    m_ptr--;
    return *this;
  }

  /// Post-decrement operator.
  iterator operator--(int) {
    iterator dummy(*this);
    m_ptr--;
    return dummy;
  }

  iterator &operator+=(difference_type offset) {
    iterator &it{*this};
    for(difference_type idx = 0; idx < offset; ++idx) {
      ++it;
    }
    return it;
  }

  iterator &operator-=(difference_type offset) {
    iterator &it{*this};
    for(difference_type idx = 0; idx < offset; ++idx) {
      --it;
    }
    return it;
  }

  friend bool operator<(const iterator &ita, const iterator &itb) {
    return ita.m_ptr < itb.m_ptr;
  }
  friend bool operator>(const iterator &ita, const iterator &itb) {
    return ita.m_ptr > itb.m_ptr;
  }
  friend bool operator>=(const iterator &ita, const iterator &itb) {
    return ita.m_ptr >= itb.m_ptr;
  }
  friend bool operator<=(const iterator &ita, const iterator &itb) {
    return ita.m_ptr <= itb.m_ptr;
  }

  friend iterator operator+(difference_type offset, iterator it) {
    iterator dummy{it};
    dummy += offset;
    return dummy;
  }
  friend iterator operator+(iterator it, difference_type offset) {
    iterator dummy{it};
    dummy += offset;
    return dummy;
  }
  friend iterator operator-(iterator it, difference_type offset) {
    iterator dummy{it};
    dummy -= offset;
    return dummy;
  }

  /// Equality operator.
  bool operator==(const iterator &rhs_) const {
    return m_ptr == rhs_.m_ptr;
  }

  /// Not equality operator.
  bool operator!=(const iterator &rhs_) const {
    return m_ptr != rhs_.m_ptr;
  }

  /// Returns the difference between two iterators.
  difference_type operator-(const iterator &rhs_) const {
    return m_ptr - rhs_.m_ptr;
  }

  /// Stream extractor operator.
  friend std::ostream &operator<<(std::ostream &os_,
                                  const MyForwardIterator &p_) {
    os_ << "[@ " << p_.m_ptr << ": " << *p_.m_ptr << " ]";
    return os_;
  }

private:
  pointer m_ptr; //!< The raw pointer.
};

/// This class implements the ADT list with dynamic array.
/*!
 * sc::vector is a sequence container that encapsulates dynamic size arrays.
 *
 * The elements are stored contiguously, which means that elements can
 * be accessed not only through iterators, but also using offsets to
 * regular pointers to elements.
 * This means that a pointer to an element of a vector may be passed to
 * any function that expects a pointer to an element of an array.
 *
 * \tparam T The type of the elements.
 */
template <typename T> class vector {
  //=== Aliases
public:
  using size_type = unsigned long; //!< The size type.
  using value_type = T;            //!< The value type.
  using pointer = value_type *; //!< Pointer to a value stored in the container.
  using reference =
      value_type &; //!< Reference to a value stored in the container.
  using const_reference = const value_type &; //!< Const reference to a value
                                              //!< stored in the container.
  using iterator =
      MyForwardIterator<value_type>; //!< The iterator, instantiated from a
                                     //!< template class.
  using const_iterator =
      MyForwardIterator<const value_type>; //!< The const_iterator,
                                           //!< instantiated from a template
                                           //!< class.

public:
  //=== [I] SPECIAL MEMBERS (6 OF THEM)
  explicit vector(size_type cp = 0) {
    m_storage = new T[cp];
    m_capacity = cp;
    m_end = cp; // Array stars full
    for (size_type i{0}; i < m_end; ++i) {
      m_storage[i] = T();
    }
  }
  
  virtual ~vector() {
    if (m_storage)
      delete[] m_storage;
  }

  vector(const vector &other) {
    m_capacity = other.m_capacity;
    m_storage = new T[m_capacity];
    m_end = other.m_end;
    // std::copy(other.m_storage, other.m_storage + other.m_end, m_storage);
    std::copy(other.cbegin(), other.cend(), begin());
  }

  vector(const std::initializer_list<T> &il) {
    m_capacity = il.size();
    m_storage = new T[m_capacity];
    m_end = m_capacity; // Array starts full.
    // Copy the elements from the il into the array.
    std::copy(il.begin(), il.end(), begin());
  }

  template <typename InputItr> vector(InputItr first, InputItr last) {
    m_capacity = std::distance(first, last);
    m_storage = new T[m_capacity];
    m_end = m_capacity;
    std::copy(first, last, begin());
  }

  vector &operator=(const vector &other) {
    m_capacity = other.m_capacity;
    m_storage = new T[m_capacity];
    m_end = other.m_end;
    // std::copy(other.m_storage, other.m_storage + other.m_end, m_storage);
    std::copy(other.cbegin(), other.cend(), begin());
    return *this;
  }

  vector &operator=(const std::initializer_list<T> &il) {
      m_capacity = il.size();
      m_storage = new T[m_capacity];
      std::copy(il.begin(), il.end(), begin());
      m_end = m_capacity;
      return *this;
  }

  //=== [II] ITERATORS
  iterator begin() { return iterator{&m_storage[0]}; }
  iterator end() { return iterator{&m_storage[m_end]}; }
  const_iterator cbegin() const { return const_iterator{&m_storage[0]}; };
  const_iterator cend() const { return const_iterator{&m_storage[m_end]}; };

  // [III] Capacity
  [[nodiscard]] size_type size() const { return m_end; }
  [[nodiscard]] size_type capacity() const { return m_capacity; }
  [[nodiscard]] bool empty() const { return m_end == 0; }

  // [IV] Modifiers
  void clear() {
      erase(begin(), end());
  }

  void push_front(const_reference value) {
    /// Check if vector is full or default
    if(this->full()) {
      size_type new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
      reserve(new_capacity);
    }

    /// Move all elements
    // std::copy_backward(m_storage, m_storage + m_end, m_storage + m_end + 1);
    std::copy_backward(cbegin(), cend(), cend() + 1);

    /// Set value
    m_storage[0] = value;
    ++m_end;
  }

  void push_back(const_reference value) {
    /// Check if vector is full or default
    if(this->full()) {
      size_type new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
      reserve(new_capacity);
    }

    /// Set value in the vector
    m_storage[m_end++] = value;
  }

  void pop_back() {
    /// Check if vector is empty
    if(this->empty()) {
      return;
    }

    --m_end;
  }

  void pop_front() {
    /// Check if vector is empty
    if(this->empty()) {
      return;
    }

    /// Move all elements
    // std::copy(m_storage + 1, m_storage + m_end, m_storage);
    std::copy(cbegin() + 1, cend(), cbegin());

    --m_end;
  }

  iterator insert(iterator pos_, const_reference value_){
      /// Check if vector is full or default
      if(this->full()) {
          // Stores begin() location before reserve
          iterator old_begin = begin();

          size_type new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
          reserve(new_capacity);
          // Updates pos_ to correspond to the new allocated memory
          iterator new_pos = begin() + std::distance(old_begin, pos_);
          pos_ = new_pos;
      }
      /// Shifts all elements to the right, starting at pos, then puts value right before pos
      std::copy_backward(pos_, end(), end()+1);
      m_storage[std::distance(begin(), pos_)] = value_;
      ++m_end;

      return pos_;
  }

  iterator insert(const_iterator pos_, const_reference value_){
      /// Check if vector is full or default
      if(this->full()) {
          // Stores begin() location before reserve
          iterator old_begin = begin();

          size_type new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
          reserve(new_capacity);
          // pos_ becomes obsolete after reserve, so new_pos must be used from now on
          iterator new_pos = begin() + std::distance(old_begin, pos_);

          /// Shifts all elements to the right, starting at new_pos, then puts value
          std::copy_backward(new_pos, end(), end()+1);
          m_storage[std::distance(begin(), new_pos)] = value_;
          ++m_end;

          return new_pos;
      } else {
          /// Shifts all elements to the right, starting at pos, then puts value right before pos
          std::copy_backward(pos_, end(), end()+1);
          m_storage[std::distance(begin(), pos_)] = value_;
          ++m_end;

          return pos_;
      }
  }

  template <typename InputItr>
  iterator insert(iterator pos_, InputItr first_, InputItr last_){
    size_t range_size = std::distance(first_, last_);

    vector aux = vector(first_, last_); //<! Vector to storage elements from range

    /// Insert values
    for (auto it = aux.cend() - 1; it >= aux.cbegin(); --it) {
      pos_ = this->insert(pos_, *it);
    }
      return pos_;
  }

  template <typename InputItr>
  iterator insert(const_iterator pos_, InputItr first_, InputItr last_) {
    size_t range_size = std::distance(first_, last_);

    vector aux(first_, last_); //<! Vector to storage elements from range

    // Insert values
    for (auto it = aux.cend() - 1; it >= aux.cbegin(); --it) {
        pos_ = this->insert(pos_, *it);
    }
    return iterator{pos_};
  }

  iterator insert(iterator pos_, const std::initializer_list<value_type> &ilist_) {
    /// Set values of ilist in vector
    for (const auto &value : ilist_) {
        pos_ = this->insert(pos_, value);
        ++pos_;
    }
    return pos_;
  }

  iterator insert(const_iterator pos_, const std::initializer_list<value_type> &ilist_) {
    iterator pos = begin() + std::distance(cbegin(), pos_);

    /// Set values of ilist in vector
    for (const auto &value : ilist_) {
        pos = insert(pos, value);
        ++pos;
    }
    return pos;
  }

  void reserve(size_type new_capacity) {
    /// Check if it is necessary to allocate more memory for the array.
    if (new_capacity <= m_capacity) {
      return;
    }

    T *new_storage = new T[new_capacity]; //!< New capacity of vector
    std::copy(cbegin(), cend(), new_storage);

    /// Free old memory of storage
    delete[] m_storage;

    /// Update data of vector
    m_storage = new_storage;
    m_capacity = new_capacity;
  }

  void shrink_to_fit() {
    T* new_storage = new T[m_end]; //!< New capacity of vector
    std::copy(m_storage, m_storage + m_end, new_storage);

    /// Free old memory of storage
    delete[] m_storage;

    /// Update data of vector
    m_storage = new_storage;
    m_capacity = m_end;
  }

  void assign(size_type count_, const_reference value_) {
    /// Check if it is necessary to allocate more memory.
    if(count_ > m_capacity) {
      delete[] m_storage;
      m_storage = new T[count_];  //!< New capacity of vector
      m_capacity = count_;
    }

    /// Set value in vector
    for(int idx = 0; idx < count_; ++idx) {
      m_storage[idx] = value_;
    }

    m_end = count_;
  }

  void assign(const std::initializer_list<T> &ilist) {
    /// Set size of vector
    m_end = ilist.size();

    /// Check if it is necessary to allocate more memory.
    if(m_end > m_capacity) {
      delete[] m_storage;
      m_storage = new T[m_end];  //!< New capacity of vector
      m_capacity = m_end;
    }  

    /// Copy element from list to vector
    std::copy(ilist.begin(), ilist.end(), m_storage);
  }

  template <typename InputItr> void assign(InputItr first, InputItr last){
    size_type count_ = last - first;

    /// Check if it is necessary to allocate more memory.
    if(count_ > m_capacity) {
      delete[] m_storage;
      m_storage = new T[count_];  //!< New capacity of vector
      m_capacity = count_;
    }

    /// Copy element from range to vector
    std::copy(first, last, m_storage);

    m_end = count_;
  }

  iterator erase(iterator first, iterator last){
    size_t range_size = std::distance(first, last);

    std::copy(last, end(), first);

    m_end -= range_size;
    return first;
  }

  iterator erase(const_iterator first, const_iterator last){
    size_t range_size = std::distance(first, last);

    std::copy(last, end(), first);

    m_end -= range_size;
    return first;
  }

  iterator erase(const_iterator pos){
    std::copy(pos+1, end(), pos);
    m_end--;
    return pos;
  }
  iterator erase(iterator pos){
    std::copy(pos+1, end(), pos);
    m_end--;
    return pos;
  }

  // [V] Element access
  const_reference back() const { return m_storage[m_end - 1]; }
  const_reference front() const { return m_storage[0]; }
  reference back() { return m_storage[m_end - 1]; }
  reference front() { return m_storage[0]; }
  const_reference operator[](size_type idx) const { return m_storage[idx]; }
  reference operator[](size_type idx) { return m_storage[idx]; }
  // TODO: THROW ERROR IF TRYING TO ACCESS IMPOSSIBLE INDEX
  const_reference at(size_type i) const{
      if (i >= size()){
          throw std::out_of_range("Invalid index");
      }
      return m_storage[i];
  }
  reference at(size_type i){
      if (i >= size()){
          throw std::out_of_range("Invalid index");
      }
      return m_storage[i];
  }
  pointer data() { return *m_storage; }
  const_reference data() const { return *m_storage; }

  // [VII] Friend functions.
  friend std::ostream &operator<<(std::ostream &os_, const vector<T> &v_) {
    // O que eu quero imprimir???
    os_ << "{ ";
    for (auto i{0u}; i < v_.m_capacity; ++i) {
      if (i == v_.m_end)
        os_ << "| ";
      os_ << v_.m_storage[i] << " ";
    }
    os_ << "}, m_end=" << v_.m_end << ", m_capacity=" << v_.m_capacity;

    return os_;
  }
  friend void swap(vector<T> &first_, vector<T> &second_) {
    // enable ADL
    using std::swap;

    // Swap each member of the class.
    swap(first_.m_end, second_.m_end);
    swap(first_.m_capacity, second_.m_capacity);
    swap(first_.m_storage, second_.m_storage);
  }

private:
  [[nodiscard]] bool full() const {return m_end == m_capacity;}

  size_type m_end; //!< The list's current size (or index past-last valid element).
  size_type m_capacity; //!< The list's storage capacity.
  T *   m_storage;         //!< The list's data storage area.
};

// [VI] Operators
template <typename T> bool operator==(const vector<T> &lhs, const vector<T> &rhs) {
    if (lhs.size() != rhs.size())
        return false;

    for (auto i = 0; i < lhs.size(); ++i){
        if (lhs.at(i) != rhs.at(i))
            return false;
    }
    return true;
}
template <typename T> bool operator!=(const vector<T> &lhs, const vector<T> &rhs){
    return !operator==(lhs, rhs);
}

} // namespace sc.

#endif