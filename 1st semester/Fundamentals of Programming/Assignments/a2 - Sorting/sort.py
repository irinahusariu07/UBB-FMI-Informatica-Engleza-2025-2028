def show_menu():
    print ("\n=== CHOOSE THE TASK ===")
    print ("Please make sure to follow the steps in order.")
    print ("1. Generate a list of n random natural numbers. Generated numbers must be between 0 and 1000.")
    print ("2. Sort the list using cocktail sort. ")
    print ("3. Sort the list using heap sort. ")
    print ("4. Search for an item in the list using jump search.")
    print ("0. Exit")

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

def checkTaskNumber():
    #verific daca taskul ales este disponibil
        while True:
            # cat timp nu se introduce un numar natural din intervalul 0 - 4 programul va atentiona utilizatorul si ii va cere un nou input
            n = input("Choose a task: ")

            #verific daca fiecare caracter din n este cifra, daca da - returneaza nr taskului
            if n.isdigit() and 0 <= int(n) <= 4:
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

def cocktailSort(list, step):
    countStep = 0 #contorizez numarul de pasi

    for i in range (len(list) - 1, 0, -1):
        is_swapped = False #verific daca a fost facuta o schimbare in listala fiecare iteratie

        #parcurg lista de la final la inceput si pt fiecare element il verific daca e mai mic decat cel din fata sa
        for j in range (i, 0, -1):
            if list[j] < list [j-1]:
                list[j], list[j-1] = list[j-1], list[j]
                countStep += 1
                is_swapped = True

                #daca s-a implinit nr de pasi ceruti afisam sortarea intermediara
                if countStep % step == 0:
                    print(f"List after {countStep} swaps: ",list)

        #parcurg lista de la inceput spre final si pt fiecare element il verifici daca e mai mare decat cel ce urmeaza
        for j in range (i):
            if list[j] > list[j+1]:
                list[j], list[j+1] = list[j+1], list[j]
                countStep += 1
                is_swapped = True

                # daca s-a implinit nr de pasi ceruti afisam sortarea intermediara
                if countStep % step == 0:
                    print(f"List after {countStep} swaps: ", list)

        #daca la un pas lista nu se mai sorteaza din nicio directie inseamna ca lista nu mai poate fi sortata
        if not is_swapped:
            break
    print("Total swaps made: ", countStep)
    return list

def heapify(array, n, i, countStep, step): #este apelata recursiv in algoritmul de sortare pt a crea un arbore cu nodurile ordonate descrescator
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

        #contorizez schimbarea
        countStep += 1
        if countStep % step == 0:
            print(f"List after {countStep} swaps: ", array)

         #reintru recursiv in functie pt noua radacina
        countStep = heapify(array, n, largest, countStep, step)
    return countStep

def heapSort(list, step):
    n = len(list)
    countStep = 0
    for i in range(n//2 - 1, -1, -1): # n//2 este ultimul nod care are fii, ultimul nod care nu e frunza
        countStep = heapify(list, n, i, countStep, step) #alcatuim un heap ordonat de la mare la mic
    #mut radacina pe ultima pozitie pt a o elimina din noua sortare
    for i in range (n-1, 0, -1):
        list[0], list[i] = list[i], list[0]
        countStep += 1 #am inaintat in procesul de ordonare

        if countStep % step == 0:
            print(f"List after {countStep} swaps: ", list)

        countStep = heapify(list, i, 0, countStep, step)

    print("Total swaps made: ", countStep)
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

def main():
    #initializez doua variabile ca sa verific ca utilizatorul face intai cerinta de generare a listei si pe cea de sortare a listei
    list = None
    wasSorted = False
    # mainul e recursiv deoarece utilizatorul poate sa revina sa ceara diferite taskuri
    while True:
        show_menu()
        # verific daca taskul este valid, exista
        choice = checkTaskNumber()

        if choice == 0:
            print("Exiting!")
            break

        if choice == 1:
            list = genList()

        if choice == 2:
            if not checkList(list):
                continue #sare peste task si mai cere o data introducerea unei cerinte
            else:
                print("Choose a step - how often do you want to see the progress: ")
                step = checkInput()
                sortedList = cocktailSort(list, step)
                print("Final sorted list: ", sortedList)
                #marchez ca s-a executat sortarea listei prin metoda cocktail sort
                wasSorted = True

        if choice == 3:
            if not checkList(list):
                continue #sare peste task si mai cere o data introducerea unei cerinte
            else:
                print("Choose a step - how often do you want to see the progress: ")
                step = checkInput()
                sortedList = heapSort(list, step)
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



if __name__ == "__main__":
    main()