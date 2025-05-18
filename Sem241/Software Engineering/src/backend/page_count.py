from flask import Flask, jsonify, request, send_file, abort, Blueprint
from flask_cors import CORS
import os
from pdf2image import convert_from_path
from PIL import Image
import io
import shutil
from PyPDF2 import PdfReader
from docx import Document
# Define a Blueprint for the page count functionality
page_count_bp = Blueprint('page_count_bp', __name__)

@page_count_bp.route('/api/pages-count', methods=['POST'])
def get_page_count():
    if 'file' not in request.files:
        return jsonify({"error": "No file uploaded"}), 400

    uploaded_file = request.files['file']
    file_extension = uploaded_file.filename.split('.')[-1].lower()

    base_dir = os.path.abspath(os.path.dirname(__file__))  # Get the directory of the script
    temp_file_path = os.path.join(base_dir, "temp_file.docx")
    pdf_path = os.path.join(base_dir, "temp.pdf")

    try:
        if file_extension == "pdf":
            uploaded_file.save(temp_file_path)
            with open(temp_file_path, 'rb') as pdf_file:
                reader = PdfReader(pdf_file)
                page_count = len(reader.pages)
            if os.path.exists(pdf_path):
                os.remove(pdf_path)
            return jsonify({"page_count": page_count})
        else:
            return jsonify({"page_count": 0})

    finally:
        if os.path.exists(temp_file_path):
            os.remove(temp_file_path)   