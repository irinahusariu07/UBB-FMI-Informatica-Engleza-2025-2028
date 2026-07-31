"""
Choose a particular function ƒ, a point x and compute exactly f'(x).
By taking a range of small values h, show that the errors when approximating f'(x) with the finite differences above are proportional to h and h^2, respectively.
Explain why after h becomes small enough the errors start to increase.
"""

def f(x):
    return x**3

def f_prime(x):
    return 3*x**2

def forward_diff(x,h):
    return (f(x+h) - f(x))/h

def centered_diff(x,h):
    return (f(x+h) - f(x-h))/(2*h)

x0 = 2
exact = f_prime(x0)

h_values = [1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9]
print(f"Function: f(x)=x^2, point x={x0}, exact derivative f'={exact}\n")
print("h      | Forward approx | Forward error | Centered approx | Centered error")
print("-"*70)

for h in h_values:
    fd = forward_diff(x0, h)
    cd = centered_diff(x0, h)
    error_fwd = abs(fd - exact)
    error_ctd = abs(cd - exact)
    print(f"{h:<6} | {fd:<14.6f} | {error_fwd:<12.6f} | {cd:<14.6f} | {error_ctd:<12.6f}")


print("Forrward difference: As we make h smaller, the forward difference gets closer to the true derivative")
print("Centered difference: Centered difference decreases much faster, roughly proportional to h^2")
print("For very small h (10^−7and below), the errors start increasing due to round-off errors.")
