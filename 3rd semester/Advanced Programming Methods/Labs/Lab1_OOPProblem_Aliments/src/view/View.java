package view;
import controller.Controller;
import exceptions.NegativeNumberException;
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

            //test exceeding capacity
            /*
            controller.addProduct(new Salt(13.9, "salt3"));
            System.out.println("Se printeaza?"); //nu se printeaza cand da de execptie
            */

            //test remove
            /*
            System.out.println("Number of products before remove: " + all.length);
            controller.removeProduct("salt3");
            ProductInterface[] updated_list = controller.getAll();
            System.out.println("Number of products after remove: " + updated_list.length);
            */
        }
        catch (RepoException | NegativeNumberException e) //fie repo exception fie negative number exception
        {
            System.out.println("Exception: " + e.getMessage());
        }
        //ca sa fac programul sa ruleze dupa o exceptie aruncata - wrap each block individual in try catch
    }
}
