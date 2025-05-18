import React, { useState, useEffect } from "react";
import axios from "axios";
import { Navbar } from "../../components/Navbar/Navbar";
import { Footer } from "../../components/Footer/Footer";
import BackgroundSVG from "../../assets/background.svg";
import "./Manage_Printer.css";
import { IconPrinter } from "icons";

const Manage_Printer = () => {
  const [printers, setPrinters] = useState([]);
  const [selectedPrinters, setSelectedPrinters] = useState([]);
  const [newPrinter, setNewPrinter] = useState("");
  const [selectedExtensions, setSelectedExtensions] = useState([]);

  useEffect(() => {
    // Fetch printers from the backend
    axios
      .get("http://127.0.0.1:5000/api/printers-admin")
      .then((response) => {
        setPrinters(response.data);
      })
      .catch((error) => {
        console.error("Error fetching printers:", error);
      });

      // Fetch allowed extensions from the backend
    axios
    .get("http://127.0.0.1:5000/api/allowed-extensions")
    .then((response) => {
      setSelectedExtensions(response.data.allowed_extensions);
      console.log("Selected extensions:", response.data.allowed_extensions);
    })
    .catch((error) => {
      console.error("Error fetching allowed extensions:", error);
    });
  }, []);


  const saveExtensions = (extension, status) => {
    setSelectedExtensions((prev) => 
      prev.map((ext) =>
        ext.Extension === extension ? { ...ext, Status: status } : ext
      )
    );
  };

  useEffect(() => {
    // Only send the request if the extensions have changed
    if (selectedExtensions.length > 0) {
      axios
        .put("http://127.0.0.1:5000/api/allowed-extensions", selectedExtensions)
        .then((response) => {
          console.log("Extensions updated");
        })
        .catch((error) => {
          console.error("Error updating extensions:", error);
        });
    }
  }, [selectedExtensions]); // Trigger this effect when selectedExtensions changes
  
  const togglePrinterStatus = (id, currentStatus) => {
    const updatedStatus = currentStatus === "Khả dụng" ? "Không khả dụng" : "Khả dụng";

    axios
      .put(`http://127.0.0.1:5000/api/printers/${id}`, { status: updatedStatus })
      .then((response) => {
        setPrinters((prevPrinters) =>
          prevPrinters.map((printer) =>
            printer.id === id ? { ...printer, status: updatedStatus } : printer
          )
        );
      })
      .catch((error) => {
        console.error("Error updating printer status:", error);
      });
  };

  const addPrinter = () => {
    if (newPrinter.trim()) {
      const newPrinterData = { name: newPrinter, status: "Khả dụng" };
      axios
        .post("http://127.0.0.1:5000/api/printers", newPrinterData)
        .then((response) => {
          setPrinters((prevPrinters) => [...prevPrinters, response.data]);
          setNewPrinter("");
        })
        .catch((error) => {
          console.error("Error adding new printer:", error);
        });
    }
  };

  return (
    <div>
      <Navbar property="Admin" />
      <div
        style={{
          backgroundImage: `url(${BackgroundSVG})`,
          backgroundSize: "cover",
          backgroundRepeat: "no-repeat",
          backgroundPosition: "center",
          width: "100%",
          height: "100vh",
          display: "flex",
          flexDirection: "column",
          justifyContent: "center",
          alignItems: "center",
          padding: "20px",
          paddingBottom: "50px",
        }}
      >
        <h1
          style={{
            color: "#fff",
            marginBottom: "30px",
            marginTop: "50px",
            fontSize: "36px",
          }}
        >
          Quản lý máy in
        </h1>

        {/* Add Printer Section */}
        <div className="add-printer-section">
          <input
            type="text"
            placeholder="Nhập thông tin máy in..."
            value={newPrinter}
            onChange={(e) => setNewPrinter(e.target.value)}
            className="add-printer-input"
          />
          <button onClick={addPrinter} className="add-printer-button">
            Thêm máy in
          </button>
        </div>

        <div className="manageprinter-container">
          {printers.map((printer) => (
            <div className="printer-card" key={printer.id}>
              <div className="printer-info">
                <IconPrinter size="32" className="icon-black" />
                <span>
                  {printer.name} - {printer.status}
                </span>
              </div>
              <input
                type="checkbox"
                checked={printer.status === "Khả dụng"}
                onChange={() => togglePrinterStatus(printer.id, printer.status)}
              />
            </div>
          ))}
        </div>
        <div className="ext-container">
          <h2>Các loại file được hỗ trợ:</h2>
          {selectedExtensions.map((extension) => (
            <div className="printer-card-sm" key={extension.Extension}>
                <input
                  type="checkbox"
                  value={extension.Extension}
                  checked={extension.Status === "Hỗ trợ"}
                  onChange={(e) => saveExtensions(extension.Extension, e.target.checked ? "Hỗ trợ" : "Không hỗ trợ")}
                />
                {extension.Extension}
            </div>
          ))}
        </div>
      </div>
      <Footer />
    </div>
  );
};

export default Manage_Printer;
