#include <assert.h>
#include <cmath>
#include <stdexcept>

#include "../../include/contracts/contracts.hpp"

Contract::Contract(double S, double p, double T, double K)
{
    underlying_value = S;
    current_value = p;
    market_value = p;
    expiry = T;
    strike = K;
}

double Contract::getPrice()
{
    return current_value;
}

void Contract::ResolveContract()
{
    
}

void Contract::CalculateD(double forward_rate, double volatility, bool use_imp_vol)
{
    double vol;
    vol = use_imp_vol ? implied_volatility : volatility;

    d1 = std::log(underlying_value / strike) + (forward_rate + vol * vol / 2.0) * expiry;
    d1 /= (vol * std::sqrt(expiry));
    d2 = d1 - vol * std::sqrt(expiry);

}

double Contract::payoff(double price)
{
    throw std::runtime_error("Function is not implemented!");
}

void Contract::CalculateImpliedVolatility()
{
    throw std::runtime_error("Function is not implemented!"); 
}

void Contract::CalculateFairPrice(double forward_rate, double volatility, bool use_imp_vol)
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

    CalculateD(forward_rate, volatility);
    CalculateFairPrice(forward_rate, volatility);
}