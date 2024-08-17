#include <iostream>
#include "contracts.hpp"

class European : public Contract
{
    protected:
        OPTION_TYPE option_type;

        double payoff(double price) override;

    public:
        European(OPTION_TYPE ot, double p, double T, double K);
        
        double CalculateFairPrice(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false) override;
        double CalculateDelta(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false) override;
        double CalculateGamma(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false) override;
        double CalculateVega(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false) override;
};