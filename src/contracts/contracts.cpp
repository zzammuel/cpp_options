#include <assert.h>
#include <cmath>
#include <stdexcept>

#include "../../include/util/bisection.hpp"
#include "../../include/contracts/contracts.hpp"

Contract::Contract(double S, double p, double T, double K)
{
    underlying_value = S;
    current_value = p;
    market_value = p;
    expiry = T;
    strike = K;

    implied_volatility = 0.0;
}

double Contract::getPrice()
{
    return current_value;
}

double Contract::getImpliedVol()
{
    return implied_volatility;
}

void Contract::ResolveContract()
{
    
}

std::pair<double, double> Contract::CalculateD(double forward_rate, double volatility, bool use_imp_vol)
{
    double vol;
    vol = use_imp_vol ? implied_volatility : volatility;

    d1 = std::log(underlying_value / strike) + (forward_rate + vol * vol / 2.0) * expiry;
    d1 /= (vol * std::sqrt(expiry));
    d2 = d1 - vol * std::sqrt(expiry);

    std::pair dpair = {d1, d2};

    return dpair;
}

double Contract::payoff(double price)
{
    throw std::runtime_error("Function is not implemented!");
}

void Contract::CalculateImpliedVolatility(double quoted_price, double forward_rate)
{
    // auto rootfunction = [this, forward_rate, quoted_price](double x){return CalculateFairPrice(forward_rate, x) - quoted_price;};

    auto vol = bisection(
        [this, forward_rate, quoted_price](double x){return CalculateFairPrice(forward_rate, x) - quoted_price;},
        0.0, 2.0
    );

    implied_volatility = vol;
}

double Contract::CalculateFairPrice(double forward_rate, double volatility, bool use_imp_vol)
{
    throw std::runtime_error("Function is not implemented!");
}

double Contract::CalculateDelta(double forward_rate, double volatility, bool use_imp_vol)
{
    throw std::runtime_error("Function is not implemented!");
}

double Contract::CalculateGamma(double forward_rate, double volatility, bool use_imp_vol)
{
    throw std::runtime_error("Function is not implemented!");
}

double Contract::CalculateVega(double forward_rate, double volatility, bool use_imp_vol)
{
    throw std::runtime_error("Function is not implemented!");
}

void Contract::ingest_new_point(double dt, double S, double forward_rate, double volatility)
{
    underlying_value = S;
    expiry -= dt;

    if (expiry <= 0){ResolveContract();}

    current_value = CalculateFairPrice(forward_rate, volatility);
}