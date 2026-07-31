#include "BP.h"

bool BP::isResultOK()
{
    return (systolic >= 90 && systolic <= 119 && diastolic >= 60 && diastolic <= 79);
}

std::string BP::toString()
{
    return "BP | Systolic Value: " + std::to_string(systolic) + " | Diastolic: " + std::to_string(diastolic) +
        " | Date: " + date + "\n";
}

