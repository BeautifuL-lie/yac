#pragma once

#include <memory>
#include <utility>

class Node {
  public:
    virtual int evaluate() const = 0;
    virtual ~Node() = default;
};

class NumberNode : public Node {
  private:
    int m_value;

  public:
    int evaluate() const override {
        return m_value;
    }

    NumberNode(int v) : m_value(v) {}
};

class OperatorNode : public Node {
  private:
    char m_operator;
    std::unique_ptr<Node> m_left;
    std::unique_ptr<Node> m_right;

  public:
    int evaluate() const override {
        if (m_operator == '+') {
            return m_left->evaluate() + m_right->evaluate();
        } else {
            return m_left->evaluate() - m_right->evaluate();
        }
    }

    OperatorNode(char o, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : m_operator(o), m_left(std::move(l)), m_right(std::move(r)) {}
};
