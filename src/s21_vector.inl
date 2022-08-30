#pragma once
using namespace s21;

template <typename value_type>
vector<value_type>::vector() {
  cap_ = 100;
  item_ = new value_type[cap_];
  it_begin_.setIterator(item_);
  it_end_.setIterator(item_);
}

template <typename value_type>
vector<value_type>::vector(size_type size) {
  if (size < 1) {
    throw std::runtime_error("your vector can't create, because size < 1");
  }
  cap_ = size;
  item_ = new value_type[cap_];
  it_begin_.setIterator(item_);
  it_end_.setIterator(item_);
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items) {
  count_ = 0;
  cap_ = items.size() * 2;
  item_ = new value_type[cap_];
  it_begin_.setIterator(item_);
  for (value_type temp : items) {
    push_back(temp);
  }
  it_end_.setIterator(item_ + items.size());
}

template <typename value_type>
vector<value_type>::vector(const vector &other) {
  *this = other;
}

template <typename value_type>
vector<value_type>::vector(vector &&other) {
  *this = other;
};

template <typename value_type>
vector<value_type>::~vector() {
  delete[] item_;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(const vector &other) {
  if (this != &other) {
    vector<value_type> temp(other.cap_);
    for (auto i = other.begin(), endl = other.end(); i != endl; ++i) {
      temp.push_back(*i);
    }

    this->swap(temp);
  }
  return *this;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(vector &&other) {
  if (this != &other) {
    std::swap(item_, other.item_);
    std::swap(count_, other.count_);
    std::swap(cap_, other.cap_);
    std::swap(it_begin_, other.it_begin_);
    std::swap(it_end_, other.it_end_);
  }
  return *this;
}

template <typename value_type>
void vector<value_type>::clear() {
  memset(item_, 0, sizeof(value_type) * count_);
  count_ = 0;
}

template <typename value_type>
void vector<value_type>::push_back(const value_type &value) {
  if ((count_ + 1) > max_size()) {
    throw std::runtime_error("exceeded max size");
  }
  check_fillness();
  item_[++count_ - 1] = value;
  ++it_end_;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  item_[--count_] = 0;
  --it_end_;
}

template <typename value_type>
void vector<value_type>::check_fillness() {
  if (capacity() < 3) {
    value_type *temp = item_;
    cap_ *= 2;
    value_type *novella = new value_type[cap_];
    std::memcpy(novella, temp, sizeof(value_type) * count_);
    std::swap(item_, novella);
    delete[] temp;
  }
}

template <typename value_type>
void vector<value_type>::swap(vector<value_type> &other) noexcept {
  std::swap(item_, other.item_);
  std::swap(count_, other.count_);
  std::swap(cap_, other.cap_);
}

template <typename value_type>
void vector<value_type>::reserve(size_t size) {
  if (size > cap_) {
    vector<value_type> temp(size);
    cap_ = size;
    memcpy(temp.item_, item_, sizeof(value_type) * count_);
    std::swap(item_, temp.item_);
  }
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  vector<value_type> temp(count_);
  cap_ = count_;
  memcpy(temp.item_, item_, sizeof(value_type) * count_);
  std::swap(item_, temp.item_);
}

template <typename value_type>
value_type &vector<value_type>::at(size_t pos) {
  if (pos > (count_ - 1)) {
    throw std::range_error("you havn't this index");
  }
  return item_[pos];
}

template <typename value_type>
const value_type &vector<value_type>::front() {
  if (empty()) {
    throw std::runtime_error("vector is empty");
  }
  return item_[0];
}

template <typename value_type>
const value_type &vector<value_type>::back() {
  if (count_ == 0) {
    throw std::runtime_error("vector is empty");
  }
  return (item_)[count_ - 1];
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
  if (pos >= it_end_ || pos < it_begin_) {
    throw std::runtime_error(
        "your vector said \"segmentation fault\" to your erase\n");
  }
  value_type *temp = item_;
  for (auto iter = it_begin_; iter != it_end_; ++iter) {
    if (iter != pos) {
      *temp = *iter;
      ++temp;
    }
  }
  --count_;
  --it_end_;
  *it_end_ = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const value_type &value) {
  if ((count_ + 1) > max_size()) {
    throw std::range_error("exceeded max size");
  }
  iterator temp = it_end_;
  if ((pos > it_end_) || (pos < it_begin_)) {
    throw std::runtime_error(
        "your vector said \"segmentation fault\" to your insert\n");
  }
  if (pos == temp) {
    *temp = value;
  } else {
    iterator needle = it_end_;
    --needle;
    for (; needle >= pos; --needle, --temp) {
      if (needle > pos) {
        *temp = *needle;
      } else {
        *temp = *needle;
        *needle = value;
      }
    }
  }
  count_++;
  ++it_end_;
  return temp;
}

template <typename value_type>
template <class... Args>
typename vector<value_type>::iterator vector<value_type>::emplace(
    const iterator pos, Args &&...args) {
  value_type storage[] = {args...};
  auto current = pos;
  for (value_type &elem : storage) {
    insert(current, elem);
    ++current;
  }
  return pos;
}

template <typename value_type>
template <class... Args>
void vector<value_type>::emplace_back(Args &&...args) {
  value_type storage[] = {args...};
  for (value_type &elem : storage) {
    push_back(elem);
  }
}

template <typename value_type>
bool vector<value_type>::empty() {
  return !count_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() {
  return count_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() {
  return static_cast<long>(9223372036854775807) / sizeof(value_type);
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() {
  return cap_;
}