#pragma once

#include <memory>
#include <stdexcept>
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
        switch (m_operator) {
        case '+':
            return m_left->evaluate() + m_right->evaluate();
        case '-':
            return m_left->evaluate() - m_right->evaluate();
        case '*':
            return m_left->evaluate() * m_right->evaluate();
        case '/': {
            const int right = m_right->evaluate();
            if (right == 0) {
                throw std::runtime_error("[ERROR: Can't divide by zero!]");
            }
            return m_left->evaluate() / right;
        }
        default:
            throw std::runtime_error("[ERROR: Invalid Operator!]");
        }
    }

    OperatorNode(char o, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : m_operator(o), m_left(std::move(l)), m_right(std::move(r)) {}
};
