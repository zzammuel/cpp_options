#include <iostream>
#include <assert.h>
#include <cmath>

#include "../../include/util/stats.hpp"
#include "../../include/contracts/european.hpp"

European::European(OPTION_TYPE ot, double p, double T, double K) : Contract(p, T, K)
{
    assert((ot==CALL) | (ot==PUT));
    option_type = ot;
};

double European::payoff(double price)
{
    return std::max(0.0, option_type * (price - strike));
}

double European::CalculateFairPrice(double underlying_value, double forward_rate, double volatility, bool use_imp_vol)
{
    /* The fairvalue is equal to:
    Call --> S * N(d1) - K * exp(-rT) * N(d2)
    Put  --> K * exp(-rT) * N(-d2) - S * N(-d1) */
    
    std::pair<double, double> dpair = CalculateD(forward_rate, volatility, use_imp_vol);
    double newprice = option_type * (normalCDF(option_type * dpair.first) * underlying_value - normalCDF(option_type * dpair.second) * strike * std::exp(-forward_rate * expiry));
    return newprice;
}

double European::CalculateDelta(double underlying_value, double forward_rate, double volatility, bool use_imp_vol)
{
    /* The Delta is equal to:
    Call --> N(d1)
    Put  --> -N(-d1)*/
    
    std::pair<double, double> dpair = CalculateD(forward_rate, volatility, use_imp_vol);
    return option_type * normalCDF(option_type * dpair.first);
}

double European::CalculateGamma(double underlying_value, double forward_rate, double volatility, bool use_imp_vol)
{
    /* The Gamma is equal to
    Call --> n(d1) / (S * vol * sqrt(T))
    Put  --> n(d1) / (S * vol * sqrt(T))*/
    double vol;
    vol = use_imp_vol ? implied_volatility : volatility;
        
    std::pair<double, double> dpair = CalculateD(forward_rate, volatility, use_imp_vol);
    return normalPDF(dpair.first) / (underlying_value * vol * std::sqrt(expiry));
}

double European::CalculateVega(double underlying_value, double forward_rate, double volatility, bool use_imp_vol)
{
    /* The Vega is equal to:
    Call --> S * n(d1) * sqrt(T)
    Put  --> S * n(d1) * sqrt(T) */

    std::pair<double, double> dpair = CalculateD(forward_rate, volatility, use_imp_vol);   
    return underlying_value * std::sqrt(expiry) * normalPDF(dpair.first);
}