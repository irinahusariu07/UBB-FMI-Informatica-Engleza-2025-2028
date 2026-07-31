a = 10 #number to find the sqrt for
x = a / 2 #initial guess
exact = a**0.5 #exact sqrt

import math

def correct_digits(x, exact):
    if x == exact:
        return "infinite"
    return int(-math.log10(abs(x - exact)))

print(f"Approximating sqrt({a}) using Newton's method")
print("Iteration | Approximation x_n | Error | Correct digits")
print("-"*60)


for n in range(10):
    err = abs(x - exact)
    digits = correct_digits(x, exact)
    print(f"{n:<9} | {x:<16.10f} | {err:<10.2e} | {digits}")
    # Newton iteration
    x = 0.5 * (x + a/x)

print("\nObservation: The number of correct digits roughly doubles each iteration")