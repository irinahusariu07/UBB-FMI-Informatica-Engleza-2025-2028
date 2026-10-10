#include<iostream>
#include<cassert>
#include"tests.h"

void testDog()
{
	Dog d{ "husky", "max", 1, 5, "max_link" };
	assert(d.getBreed() == "husky");
	assert(d.getName() == "max");
	assert(d.getLink() == "max_link");

	assert(d.getAge().getYears() == 1);
	assert(d.getAge().getMonths() == 5);

	d.setBreed("bully");
	d.setLink("bobby_link");
	d.setName("bobby");
	d.getAge().setYears(2);
	d.getAge().setMonths(0);

	assert(d.getBreed() == "bully");
	assert(d.getName() == "bobby");
	assert(d.getLink() == "bobby_link");

	assert(d.getAge().getYears() == 2);
	assert(d.getAge().getMonths() == 0);
}

void testDynamic()
{
	DynamicVector<Dog> v(2);
	Dog d1{ "husky", "max", 3, 3, "link" };
	Dog d2{ "border collie", "luna", 0, 3, "link" };
	Dog d3{ "shiba", "miki", 2,2,"link" };
	v.add(d1);
	v.add(d2);
	assert(v.getSize() == 2);

	//trigger resize
	v.add(d3);
	assert(v.getSize() == 3);
	
	assert(v.getElem(0).getName() == "max");

	//delete element
	v.remove(0);
	assert(v.getSize() == 2);
	assert(v.getElem(0).getName() == "luna");

	DynamicVector<Dog> v2;
	v2 = v; 
	assert(v2.getSize() == 2);
}

void testRepo()
{
	Repo repo;

	Dog d1("husky", "max", 1, 3, "link");
	Dog d2("beagle", "luna", 2, 4, "link");

	//add to db
	repo.addDB(d1);
	repo.addDB(d2);
	assert(repo.getDBSize() == 2);

	//find in db 
	int id = repo.findDog("husky", "max");
	assert(id == 0);
	id = repo.findDog("bully", "bobby");
	assert(id == -1);

	//delete fromm db
	repo.removeDB(0);
	assert(repo.getDBSize() == 1);

	//update and all 
	repo.updateDB("beagle", "luna", Dog("beagle", "luna", 5, 0, "new"));
	DynamicVector<Dog> dogs = repo.getAllDogs();
	assert(dogs.getElem(0).getAge().getYears() == 5);
}

