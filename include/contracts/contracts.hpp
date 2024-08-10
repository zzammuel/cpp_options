class Contract
{
    protected:
        double current_value; // Current price of the contract
        double underlying_value; // Price of underlying asset
        double market_value; // Price at which the contract was bought or sold
        double expiry; // Time until the contract expires
        double strike; // The strike price of the contract

        double d1, d2;
        double implied_volatility;

        void ResolveContract();

        virtual double payoff(double price);

        void CalculateImpliedVolatility();
        virtual double CalculateDelta(double forward_rate, double volatility, bool use_imp_vol = false);
        virtual double CalculateVega(double forward_rate, double volatility, bool use_imp_vol = false);
        virtual double CalculateGamma(double forward_rate, double volatility, bool use_imp_vol = false);
    public:
        Contract(double s, double p, double T, double K);

        double getPrice();

        virtual void CalculateFairPrice(double forward_rate, double volatility, bool use_imp_vol = false);
        
        // Make an evaluator class??
        void CalculateD(double forward_rate, double volatility, bool use_imp_vol = false);

        void ingest_new_point(double dt, double S, double forward_rate, double volatility);
};