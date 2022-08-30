#pragma once

template <typename T, size_t N>
s21::Array<T, N>::Array() {
  arr_ = new value_type[size_];
};

template <typename T, size_t N>
s21::Array<T, N>::Array(std::initializer_list<value_type> const &items) {
  arr_ = new value_type[size_];
  int count = 0;
  for (auto element : items) {
    arr_[count] = element;
    ++count;
  }
}

template <typename T, size_t N>
s21::Array<T, N>::Array(const Array &other) {
  *this = other;
}

template <typename T, size_t N>
s21::Array<T, N>::Array(Array &&other) {
  *this = other;
}

template <typename T, size_t N>
typename s21::Array<T, N>::value_type &s21::Array<T, N>::operator[](
    size_type const &index) {
  return arr_[index];
}

template <typename T, size_t N>
void s21::Array<T, N>::operator=(const Array &other) {
  if (size_ != other.size_) {
    throw std::invalid_argument("Size isn't equals");
  }
  this->~Array();
  arr_ = new value_type[size_];
  memcpy(arr_, other.arr_, size_);
}

template <typename T, size_t N>
void s21::Array<T, N>::operator=(Array &&other) {
  if (size_ != other.size_) {
    throw std::invalid_argument("Size isn't equals");
  }
  std::swap(arr_, other.arr_);
}

template <typename T, size_t N>
s21::Array<T, N>::~Array() {
  delete[] arr_;
}

template <typename T, size_t N>
typename s21::Array<T, N>::iterator s21::Array<T, N>::begin() {
  if (size_ < 2) {
    throw std::out_of_range("We havn't begin iterator");
  }
  iterator temp(arr_);
  return temp;
}

template <typename T, size_t N>
typename s21::Array<T, N>::iterator s21::Array<T, N>::end() {
  if (size_ < 2) {
    throw std::out_of_range("We havn't end iterator");
  }
  iterator temp(arr_ + size_ - 1);
  return temp;
}

template <typename T, size_t N>
const typename s21::Array<T, N>::value_type &s21::Array<T, N>::front() {
  if (size_ < 2) {
    throw std::out_of_range("That index isn't validate!");
  }
  return arr_[0];
}

template <typename T, size_t N>
const typename s21::Array<T, N>::value_type &s21::Array<T, N>::back() {
  if (size_ < 2) {
    throw std::out_of_range("That index isn't validate!");
  }
  return arr_[size_ - 2];
}

template <typename T, size_t N>
typename s21::Array<T, N>::iterator s21::Array<T, N>::data() {
  return begin();
}

template <typename T, size_t N>
typename s21::Array<T, N>::value_type &s21::Array<T, N>::at(
    size_type const &index) {
  if (index >= (size_ - 2)) {
    throw std::out_of_range("That index isn't validate!");
  }
  return arr_[index];
}

template <typename T, size_t N>
bool s21::Array<T, N>::empty() {
  return size_ == 1;
}

template <typename T, size_t N>
void s21::Array<T, N>::swap(Array &other) {
  if (size_ != other.size_) {
    throw std::invalid_argument("Size isn't equals");
  }
  std::swap(arr_, other.arr_);
}

template <typename T, size_t N>
void s21::Array<T, N>::fill(value_type const &value) {
  for (value_type &element : *this) {
    element = value;
  }
}

template <typename T, size_t N>
typename s21::Array<T, N>::size_type s21::Array<T, N>::size() {
  return size_ - 1;
}

template <typename T, size_t N>
typename s21::Array<T, N>::size_type s21::Array<T, N>::max_size() {
  return size();
}