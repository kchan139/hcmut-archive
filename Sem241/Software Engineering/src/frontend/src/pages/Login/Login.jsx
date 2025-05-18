import React, { useState, useEffect } from "react";
import { Navbar } from "../../components/Navbar/Navbar";
import { Footer } from "../../components/Footer/Footer";
import BackgroundSVG from "../../assets/background.svg";
import { IconFilePlus } from "icons"
import { Button } from "primitives"
import { useNavigate } from "react-router-dom";
import "./login.css";
import "../../global.css";

function Home() {
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

        if (username === '2252938' && password === '123') {
            print_info.MSSV = "2252938"
            localStorage.setItem('print_info', JSON.stringify(print_info));
            console.log('Record set in localStorage:', print_info);
            navigate('/Home')
        }
        else if (username === '2252939' && password === '123') {
            print_info.MSSV = "2252939"
            localStorage.setItem('print_info', JSON.stringify(print_info));
            console.log('Record set in localStorage:', print_info);
            navigate('/Home')
        }
        else {
            localStorage.removeItem('print_info');
            alert('Sai tên đăng nhập hoặc mật khẩu')
        }
    } 
    
    return (
        <div>
            <Navbar property="Guest" />

            <div className="login-section">
                <div className="login-content">
                    <div className="left-pane">
                        <form className="login-form">
                            {/* Caption */}
                            <p className="form-caption">
                                <Button variant="subtle" className="change-user-button" onPress={() => navigate("/AdminLogin")}>
                                Bạn là quản trị viên? <u>Đăng nhập dưới quyền quản trị để tiếp tục.</u>
                                </Button>
                            </p>

                            <div className="form-content">
                                {/* Username Field */}
                                <div className="form-group">
                                    <label htmlFor="username" className="form-label">
                                        Tên đăng nhập
                                    </label>
                                    <input
                                        id="username"
                                        type="text"
                                        className="form-input"
                                        value={username}
                                        onChange={(e) => setUsername(e.target.value)}
                                    />
                                </div>

                                {/* Password Field */}
                                <div className="form-group">
                                    <label htmlFor="password" className="form-label">
                                        Mật khẩu
                                    </label>
                                    <input
                                        id="password"
                                        type="password"
                                        className="form-input"
                                        value={password}
                                        onChange={(e) => setPassword(e.target.value)}
                                    />
                                </div>

                                {/* Remember Me Checkbox */}
                                <div className="form-group-checkbox">
                                    <input
                                        id="remember-me"
                                        type="checkbox"
                                        className="form-checkbox"
                                    />
                                    <label htmlFor="remember-me" className="form-checkbox-label">
                                        Ghi nhớ đăng nhập
                                    </label>
                                </div>

                                {/* Submit Button */}
                                <div className="form-group">
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

export default Home;