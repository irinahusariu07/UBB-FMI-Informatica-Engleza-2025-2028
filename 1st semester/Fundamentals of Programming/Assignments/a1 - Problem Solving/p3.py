# Solve the problem from the third set here
#pb 15
# Generate the largest perfect number smaller than a given natural number n. If such a number does not exist, a message should be displayed. A number is perfect if it is equal to the sum of its divisors, except itself. (e.g. 6 is a perfect number, as 6=1+2+3).
n = int(input("Se citeste n: "))

# verific daca un nr este perfect - adica daca este egal cu suma divizorilor sai fara el
def is_perfect(n):
    sum = 0
    for i in range (1, n-1):
        if n % i == 0 :
            sum += i
    return sum == n

# parcurg numerele de la n-1 la 1 pt a gasi primul nr perfect mai mic ca n
ok = False
x = n-1
while ok == False:
    if is_perfect(x):
        ok = True
    else:
        x = x-1

print ("cel mai mare nr perfect mai mic decat n este: ", x)