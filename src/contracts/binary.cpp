#include <iostream>
#include <assert.h>
#include <cmath>

#include "../../include/contracts/binary.hpp"
#include "../../include/util/stats.hpp"

Binary::Binary(OPTION_TYPE ot, double S, double p, double T, double K) : Contract(S, p, T, K)
{
    assert((ot==CALL) | (ot==PUT));
    option_type = ot;
}

double Binary::payoff(double price)
{
    /* Asset-or-nothing payout */
    if (strike < price) {return price;}
    else {return 0;}
}

double Binary::CalculateFairPrice(double forward_rate, double volatility, bool use_imp_vol)
{
    /* 
    Asset-or-nothing payout
    The fairvalue is equal to:
    Call --> S * exp(-qT) * N(d2)
    Put  --> S * exp(-qT) * N(-d2) */

    std::pair<double, double> dpair = CalculateD(forward_rate, volatility, use_imp_vol);
    double newprice = underlying_value * normalCDF(option_type * dpair.second);
    return newprice;
}

double Binary::CalculateDelta(double forward_rate, double volatility, bool use_imp_vol)
{

    double vol;
    vol = use_imp_vol ? implied_volatility : volatility;

    std::pair<double, double> dpair = CalculateD(forward_rate, volatility, use_imp_vol);
    return std::exp(-forward_rate * expiry) * normalPDF(option_type * dpair.second) / (underlying_value * vol * std::sqrt(expiry));
};

double Binary::CalculateGamma(double forward_rate, double volatility, bool use_imp_vol)
{
    double vol;
    vol = use_imp_vol ? implied_volatility : volatility;

    std::pair<double, double> dpair = CalculateD(forward_rate, volatility, use_imp_vol);
    return std::exp(-forward_rate * expiry) * d1 * normalPDF(option_type * dpair.second) / (underlying_value * underlying_value * vol * vol * expiry);
};

double Binary::CalculateVega(double forward_rate, double volatility, bool use_imp_vol)
{
    double vol;
    vol = use_imp_vol ? implied_volatility : volatility;

    std::pair<double, double> dpair = CalculateD(forward_rate, volatility, use_imp_vol);
    return std::exp(-forward_rate * expiry) * normalPDF(option_type * dpair.second) * d1 / vol;
};