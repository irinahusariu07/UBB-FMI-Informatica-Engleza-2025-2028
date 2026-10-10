package view;
import controller.Controller;
import exceptions.RepoException;
import model.Flour;
import model.Salt;
import model.Sugar;
import repo.RepoInterface;
import model.ProductInterface;

public class View
{
    private Controller controller;
    public View(Controller ctrl)
    {
        this.controller = ctrl;
    }

    public void run()
    {
        try
        {
            //initial 7 produse
            controller.addProduct(new Sugar(20.5, "sugar1"));
            controller.addProduct(new Sugar(18.9, "sugar2"));
            controller.addProduct(new Salt(17.7, "salt1"));
            controller.addProduct(new Salt(19.9, "salt2"));
            controller.addProduct(new Flour(21.0, "flour1"));
            controller.addProduct(new Flour(23.4, "flour2"));
            controller.addProduct(new Flour(20.0, "flour3"));

            //ALL PRODS
            System.out.println("\nALL PRODUCTS: \n");
            ProductInterface[] all = controller.getAll();

            for(int i=0; i<all.length; i++)
            {
                System.out.println(all[i].toString());
            }

            //FILTERED PRODS > 20 lei
            System.out.println("\nPRODUCTS WITH PRICE PER KG > 20.0lei");
            ProductInterface[] result = controller.getProductsPriceGreaterThan20();

            for(int i=0; i<result.length; i++)
            {
                System.out.println(result[i].toString());
            }

            
        }
        catch (RepoException e)
        {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}
