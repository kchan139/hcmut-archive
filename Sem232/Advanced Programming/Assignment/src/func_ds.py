from pyrsistent import pvector

# Create an immutable vector
vec = pvector([1, 2, 3])
print(vec)  # Output: pvector([1, 2, 3])

# Add an element
new_vec = vec.append(4)
print(new_vec)  # Output: pvector([1, 2, 3, 4])

# Original vector remains unchanged
print(vec)  # Output: pvector([1, 2, 3])