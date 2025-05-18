import React, { useState, useEffect } from "react";
import { Navbar } from "../../components/Navbar/Navbar";
import { Footer } from "../../components/Footer/Footer";
import BackgroundSVG from "../../assets/background.svg"; // Path to the SVG
import "./configurations.css"
import { Select, SelectItem } from "primitives"
import { ButtonGroup, Navigation } from "primitives";
import { Button } from "primitives";
import { InputField } from "primitives";
import { useNavigate } from "react-router-dom";
import axios from "axios";
import mammoth from 'mammoth';

function Configurations() {
    let print_info = JSON.parse(localStorage.getItem('print_info'))
    const [studentPages, setStudentPages] = useState("")
    const [totalPages, setTotalPages] = useState(0);
    const [options, setOptions] = useState({
        doubleSided: "Yes",
        copies: 1,
    });
    const [preview, setPreview] = useState(null);
    const [record, setRecord] = useState({
        Name: "Nguyen Van Teo",
        ID: "2252937",
        Email: "TeoVanNg@gmail.com",
        Faculty: "Computer Science",
        Code: "MF125241242",
        Area: "A4 - 402",
        Time: "32 - 11 - 2024"
    });
    const navigate = useNavigate();

    function NavigationButtons(){
        return(
            <ButtonGroup className="button-group-configurations" style={{marginLeft: "90px", marginTop: "30px"}}>
                <Button className="button-back" onPress={() => navigate("/ChoosePrinter")} variant="subtle">Quay lại</Button>
                <Button className="button-next" onPress={addRecord} variant="primary">Tiếp tục</Button>
            </ButtonGroup>
        )
    }

    const addRecord = () => {
        if (Number(studentPages) < Number(totalPages)) {
            alert("Số trang của tài khoản không đủ. Hãy mua thêm trang in");
            return;
        }
        console.log(print_info.MSSV)
        axios
            .put(`http://127.0.0.1:5000/api/page_num/${print_info.MSSV}`, {'page_num' : Number(studentPages) - Number(totalPages)})
            .then((response) => {
                console.log(response.data);
            })
            .catch((error) => {
                console.error('Error updating page:', error);
                alert('Failed to add page.');
            });

        axios
            .put(`http://127.0.0.1:5000/api/records/${print_info.MSSV}`, print_info)
            .then((response) => {
                console.log(response.data);
                alert('Thêm tác vụ in thành công');
                navigate("/PrintingComplete")
            })
            .catch((error) => {
                console.error('Error adding record:', error);
                alert('Thêm tác vụ in thất bại');
            });
    };

    useEffect(() => {
        // Fetch the file preview from the backend
        print_info = JSON.parse(localStorage.getItem('print_info'))
        setRecord({
            Name: "Nguyen Van Teo",
            ID: print_info?.MSSV || "",
            Email: "TeoVanNg@gmail.com",
            Faculty: "Computer Science",
            Code: "MF125241242",
            Area: "A4 - 402",
            Time: print_info?.date || "",
        })
        axios
            .get(`http://127.0.0.1:5000/api/page_num/${print_info.MSSV}`)
            .then((response) => {
                setStudentPages(response.data.page_num);
            })
            .catch((error) => {
                console.error("Error fetching student_page:", error);
                setStudentPages(""); // Clear previous records
            });
        axios
            .get("http://127.0.0.1:5000/api/get-file", { responseType: "blob" }) // Adjust the endpoint as needed
            .then((response) => {
                const file = response.data;
                const fileType = response.headers["content-type"];
                const fileUrl = URL.createObjectURL(file);
                console.log(file, fileType, fileUrl);
    
                // Check the content type to determine how to handle the preview
                if (fileType.startsWith("image/")) {
                    // For image previews (e.g., PNG for the first page of a PDF or DOCX)
                    setPreview(<img src={fileUrl} alt="Preview" style={{ width: "100%", height: "100%", objectFit: "contain" }} />);
                } else if (fileType === "application/pdf") {
                    // If the backend still returns PDFs for some reason (not expected here)
                    setPreview(<iframe src={fileUrl} style={{ width: "100%", height: "400px" }} title="PDF Preview" />);
                } else {
                    alert("Unsupported file type.");
                }
            })
            .catch((error) => {
                console.error("Error fetching file:", error);
            });
    }, []);

    useEffect(() => {
        const calculateTotalPages = () => {
            const pagesPerCopy = print_info?.page_num || 0;
            const isDoubleSided = options.doubleSided === "Yes";
            const copies = parseInt(options.copies, 10) || 1;

            // Double-sided logic
            const pagesPerSheet = isDoubleSided ? Math.ceil(pagesPerCopy / 2) : pagesPerCopy;
            const total = pagesPerSheet * copies;

            setTotalPages(total);
        };

        calculateTotalPages();
    }, [options, print_info]);

    const handleOptionChange = (event) => {
        const { name, value } = event.target;
        setOptions((prev) => ({ ...prev, [name]: value }));
    };
    

    return (
        <div>
            <Navbar property="Registered User"/>
            <div className="background_Configurations">
                <img
                    src={BackgroundSVG}
                    alt="Background_Configurations"
                    className="background-image_Configurations"
                />{
                    <div className="content_Configurations">
                        <div className="border_Configurations">
                            <div className="header_Configurations">In tài liệu</div>
                            <div className="line_Configurations"><p>Số trang hiện có của người dùng: <strong>{studentPages}</strong></p></div><br />
                            <div className="line_Configurations">In hai mặt
                                <select className="box_Configurations" style={{marginLeft: "99px"}} name="doubleSided" value={options.doubleSided} onChange={handleOptionChange}>
                                    <option value="Yes">Có</option>
                                    <option value="No">Không</option>
                                </select>
                            </div><br />
                            <div className="line_Configurations">Số bản sao
                                <input className="box_Configurations" name="copies" type="number" min="1" defaultValue={1} onChange={handleOptionChange} style={{marginLeft: "88px", width: "100px"}}/></div><br />
                            <div className="line_Configurations">Loại giấy
                                <select className="box_Configurations" style={{marginLeft: "105px"}}>
                                    <option value="Letter">Letter</option>
                                    <option value="Tabloid">Tabloid</option>
                                    <option value="A3">A3</option>
                                    <option value="A4" selected>A4</option>
                                    <option value="A5">A5</option>
                                </select>
                            </div><br />
                            <div className="line_Configurations">Hướng in
                                <select className="box_Configurations" style={{marginLeft: "105px"}}>
                                    <option value="Vertical" selected>Dọc</option>
                                    <option value="Horizontal">Ngang</option>
                                </select>
                            </div><br />
                            <div className="line_Configurations">Tỉ lệ in
                                <input className="box_Configurations" type="number" min="1" max="1000" defaultValue={100} style={{marginLeft: "123px"}}/>
                                <span class="input-group-text">%</span>    
                            </div><br />
                            <div className="line_Configurations">
                                <p>Tổng số trang cần in: <strong>{totalPages}</strong></p>
                            </div><br />
                            <NavigationButtons/>
                        </div>
                        <div className="preview-container">
                            {preview || <div className="placeholder">File Preview</div>}
                        </div>
                    </div>
                }
            </div>
            <Footer />
        </div>
    )
}

export default Configurations;
