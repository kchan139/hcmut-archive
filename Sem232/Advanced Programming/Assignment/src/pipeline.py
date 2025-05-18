from functools import partial

# Sample data: list of dictionaries
data = [
    {'name': 'Alice', 'age': 30, 'salary': 70000},
    {'name': 'Bob', 'age': 24, 'salary': 48000},
    {'name': 'Charlie', 'age': 36, 'salary': 120000},
    {'name': 'Diana', 'age': 28, 'salary': 60000},
]

# Function to filter employees by age
def filter_by_age(min_age, person):
    return person['age'] >= min_age

# Function to transform data to extract salaries
def extract_salary(person):
    return person['salary']

# Function to calculate average
def average(salaries):
    return sum(salaries) / len(salaries) if salaries else 0

# Partial application of filter function
filter_adults = partial(filter_by_age, 30)

# Functional pipeline
adult_salaries = map(extract_salary, filter(filter_adults, data))
average_salary = average(list(adult_salaries))

print(f"The average salary of employees aged 30 and above is: {average_salary}")