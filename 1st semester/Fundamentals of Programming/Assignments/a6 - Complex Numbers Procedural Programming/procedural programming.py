#
# Write the implementation in this file
#


#
# Write below this comment
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
"""
List Representation: [real_part, imaginary_part]
"""
def createComplex_list(real, imaginary):
    return [real, imaginary]

def getReal_list(complexNumber):
    # iau partea reala din lista
    return complexNumber[0]

def getImaginary_list(complexNumber):
    # iau partea imaginara din lista
    return complexNumber[1]

def toStr_list(z:list) -> str:
    # pt a converti reprezentarile ca string
    a, b = z[0], z[1]
    sign = '+' if b >= 0 else '-'
    return f"{a:.1f} {sign} {abs(b):.1f}i"

def setReal_list(z, newReal):
    # daca vreau sa schimb partea reala la un numar z
    z[0] = newReal
    return z

def setImaginary_list(z, newImaginary):
    # daca vreau sa schimb partea imaginara la un numar z
    z[1] = newImaginary
    return z
#
# Write below this comment
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
"""
Dictionary Representation: {'real' : real_part, 'imaginary' : imaginary_part}
"""
def createComplex_dict(real, imaginary):
    return {'real': real, 'imaginary': imaginary}

def getReal_dict(complexNumber):
    # iau partea reala din dictionar
    return complexNumber['real']

def getImaginary_dict(complexNumber):
    # iau partea imaginara din dictionar
    return complexNumber['imaginary']

def toStr_dict(z:dict) -> str:
    # pt a converti reprezentarile ca string
    a, b = z['real'], z['imaginary']
    sign = '+' if b >= 0 else '-'
    return f"{a:.1f} {sign} {abs(b):.1f}i"

def setReal_dict(z, newReal):
    # daca vreau sa schimb partea reala la un numar z
    z['real'] = newReal
    return z

def setImaginary_dict(z, newImaginary):
    # daca vreau sa schimb partea imaginara la un numar z
    z['imaginary'] = newImaginary
    return z

#
# Write below this comment
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

# functie care verifica daca un numar este prim
def isprime(x):
    if x == 2:
        return True
    if x < 2 or x % 2 == 0:
        return False
    for i in range(3, int(x**0.5) + 1, 2):
        if x % i == 0:
            return False
    return True

# functie care calculeaza modulul unui numar complex
import math
def moduleofComplex(complexNumber, getReal, getImaginary):
    a = getReal(complexNumber)
    b = getImaginary(complexNumber)
    return math.sqrt((a ** 2) + (b ** 2))

def longestSubarray(numbers, getReal, getImaginary):
    """
    :param numbers: my list of complex numbers (min 10)
    :param getReal: a function that returns the real part of the complex number
    :param getImaginary: a function that returns the imaginary part of the complex number
    :return: returns the position of the first element in my subarray and the length of the longest subarray
    """
    """
    Returns the longest subarray from my default list
    in which the difference of the modulus of 2 complex numbers is a prime number
    Functia va returna pozitia de start si pozitia de stop a celui mai lung subarray
    """
    n = len(numbers)
    if n == 0:
        return 0, 0
    if n == 1:
        return 0, 1
    # definesc o lista care retine modulele fiecarui numar din lista mea
    modules = [moduleofComplex(z, getReal, getImaginary) for z in numbers]
    bestStart, bestLen = 0, 1
    currentStart, currentLen = 0, 1

    for i in range(1, n):
        diff = abs(modules[i] - modules[i - 1])
        if diff.is_integer() and isprime(int(diff)):
            currentLen += 1 #continui sa cresc lungimea in subarrayul curent
        else :
            #daca sirul curent este mai lung ca best length le schimb
            if currentLen > bestLen:
                bestLen = currentLen
                bestStart = currentStart
            # incep acum un subsir nou
            currentStart = i
            currentLen = 1

    # verificare finala
    if currentLen > bestLen:
        bestLen = currentLen
        bestStart = currentStart

    return bestStart, bestLen

