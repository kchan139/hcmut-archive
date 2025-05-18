import React, { useState, useEffect } from "react";
import { Navbar } from "../../components/Navbar/Navbar";
import { Footer } from "../../components/Footer/Footer";
import BackgroundSVG from "../../assets/background.svg"; // Path to the SVG
import "./printingComplete.css"
import { ButtonGroup } from "primitives"
import { Button } from "primitives"
import { useNavigate } from "react-router-dom";

function NavigationButtons(){
    const navigate = useNavigate();
    return(
        <ButtonGroup style={{position: "absolute", bottom: "15%", left: "10%"}}>
            <Button className="button-login" onPress={() => navigate("/Home")}>Trở về trang chủ</Button>
        </ButtonGroup>
    )
}

function PrintingComplete(){
    const [record, setRecord] = useState({
        Name: "Nguyen Van Teo",
        ID: "2252937",
        Email: "TeoVanNg@gmail.com",
        Faculty: "Computer Science",
        Code: "MF125241242",
        Area: "A4 - 402",
        Time: "32 - 11 - 2024"
    });
    useEffect(() => {
        // Fetch the file preview from the backend
        const print_info = JSON.parse(localStorage.getItem('print_info'))
        setRecord({
            Name: "Nguyen Van Teo",
            ID: print_info?.MSSV || "",
            Email: "TeoVanNg@gmail.com",
            Faculty: "Computer Science",
            Code: "MF125241242",
            Area: "A4 - 402",
            Time: print_info?.date || "",
        })
    }, [])
    
    return(
        <div>
            <Navbar property="Registered User"/>
            <div className="background_PrintingComplete">
                <img
                    src={BackgroundSVG}
                    alt="Background_PrintingComplete"
                    className="background-image_PrintingComplete"
                />{
                    <div className="content_PrintingComplete">
                        <div className="border_PrintingComplete">
                            <div className="header_PrintingComplete">Gửi yêu cầu in thành công</div>
                            <div className="line1_PrintingComplete">Tài liệu in của bạn đang được xử lý, cảm ơn vì đã sử dụng dịch vụ</div>
                            <div className="line2_PrintingComplete" style={{fontSize:"20px", marginTop: "50px"}}><b>Thông tin</b></div>
                            <div style={{ display: "flex", gap: "200px" }}>
                                <span>
                                    <div className="line2_PrintingComplete">Họ và tên: <span style={{marginLeft:"10px"}}>{record.Name}</span></div>
                                    <div className="line2_PrintingComplete">Mã số sinh viên: <span style={{marginLeft:"10px"}}>{record.ID}</span></div>
                                    <div className="line2_PrintingComplete">Email: <span style={{marginLeft:"10px"}}>{record.Email}</span></div>
                                    <div className="line2_PrintingComplete">Khoa: <span style={{marginLeft:"10px"}}>{record.Faculty}</span></div>
                                </span>
                                <span>
                                    <div className="line2_PrintingComplete">Mã yêu cầu: <span style={{marginLeft:"10px"}}>{record.Code}</span></div>
                                    <div className="line2_PrintingComplete">Địa điểm: <span style={{marginLeft:"10px"}}>{record.Area}</span></div>
                                    <div className="line2_PrintingComplete">Thời gian yêu cầu: <span style={{marginLeft:"10px"}}>{record.Time}</span></div>
                                </span>    
                            </div>
                            

                            <div style={{width:"100px", height:"100px"}}></div>

                            <NavigationButtons/>
                        </div>
                    </div>
                }
            </div>
            <Footer />
        </div>
    )
}

export default PrintingComplete