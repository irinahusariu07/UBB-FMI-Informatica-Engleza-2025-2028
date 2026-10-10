#pragma once
#include "Action.h"
#include "Repo.h"

class ActionRemove : public Action {
private:
    Repo& r;
    Dog removed_dog;

public:
    ActionRemove(Repo& r, const Dog& removed_dog) : r(r), removed_dog{ removed_dog } {}

    void undo() override {
        r.addDB(removed_dog);
    }

    void redo() override {
        int id = r.findDog(removed_dog.getBreed(), removed_dog.getName());
        if (id != -1) {
            r.removeDB(id);
        }
    }
};