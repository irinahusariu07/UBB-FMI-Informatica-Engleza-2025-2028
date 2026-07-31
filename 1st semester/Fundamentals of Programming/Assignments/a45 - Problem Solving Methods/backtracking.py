def showMenu():
    print("\n === CHOOSE THE BACKTRACKING METHOD ===")
    print("1. iterative")
    print("2. recursive")
    print("0. exit")

def checkTask():
    while True:
        n = input("Choose the way backtracking is implemented: ")
        if n.isdigit() and 0 <= int(n) <= 2:
            return int(n)
        else:
            print("Invalid input. Please choose one of the two methods!")

def checkInput():
    while True:
        n = input("Choose a natural number: ")
        if n.isdigit() and int(n) > 0:
            return int(n)
        else:
            print("Invalid input. Please choose a natural number!")

def btIterative(n, m):
    solution = [None] * n #golesc lista de solutie
    nextTry = [1] * n #pt fiecare pozitie retin candidatul pe care il incerc, incep cu 1 pt fiecare
    k = 0 #pozitia curenta
    found = False #ca sa verific daca am solutii la final

    while k >= 0:
        if nextTry[k] > n: #inseamna ca am epuizat toate pozitiile 1 -> n si trebe sa revenim la nivelul anterior
            nextTry[k] = 1 #incep cu 1 din nou
            k -= 1 #merg la pozitia anterioara
            if k >= 0: #adica daca sunt inca in rangeul 1 -> n
                solution[k] = None #golesc solutia de pe pozitia k
                nextTry[k] += 1 #si incerc candidatul urmator
            continue #continui while cu ce modificari am facut

        x = nextTry[k]
        # verific daca:
        # 1. x a mai fost solosit in solutia curenta
        # 2. respecta conditia cu dif >= m daca k nu e primul element (ala poate fi oricat si ma iau dupa el)

        unused = (x not in solution)
        checksCondition = (k == 0) or (abs(x - solution[k-1]) >= m)

        if unused and checksCondition:
            #pot pune x in solutie
            solution[k] = x

            if k == n - 1:
                # am o solutie completa
                print(solution)
                found = True

                # golesc solutia ca sa descopar o alta
                solution[k] = None
                nextTry[k] += 1

            else:
                # inaintez in lista de candidati
                k +=1
                nextTry[k] = 1 #incep iar verificarea de la 1

        else:
            nextTry[k] += 1 #incerc urmatorul candidat
    if not found:
        print("There are no possible solutions!")

def btRecursive(n,m):
    solution = [] #solutia partiala curenta
    found = [False] #ca sa stiu daca am printat vreo solutie completa

    def bt():
        # daca am completat toate pozitiile am o solutie completa
        if len(solution) == n:
            print(solution)
            found[0] = True #am gasit cel putin o solutie
            return

        # incerc numerele de la 1 la n pt urmatoarea pozitie
        for x in range(1, n+1):
            # 1. verific daca a fost deja folosit
            if x in solution:
                continue
            # 2. verific daca indeplineste conditia diferentei
            if len(solution) > 0 and abs(x - solution[-1]) < m:
                continue
            solution.append(x) #am adaugat in solutie
            # recursiv pt pasul urmator
            bt()
            solution.pop() #la intoarcere elimin elementele de la coada

    bt() # apelul initial

    if not found[0]:
        print("There are no possible solutions!")



def main():
    print("TASK: Two natural numbers m and n are given.\nDisplay in all possible modalities the numbers from 1 to n, such that between any two numbers on consecutive positions, the difference in absolute value is at least m.\nIf there is no solution, display a message.")
    print ("Choose n: ")
    n = checkInput()
    print ("Choose m: ")
    m = checkInput()

    if n >= 2 and m > n - 1:
        print("There are no possible solutions for the numbers you've chosen! (m > n-1) ")
        return

    while True:
        showMenu()
        choice = checkTask()

        if choice == 0:
            print("Exiting!")
            break

        if choice == 1:
            # voi implementa backtracking iterativ
            btIterative(n, m)

        if choice == 2:
            #voi implementa backtracking recursiv
            btRecursive(n, m)

if __name__ == '__main__':
    main()