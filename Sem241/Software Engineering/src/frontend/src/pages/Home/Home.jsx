import React, { useState, useEffect, useRef } from "react";
import { Navbar } from "../../components/Navbar/Navbar";
import { Footer } from "../../components/Footer/Footer";
import BackgroundSVG from "../../assets/background.svg";
import { IconFilePlus } from "icons";
import { Button } from "primitives";
import { useNavigate } from "react-router-dom";
import axios from "axios"; // Import axios
import "./home.css";

function Home() {
    // State to hold the selected file and allowed extensions
    const navigate = useNavigate();
    const [file, setFile] = useState(null);
    const [allowedExtensions, setAllowedExtensions] = useState([]);
    const [acceptExtensions, setAcceptExtensions] = useState(""); // State for dynamic accept value
    const fileInputRef = useRef(null); // Create a ref for the file input

    // Fetch allowed extensions from the backend on component mount
    useEffect(() => {
        const fetchAllowedExtensions = async () => {
            try {
                const response = await axios.get("http://127.0.0.1:5000/api/allowed-extensions");
                setAllowedExtensions(response.data.allowed_extensions);

                // Generate the accept attribute based on allowed extensions
                const extensions = response.data.allowed_extensions
                    .filter(ext => ext.Status === "Hỗ trợ")
                    .map(ext => `${ext.Extension}`)
                    .join(", ");
                setAcceptExtensions(extensions); // Set the dynamic accept value
            } catch (error) {
                console.error("Error fetching allowed extensions:", error);
                alert("Error fetching allowed extensions.");
            }
        };

        fetchAllowedExtensions();
    }, []);

    const handleButtonClick = () => {
        // Simulate a click on the hidden file input
        fileInputRef.current.click();
    };

    const handleFileChange = (event) => {
        const selectedFile = event.target.files[0]; // Get the first file selected
        const fileExtension = selectedFile?.name.split(".").pop()?.toLowerCase();
        // Validate if the file extension is allowed
        if (selectedFile && allowedExtensions.some(ext => ext.Extension === fileExtension && ext.Status === "Hỗ trợ")) {
            let print_info = JSON.parse(localStorage.getItem('print_info'));
            const fileInfo = {
                file_name: selectedFile?.name,
                file_ext: selectedFile?.name.split(".").pop()?.toLowerCase(),
                file_size: selectedFile?.size,
                page_num: 0,
            }
            const formData = new FormData();
            formData.append("file", selectedFile);

            fetch("http://127.0.0.1:5000/api/pages-count", {
                method: "POST",
                body: formData,
            })
                .then(response => response.json())
                .then(data => {
                    if (data.page_count) {
                        console.log(`The document has ${data.page_count} pages.`);
                        fileInfo.page_num = data.page_count;
                    } else {
                        console.log(data.error || "Unable to get page count.");
                    }
                    Object.assign(print_info, fileInfo);
                    localStorage.setItem('print_info', JSON.stringify(print_info));
                    setFile(selectedFile);  // Store the file in state
                    console.log("File selected:", selectedFile);
                })
                .catch(error => {
                    console.error("Error uploading file:", error);
                }); 
            // navigate("/ChoosePrinter");
        } else {
            alert("Hãy chọn file với dạng tệp hợp lệ");
            // Reset the input field by clearing the file input
            event.target.value = "";
            // Optionally, reset the file state to null (or set it to an empty string)
            setFile(null); 
        }
    };
    // Upload the file when the file state changes
    useEffect(() => {
        if (file) {
            handleUpload();
        }
    }, [file]); // This hook runs whenever `file` changes

    const handleUpload = () => {
        if (!file) {
            console.log("No file selected.");
            alert("Cần chọn 1 file để tiếp tục");
            return;
        }
    
        console.log("File to upload:", file);
    
        // First, delete the uploads directory
        axios
            .delete("http://127.0.0.1:5000/api/delete-uploads")
            .then((response) => {
                if (response.status === 200) {
                    console.log("Uploads directory deleted successfully.");
    
                    // Now proceed with the file upload
                    const formData = new FormData();
                    formData.append("file", file); // Add the selected file to form data
    
                    axios
                        .post("http://127.0.0.1:5000/upload", formData, {
                            headers: {
                                "Content-Type": "multipart/form-data",
                            },
                        })
                        .then((uploadResponse) => {
                            if (uploadResponse.status === 200) {
                                alert("Thêm file thành công!");
                                navigate("/ChoosePrinter");
                            } else {
                                alert("Thêm file thất bại");
                            }
                        })
                        .catch((uploadError) => {
                            console.error("Error uploading file:", uploadError);
                            alert("Xảy ra lỗi trong quá trình thêm file");
                        });
                } else {
                    alert("Failed to delete uploads directory.");
                }
            })
            .catch((deleteError) => {
                console.error("Error deleting uploads directory:", deleteError);
                alert("Error deleting uploads directory.");
            });
    };
    

    return (
        <div>
            <Navbar property="Registered User" />
            <div className="background">
                <img
                    src={BackgroundSVG}
                    alt="Background"
                    className="background-image"
                />
                <div className="home-frame">
                    <div className="text-wrapper">Tải tài liệu</div>
                    <div className="home-frame-wrapper">
                        <div className="button-div">
                            <p className="text-wrapper-2">
                                Dạng tệp cho phép: {acceptExtensions}
                            </p>
                            <input
                                type="file"
                                onChange={handleFileChange}
                                className="file-input"
                                accept={acceptExtensions}
                                ref={fileInputRef} // Attach the ref to the file input
                                style={{ display: "none" }} // Hide the file input
                            />
                            <Button className="button-choose-file" onPress={handleButtonClick} variant="secondary">
                                <IconFilePlus className="icon-file-plus"/>
                                Chọn tệp từ thiết bị
                            </Button>
                        </div>
                    </div>
                </div>
            </div>
            <Footer />
        </div>
    );
}

export default Home;
