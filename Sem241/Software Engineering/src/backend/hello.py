from flask import Flask, jsonify, request, send_file, abort
from flask_cors import CORS
import os
from pdf2image import convert_from_path
from PIL import Image
import io
import shutil
from page_count import page_count_bp

app = Flask(__name__)
CORS(app, resources={r"/*": {"origins": "http://localhost:8000"}})
app.register_blueprint(page_count_bp)
UPLOAD_FOLDER = './uploads'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

# Example data structure
printers = [
    {"id": 1, "name": "A4 - 402: Printer 1", "status": "Khả dụng"},
    {"id": 2, "name": "A4 - 402: Printer 2", "status": "Không khả dụng"},
    {"id": 3, "name": "A4 - 402: Printer 3", "status": "Khả dụng"},
    {"id": 4, "name": "A4 - 402: Printer 4", "status": "Khả dụng"},
]

allowed_extensions = [
    {"Extension": "pdf", "Status": "Hỗ trợ"},
    {"Extension": "docx", "Status": "Hỗ trợ"},
    {"Extension": "pptx", "Status": "Hỗ trợ"},
] 

records_2252938 = [
    { "MSSV": "2252938", "printer": "A4 - 402: Printer 1", "date": "2024-11-20", "file_ext": "pdf", "file_name": "test1.pdf", "file_size": "123534", "page_num": "10", "status": "Đã in" },
    { "MSSV": "2252938", "printer": "A4 - 402: Printer 2", "date": "2024-11-19", "file_ext": "pdf", "file_name": "test2.pdf", "file_size": "234875", "page_num": "9", "status": "Đang chờ" },
    { "MSSV": "2252938", "printer": "A4 - 402: Printer 3", "date": "2024-11-18", "file_ext": "pdf", "file_name": "test3.pdf", "file_size": "1938759", "page_num": "5", "status": "Đã in" },
    { "MSSV": "2252938", "printer": "A4 - 402: Printer 4", "date": "2024-11-17", "file_ext": "pdf", "file_name": "test4.pdf", "file_size": "48759", "page_num": "2", "status": "Đang chờ" },
]

records_2252939 = [
    { "MSSV": "2252939", "printer": "A4 - 402: Printer 1", "date": "2024-11-20", "file_ext": "pdf", "file_name": "test5.pdf", "file_size": "102745", "page_num": "15", "status": "Đã in" },
    { "MSSV": "2252939", "printer": "A4 - 402: Printer 2", "date": "2024-11-19", "file_ext": "pdf", "file_name": "test6.pdf", "file_size": "947599", "page_num": "18", "status": "Đang chờ" },
    { "MSSV": "2252939", "printer": "A4 - 402: Printer 3", "date": "2024-11-18", "file_ext": "pdf", "file_name": "test7.pdf", "file_size": "12993", "page_num": "35", "status": "Đã in" },
    { "MSSV": "2252939", "printer": "A4 - 402: Printer 4", "date": "2024-11-17", "file_ext": "pdf", "file_name": "test8.pdf", "file_size": "307514", "page_num": "4", "status": "Đang chờ" },
]

page_numbers = {
    "2252938": 10,
    "2252939": 15
}

@app.route('/api/page_num/<mssv>', methods=['GET'])
def get_page(mssv):
    if mssv in page_numbers:
        return jsonify({"page_num": page_numbers[mssv]})
    else:
        abort(404, description="Không tìm thấy hồ sơ cho MSSV đã cho")

@app.route('/api/page_num/<mssv>', methods=['PUT'])
def update_page(mssv):
    if mssv in page_numbers:
        data = request.get_json() 
        
        page_num = data.get('page_num') 
        
        try:
            page_num = int(page_num) 
        except (ValueError, TypeError):
            return jsonify({"error": "Invalid input: 'page_num' must be an integer"}), 400

        page_numbers[mssv] = page_num
        return jsonify({"message": "Page number updated successfully", "page_num": page_numbers[mssv]}), 200
    else:
        abort(404, description="Records not found for the given MSSV")

@app.route('/api/records/<mssv>', methods=['PUT'])
def update_records(mssv):
    data = request.json
    print(mssv)

    if not data or not isinstance(data, dict):
        abort(400, description="Dữ liệu không hợp lệ. Vui lòng cung cấp một đối tượng JSON hợp lệ.")

    # Ensure MSSV matches in the provided record
    if data.get('MSSV') != mssv:
        abort(400, description="MSSV trong hồ sơ không khớp với MSSV đã cung cấp.")

    # Add the record to the appropriate list
    if mssv == "2252938":
        records_2252938.append(data)
        return jsonify({"message": "Hồ sơ đã được thêm thành công", "records": records_2252938})
    elif mssv == "2252939":
        records_2252939.append(data)
        return jsonify({"message": "Hồ sơ đã được thêm thành công", "records": records_2252939})
    else:
        abort(404, description="Không tìm thấy hồ sơ cho MSSV đã cho.")

