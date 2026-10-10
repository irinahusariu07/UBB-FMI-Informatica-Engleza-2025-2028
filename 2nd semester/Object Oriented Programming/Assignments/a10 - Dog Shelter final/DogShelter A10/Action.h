#pragma once
#include "Dog.h"
#include "Repo.h"

class Action {
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~Action() = default;
};