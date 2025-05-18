def add(x, y):
    return x + y

def apply_function(f, x, y):
    return f(x, y)

result = apply_function(add, 5, 10)
print(result)  # Output: 15