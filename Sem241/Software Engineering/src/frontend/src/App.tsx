import Home from "./pages/Home/Home";
import Login from "./pages/Login/Login";
import ChoosePrinter from "./pages/ChoosePrinter/ChoosePrinter";
import Configurations from "./pages/Configurations/Configurations";
import PrintingComplete from "./pages/PrintingComplete/PrintingComplete";
import UserLog from "./pages/UserLog/UserLog";
import Buy_Page from "./pages/Buy_Page/Buy_Page";
import Admin_history from "./pages/Printing_History(Admin)/hist_Admin";
import Manage_Printer from "./pages/Manage_Printer/Manage_Printer";
import AdminLogin from "./pages/AdminLogin/AdminLogin";
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";

function App() {
    return (
        <div>
            <Router>
                <Routes>
                    <Route path="/" element={<Login />} />
                    <Route path="/Login" element={<Login />} />
                    <Route path="/Home" element={<Home />} />
                    <Route path="/ChoosePrinter" element={<ChoosePrinter />} />
                    <Route path="/Configurations" element={<Configurations />} />
                    <Route path="/PrintingComplete" element={<PrintingComplete />} />
                    <Route path="/UserLog" element={<UserLog />} />
                    <Route path="/Buy_Page" element={<Buy_Page />} />
                    <Route path="/Admin_history" element={<Admin_history />} />
                    <Route path="/Manage_Printer" element={<Manage_Printer />} />
                    <Route path="/AdminLogin" element={<AdminLogin />} />
                </Routes>
            </Router>
        </div>
    );
}

export default App;
