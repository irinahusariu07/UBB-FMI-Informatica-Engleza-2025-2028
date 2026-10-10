#include "HTMLAdoptionList.h"

void HTMLAdoptionList::writeToFile()
{
    std::ofstream file(this->filename);
    file << "<!DOCTYPE html>\n";
    file << "<html> \n";
    file << "<head> \n";
    file << "          <title>Adoption List</title>\n";
    file << "</head>\n";

    file << "<body> \n";
    file << "<table border = \"1\">\n";
    file << "   <tr>\n";
    file << "        <td>Breed</td>\n";
    file << "        <td>Name</td>\n";
    file << "        <td>Age</td>\n";
    file << "        <td>Photo link</td>\n";
    file << "</tr>\n";

    for (auto& d : this->adopted_dogs)
    {
        file << "    <tr>\n";
        file << "        <td>" << d.getBreed() << "</td>\n";
        file << "        <td>" << d.getName() << "</td>\n";
        file << "        <td>" << d.getAge().getYears() << "years " << d.getAge().getMonths() << "months</td>\n";
        file << "        <td><a href=\"" << d.getLink() << "\">Link</a></td>\n";
        file << "    </tr>\n";
    }
        file << "</table>\n";
        file << "</body>\n";
        file << "</html>\n";
        file.close();
}

