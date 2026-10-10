package model;

public class Sugar implements ProductInterface{
    private double pricePerKg;
    private String name;
    public Sugar(double ppk, String n)
    {
        this.pricePerKg = ppk;
        this.name = n;
    }

    //defining their own behaviour for a method => return its price
    @Override
    public double getPrice() {
        return this.pricePerKg;
    }

    //sugar will tell that it is a sugar and costs this much
    @Override
    public String toString()
    {
        return "Sugar " + this.name + "\nPrice per kg: " + this.getPrice() + "\n";
    }

    @Override
    public String getName(){
        return this.name;
    }
}