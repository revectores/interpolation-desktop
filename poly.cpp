#include "poly.h"
#include "cmath"


bool term_cmp(Monomial term1, Monomial term2){
	return (term1.exp > term2.exp);
}


Monomial Monomial::operator+ (Monomial const &m){
	// assert(exp == m.exp);
    return Monomial(coef + m.coef, exp);
}

Monomial Monomial::operator* (Monomial const &m){
    return Monomial(coef * m.coef, exp + m.exp);
}

std::ostream& operator<< (std::ostream& os, const Monomial &m){
	if (m.coef == 0){
		return os;
	}

	if (m.coef > 0) {
		os << "+";
	}

	os << std::setprecision(10) << std::fixed << m.coef << "x^" << m.exp;
    return os;
}


Polynomial Polynomial::sort(){
	std::sort(terms.begin(), terms.end(), term_cmp);
	return *this;
}


Polynomial Polynomial::operator+ (Monomial const &m) {
	std::vector<Monomial> sum_terms = terms;
	for (auto it = sum_terms.begin(); it != sum_terms.end(); it++){
		if (it->exp == m.exp) {
			it->coef += m.coef;
			return Polynomial(sum_terms);
		}
	}
	sum_terms.push_back(m);
	return Polynomial(sum_terms);
}


Polynomial Polynomial::operator+ (Polynomial const &p) {
	Polynomial sum = terms;
	for (auto it = p.terms.begin(); it != p.terms.end(); it++){
		sum = sum + (*it);
	}
	return sum;
}


Polynomial Polynomial::operator* (Monomial const &m) {
	std::vector<Monomial> product_terms;
	for (auto it = terms.begin(); it != terms.end(); it++){
		product_terms.push_back((*it) * m);
	}
	return Polynomial(product_terms);
}


Polynomial Polynomial::operator* (Polynomial const &p) {
	Polynomial product;
	for (auto it = p.terms.begin(); it != p.terms.end(); it++){
		product = product + (*this) * (*it);
	}
	return product;
}


std::ostream& operator<< (std::ostream& os, const Polynomial &p){
	for (auto it = p.terms.begin(); it != p.terms.end(); it++){
		std::cout << *it << " ";
	}
    return os;
}


double Polynomial::evaluate(double x){
	double sum = 0;
	for (auto term_it = terms.begin(); term_it != terms.end(); term_it++){
		sum += term_it->coef * std::pow(x, term_it->exp);
	}
	return sum;
} 


Polynomial Lagrange_interp(std::vector<point> points) {
	Polynomial Lagrange_interp_polynomial {};

	int n = points.size();
	for (int k=0; k < n; k++){
		Polynomial product {std::vector<Monomial> {1, 0}};
		for (int i=0; i < n; i++){
			if (i == k) continue;
			Polynomial term {{{1, 1}, {-points[i].x, 0}}};
			term = term * (1.0 / (points[k].x - points[i].x));
			// std::cout << "k=" << k << "i=" << i << "term=" << term << std::endl;
			product = product * term;
		}
		product = product * points[k].y;
		// std::cout << "product=" << product << std::endl;
		Lagrange_interp_polynomial = Lagrange_interp_polynomial + product;
	}

	Lagrange_interp_polynomial.sort();
	return Lagrange_interp_polynomial;
}


Polynomial Newton_interp(std::vector<point> points) {
	Polynomial Newton_interp_polynomial {};

	int n = points.size();
	for (int k=1; k <= n; k++){
		double diff = 0;
		for (int i=0; i < k; i++){
			double denominator = 1;
			for (int j=0; j < k; j++){
				if (i==j) continue;
				denominator *= (points[i].x - points[j].x);
			}
			diff += points[i].y / denominator;
		}

		Polynomial prod {std::vector<Monomial> {1, 0}};
		for (int j=0; j<k-1; j++){
			Polynomial term {{{1, 1}, {-points[j].x, 0}}};
			prod = prod * term;
		}

		Newton_interp_polynomial = Newton_interp_polynomial + prod * diff;
	}

	Newton_interp_polynomial.sort();
	return Newton_interp_polynomial;
}




/*
int main(){
	Monomial a = Monomial(1, 3);
	Monomial b = Monomial(2, 5);
	Polynomial p1(std::vector<Monomial> {a, b});
	Polynomial p2(std::vector<Monomial> {b, a});
	std::cout << p1 * p2 << std::endl; // (x^3 + 2x^5)^2 = 4x^10 + 4x^8 + x^6

	// std::vector<point> points {{0, 1}, {1, 0}};
	std::vector<point> points {
		{0.4, 0.41075},
		{0.55, 0.57815},
		{0.65, 0.69675},
		{0.80, 0.90},
		{0.95, 1.00},
		{1.05, 1.25382}
	};

	std::vector<point> points {
		{1, 0.368},
		{2, 0.135},
		{3, 0.050},
		{4, 0.018},
		{5, 0.007},
		{6, 0.002},
		{7, 0.001},
	};
	
	std::cout << Newton_interp(points).sort() << std::endl;
	std::cout << Lagrange_interp(points).sort() << std::endl;

	// Polynomial a = Polynomial(std::vector<Monomial> {{1, 0}, {0, 1}});
	// std::cout << a * a << std::endl;
}
*/