#include <string>
#include <sstream>

class Expression {
public:
	Expression() {}
	virtual std::string toString() const = 0;
	virtual ~Expression() {}
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression {
	long numVal;
public:
	NumExpression(long n) : numVal(n) {}
	virtual std::string toString() const {
		std::stringstream ret;
		ret << numVal;
		return ret.str();
	}
  virtual ~NumExpression() {} 
  virtual long evaluate() const {
    return numVal;
  }
};


class PlusExpression : public Expression {
	Expression * left;
	Expression * right;
public:
	PlusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
	virtual std::string toString() const {
    	std::stringstream ret;
    	ret << "(" << left->toString() << " + " << right->toString() << ")";
    	return ret.str();
  	}
  virtual long evaluate() const {
    long ret;
    ret = left->evaluate() + right->evaluate();
    return ret;
  }
  virtual ~PlusExpression() {
    delete left;
    delete right;
  }
};

class MinusExpression : public Expression
{
  Expression * left;
  Expression * right;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::stringstream ret;
    ret << "(" << left->toString() << " - " << right->toString() << ")";
    return ret.str();
  }
  virtual ~MinusExpression() {
    delete left;
    delete right;
  }
  virtual long evaluate() const {
    long ret;
    ret = left->evaluate() - right->evaluate();
    return ret;
  }
};


class TimesExpression : public Expression
{
  Expression * left;
  Expression * right;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::stringstream ret;
    ret << "(" << left->toString() << " * " << right->toString() << ")";
    return ret.str();
  }
  virtual ~TimesExpression() {
    delete left;
    delete right;
  }
  virtual long evaluate() const {
    long ret;
    ret = left->evaluate() * right->evaluate();
    return ret;
  }
};

class DivExpression : public Expression
{
  Expression * left;
  Expression * right;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::stringstream ret;
    ret << "(" << left->toString() << " / " << right->toString() << ")";
    return ret.str();
  }
  virtual ~DivExpression() {
    delete left;
    delete right;
  }
  virtual long evaluate() const {
    long ret;
    ret = left->evaluate() / right->evaluate();
    return ret;
  }
};

