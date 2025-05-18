import React from "react";
import PropTypes from "prop-types";
import { Logo } from "../Logo/Logo";
import { Button } from "primitives"; // Replace with your Button import
import "./Navbar.css";
import { useNavigate } from "react-router-dom";

export const Navbar = ({ property }) => {
    const navigate = useNavigate();
    return (
        <div className="navbar">
            {/* Navbar Content */}
            <div className="navbar-content">
                {/* Links Section */}
                <div className="links">
                    {/* Logo */}
                    <Logo />

                    {/* Buttons based on property */}
                    {property === "Admin" && (
                        <>
                            <Button variant="secondary" className="navbar-button" onPress={() => alert("/Admin_history")}>
                                Trang chủ
                            </Button>
                            <Button variant="secondary" className="navbar-button" onPress={() => navigate("/Admin_history")}>
                                Lịch sử
                            </Button>
                            <Button variant="secondary" className="navbar-button" onPress={() => alert("No functions yet")}>
                                Thống kê
                            </Button>
                            <Button variant="secondary" className="navbar-button" onPress={() => navigate("/Manage_Printer")}>
                                Quản lý
                            </Button>
                        </>
                    )}
                    {property === "Registered User" && (
                        <>
                            <Button variant="secondary" className="navbar-button" onPress={() => navigate("/Home")}>
                                Trang chủ
                            </Button>
                            <Button variant="secondary" className="navbar-button" onPress={() => navigate("/UserLog")}>
                                Lịch sử
                            </Button>
                            <Button variant="secondary" className="navbar-button" onPress={() => navigate("/Buy_Page")}>
                                Mua trang in
                            </Button>
                        </>
                    )}
                </div>

                {/* Additional Links */}
                <div className="links">
                    {property === "Guest" ? (
                        <Button variant="secondary" className="navbar-button" onPress={() => alert("Đăng nhập clicked!")}>
                            Đăng nhập
                        </Button>
                    ) : (
                        <Button variant="secondary" className="navbar-button" onPress={() => navigate("/")}>
                            Đăng xuất
                        </Button>
                    )}
                </div>
            </div>
        </div>
    );
};

// PropTypes validation
Navbar.propTypes = {
    property: PropTypes.oneOf(["Admin", "Registered User", "Guest"]).isRequired,
};
