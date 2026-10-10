package repo;

import model.ProductInterface;
import exceptions.RepoException;

public class MemoryRepo implements RepoInterface
{
    private ProductInterface[] products;
    private int size;
    private int fixed_capacity;
    public MemoryRepo(int cap)
    {
        this.fixed_capacity = cap;
        this.products = new ProductInterface[this.fixed_capacity]; //define a fixed capacity vector
        this.size = 0;  //initial size
    }

    @Override
    public void addProduct(ProductInterface item) throws RepoException {
        if (size < fixed_capacity)
        {
            products[size] = item;
            size++;
        }

        else throw new RepoException("Repo capacity exceeded!");
    }

    @Override
    public void removeProduct(String name) throws RepoException {
        int idx = -1;
        for (int i = 0; i<size; i++)
        {
            if (products[i].getName().equals(name))
            {
                idx = i;
                break;
            }
        }

        if (idx != -1)
        {
            //shift all elems to left to remove the elem at pos idx
            for (int i = idx+1; i<size; i++)
            {
                products[i-1] = products[i];
            }
            products[size - 1] = null; //mark the end
            size -- ;
        }

        if (idx == -1) throw new RepoException("Did not find product with given name");
    }

    @Override
    public ProductInterface[] getAll() {
        ProductInterface[] current_prods = new ProductInterface[size];
        //copy elems in current_prods
        for (int i = 0; i < size; i++) current_prods[i] = products[i];
        return current_prods;
    }

    @Override
    public int getSize() {
        return size;
    }
}
