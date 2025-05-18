import React, { useState, useEffect } from 'react';
import { Navbar } from "../../components/Navbar/Navbar";
import { Footer } from "../../components/Footer/Footer";
import BackgroundSVG from "../../assets/background.svg";
import "./choosePrinter.css";
import { IconPrinter } from "icons";
import { ButtonGroup, Navigation } from "primitives";
import { Button } from "primitives";
import { useNavigate } from "react-router-dom";
import axios from "axios";

function ChoosePrinter(){
    // State to hold the printers data
    const [printers, setPrinters] = useState([]);
    const [selectedPrinter, setSelectedPrinter] = useState('');
    const navigate = useNavigate();

    function NavigationButtons(){
        return(
            <ButtonGroup align="justify">
                <Button onPress={() => navigate("/Home")} variant="primary" className="button-back">Quay lại</Button>
                <Button onPress={setPrinter} variant="secondary" className="button-next">Tiếp tục</Button>
            </ButtonGroup>
        )
    }

    const setPrinter = () => {
        if (!selectedPrinter) {
            alert("Máy in không được để trống")
            return;
        }
        const print_info = JSON.parse(localStorage.getItem('print_info'))
        print_info.printer = selectedPrinter; // Update the print_info object with the selected printer
        localStorage.setItem('print_info', JSON.stringify(print_info));
        navigate("/Configurations")
    };
    
    // Fetch printers when the component mounts
    useEffect(() => {
        // Fetch data from Flask backend
        axios.get("http://127.0.0.1:5000/api/printers")
            .then(response => {
                // Set the printers data to state
                setPrinters(response.data);
            })
            .catch(error => {
                console.error("Error fetching printers:", error);
            });
    }, []);

    return (
        <div>
            <Navbar property="Registered User" />
            <div className="background_choosePrinter">
                <img
                    src={BackgroundSVG}
                    alt="Background_choosePrinter"
                    className="background-image_choosePrinter"
                />
                <div className="content_choosePrinter">
                    <div className="border_choosePrinter">
                        <div className="header_choosePrinter">Máy in khả dụng</div>

                        {/* Dynamically render printers */}
                        {printers.map(printer => (
                            <div key={printer.id} className="bar_choosePrinter">
                                <IconPrinter size="32" className="printerIcon_choosePrinter" />
                                <span className="line_choosePrinter">
                                    {printer.name}
                                </span>
                                <input type="radio" name="printer" className="radioButton_choosePrinter" value={printer.name} onChange={(e) => setSelectedPrinter(e.target.value)} />
                            </div>
                        ))}

                        <NavigationButtons />
                    </div>
                </div>
            </div>
            <Footer />
        </div>
    );
}

export default ChoosePrinter