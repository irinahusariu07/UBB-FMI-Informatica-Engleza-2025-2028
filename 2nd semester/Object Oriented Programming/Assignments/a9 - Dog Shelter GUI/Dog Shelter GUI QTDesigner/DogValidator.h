#pragma once
#include "Dog.h"
#include "Exceptions.h"

class DogValidator {
public:
    static void validate(Dog& d) {
        std::string errors = "";
        if (d.getBreed().empty()) errors += "Breed cannot be empty! ";
        if (d.getName().empty()) errors += "Name cannot be empty! ";
        if (d.getAge().getYears() < 0 || d.getAge().getMonths() < 0)
            errors += "Age cannot be negative! ";
        if (d.getLink().empty())
            errors += "Link cannot be empty! ";

        if (!errors.empty()) throw ValidationException(errors);
    }
};