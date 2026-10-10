import controller.Controller;
import repo.MemoryRepo;
import view.View;
import repo.RepoInterface;
void main() {
    RepoInterface repo = new MemoryRepo(7); //fixez cap de 7
    Controller controller = new Controller(repo);
    View view = new View(controller);

    view.run();
}
