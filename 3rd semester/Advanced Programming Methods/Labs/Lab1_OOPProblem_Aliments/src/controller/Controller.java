package controller;
import exceptions.NegativeNumberException;
import model.ProductInterface;
import repo.RepoInterface;
import exceptions.RepoException;

public class Controller {
    private RepoInterface repo;

    public Controller(RepoInterface r)
    {
        this.repo = r;
    }

    public void addProduct(ProductInterface product) throws RepoException, NegativeNumberException
    {
        repo.addProduct(product);
    }

    public void removeProduct(String name) throws RepoException
    {
        repo.removeProduct(name);
    }

    public ProductInterface[] getProductsPriceGreaterThan20()
    {
        ProductInterface[] all = repo.getAll();
        int cnt = 0; //imi trb contor ca sa declar array de filtered cu size
        for (int i = 0; i<all.length; i++)
        {
            if(all[i].getPrice() > 20.0) cnt++;
        }

        ProductInterface[] filtered = new ProductInterface[cnt];
        int idx = 0; //idx for filtered array
        for (int i = 0; i<all.length; i++)
        {
            if(all[i].getPrice() > 20.0)
            {
                filtered[idx] = all[i]; //copiez prod care indeplineste cond in vectorul rezultat
                idx++;
            }
        }

        return filtered;
    }

    public ProductInterface[] getAll()
    {
        return repo.getAll();
    }
}
