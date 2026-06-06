#include <iostream>
#include <cmath>
#include <string>

struct Option {
    double stock_price;
    double strike_price;
    double time_to_maturity;
    double rfir;
    double vol;
};

double normalCDF(double x){
    return 0.5 * std::erfc(-x * std::sqrt(0.5));
}

Option& userInput(Option& opt){
    std::cout << "please enter stock price: \n";
    std::cin >> opt.stock_price;

    std::cout << "enter strike: \n";
    std::cin >> opt.strike_price;

    std::cout << "enter time to maturity: \n";
    std::cin >> opt.time_to_maturity;

    std::cout << "enter risk free interest rate: \n";
    std::cin >> opt.rfir;

    std::cout << "enter volatility: \n";
    std::cin >> opt.vol;

    return opt;
}

bool chooseoptionType(){
    char uin;

    while(true){
        std::cout << "type c for call option calculation, p for put: \n";
        std::cin >> uin;

        if (uin == 'c' || uin =='C'){
            std::cout << "you chose call.\n";
            return true;
        }
        if (uin == 'p' || uin =='P'){
            std::cout << "you chose put.\n";
            return false;
        }
        else{
            std::cerr << "please enter c or p for option type selection. \n";
        }
    }
}


double d1Calculator(const Option& opt){
    double S = opt.stock_price;
    double K = opt.strike_price;
    double T = opt.time_to_maturity;
    double r = opt.rfir;
    double sigma = opt.vol;

    return (std::log(S / K) + (r + 0.5 * std::pow(sigma, 2)) * T) / (sigma * std::sqrt(T));
}


double d2Calculator(const Option& opt, double d1){
    return d1 - (opt.vol * std::sqrt(opt.time_to_maturity));
}


double bsCalculator(const Option& opt, double d1, double d2, bool isCall){
    double S = opt.stock_price;
    double K = opt.strike_price;
    double T = opt.time_to_maturity;
    double r = opt.rfir;

    if (isCall) {
        // Call pricing logic
        return S * normalCDF(d1) - K * std::exp(-r * T) * normalCDF(d2);
    } else {
        // Put pricing logic
        return K * std::exp(-r * T) * normalCDF(-d2) - S * normalCDF(-d1);
    }
}

int main(){
    Option opt;

    userInput(opt);

    bool isCall = chooseoptionType(); //you can asign variables to a functions return value

    double d1 = d1Calculator(opt);
    double d2 = d2Calculator(opt, d1);

    double finalPrice = bsCalculator(opt, d1, d2, isCall);


    std::cout << "\nThe calculated option price is: $" << finalPrice << "\n";
    return 0;
}