#include <iostream>
#include "contracts.hpp"

enum OPTION_TYPE {CALL = 1, PUT = -1};

class European : public Contract
{
    protected:
        OPTION_TYPE option_type;

        double payoff(double price) override;

        double CalculateDelta(double forward_rate, double volatility, bool use_imp_vol = false) override;
        double CalculateGamma(double forward_rate, double volatility, bool use_imp_vol = false) override;
        double CalculateVega(double forward_rate, double volatility, bool use_imp_vol = false) override;
    public:
        European(OPTION_TYPE ot, double S, double p, double T, double K);
        void CalculateFairPrice(double forward_rate, double volatility, bool use_imp_vol = false) override;
};