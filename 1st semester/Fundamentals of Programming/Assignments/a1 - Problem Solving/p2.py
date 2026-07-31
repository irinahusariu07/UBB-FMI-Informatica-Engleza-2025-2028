# Solve the problem from the second set here
# pb 7
# Determine the twin prime numbers p1 and p2 immediately larger than the given non-null natural number n. Two prime numbers p and q are called twin if q - p = 2.

n = int(input("Se citeste n: "))

#verific daca un nr e prim
def is_prime(n):
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range (3, int(n**0.5)+1, 2):
        if n % i == 0:
            return False
    return True

# caut doua numere p1 si p2 consecutive mai mari decat n
p1 = n + 1
p2 = p1 + 2
ok = False

while ok == False :
    if is_prime(p1) and is_prime(p2):
        ok = True
    else :
        p1 = p1 + 1
        p2 = p2 + 1

print ("perechea de numere prime cu proprietatea ceruta este: ", p1, p2)


