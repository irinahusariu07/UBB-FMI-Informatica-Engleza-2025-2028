def showMenu():
    print("=== CHOOOSE THE WAY YOU WANT TO SOLVE THE PROBLEM ===")
    print("1. naive non - optimised version")
    print("2. dynamic programming version")
    print("0. exit")

def checkTask():
    while True:
        n = input("Choose one of the two methods: ")
        if n.isdigit() and 0 <= int(n) <= 2:
            return int(n)
        else:
            print("Invalid input. Please choose one of the two methods!")

def naiveVersion(s1, s2, len1, len2):
    if len1 == 0 or len2 == 0:  #daca am terminat vreunul din siruri
        return ""

    if s1[len1-1] == s2[len2-1]: #daca ultimele elemente din cele doua siruri sunt egale
        return naiveVersion(s1, s2, len1-1, len2-1) + s1[len1-1] #reintru recursiv eliminand ultimele elemente si retin pe cel comun

    else:
        # trebuie sa vad care varianta imi alege un sir mai lung, ca sa stiu pe care o combin cu ce am pana acum
        # dica elimin ultimul element din X respectiv ultimul din Y si vad care imi returneaza secventa mai lunga
        removeX = naiveVersion(s1, s2, len1-1, len2)
        removeY = naiveVersion(s1, s2, len1, len2-1)
        if len(removeX) >= len(removeY):
            return removeX
        else:
            return removeY

def dynamicProgrammingVersion(s1, s2):
    len1 = len(s1)
    len2 = len(s2)
    commonTable = [[0] * (len2 + 1) for i in range(len1 + 1)] #initializez tabelul de comun cu 0 complet, merg cu len + 1 pt ca am in plus o linie si o coloana 0

    for i in range(1, len1 + 1):
        for j in range(1, len2 + 1):
            if s1[i-1] == s2[j-1]:
                commonTable[i][j] = commonTable[i-1][j-1] + 1 #echivalentul la return naiveVersion(s1, s2, len1-1, len2-1) + s1[len1-1] doar ca insumez lungimea nu caracterul
            else:
                commonTable[i][j] = max(commonTable[i-1][j], commonTable[i][j-1])  #echivalentul la removeX si removeY

    # trebuie (cerinta) sa afisez structura intermediara folosita in dynamic programming => commonTable
    print("\n Dynamic Programming table (rows = X, cols = Y):" )
    header = "    " + "  ".join(["0"] + list (s2)) # antetul tabelului
    print(header)
    for i in range(0, len1 + 1):
        if i > 0:
            rowLabel = s1[i-1]
        else:
            rowLabel = "0"
        rowValues = "  ".join(str(commonTable[i][j]) for j in range(len2 + 1))
        print(f"{rowLabel} | {rowValues}")

    # ca sa imi afiseze o subsecventa comuna trebuie sa fac un backtracking care parcurge matricea si urmareste la ce pozitie mi se schimba lungimea sirului

    i, j = len1, len2
    subsequence = []
    while i > 0 and j > 0:
        if s1[i-1] == s2[j-1]:
            subsequence.append(s1[i-1])
            i -= 1
            j -= 1
        # daca nu coincid valorile din tabel (pozitii finale din fiecare sir) mergem pe varianta de removeX sau removeY care e mai mare
        elif commonTable[i-1][j] >= commonTable[i][j-1]:
            i -=1
            #removeX a returnat secventa mai lunga
        else:
            j -= 1
            #removeY a returnat secventa mai lunga

        # la final subsequence este inversat si trebuie sa il scriu in ordinea aparitiei
    subsequence.reverse()
    subsequence = "".join(subsequence) #adica din lista de caractere o fac string (initial 'A' 'B' 'C', ulterior "ABC")

    print("\nThe longest subsequence is of length: ", commonTable[len1][len2])
    print("One of the found subsequences is: ", subsequence)



def main():
    print("TASK: Determine the longest common subsequence of two given sequences.\nSubsequence elements are not required to occupy consecutive positions.\nDetermine and display both the length of the longest common subsequence as well as at least one such subsequence.")
    X = input("Choose the first sequence: ")
    Y = input("Choose the second sequence: ")

    while True:
        showMenu()
        choice = checkTask()
        if choice == 0:
            print("Exiting!")
            break

        if choice == 1:
            subsequence = naiveVersion(X, Y, len(X), len(Y))
            print("\nThe longest common subsequence is of length: ", len(subsequence))
            print("One of the found common subsequences is: ", subsequence)

        if choice == 2:
            dynamicProgrammingVersion(X, Y)

if __name__ == "__main__":
    main()
