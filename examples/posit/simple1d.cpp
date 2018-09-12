/* Boost libs/numeric/odeint/examples/simple1d.cpp

 Copyright 2012-2013 Mario Mulansky
 Copyright 2012 Karsten Ahnert

 example for a simple one-dimensional 1st order ODE

 Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#include <iostream>
#include <posit>
#include <boost/numeric/odeint.hpp>

using namespace std;
using namespace boost::numeric::odeint;
using namespace sw::unum;

constexpr size_t nbits = 16;
constexpr size_t es = 2;
using value_type = sw::unum::posit<nbits, es>;
using state_type = boost::array< value_type, 3 >;

/* we solve the simple ODE x' = 3/(2t^2) + x/(2t)
 * with initial condition x(1) = 0.
 * Analytic solution is x(t) = sqrt(t) - 1/t
 */
template<typename Ty>
void rhs( const Ty x , Ty &dxdt , const Ty t )
{
    dxdt = 3.0/(2.0*t*t) + x/(2.0*t);
}

template<typename Ty>
void write_cout( const Ty &x , const Ty t )
{
    cout << t << '\t' << x << endl;
}

int main()
{
#if 0
	{
		using state_type = double;
		using stepper_type = runge_kutta_dopri5< state_type > ;

		double x = 0.0; //initial value x(1) = 0
		// use dopri5 with stepsize control and allowed errors 10^-12, integrate t=1...10
		integrate_adaptive( make_controlled( 1E-12 , 1E-12 , stepper_type() ) , rhs<double> , x , 1.0 , 10.0 , 0.1 , write_cout<state_type> );
	}
#else
	{
		using stepper_type = runge_kutta_dopri5< value_type, value_type >;

		double abs_error_delta = 1E-12;
		double rel_error_delta = 1E-12;
		// compare minpos of the posit configuration to error deltas requested
		cout << minpos<nbits, es>() << (minpos<nbits,es>() < abs_error_delta ? " < " : " !< ") << abs_error_delta << endl;

		value_type abs_error = abs_error_delta;
		value_type rel_error = rel_error_delta;
		value_type x = 0.0; //initial value x(1) = 0
						    // use dopri5 with stepsize control and allowed errors 10^-12, integrate t=1...10
		value_type start = 1.0;
		value_type stop = 10.0;
		value_type time_step = 0.1;
		integrate_adaptive( make_controlled( abs_error, rel_error, stepper_type() ), rhs<value_type>, x, start, stop, time_step, write_cout<value_type>);
	}
#endif
}
