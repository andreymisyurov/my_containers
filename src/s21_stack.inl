using namespace s21;

template <typename value_type>
stack<value_type>::stack() : m_count_(0), m_head_(nullptr) {}

template <typename value_type>
stack<value_type>::stack(std::initializer_list<value_type> const &items)
    : stack() {
  for (const_reference el : items) {
    push(el);
  }
}

template <typename value_type>
stack<value_type>::stack(const stack &other) : stack() {
  if (this != &other) {
    *this = other;
  }
}

template <typename value_type>
stack<value_type>::stack(stack &&other) {
  if (this != &other) {
    std::swap(m_head_, other.m_head_);
    std::swap(m_count_, other.m_count_);
    other.m_head_ = nullptr;
  }
}

template <typename value_type>
stack<value_type>::~stack() {
  while (m_head_ != nullptr) {
    pop();
  }
}

template <typename value_type>
stack<value_type> &stack<value_type>::operator=(stack &&other) {
  std::swap(m_head_, other.m_head_);
  std::swap(m_count_, other.m_count_);
  return *this;
}

template <typename value_type>
void stack<value_type>::copy_stack(stack<value_type> &other, Node *temp) {
  value_type my_perfect{};
  Node *check = temp;
  if (temp != nullptr) {
    my_perfect = temp->item_;
    temp = temp->prev_;
    copy_stack(other, temp);
  }
  if (check != nullptr) {
    other.push(my_perfect);
  }
}

template <typename value_type>
stack<value_type> &stack<value_type>::operator=(const stack &other) {
  if (this != &other) {
    Node *temp = other.m_head_;
    this->~stack();
    copy_stack(*this, temp);
  }
  return *this;
}

template <typename value_type>
const typename stack<value_type>::value_type &stack<value_type>::top() {
  return m_head_->item_;
}

template <typename value_type>
bool stack<value_type>::empty() {
  return (m_head_ == nullptr) ? true : false;
}

template <typename value_type>
size_t stack<value_type>::size() {
  return m_count_;
}

template <typename value_type>
void stack<value_type>::push(const value_type value) {
  m_head_ = new Node(value, m_head_);
  ++m_count_;
}

template <typename value_type>
void stack<value_type>::pop() {
  Node *temp = m_head_;
  m_head_ = m_head_->prev_;
  --m_count_;
  delete temp;
}

template <typename value_type>
void stack<value_type>::swap(stack &other) {
  if (this != &other) {
    std::swap(m_head_, other.m_head_);
    std::swap(m_count_, other.m_count_);
  }
}

template <typename value_type>
void stack<value_type>::emplace_front(value_type const last_value) {
  push(last_value);
};

template <typename value_type>
template <typename... Args>
void stack<value_type>::emplace_front(value_type const value, Args &&...args) {
  push(value);
  emplace_front(args...);
}
