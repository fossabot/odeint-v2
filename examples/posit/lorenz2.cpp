/*
 * lorenz2.cpp
 *
 * This example demonstrates how odeint can be used with posit universal numbers.
 *
 * Copyright 2018 Theodore Omtzigt
 *
 * ODEintv2 distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#include <iostream>
#include <boost/array.hpp>

#include <boost/numeric/odeint.hpp>

#include <universal/posit/posit>

using namespace std;
using namespace boost::numeric::odeint;

const double sigma = 10.0;
const double R = 28.0;
const double b = 8.0 / 3.0;

constexpr size_t nbits = 256;
constexpr size_t es = 5;
using Real = sw::unum::posit<nbits, es>;
//using Real = float;

using value_type = Real;
using state_type = boost::array< value_type, 3 >;

void lorenz(const state_type &x, state_type &dxdt, double t)
{
	dxdt[0] = sigma * (x[1] - x[0]);
	dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
	dxdt[2] = -b * x[2] + x[0] * x[1];
}

void write_lorenz(const state_type &x, const double t)
{
	cout << t << '\t' << x[0] << '\t' << x[1] << '\t' << x[2] << endl;
}

int main(int argc, char **argv)
{
	state_type x = { 10.0 , 1.0 , 1.0 }; // initial conditions
	integrate(lorenz, x, 0.0, 5.0, 0.125, write_lorenz);
}
