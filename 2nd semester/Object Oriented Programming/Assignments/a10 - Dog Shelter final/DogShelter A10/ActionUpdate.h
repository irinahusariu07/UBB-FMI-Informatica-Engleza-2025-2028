#pragma once
#include "Action.h"
#include "Repo.h"

class ActionUpdate : public Action {
private:
    Repo& r;
    Dog old_dog;
    Dog new_dog;

public:
    ActionUpdate(Repo& r, const Dog& old_dog, const Dog& new_dog) : r(r), old_dog{ old_dog }, new_dog{ new_dog } {}

    void undo() override {
        r.updateDB(new_dog.getBreed(), new_dog.getName(), old_dog); //revin la old dog
    }

    void redo() override {
        r.updateDB(old_dog.getBreed(), old_dog.getName(), new_dog); //revin la new dog 
    }
};