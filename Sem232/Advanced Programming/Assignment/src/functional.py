from functools import reduce

# List of numbers
numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# Filter out even numbers
odd_numbers = list(filter(lambda x: x % 2 != 0, numbers))

# Square the remaining numbers
squared_numbers = list(map(lambda x: x * x, odd_numbers))

# Sum the squared numbers
sum_of_squares = reduce(lambda x, y: x + y, squared_numbers)

print(f"The sum of squares of odd numbers is: {sum_of_squares}")