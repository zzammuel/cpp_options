#include <assert.h>
#include <cmath>
#include <stdexcept>

#include "../../include/util/bisection.hpp"
#include "../../include/contracts/contracts.hpp"

Contract::Contract(double p, double T, double K)
{
    value = p;
    market_value = p;
    expiry = T;
    strike = K;

    implied_volatility = 0.0;
}

double Contract::getPrice()
{
    return value;
}

double Contract::getImpliedVol()
{
    return implied_volatility;
}

void Contract::ResolveContract()
{
    
}

std::pair<double, double> Contract::CalculateD(double underlying_value, double forward_rate, double volatility, bool use_imp_vol)
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

void Contract::CalculateImpliedVolatility(double quoted_price, double underlying_value, double forward_rate)
{
    // auto rootfunction = [this, forward_rate, quoted_price](double x){return CalculateFairPrice(forward_rate, x) - quoted_price;};

    auto vol = bisection(
        [this, underlying_value, forward_rate, quoted_price](double x){return CalculateFairPrice(underlying_value, forward_rate, x) - quoted_price;},
        0.0, 2.0
    );

    implied_volatility = vol;
}

double Contract::CalculateFairPrice(double underlying_value, double forward_rate, double volatility, bool use_imp_vol)
{
    throw std::runtime_error("Function is not implemented!");
}

double Contract::CalculateDelta(double underlying_value, double forward_rate, double volatility, bool use_imp_vol)
{
    throw std::runtime_error("Function is not implemented!");
}

double Contract::CalculateGamma(double underlying_value, double forward_rate, double volatility, bool use_imp_vol)
{
    throw std::runtime_error("Function is not implemented!");
}

double Contract::CalculateVega(double underlying_value, double forward_rate, double volatility, bool use_imp_vol)
{
    throw std::runtime_error("Function is not implemented!");
}

void Contract::ingest_new_point(double dt, double S, double forward_rate, double volatility)
{
    expiry -= dt;

    if (expiry <= 0){ResolveContract();}

    value = CalculateFairPrice(S, forward_rate, volatility);
    delta = CalculateDelta(S, forward_rate, volatility);
    gamma = CalculateGamma(S, forward_rate, volatility);
    vega = CalculateVega(S, forward_rate, volatility);
}