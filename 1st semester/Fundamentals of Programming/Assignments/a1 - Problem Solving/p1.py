# Solve the problem from the first set here
# pb 1
# Generate the first prime number larger than a given natural number n.

n = int(input("Se citeste n:  "))

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

ok = False
#caut numere prime strict mai mari ca n
x = n + 1
#pana nu gasesc primul numar prim il caut
while ok == False :
    if is_prime(x) == True :
        ok = True
    else:
        x +=1
#returnez nr gasit
print("primul nr prim dupa n este: ", x)