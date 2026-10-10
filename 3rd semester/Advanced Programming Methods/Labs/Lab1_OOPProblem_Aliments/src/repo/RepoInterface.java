package repo;
//the interface for the repository

//ca si #include<Domain.h> in C++, ca sa pot stoca obiecte de tip ProductInterface:
import exceptions.RepoException;
import model.ProductInterface;
public interface RepoInterface
{
    //to add a product
    void addProduct(ProductInterface item) throws RepoException;

    //to remove a product - identified by name
    void removeProduct(String name) throws RepoException;

    //to get all the objects in the repo
    //returns a vector => return type is ProductInterface[]
    ProductInterface[] getAll();
    int getSize(); //to get the number of items
}
