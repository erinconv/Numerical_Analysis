#pragma once
#include <iostream>
#include <cmath>

class SolutionMethod
{
public:
    // Constructor
    SolutionMethod(float (*f)(float), float (*fp)(float), float a, float b, float TOL);
    ~SolutionMethod();
    // Getter for each method
    void get_BisectRoot();
    void get_FalseRoot();
    void get_SecantRoot();
    void get_NewtonRoot();

private:
    // Memeber variables
    const float a_;             // lower bound
    const float b_;             // upper bound
    const float TOL_;           // tolerance
    const size_t max_iter_ = 1e+3; // maximum number of iterations (can be changed)
    float (*f_)(float);         // function to find root of
    float (*fp_)(float);        // derivative of function f_
    float root_;                // root of function
    // Methods
    float bisectionMethod();     // bisection method
    float falseRuleMethod();     // false-rule method
    float secantMethod();        // secant method
    float newtonraphsonMethod(); // Newton-Raphson method
};

// Constructor
SolutionMethod::SolutionMethod(float (*f)(float),
                               float (*fp)(float),
                               float a, float b,
                               float TOL) : a_(a),
                                            b_(b),
                                            f_(&(*f)),
                                            fp_(&(*fp)),
                                            TOL_(TOL)
{
}
// Destructor
SolutionMethod::~SolutionMethod()
{
}

void SolutionMethod::get_BisectRoot()
{
    std::cout << "The bisection method: " << bisectionMethod() << std::endl;
}

void SolutionMethod::get_NewtonRoot()
{
    std::cout << "The Newton-Raphson method: " << newtonraphsonMethod() << std::endl;
}

void SolutionMethod::get_FalseRoot()
{
    std::cout << "The False-Rule method: " << falseRuleMethod() << std::endl;
}
void SolutionMethod::get_SecantRoot()
{
    std::cout << "The Secant method: " << secantMethod() << std::endl;
}

float SolutionMethod::bisectionMethod()
{

    float a = a_;
    float b = b_;

    // initialize the iteration counter
    int i = 0;
    // compute the midpoint p of the interval [a,b]
    float p = (a + b) / 2;

    // while the interval [a,b] is greater than the specified tolerance, TOL_
    while ((b - a) / 2 > TOL_)
    {
        // if f(p) is equal to 0, terminate the algorithm and return p
        if (f_(p) == 0)
        {
            break;
        }
        // if f(p) is not equal to 0 and the number of iterations has reached the maximum number of iterations,
        // terminate the algorithm and print a message indicating that the maximum number of iterations has been exceeded
        else if (i == max_iter_)
        {
            std::cout << "Max iterations exceeded! ";
            break;
        }

        // if f(p) is not equal to 0 and the number of iterations has not reached the maximum, check the sign of f(p)
        // and f(a). If they have the same sign, update the interval to [a,b] where a = p.
        // If they have opposite signs, update the interval to [a,b] where b = p.
        if (f_(p) * f_(a) > 0)
        {
            a = p;
        }
        else
        {
            b = p;
        }

        // recompute the midpoint p of the updated interval [a,b]
        p = (a + b) / 2;

        // increment the iteration counter
        i = i + 1;
    }

    // return the midpoint p of the final interval [a,b]
    return p;
}

float SolutionMethod::newtonraphsonMethod()
{
    // initialize the starting value of p to the midpoint of the interval [a,b]
    float p0 = (a_ + b_) / 2;

    // compute the first approximation of the root using the Newton-Raphson formula
    float p = p0 - f_(p0) / fp_(p0);

    // initialize the iteration counter
    int i = 1;

    // while the difference between p and the previous value of p is greater than the specified tolerance, TOL_
    while (std::abs(p - p0) > TOL_)
    {
        // set the previous value of p to the current value of p
        p0 = p;

        // compute the next approximation of the root using the Newton-Raphson formula
        p = p0 - f_(p0) / fp_(p0);

        // increment the iteration counter
        i = i + 1;

        // if f(p) is equal to 0, terminate the algorithm and return p
        if (f_(p) == 0)
        {
            break;
        }
        // if the number of iterations has reached the maximum number of iterations,
        // terminate the algorithm and print a message indicating that the maximum number of iterations has been exceeded
        else if (i == max_iter_)
        {
            std::cout << "Max iterations exceeded! ";
            break;
        }
        // if the derivative f'(p) is equal to 0, print a message and return p
        else if (fp_ == 0)
        {
            std::cout << "Denominator equal to zero! ";
            return p;
            break;
        }
    }

    // return the final approximation of the root
    return p;
}

float SolutionMethod::secantMethod()
{
    // Initialize the function input values and the iteration counter
    float a = a_;
    float b = b_;
    int i = 1;

    // Evaluate the function at the initial input values
    float q0 = f_(a);
    float q1 = f_(b);

    // Compute the first approximation of the root
    float p = b - q1 * (b - a) / (q1 - q0);

    // Continue iterating until the difference between the current and previous approximations is less than the tolerance
    while (std::abs(p - a) > TOL_)
    {
        // Compute the next approximation of the root
        p = b - q1 * (b - a) / (q1 - q0);

        // Increment the iteration counter
        i = i + 1;

        // Check if the current approximation is the root, the maximum number of iterations has been reached, or the denominator is zero
        if (f_(p) == 0)
        {
            break;
        }
        else if (i == max_iter_)
        {
            std::cout << "Max iterations exceeded! ";
            break;
        }
        else if ((q1 - q0) == 0)
        {
            std::cout << "Denominator equal to zero! ";
            return p;
            break;
        }

        // Update the input values and function evaluations
        a = b;
        b = p;
        q0 = q1;
        q1 = f_(p);
    }

    // Return the final approximation of the root
    return p;
}

float SolutionMethod::falseRuleMethod()
{
    // Initialize variables
    int i = 0;
    float a = a_;
    float b = b_;
    // Compute initial estimate of the root
    float p = b - f_(b) * (b - a) / (f_(b) - f_(a));

    // Iterate until root is found or maximum number of iterations is reached
    while (std::abs(p - a) > TOL_)
    {
        // Update values of a and b
        a = b;
        b = p;
        // Compute new estimate of the root
        p = b - f_(b) * (b - a) / (f_(b) - f_(a));
        // Increment iteration counter
        i = i + 1;

        // Check for special cases and exit loop if necessary
        if (f_(p) == 0)
        {
            // Function value at p is zero, root has been found
            break;
        }
        else if (i == max_iter_)
        {
            // Maximum number of iterations reached, root could not be found
            std::cout << "Max iterations exceeded! ";
            return -9999;
            break;
        }
        else if ((f_(b) - f_(a)) == 0)
        {
            // Denominator of fraction is zero, return current estimate of root
            std::cout << "Denominator equal to zero! ";
            return p;
            break;
        }
    }

    // Return final estimate of the root
    return p;
}
