from time import perf_counter


def show_menu():
    print ("\n=== CHOOSE THE TASK ===")
    print ("Please make sure to follow the steps in order.")
    print ("1. Generate a list of n random natural numbers. Generated numbers must be between 0 and 1000.")
    print ("2. Sort the list using cocktail sort. ")
    print ("3. Sort the list using heap sort. ")
    print ("4. Search for an item in the list using jump search.")
    print ("5. BEST Case")
    print ("6. WORST Case")
    print ("7. AVERAGE Case")
    print ("0. Exit")

def show_subMenu(caseName):
    print (f"\n=== {caseName.upper()} CASE ===")
    print ("1. Cocktail sort. ")
    print ("2. Heap sort. ")
    print ("3. Jump search. ")
    print ("0. Return to main menu.")

def checkInput():
    #verific daca ce e introdus de la tastatura este numar natural
        while True:
            # cat timp nu se introduce un numar natural programul va atentiona utilizatorul si ii va cere un nou input
            n = input("Enter a natural number: ")

            #verific daca fiecare caracter din n este cifra, daca da - returneaza n ca nr intreg
            if n.isdigit():
                return int(n)
            else:
                print("Invalid input. Please enter a positive whole number.")

def checkTaskNumberMain():
    #verific daca taskul ales este disponibil
        while True:
            # cat timp nu se introduce un numar natural din intervalul 0 - 7 programul va atentiona utilizatorul si ii va cere un nou input
            n = input("Choose a task: ")

            #verific daca fiecare caracter din n este cifra, daca da - returneaza nr taskului
            if n.isdigit() and 0 <= int(n) <= 7:
                return int(n)
            else:
                print("Invalid input. Please choose a task that exists.")

def checkTaskNumberSub():
    #verific daca subtaskul ales este disponibil
        while True:
            # cat timp nu se introduce un numar natural din intervalul 0 - 3 programul va atentiona utilizatorul si ii va cere un nou input
            n = input("Choose a subtask: ")

            #verific daca fiecare caracter din n este cifra, daca da - returneaza nr taskului
            if n.isdigit() and 0 <= int(n) <= 3:
                return int(n)
            else:
                print("Invalid input. Please choose a task that exists.")


import random
# Generarea unei liste cu n numere random intre 0 si 1000
def genList():
    print("Choose how many natural numbers between 0 and 1000 you want to generate.")
    # verifica numarul introdus
    n = checkInput()
    # genereaza lista numbers cu n numere de la 0 la 1000
    numbers = [random.randint(0,1000) for i in range(n)]
    print("Generated numbers: ", numbers)
    return numbers

def cocktailSort(list):

    for i in range (len(list) - 1, 0, -1):
        is_swapped = False #verific daca a fost facuta o schimbare in listala fiecare iteratie

        #parcurg lista de la final la inceput si pt fiecare element il verific daca e mai mic decat cel din fata sa
        for j in range (i, 0, -1):
            if list[j] < list [j-1]:
                list[j], list[j-1] = list[j-1], list[j]
                is_swapped = True

        #parcurg lista de la inceput spre final si pt fiecare element il verifici daca e mai mare decat cel ce urmeaza
        for j in range (i):
            if list[j] > list[j+1]:
                list[j], list[j+1] = list[j+1], list[j]
                is_swapped = True

        #daca la un pas lista nu se mai sorteaza din nicio directie inseamna ca lista nu mai poate fi sortata
        if not is_swapped:
            break
    return list

def heapify(array, n, i): #este apelata recursiv in algoritmul de sortare pt a crea un arbore cu nodurile ordonate descrescator
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2
    # verific daca exista fiul stang si daca este mai mare decat radacina
    if left < n and array[largest] < array[left]:
        largest = left
    #verific daca exista fiul drept si daca este mai mare decat radacina
    if right < n and array[largest] < array[right]:
        largest = right
    #daca s a gasit un nou largest schimb radacina arbore
    if largest != i:
        array[i], array[largest] = array[largest], array[i]
         #reintru recursiv in functie pt noua radacina
        heapify(array, n, largest)

