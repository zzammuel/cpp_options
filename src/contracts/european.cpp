#include <iostream>
#include <assert.h>
#include <cmath>

#include "../../include/util/stats.hpp"
#include "../../include/contracts/european.hpp"

European::European(OPTION_TYPE ot, double S, double p, double T, double K) : Contract(S, p, T, K)
{
    assert((ot==CALL) | (ot==PUT));
    option_type = ot;
};

double European::payoff(double price)
{
    return std::max(0.0, option_type * (price - strike));
}

void European::CalculateFairPrice(double forward_rate, double volatility, bool use_imp_vol)
{
    /* The fairvalue is equal to:
    Call --> S * N(d1) - K * exp(-rT) * N(d2)
    Put  --> K * exp(-rT) * N(-d2) - S * N(-d1) */
    
    current_value = option_type * (normalCDF(option_type * d1) * underlying_value - normalCDF(option_type * d2) * strike * std::exp(-forward_rate * expiry));
}

double European::CalculateDelta(double forward_rate, double volatility, bool use_imp_vol)
{
    /* The Delta is equal to:
    Call --> N(d1)
    Put  --> -N(-d1)*/
    
    return option_type * normalCDF(option_type * d1);
}

double European::CalculateGamma(double forward_rate, double volatility, bool use_imp_vol)
{
    /* The Gamma is equal to
    Call --> n(d1) / (S * vol * sqrt(T))
    Put  --> n(d1) / (S * vol * sqrt(T))*/
    double vol;
    vol = use_imp_vol ? implied_volatility : volatility;
        
    return normalPDF(d1) / (underlying_value * vol * std::sqrt(expiry));
}

double European::CalculateVega(double forward_rate, double volatility, bool use_imp_vol)
{
    /* The Vega is equal to:
    Call --> S * n(d1) * sqrt(T)
    Put  --> S * n(d1) * sqrt(T) */
    
    return underlying_value * std::sqrt(expiry) * normalPDF(d1);
}