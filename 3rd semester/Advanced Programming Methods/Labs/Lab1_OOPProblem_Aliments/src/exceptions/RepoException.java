package exceptions;

/*
    RuntimeException e UNCHECKED
    daca voiam sa folosesc extends Exception trebuia sa declar in RepoInterface ce metode throw exceptions
*/
public class RepoException extends Exception{
    public RepoException(String message)
    {
        super(message); //cheama constructorul base class ului Exception (care e deja existent in java)
    }
}
