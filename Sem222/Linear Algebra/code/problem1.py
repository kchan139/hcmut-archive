import numpy as np

# Define the encoded message as a numpy array
encodedMSG = np.array ( [[45, -35, 38, -30, 18, -18, 35, -30, 81, -60, 42, -28, 75, -55, 2, -2, 22, -21, 15, -10]] )

# Define the known vectors [45 -35]A^-1 and [38 -30]A^-1 as numpy arrays
v1 = np.array ( [[10, 15],  [8, 14]] )
v2 = np.array ( [[45, -35], [38, -30]] )

# Solve the systems of equations to find w, x, y, and z
[[w, x], [y, z]] = np.linalg.solve (v2, v1)

# Round w, x, y, and z to integers and print them
w, x, y, z = map (int, np.round([w, x, y, z]))
print("w = ", w)
print("x = ", x)
print("y = ", y)
print("z = ", z)

#Shape the encoded message into a 2x10 matrix
encodedMSG = encodedMSG.reshape(10,2)

# Define the encoding matrix A as a numpy array
A_inv = np.array([[w, x], [y, z]])

# Decode the message using the inverse of the encoding matrix A^-1
decodedMSG = np.dot(encodedMSG,A_inv).astype(int)
#mod 26 to get the correct values for the message
decodedMSG = decodedMSG % 26


# Turn the decoded message into a string
result = ''
for row in decodedMSG:
    for val in row:
        result += chr (val + 64) # Convert the integer value to its corresponding ASCII character
result = result.replace ('@',' ') # Replace any '@' with ' ' (space)

# Print the decoded message
print ("Decoded Message: ", result)