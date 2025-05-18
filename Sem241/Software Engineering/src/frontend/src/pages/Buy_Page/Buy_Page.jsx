import React, { useState, useEffect } from "react";
import { Navbar } from "../../components/Navbar/Navbar";
import { Footer } from "../../components/Footer/Footer";
import BackgroundSVG from "../../assets/background.svg";
import "./Buy_Page.css";
import axios from "axios";

const Buy_Page = () => {
  const [balance, setBalance] = useState(0); // Balance with initial being 100 (Change the default to actual data in backend)
  const [pagesToBuy, setPagesToBuy] = useState(0); // The numbers of pages the user input
  const [paymentMethod, setPaymentMethod] = useState("ZaloPay");
  const pricePerPage = 500; // Price per page (500 VNĐ)
  const totalPrice = pagesToBuy * pricePerPage;
  let print_info = JSON.parse(localStorage.getItem('print_info'))

  useEffect(() => {
    print_info = JSON.parse(localStorage.getItem('print_info'))
    axios
        .get(`http://127.0.0.1:5000/api/page_num/${print_info.MSSV}`)
        .then((response) => {
            setBalance(response.data.page_num);
        })
        .catch((error) => {
            console.error("Error fetching student_page:", error);
            setBalance(""); // Clear previous records
        });
}, []);

  const handleBuyPages = () => {
    if (pagesToBuy > 0) {
      const confirmPurchase = window.confirm(
        `Bạn chuẩn bị mua ${pagesToBuy} trang với giá ${totalPrice.toLocaleString()} VNĐ với phương thức thanh toán ${paymentMethod}. Xác nhận thanh toán ?`
      );
  
      if (confirmPurchase) {
        setBalance(balance + pagesToBuy); // Update balance
        axios
            .put(`http://127.0.0.1:5000/api/page_num/${print_info.MSSV}`, {'page_num' : Number(balance + pagesToBuy)})
            .then((response) => {
                console.log(response.data);
            })
            .catch((error) => {
                console.error('Error updating page:', error);
                alert('Failed to add page.');
            });
        alert(
          `Thành công mua ${pagesToBuy} trang với giá ${totalPrice.toLocaleString()} VNĐ bằng ${paymentMethod}.`
        );
        setPagesToBuy(0); // Reset input field
      }
    } else {
      alert("Vui lòng nhập số trang mua hợp lệ.");
    }
  };
  

  return (
    <div>
      <Navbar property="Registered User" />
      <div
        style={{
          backgroundImage: `url(${BackgroundSVG})`,
          backgroundSize: "cover",
          backgroundRepeat: "no-repeat",
          backgroundPosition: "center",
          width: "100%",
          height: "100vh",
          display: "flex",
          justifyContent: "center",
          alignItems: "center",
          padding: "20px",
        }}
      >
        <div className="buypage-container">
          <h2 className="page-balance">
            Số trang dư hiện tại: {balance.toLocaleString()} trang
          </h2>
          <div className="buy-form">
            <label htmlFor="pagesToBuy" className="form-label">
              Nhập số trang cần mua:
            </label>
            <input
                type="number"
                id="pagesToBuy"
                className="form-input"
                min="0"
                value={pagesToBuy === 0 ? "" : pagesToBuy} // Display blank for 0
                onChange={(e) => {
                    const value = e.target.value;
                    setPagesToBuy(value === "" ? 0 : parseInt(value, 10)); // Parse and handle empty input
                }}
            />
            <label htmlFor="paymentMethod" className="form-label">
              Chọn phương thức thanh toán:
            </label>
            <select
              id="paymentMethod"
              className="form-select"
              value={paymentMethod}
              onChange={(e) => setPaymentMethod(e.target.value)}
            >
              <option value="ZaloPay">ZaloPay</option>
              <option value="MoMo">MoMo</option>
              <option value="BkPay">BkPay</option>
            </select>
            <p className="total-price">
              Tổng số tiền: {totalPrice.toLocaleString()} VNĐ
            </p>
            <button className="buy-button" onClick={handleBuyPages}>
              Mua trang
            </button>
          </div>
        </div>
      </div>
      <Footer />
    </div>
  );
};

export default Buy_Page;
