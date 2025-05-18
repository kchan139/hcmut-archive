def memoize(f):
    cache = {}
    def memoized_function(*args):
        if args not in cache:
            cache[args] = f(*args)
        return cache[args]
    return memoized_function

@memoize
def fibonacci(n):
    if n <= 1:
        return n
    return fibonacci(n-1) + fibonacci(n-2)

print(fibonacci(10))  # Output: 55