def longestSubsequence(numbers, getReal):
    """
    :param numbers: my list of complex numbers (min 10)
    :param getReal: a function that returns the real part of the complex number
    :return:
    """

    """
    Returns the longest increasing subsequence with respect to the real part
    It uses dynamic programming
    Fac o lista de lungimi - retine lungimea subsequence pana la fiecare pozitie
        o lista de previous - retine ultima pozitie din subsequence (care a fost contorizata la lungime gen)
    """


    n = len(numbers)
    if n == 0:
        return []
    # extrag partea reala o singura data
    reals = [getReal(z) for z in numbers]

    # initializez sublength cu 1 (adica la inceput lungimea fiecarei subsequence este 1 - elem curent)
    sublength = [1] * n
    # initializez lastel cu -1 (adica inca niciun element anterior)
    lastel = [-1] * n

    for i in range(n):
        for j in range(i): # fiecare element pana la i
            if reals[j] < reals[i] and sublength[j] + 1 > sublength[i]:
                # e crescator si face parte dintr o subsecventa in construire
                sublength[i] = sublength[j] + 1 # cresc lungimea subsecventei
                lastel[i] = j # la elementul curent i retin pozitia la care am gasit un numar care nu intrerupe subsequence

    # caut capatul/ finalul celui mai lung subsequence crescator
    bestLen = sublength[0]
    end = 0
    for i in range(1, n):
        if sublength[i] > bestLen:
            bestLen = sublength[i]
            end = i

    # reconstruiesc subsequenceul folosind lastel incepand de la end
    indices = []
    current = end
    while current != -1: # adica cat timp is in subsequence
        indices.append(current)
        current = lastel[current]
    indices.reverse()
    return indices

#
# Write below this comment
# Functions regarding the lists and user input
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def getInitialData(createComplex):
    """
    Functia unde definesc ista default cu 10 elemente
    """
    numbers = [
        createComplex(3, 4),
        createComplex(6, 8),
        createComplex(-7, 0),
        createComplex(5, 7),
        createComplex(4, 0),
        createComplex(7, 3),
        createComplex(4, 3),
        createComplex(2, 1),
        createComplex(0, 2),
        createComplex(0, 0),
    ]
    return numbers

def transformUserInput(s:str):
    """
    Primesc un sir in formatul a + bi si returneaza (a,b) ca floats
    Asa userul poate sa scrie si a, bi, i, -i, a + bi, a - bi
    """
    s = s.strip().replace(' ', '').lower()
    if s.find("i") < s.find("+") or s.find("i") < s.find("-"):
        raise ValueError("Invalid input. Write numbers like a + bi or a - bi")
    # daca sirul e gol
    if not s:
        raise ValueError("Empty input. Write numbers like a + bi or a - bi")
    # daca nu are i sa verific sa fie doar un simplu numar real
    if 'i' not in s:
        try:
            a = float(s)
            return a, 0.0
        except ValueError:
            raise ValueError("Invalid input. If you want a complex number that isnt real the number should end with 'i' ")

    # daca e doar +/- i
    if s == 'i' or s == '+i':
        return 0.0, 1.0
    if s == '-i':
        return 0.0, -1.0


    # elimin i ca sa stochez numarul
    s = s.replace('i', '')

    # caut semnul operatiei a + bi sau a - bi
    for i in range(1, len(s)):
        if s[i] in '+-':
            try:
                a = float(s[:i])
                # exista cazul in care se scrie a + -bi sau a - -bi si atunci sa le transform ca sa nu fie confuzii
                b_str = s[i:]
                b_str = b_str.replace('+-', '-').replace('--', '+')
                b = float(b_str)
                return a, b
            except ValueError:
                raise ValueError("Invalid input. Write numbers like a + bi or a - bi")
    # daca nu a fost gasit semn, e numarul doar imaginar pt ca am testat inainte daca n are i
    try:
        return 0.0, float(s)
    except ValueError:
        raise ValueError("Invalid input. Write numbers like a + bi or a - bi")
