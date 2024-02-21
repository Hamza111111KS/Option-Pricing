# Option-Pricing
Option Pricing Model (Black Scholes Model) and Greek Calculation.


The "Option Pricing Model (Black Scholes Model) and Greek Calculation" project is a C++ implementation of the Black-Scholes option pricing model along with the calculation of option Greeks. The Black-Scholes model is a mathematical model widely used for pricing options contracts. It provides a theoretical estimate of the price of financial options under certain assumptions, including constant volatility and risk-free interest rate.

This project consists of several components:

OptionsPricing.h/cpp: This component contains the implementation of the Black-Scholes option pricing model. It includes functions to calculate the price of a European call or put option based on the Black-Scholes formula. Additionally, it provides functions to calculate the payoffs of options.

Parsing.h/cpp: This component handles the parsing of CSV files containing option data. It includes functions to read option data from a CSV file, parse the data, and store it in a suitable data structure for further processing.

Reading.h/cpp: This component handles the reading of CSV files and the output of results. It includes functions to read CSV files, process the data using the Black-Scholes model, and output the results to a CSV file.

main.cpp: This is the main entry point of the program. It demonstrates how to use the functionality provided by the other components to price options and calculate option Greeks. It reads option data from a CSV file, calculates option prices and payoffs, and outputs the results to another CSV file.

OptionData: This structure represents the attributes of an option, such as spot price, strike price, maturity, interest rate, volatility, and option type.

The project aims to provide a comprehensive tool for pricing options and calculating option Greeks using the Black-Scholes model. Users can input option data from CSV files, obtain option prices, payoffs, and other important metrics, and analyze the sensitivity of option prices to changes in underlying parameters using option Greeks such as delta, gamma, theta, vega, and rho.

This project can serve as a valuable resource for financial analysts, traders, and researchers interested in options pricing and risk management. It can be further extended to include additional features or integrated into larger financial software systems.
