def f(x):
    return x**2
def f_prime(x):
    return 2*x

def gradient_descent(x_start, learning_rate, steps):
    x = x_start
    print("Step | x value | f(x)")
    for i in range(steps):
        print(f"{i+1:4} | {x:7.4f} | {f(x):7.4f}")
        x = x - learning_rate * f_prime(x)
    return x

# a) Small learning rate - method converges slowly
print("=== Small learning rate (0.1) ===")
gradient_descent(x_start=5, learning_rate=0.1, steps=10)

#b) Larger learning rate - method converges faster
print("\n=== Larger learning rate (0.4) ===")
gradient_descent(x_start=5, learning_rate=0.4, steps=10)

#c) Too large learning rate - method diverges
print("\n=== Too large learning rate (1.1) ===")
gradient_descent(x_start=5, learning_rate=1.1, steps=10)

#d) Nonconvex function

def g(x):
    return x**4 - 3*x**3 + 2
def g_prime(x):
    return 4*x**3 - 9*x**2

def gradient_descent_nonconvex(x_start, learning_rate, steps):
    x = x_start
    print("Step | x value | g(x)")
    for i in range(steps):
        print(f"{i+1:4} | {x:7.4f} | {g(x):7.4f}")
        x = x - learning_rate * g_prime(x)
    return x

print("\n=== Nonconvex function, start at x = 0===")
gradient_descent_nonconvex(x_start=0, learning_rate=0.1, steps=10)

print("\n=== Nonconvex function, start at x = 2===")
gradient_descent_nonconvex(x_start=2, learning_rate=0.1, steps=10)
