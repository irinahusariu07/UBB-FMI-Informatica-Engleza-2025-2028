package model;

public class Flour implements ProductInterface{
    private double pricePerKg;
    private String name;
    public Flour(double ppk, String n)
    {
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
        return "Flour " + this.name + "\nPrice per kg: " + this.getPrice() + "\n";
    }

    @Override
    public String getName() {
        return this.name;
    }
}

