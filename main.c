#include <math.h>
#include <stdio.h>
#include <stdlib.h>


double deduceRate(double numberOfInstallments, double equatedInstallment, double Principal, double futureValue, double type, double guess) {
    
    int MAX_ITERATIONS = 8, iterator = 0;

    double FINANCIAL_PRECISION = 0.000001;

    double x0 = 0, x1 = 0.0, factor = 0.0;

    double iteratedInterestRate = guess;

    double y, y0, y1;

    if (fabs(iteratedInterestRate) < FINANCIAL_PRECISION) {

        y = Principal * (1 + numberOfInstallments * iteratedInterestRate) + equatedInstallment * (1 + iteratedInterestRate * type) * numberOfInstallments + futureValue;

    } else {

        factor = exp(numberOfInstallments * log(1 + iteratedInterestRate));


        y = Principal * factor + equatedInstallment * (1 / iteratedInterestRate + type) * (factor - 1) + futureValue;

    }

    y0 = Principal + equatedInstallment * numberOfInstallments + futureValue;

    y1 = Principal * factor + equatedInstallment * (1 / iteratedInterestRate + type) * (factor - 1) + futureValue;


    x1 = iteratedInterestRate;


    while ((fabs(y0 - y1) > FINANCIAL_PRECISION) && (iterator < MAX_ITERATIONS)) {

        iteratedInterestRate = (y1 * x0 - y0 * x1) / (y1 - y0);

        x0 = x1;

        x1 = iteratedInterestRate;

        if (fabs(iteratedInterestRate) < FINANCIAL_PRECISION) {

            y = Principal * (1 + numberOfInstallments * iteratedInterestRate) + equatedInstallment * (1 + iteratedInterestRate * type) * numberOfInstallments + futureValue;

        } 
        else {

            factor = exp(numberOfInstallments * log(1 + iteratedInterestRate));

            y = Principal * factor + equatedInstallment * (1 / iteratedInterestRate + type) * (factor - 1) + futureValue;
        }

        y0 = y1;

        y1 = y;

        ++iterator;
    }

    return iteratedInterestRate;

}


double rateCalculation(double numberOfInstallments, double equatedInstallment, double Principal) {

    double futureValue = 0;

    double type = 0;

    equatedInstallment = -equatedInstallment;
    
    double powerFactor = log(1.0 + 1.0 / numberOfInstallments) / log(2.0);

    double rateGuess = pow(pow(1.0 - equatedInstallment/Principal, 1.0/powerFactor) - 1.0, powerFactor) - 1.0;

    double guess = rateGuess;

    return deduceRate(numberOfInstallments, equatedInstallment, Principal, futureValue, type, guess);
}


int main(int argc, char *argv[]) {

    double numberOfInstallments = atof(argv[1]);
    double equatedInstallment = atof(argv[2]);
    double Principal = atof(argv[3]);

    printf("%.2f%%\n",rateCalculation(numberOfInstallments, equatedInstallment, Principal) * 100);

}
