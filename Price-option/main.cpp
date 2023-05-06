#include <cmath>
#include <iostream>
#include <vector>

#include "AmOption.h"
#include "EurOption.h"
#include "GrowOption.h"
#include "ParOption.h"
#include "PricePathGenerator.h"

//Each class must be implemented in a separate cpp file which must have a corresponding header file.
//The task: to create a project for pricing path dependent options.
//
//Pricing is done under a binomial model (implemented in class BinModel).
//We will have
//        Perhaps we will need a class for path generator (implemented in class PricePathGenerator).
//The most general class is the class of options (Option).
//It has child classes: AmOption, EurOption (with dummy implementation as we are not interested in those)
//  and PathDependentOption.
//PathDependentOption has several subclasses:
//1)	LookbackBuy option: a lookback option is a path dependent option where the option owner has the right to buy (sell) the underlying instrument at its lowest (highest) price over some preceding period.
//2)	An AsianCall option with arithmetic average
//3)	ParOption: standard Parisian option: the payoff of a standard Parisian option is
//          dependent on the maximum amount of time the underlying asset value has spent consecutively above or below a strike price.
//4)	GrowOption: an option that pays an amount equal to the duration of the longest period of growth of the underlying asset.



// we need to have something that stores information about AllPathInfo 2^N of paths, we call this class PathsGenerator
// we also want to have a class PathInfo that stores the information about a single path with number x
// construction of the bijection between the set of AllPathInfo possible paths and the set of numbers {0,1,2,...,2^N-1}
// is left to the students
// later in the path dependent options we will retrieve vector of prices/a path/probability and calculate
// a payoff along a given path and perhaps multiply this payoff by the probability to find an
// average payoff along paths. Which then is discounted and the option price is obtained.


int main() {

    BinModel Model;
    if (Model.GetInputData() == 1) return 1;
    int N = 10; // read from input

    // Generate All Paths

    PathsGenerator MyPathGen(Model, N);
    AllPaths paths = MyPathGen.GenAllPaths();

    // create different flavours of options
    EurOption eurOption(Model, N);
    AmOption amOption(Model, N);
    ParOption parOption(Model, N, paths, 10);
    GrowOption growOption(Model, N, paths);

    // count prices
//    std::cout << "Eur Option Price: " << eurOption.GetPrice() << std::endl;
//    std::cout << "Am Option Price: " << amOption.GetPrice() << std::endl;
    std::cout << "Par Option Price: " << parOption.GetPrice() << std::endl;
    std::cout << "Grow Option Price: " << growOption.GetPrice() << std::endl;
    return 0;
}