def heapSort(list):
    n = len(list)

    for i in range(n//2 - 1, -1, -1): # n//2 este ultimul nod care are fii, ultimul nod care nu e frunza
        heapify(list, n, i) #alcatuim un heap ordonat de la mare la mic
    #mut radacina pe ultima pozitie pt a o elimina din noua sortare
    for i in range (n-1, 0, -1):
        list[0], list[i] = list[i], list[0]
        heapify(list, i, 0)
    return list

def checkList(list):
    # verific daca lista a fost generata anterior pt a putea continua cu sortarea
    if list is None or len(list) == 0:
        print("You need to generate the list first! Please choose task 1.")
        return False
    return True

import math
def jumpSearch(list, searchFor):
    n = len(list)
    pas = int(math.sqrt(n)) #de obicei pasul e implemented ca radical din lungime sir
    prev = 0 #pozitia de la care incep sa caut elemenetul
    #iau mereu ultimul element din fiecare bloc si verific daca e mai mic ca elementul1
    while list[min(pas, n) - 1] < searchFor: #merg cu min(n, pas) pt ca pasul ar putea depasi n
        prev = pas #mut pozitia la blocul urmator
        pas += int(math.sqrt(n)) #delimitez noul bloc in care caut
        if prev >= n: #nu am gasit elementul daca am depasit lungimea sirului
            return -1
    #va iesi din while cand ultimul element din bloc e mai mare ca elementul cautat, ceea ce inseamna ca elementul poate fi in blocul curen
    while list[prev] < searchFor: #cat timp nu intalnesc elementul in blocul cautat
        prev += 1 #inaintez in vector
        if prev == min(pas, n): #daca am depasit cu pozitia pragul de sus al blocului fara sa gasim elementul => NU EXISTA
            return -1
    if list[prev] == searchFor: #daca am gasit elementul
        return prev
    return -1

import random

#fac o functie care sa imi genereze automat dublarea dimensiunii
def doubleCapacity(startSize, k):
    sizes = []
    n = startSize
    for i in range(k):
        sizes.append(n) #adauga noua dimensiune la finalul listei cu dimensiuni
        n *= 2
    return sizes

def generateLists(caseName, startSize, k):
    sizes = doubleCapacity(startSize, k)
    lists = []

    for n in sizes :
        if caseName == "BEST":
            L = list(range(n)) #adica lista ordonata crescator
        elif caseName == "WORST":
            L = list(range(n, 0, -1)) #adica lista ordonata descrescator
        else: # e average
            L = [random.randint(0, 1000) for i in range(n)]
        lists.append(L) #adauga fiecare lista generata in interiorul unui vector de liste

    return lists

import time

def measureTime(wantedAlg, *arguments):
    t0 = perf_counter()
    wantedAlg(*arguments)
    t1 = perf_counter()
    return t1 - t0

def main():
    #initializez doua variabile ca sa verific ca utilizatorul face intai cerinta de generare a listei si pe cea de sortare a listei
    list = None
    wasSorted = False
    # mainul e recursiv deoarece utilizatorul poate sa revina sa ceara diferite taskuri
    while True:
        show_menu()
        # verific daca taskul este valid, exista
        choice = checkTaskNumberMain()

        if choice == 0:
            print("Exiting!")
            break

        if choice == 1:
            list = genList()

        if choice == 2:
            if not checkList(list):
                continue #sare peste task si mai cere o data introducerea unei cerinte
            else:
                sortedList = cocktailSort(list)
                print("Final sorted list: ", sortedList)
                #marchez ca s-a executat sortarea listei prin metoda cocktail sort
                wasSorted = True

        if choice == 3:
            if not checkList(list):
                continue #sare peste task si mai cere o data introducerea unei cerinte
            else:
                sortedList = heapSort(list)
                print("Final sorted list: ", sortedList)
                #marchez ca s-a executat sortarea listei prin metoda heap sort
                wasSorted = True

        if choice == 4:
            if not checkList(list):
                continue
            if wasSorted == False: #daca lista nu a fost sortata nu se poate face search, deci va cere sortarea listei
                print("You need to sort the list first! Please choose task 2 or 3.")
                continue
            else:
                print("Choose the number you want to search for: ")
                searchFor = checkInput()
                if not (0 <= searchFor <= 1000):
                    print("The number you've entered is bigger than 1000 so it wont be found in the list")
                    continue
                else:
                    searching = jumpSearch(list, searchFor)
                    if searching != -1:
                        print(f"Number {searchFor} was found at index {searching}.")
                    else:
                        print(f"Number {searchFor} isnt in the generated list.")

        if choice in [5, 6, 7]: #pornesc un Submenu
            print("Enter the length of the first random list: ")  # ca sa nu imi genereze liste cu lungime fixa care sa se dubleze, ci sa zica useru
            startSize = checkInput()
            while True:
                # sa imi apara in cerinta care din cazuri il analizez
                if choice == 5: caseName = "BEST"
                elif choice == 6: caseName = "WORST"
                elif choice == 7: caseName = "AVERAGE"
                show_subMenu(caseName)
                subChoice = checkTaskNumberSub()

                if subChoice == 0:
                    print("Returning to main menu! ")
                    break

                lists = generateLists(caseName, startSize, 5)

                if subChoice == 1:
                # Cocktail Sort
                    for L in lists: #pentru fiecare lista din cele 5 cronometreaza utilizand cocktailSort
                        duration = measureTime(cocktailSort, L.copy())
                        print(f"Length of list: {len(L)}, Duration: {duration:.4f}s")
                        # afisarea duratei cu 4 zecimale

                if subChoice == 2:
                # Heap Sort
                    for L in lists:
                        duration = measureTime(heapSort, L.copy())
                        print(f"Length of list: {len(L)}, Duration: {duration:.4f}s")

                if subChoice == 3:
                # Jump Search
                    for L in lists:
                        Lsorted = sorted(L) #pt Search lista trebuie sortata crescator
                        if caseName == "BEST":
                            searchFor = Lsorted[0] if Lsorted else -1
                            # adica searchFor primeste primul element daca lista nu e goala
                            # pun -1 ca sa imi arate ca lista e goala
                        elif caseName == "WORST":
                            searchFor = (Lsorted[-1] + 1) if Lsorted else -1
                            # adica un element mai mare decat ultimul din lista (ca sa nu il gaseasca)
                        else:
                            searchFor = random.choice(Lsorted) if Lsorted else -1
                            # adica un element random din lista daca lista nu e goala

                        duration = measureTime(jumpSearch, Lsorted, searchFor)
                        print(f"Length of list: {len(L)}, Searched for = {searchFor}, Duration: {duration:.4f}s")


if __name__ == "__main__":
    main()