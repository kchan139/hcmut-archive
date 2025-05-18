def curry(f):
    def curried_function(*args):
        if len(args) == f.__code__.co_argcount:
            return f(*args)
        return lambda *more_args: curried_function(*(args + more_args))
    return curried_function

@curry
def add_three_numbers(a, b, c):
    return a + b + c

add_five = add_three_numbers(2, 3)
result = add_five(4)  # Output: 9
print(result)