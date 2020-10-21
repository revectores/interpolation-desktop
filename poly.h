#include "type.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>


class Monomial {
public:
	double coef;
	int exp;

	Monomial() {coef=0; exp=0;}
	Monomial(double _coef) {coef=_coef; exp=0;}
	Monomial(double _coef, int _exp){coef=_coef; exp=_exp;}
	~Monomial(){};

	Monomial operator+ (Monomial const &m);
	Monomial operator* (Monomial const &m);
    friend std::ostream& operator<< (std::ostream& os, const Monomial &m);
};

bool term_cmp(Monomial term1, Monomial term2);

class Polynomial {
public:
	std::vector<Monomial> terms;

	Polynomial() {terms = std::vector<Monomial> {};}
	Polynomial(Monomial term){terms = std::vector<Monomial> {term};}
	Polynomial(std::vector<Monomial> _terms) {terms = _terms;}

	Polynomial sort();
	Polynomial operator+ (Monomial const &m);
	Polynomial operator+ (Polynomial const &p);
	Polynomial operator* (Monomial const &m);
	Polynomial operator* (Polynomial const &p);
	friend std::ostream& operator<< (std::ostream& os, const Polynomial &p);
};



Polynomial Lagrange_interp(std::vector<point> points);
Polynomial Newton_interp(std::vector<point> points);

