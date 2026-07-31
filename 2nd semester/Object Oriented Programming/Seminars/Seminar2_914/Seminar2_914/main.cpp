#include "Song.h"
#include "DynamicArray.h"
#include "repo.h"
#include "Service.h"
#include <iostream>
#include <crtdbg.h>

int main() {
	{
		Song s{ "Metallica", "One", "Youtube", 7,40 };
		std::cout << s.getArtist() << "\n";
		std::cout << s.getTitle() << "\n";
		std::cout << s.getLink() << "\n";

		//DynamicArray da;
		//DynamicArray da1 = da;

		//da.add(1);
		//da.add(2);
		//da.add(3);
		//std::cout << da.get_size() << '\n';

		//DynamicArray da2;
		//da2.add(11);
		//da2.add(12);
		//da2.add(13);
		//da2.add(14);
		//std::cout << da2.get_size() << '\n';
		//da2 = da;
		//da2.operator=(da);

		//da2 = da;
		////da2.operator=(da);
		//da2 = da2;

		//std::cout << da2.get_size() << '\n';

		Repo r;
		r.add(s);
		//std::cout << r.get_size() << '\n';

		Service serv{r};
		std::cout << "Service size: " << serv.get_size() << "\n";
		serv.add("t", "a", "l", 3, 3);
		std::cout << "Service size: " << serv.get_size() << "\n";

		std::cout << "Repo size: " << r.get_size() << '\n';
	}

	_CrtDumpMemoryLeaks();
	return 0;
}