#
# Write below this comment
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#
def show_menu():
    print("\n=== CHOOSE THE TASK ====")
    print("1. Read a list of complex numbers (in z = a + bi form) from the console. (Adds to the current list) ")
    print("2. Display the entire list of numbers on the console.")
    print("3. Set A. Display a longest subarray of numbers where the difference between the modulus of consecutive numbers is a prime number.")
    print("4. Set B. Display a longest increasing subsequence, when considering each number's real part.")
    print("0. Exit")


def checkTaskNumber():
    while True:
        n = input("Choose a task: ")
        if n.isdigit() and 0 <= int(n) <= 4:
            return int(n)
        else:
            print("Invalid input. Please choose a task that exists.")

def readComplexfromConsole(createComplex):
    # cere utilizatorului un numar si il createCpmplex
    while True:
        s = input(">>> ")
        try:
            # transforma inputul userului dupa ce verifica ca e totul corespunzator - adica a va primi partea reala si b imaginara
            a, b = transformUserInput(s)
            # atribuie unui element nou din lista structura unui nr complex cu a si b
            return createComplex(a, b)
        except ValueError as ve:
            print("Error! Try again.", ve)

def readAllNComplexNumbers(createComplex):
    # aici pun numerele in lista
    while True:
        cnt = input("How many complex numbers do you want to add? >>> ").strip()
        # verifica ca ce a fost introdus este numar natural
        if cnt.isdigit():
            n = int(cnt)
            break
        else:
            print("Please enter a natural number.")
    result = []
    # adauga in lista de numere complexe numerele inputate de user
    for i in range(n):
        # face citirea unui nr complex
        z = readComplexfromConsole(createComplex)
        result.append(z)
    return result

def printEntireList(numbers, toStr):
    # afiseaza intreaga lista pe ecran
    if not numbers:
        print("List is empty.")
        return
    print("Current numbers: ")
    for i in range(len(numbers)):
        z = numbers[i]
        print(f"{i:>2}. {toStr(z)}") #ca sa afiseze ca 1. a + bi 2. c - di etc

def main():
    """
    COMMENT SI DECOMMENT REPREZENTAREA DORITA
    """
    """
    # representation using LIST
    createComplex = createComplex_list
    getReal = getReal_list
    getImaginary = getImaginary_list
    toStr = toStr_list
    """
    # representation using DiCTIONARY
    createComplex = createComplex_dict
    getReal = getReal_dict
    getImaginary = getImaginary_dict
    toStr = toStr_dict
    

    defaultNumbers = getInitialData(createComplex)

    while True:
        show_menu()
        choice = checkTaskNumber()

        if choice == 0:
            print("Exiting!")
            break

        if choice == 1:
            # voi citi o lista noua de numere complexe date de user si le voi adauga la lista initiala
            print("Reading new complex numbers and adding them to the current list...")
            newNumbers = readAllNComplexNumbers(createComplex)
            defaultNumbers.extend(newNumbers)
            print(f"Added {len(newNumbers)} new numbers.")

        if choice == 2:
            printEntireList(defaultNumbers, toStr)

        if choice == 3:
            start, length = longestSubarray(defaultNumbers, getReal, getImaginary)
            if length <= 1:
                print("No non-trivial subbaray found (length 1)")
            else:
                print(f"Longest subbaray found (length = {length}) where consecutive modules differ by a prime: ")
                for idx in range(start, start + length):
                    print(f"{toStr(defaultNumbers[idx])} (module = {moduleofComplex(defaultNumbers[idx], getReal, getImaginary):.1f})")


        if choice == 4:
            indices = longestSubsequence(defaultNumbers, getReal)
            if not indices or len(indices) == 1:
                print("There is no increasing pair")
            else:
                print(f"Longest increasing subsequence by real part (length = {len(indices)}): ")
                for pos, idx in enumerate(indices, start=1):
                    z = defaultNumbers[idx]
                    print(f"{toStr(z)}")


if __name__ == "__main__":
    main()



