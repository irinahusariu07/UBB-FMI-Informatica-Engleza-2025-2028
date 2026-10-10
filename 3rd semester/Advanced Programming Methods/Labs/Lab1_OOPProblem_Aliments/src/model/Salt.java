package model;

public class Salt implements ProductInterface{
    private double pricePerKg;
    private String name;
    public Salt(double ppk, String n)
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
        return "Salt " + this.name + "\nPrice per kg: " + this.getPrice() + "\n";
    }
    @Override
    public String getName(){
        return this.name;
    }
}