@app.route('/api/records/<mssv>', methods=['GET'])
def get_records(mssv):
    # Check the provided MSSV value and return the corresponding records
    if mssv == "2252938":
        return jsonify(records_2252938)
    elif mssv == "2252939":
        return jsonify(records_2252939)
    elif mssv == "7777":
        # Merge the records of 2252938 and 2252939
        merged_records = records_2252938 + records_2252939
        return jsonify(merged_records)
    else:
        abort(404, description="Không tìm thấy hồ sơ cho MSSV đã cho.")
@app.route('/api/get-file', methods=['GET'])
def get_file():
    try:
        # Get a list of all files in the uploads folder
        files = sorted(os.listdir(UPLOAD_FOLDER))
        
        if not files:
            abort(404, "Không tìm thấy file trong thư mục uploads.")
        
        # Select the first file
        first_file_path = os.path.join(UPLOAD_FOLDER, files[0])
        file_extension = first_file_path.split('.')[-1].lower()

        if file_extension == 'pdf':
            # For PDF: convert the first page to an image
            images = convert_from_path(first_file_path, first_page=1, last_page=1, poppler_path="./Release-24.08.0-0/poppler-24.08.0/Library/bin")  # Convert first page
            image = images[0]

            # Save the image to a BytesIO buffer
            img_io = io.BytesIO()
            image.save(img_io, 'PNG')
            img_io.seek(0)

            return send_file(img_io, mimetype='image/png')
        
        elif file_extension in ['jpg', 'jpeg', 'png', 'gif']:
            # For image files: simply return the image
            return send_file(first_file_path, mimetype=f'image/{file_extension}')
        

        else:
            abort(415, "Không hỗ trợ file type cho preview.")
    
    except Exception as e:
        abort(500, f"Error fetching file: {str(e)}")
@app.route('/upload', methods=['POST'])
def upload_file():
    os.makedirs(UPLOAD_FOLDER, exist_ok=True)
    if 'file' not in request.files:
        return jsonify({"error": "Không có file trong request"}), 400

    file = request.files['file']

    if file.filename == '':
        return jsonify({"error": "Không có file được chọn"}), 400

    if file:
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filepath)  # Save file to upload folder

        return jsonify({"message": "File đã được tải lên thành công", "filename": file.filename}), 200
    else:
        return jsonify({"error": "File type không được hỗ trợ"}), 400

@app.route('/api/delete-uploads', methods=['DELETE'])
def delete_uploads():
    # try:
        # Check if the directory exists
        if os.path.exists(UPLOAD_FOLDER):
            # Remove the directory and all its contents
            shutil.rmtree(UPLOAD_FOLDER)
            return jsonify({"message": "Thư mục uploads đã được xóa thành công"}), 200
        else:
            return jsonify({"error": "Thư mục uploads không được tìm thấy"}), 200
    
    # except Exception as e:
    #     abort(500, f"Error deleting uploads directory: {str(e)}")
# Endpoint to get the allowed extensions
@app.route('/api/allowed-extensions', methods=['GET'])
def get_allowed_extensions():
    return jsonify({"allowed_extensions": allowed_extensions})

# Endpoint to update allowed extensions
@app.route('/api/allowed-extensions', methods=['PUT'])
def update_allowed_extensions():
    data = request.json  # The new allowed extensions data from the frontend
    # Update the allowed extensions based on the received data
    for index, ext in enumerate(allowed_extensions):
        # Check if the extension is in the request data
        ext["Status"] = data[index]["Status"]  # Update the status (Allow/Not Allow)

    return jsonify({"message": "Allowed extensions updated", "allowed_extensions": allowed_extensions})

@app.route('/api/printers', methods=['GET'])
def get_printers():
    available_printers = [printer for printer in printers if printer['status'] == 'Khả dụng']
    
    return jsonify(available_printers)

@app.route('/api/printers-admin', methods=['GET'])
def get_printers_admin():
    
    return jsonify(printers)

@app.route('/api/printers/<int:printer_id>', methods=['PUT'])
def update_printer_status(printer_id):
    data = request.json
    for printer in printers:
        if printer['id'] == printer_id:
            printer['status'] = data.get('status', printer['status'])
            return jsonify(printer), 200
    return jsonify({"error": "Printer not found"}), 404

@app.route('/api/printers', methods=['POST'])
def add_printer():
    new_printer = request.json
    new_printer['id'] = len(printers) + 1
    printers.append(new_printer)
    return jsonify(new_printer), 201

if __name__ == '__main__':
    app.run(debug=True)
