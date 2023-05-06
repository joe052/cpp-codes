class LookbackOption {
private:
    double S0;  // Initial asset price
    double U;   // Up factor
    double D;   // Down factor
    double R;   // Risk-free interest rate
    double Kp;  // Strike price
    int N;      // Number of steps to expiry

public:
    LookbackOption(double S0_, double U_, double D_, double R_, double Kp_, int N_) {
        S0 = S0_;
        U = U_;
        D = D_;
        R = R_;
        Kp = Kp_;
        N = N_;
    }

    double price() {
        double dt = 1.0 / N;
        double u = exp(U * sqrt(dt));
        double d = exp(-D * sqrt(dt));
        double p = (exp(R * dt) - d) / (u - d);
        double q = 1.0 - p;

        double min_price = S0 * pow(d, N);
        double max_price = S0 * pow(u, N);

        double payoff = max(max_price - Kp, 0.0) - max(S0 - min_price, 0.0);

        return exp(-R * dt * N) * (p * payoff + q * 0.0);
    }
};

int main() {
  // Initialize input variables
  double S0, U, D, R, Ka, Kp;
  int N;

  // Prompt user to enter values of input variables
  std::cout << "Enter the value of S0: ";
  std::cin >> S0;

  std::cout << "Enter the value of U: ";
  std::cin >> U;

  std::cout << "Enter the value of D: ";
  std::cin >> D;

  std::cout << "Enter the value of R: ";
  std::cin >> R;

  std::cout << "Enter the value of Ka: ";
  std::cin >> Ka;

  std::cout << "Enter the value of Kp: ";
  std::cin >> Kp;

  std::cout << "Enter the value of N: ";
  std::cin >> N;

  // Calculate the prices of the options
  BinomialTree bt(S0, U, D, R, N);
  AsianCallOption asian_call(Ka);
  double asian_call_price = asian_call.Price(bt);

  LookbackOption lookback_option(Kp);
  double lookback_option_price = lookback_option.Price(bt);

  // Display the prices of the options to the user
  std::cout << "The price of the Asian Call Option is: " << asian_call_price << std::endl;
  std::cout << "The price of the Lookback Option is: " << lookback_option_price << std::endl;

  return 0;
}