void testService()
{
    Repo repo;
    Service s{ repo };

    //check string 
    s.checkString("ok"); // valid
    try { s.checkString(""); assert(false); }
    catch (...) { assert(true); }

    //check age
    s.checkAge(Age{ 0,0 }); // valid
    try { s.checkAge(Age{ -1,0 }); assert(false); }
    catch (...) { assert(true); }
    try { s.checkAge(Age{ 0,-1 }); assert(false); }
    catch (...) { assert(true); }

    //months to years conversion
    Age m1{ 1,14 }; s.monthsToYear(m1); assert(m1.getYears() == 2 && m1.getMonths() == 2);
    Age m2{ 1,12 }; s.monthsToYear(m2); assert(m2.getYears() == 2 && m2.getMonths() == 0);
    Age m3{ 2,0 };  s.monthsToYear(m3); assert(m3.getYears() == 2 && m3.getMonths() == 0);
    Age m4{ 3,5 };  s.monthsToYear(m4); assert(m4.getYears() == 3 && m4.getMonths() == 5);
    Age m5{ 1,11 }; s.monthsToYear(m5); assert(m5.getYears() == 1 && m5.getMonths() == 11);

    //filter dog on empty repo
    DynamicVector<Dog> emptyFilter = s.filterDogBreedByAge("husky", 5, 0);
    assert(emptyFilter.getSize() == 0);

    //add 
    s.addDog("husky", "max", 1, 3, "link");
    assert(s.getNumberOfDogs() == 1);

    // duplicate add
    try { s.addDog("husky", "max", 1, 5, "link"); assert(false); }
    catch (...) { assert(true); }

    // invalid fields
    try { s.addDog("husky", "", 1, 1, "link"); assert(false); }
    catch (...) { assert(true); }
    try { s.addDog("husky", "rex", 1, 1, ""); assert(false); }
    catch (...) { assert(true); }
    try { s.addDog("pug", "rex", -1, 5, "link"); assert(false); }
    catch (...) { assert(true); }
    try { s.addDog("pug", "rex", 5, -1, "link"); assert(false); }
    catch (...) { assert(true); }

    //remove
    s.removeDog("husky", "max");
    assert(s.getNumberOfDogs() == 0);

    try { s.removeDog("husky", "max"); assert(false); }
    catch (...) { assert(true); }

    //update
    s.addDog("beagle", "luna", 0, 27, "link"); // 27 months → normalized later
    s.updateDog("beagle", "luna", "beagle", "luna", 2, 3, "new");

    int idLuna = repo.findDog("beagle", "luna");
    Dog luna = s.allDogs().getElem(idLuna);
    assert(luna.getAge().getYears() == 2);

    // update non-existent
    try { s.updateDog("X", "Y", "A", "B", 1, 1, "link"); assert(false); }
    catch (...) { assert(true); }

    // update invalid fields
    try { s.updateDog("beagle", "luna", "", "x", 1, 1, "link"); assert(false); }
    catch (...) { assert(true); }
    try { s.updateDog("beagle", "luna", "beagle", "", 1, 1, "link"); assert(false); }
    catch (...) { assert(true); }
    try { s.updateDog("beagle", "luna", "beagle", "luna", 1, 1, ""); assert(false); }
    catch (...) { assert(true); }
    try { s.updateDog("beagle", "luna", "beagle", "luna", -1, 1, "link"); assert(false); }
    catch (...) { assert(true); }
    try { s.updateDog("beagle", "luna", "beagle", "luna", 1, -1, "link"); assert(false); }
    catch (...) { assert(true); }

    // update with months >= 12 (normalization inside update)
    s.updateDog("beagle", "luna", "beagle", "luna", 0, 15, "link");
    luna = s.allDogs().getElem(repo.findDog("beagle", "luna"));
    assert(luna.getAge().getYears() == 1);
    assert(luna.getAge().getMonths() == 3);

    s.addDog("husky", "max", 1, 0, "link");

    // filter: breed match + age match
    DynamicVector<Dog> f1 = s.filterDogBreedByAge("husky", 3, 0);
    assert(f1.getSize() == 1);
    assert(f1.getElem(0).getName() == "max");

    // filter: empty breed (all dogs)
    DynamicVector<Dog> f2 = s.filterDogBreedByAge("", 6, 0);
    assert(f2.getSize() == 2);

    // filter: breed match but equal age → should NOT include
    DynamicVector<Dog> f3 = s.filterDogBreedByAge("husky", 1, 0);
    assert(f3.getSize() == 0);

    // filter: breed mismatch
    DynamicVector<Dog> f4 = s.filterDogBreedByAge("pug", 10, 0);
    assert(f4.getSize() == 0);

    //compare ages
    Age c1{ 2,0 }, c2{ 2,3 }, c3{ 1,9 }, c4{ 5,0 };
    assert(s.compareAges(c1, c2) == true);   // same years, smaller months
    assert(s.compareAges(c1, c3) == false);  // years > given
    assert(s.compareAges(c3, c1) == true);   // years < given
    assert(s.compareAges(c1, c1) == false);  // equal
    Age c5{ 2,5 }, c6{ 2,3 };
    assert(s.compareAges(c5, c6) == false);  // same years, months > given

    //adopt dog 
    Dog adoptMax = s.allDogs().getElem(repo.findDog("husky", "max"));
    s.adoptDog(adoptMax);

    assert(s.getNumberOfDogs() == 1); // only luna remains
    assert(s.getAdoptionList().getSize() == 1);
    assert(s.getAdoptionList().getElem(0).getName() == "max");

    // adopt non-existent dog (should NOT throw)
    /*int before = s.getNumberOfDogs();
    s.adoptDog(Dog("ghost", "dog", 1, 1, "x"));
    assert(s.getNumberOfDogs() == before);
    assert(s.getAdoptionList().getSize() == 2);*/

    //add default 
    Repo r2;
    Service s2{ r2 };
    s2.addDefaultDogs();
    assert(s2.getNumberOfDogs() == 15);

    // duplicate default dog
    Repo r3;
    Service s3{ r3 };
    s3.addDog("chow chow", "ollie", 1, 2, "x");
    try { s3.addDefaultDogs(); assert(false); }
    catch (...) { assert(true); }
}


void testAll()
{
	
	testDog();
	testRepo();
	testDynamic();
	testService();
	std::cout << "All tests passed!";
}