import numpy as np
import matplotlib.pyplot as plt

theta = np.linspace(0, 2*np.pi, 100)

# Define the unit circle
x = np.cos(theta)
y = np.sin(theta)

# Define the reflection constants
a = 2  
b = 3  

# Define the refl inner product
x_refl = a * np.cos(theta)
y_refl = b * np.sin(theta)

# Plot the original and refl unit circles
plt.figure(figsize=(8, 8))
plt.plot(x, y, color='cyan', label='Unit Circle')
plt.plot(x_refl, y_refl, color='blue', label='Refl Circle')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Unit Circle and Reflected Circle')
plt.legend()
plt.grid(True)
plt.axis('equal')
plt.show()