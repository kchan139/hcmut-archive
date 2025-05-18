import React, { useState, useEffect } from "react";
import { Navbar } from "../../components/Navbar/Navbar";
import { Footer } from "../../components/Footer/Footer";
import BackgroundSVG from "../../assets/background.svg";
import { IconFilePlus } from "icons"
import { Button } from "primitives"
import "./adminLogin.css";
import { useNavigate } from "react-router-dom";


function AdminLogin() {
    const navigate = useNavigate();
    const [username, setUsername] = useState('')
    const [password, setPassword] = useState('')

    function NavigationButtons(){
        const navigate = useNavigate();
        return(
            <Button onPress={ValidateUser}
                    variant="secondary"
                    state="default"
                    size="medium"
                    className="button-login"
            >Đăng nhập
            </Button>
        )
    }

    const ValidateUser = () => {
        const today = new Date();
        const formattedDate = today.toISOString().split('T')[0]; // Get YYYY-MM-DD format
        const print_info = {
            MSSV: "",
            printer: "",
            date: formattedDate,
            status: "Đang chờ"
        };

        if (username === '7777' && password === '123') {
            print_info.MSSV = "7777"
            localStorage.setItem('print_info', JSON.stringify(print_info));
            console.log('Record set in localStorage:', print_info);
            navigate('/Admin_history')
        }
        else {
            localStorage.removeItem('print_info');
            alert('Sai tên đăng nhập hoặc mật khẩu')
        }
    }

    return (
        <div>
            <Navbar property="Guest" />

            <div className="login-section_AdminLogin">
                <div className="login-content_AdminLogin">
                    <div className="left-pane_AdminLogin">
                        <form className="login-form_AdminLogin">
                            {/* Caption */}
                            <p className="form-caption_AdminLogin">
                                <Button variant="subtle" className="change-user-button" onPress={() => navigate("/Login")}>
                                Bạn là học sinh? <u>Quay lại đăng nhập học sinh để tiếp tục.</u>
                                </Button>
                            </p>
                            <div className="form-content_AdminLogin">
                                {/* Username Field */}
                                <div className="form-group_AdminLogin">
                                    <label htmlFor="username" className="form-label_AdminLogin">
                                        Tên đăng nhập
                                    </label>
                                    <input
                                        id="username"
                                        type="text"
                                        className="form-input_AdminLogin"
                                        style={{color: 'black'}}
                                        value={username}
                                        onChange={(e) => setUsername(e.target.value)}
                                    />
                                </div>

                                {/* Password Field */}
                                <div className="form-group_AdminLogin">
                                    <label htmlFor="password" className="form-label_AdminLogin">
                                        Mật khẩu
                                    </label>
                                    <input
                                        id="password"
                                        type="password"
                                        className="form-input_AdminLogin"
                                        style={{color: 'black'}}
                                        value={password}
                                        onChange={(e) => setPassword(e.target.value)}
                                    />
                                </div>

                                {/* Remember Me Checkbox */}
                                <div className="form-group-checkbox_AdminLogin">
                                    <input
                                        id="remember-me"
                                        type="checkbox"
                                        className="form-checkbox_AdminLogin"
                                    />
                                    <label htmlFor="remember-me" className="form-checkbox-label_AdminLogin">
                                        Ghi nhớ đăng nhập
                                    </label>
                                </div>

                                {/* Submit Button */}
                                <div className="form-group_AdminLogin">
                                    <NavigationButtons/>
                                </div>
                            </div>
                        </form>
                    </div>
                </div>
            </div>

            <Footer />
        </div>
    );
}

export default AdminLogin;