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
    if (strike < price) {return strike;}
    else {return 0;}
}

void Binary::CalculateFairPrice(double forward_rate, double volatility, bool use_imp_vol)
{
    /* The fairvalue is equal to:
    Call --> exp(-rT) * N(d2)
    Put  --> exp(-rT) * N(-d2) */

    current_value = std::exp(-forward_rate * expiry) * normalCDF(option_type * d2);
}

double Binary::CalculateDelta(double forward_rate, double volatility, bool use_imp_vol)
{

    double vol;
    vol = use_imp_vol ? implied_volatility : volatility;

    return std::exp(-forward_rate * expiry) * normalPDF(option_type * d2) / (underlying_value * vol * std::sqrt(expiry));
};

double Binary::CalculateGamma(double forward_rate, double volatility, bool use_imp_vol)
{
    double vol;
    vol = use_imp_vol ? implied_volatility : volatility;

    return std::exp(-forward_rate * expiry) * d1 * normalPDF(option_type * d2) / (underlying_value * underlying_value * vol * vol * expiry);
};

double Binary::CalculateVega(double forward_rate, double volatility, bool use_imp_vol)
{
    double vol;
    vol = use_imp_vol ? implied_volatility : volatility;

    return std::exp(-forward_rate * expiry) * normalPDF(option_type * d2) * d1 / vol;
};