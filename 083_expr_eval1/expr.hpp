#include <string>
#include <sstream>

class Expression {
public:
	Expression() {}
	virtual std::string toString() const = 0;
	virtual ~Expression() {}
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
  	virtual ~PlusExpression() {
   		delete left;
    	delete right;
  	}
};
