#pragma once
#include "Action.h"

class ActionAdd : public Action {
private:
    Repo& r;
    Dog added_dog;

public:
    ActionAdd(Repo& r, const Dog added_dog) : r(r), added_dog{ added_dog } {}

    void undo() override {
        int id = r.findDog(added_dog.getBreed(), added_dog.getName());
        if (id != -1) r.removeDB(id); //remove the added dog 
    }

    void redo() override {
        r.addDB(added_dog); //readd the added dog 
    }
};