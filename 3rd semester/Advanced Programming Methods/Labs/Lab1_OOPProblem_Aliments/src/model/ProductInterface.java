package model;
//interface where i define the methods for all of the classes implementing it - every aliment should return a price and a "presentation" of itself

public interface ProductInterface {
    double getPrice();
    String toString();
    String getName();
}

