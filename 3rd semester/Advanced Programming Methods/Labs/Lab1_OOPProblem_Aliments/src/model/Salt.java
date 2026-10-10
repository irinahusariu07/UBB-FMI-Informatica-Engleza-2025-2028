package model;

import exceptions.NegativeNumberException;

public class Salt implements ProductInterface{
    private double pricePerKg;
    private String name;
    public Salt(double ppk, String n) throws NegativeNumberException
    {
        if(ppk < 0) throw new NegativeNumberException("Number is negative");
        this.pricePerKg = ppk;
        this.name = n;
    }

    @Override
    public double getPrice() {
        return this.pricePerKg;
    }

    @Override
    public String toString()
    {
        return "Salt " + this.name + "\nPrice per kg: " + this.getPrice() + "\n";
    }
    @Override
    public String getName(){
        return this.name;
    }
}