import numpy as np

def main():
    # Prompt user for input
    n           = int(input("Enter the dimension of the vector space: "))
    num_vectors = int(input("Enter the number of vectors: "))
    vectors     = np.zeros((num_vectors, n))
    
    # Read vectors from user input
    for i in range(num_vectors):
        print(f"Enter vector {i+1}:")
        vectors[i] = np.array(input().split(), dtype=float)
    
    # Perform Gram-Schmidt orthogonalization
    orthogonal_basis, orthonormal_basis = gram_schmidt(vectors)
    
    # Print the orthogonal basis
    print("\nOrthogonal Basis:")
    for i in range(num_vectors):
        print(f"Vector {i+1}: {orthogonal_basis[i]}")
    
    # Print the orthonormal basis
    print("\nOrthonormal Basis:")
    for i in range(num_vectors):
        print(f"Vector {i+1}: {orthonormal_basis[i]}")
    
    # Find the coordinates of a vector in the orthonormal basis
    input_vector = np.array(input("\nEnter a vector in R^n to find its coordinates in the basis: ").split(), dtype=float)
    coordinates  = find_coordinates(orthonormal_basis, input_vector)
    
    # Print the coordinates of the vector in the orthonormal basis
    print("\nCoordinates of the vector in the orthonormal basis:")
    for i in range(num_vectors):
        print(f"Coordinate {i+1}: {coordinates[i]}")
    
    # Calculate the length of the input vector
    vector_length = np.linalg.norm(input_vector)
    print(f"\nLength of the vector: {vector_length}")

def gram_schmidt(vectors):
    num_vectors, n    = vectors.shape
    orthogonal_basis  = np.zeros_like(vectors)
    orthonormal_basis = np.zeros_like(vectors)
    
    for i in range(num_vectors):
        orthogonal_basis[i] = vectors[i]
        for j in range(i):
            # Calculate the projection of vectors[i] onto orthogonal_basis[j]
            projection = np.dot(vectors[i], orthogonal_basis[j]) / np.dot(orthogonal_basis[j], orthogonal_basis[j])
            orthogonal_basis[i] -= projection * orthogonal_basis[j]
        # Normalize the orthogonal basis vector to obtain the orthonormal basis vector
        orthonormal_basis[i] = orthogonal_basis[i] / np.linalg.norm(orthogonal_basis[i])
    
    return orthogonal_basis, orthonormal_basis

def find_coordinates(orthonormal_basis, vector):
    num_vectors, n = orthonormal_basis.shape
    coordinates    = np.zeros(num_vectors)
    
    for i in range(num_vectors):
        # Calculate the dot product of the input vector with each orthonormal basis vector
        coordinates[i] = np.dot(vector, orthonormal_basis[i])
    
    return coordinates

main()