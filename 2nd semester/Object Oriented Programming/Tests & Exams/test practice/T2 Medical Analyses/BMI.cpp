#include "BMI.h"

bool BMI::isResultOK()
{
    return (18.5 <= this->value && this->value <= 25);
}

std::string BMI::toString()
{
    return "BMI | Value: " + std::to_string(this->value) + " | Date: " + this->date + "\n";
}


