import os

def split_file(file_path, chunk_size):
    chunks = []
    with open(file_path, "rb") as file:
        while chunk := file.read(chunk_size):
            chunks.append(chunk)
    return chunks

def reassemble_file(chunks, output_path):
    with open(output_path, "wb") as file:
        for chunk in chunks:
            file.write(chunk)
