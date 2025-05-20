import './App.css';
import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom';
import Login from './pages/Login/Login';
import DashboardPage from './pages/Dashboard/DashboardPage';
import DeviceLogPage from './pages/DeviceLog/DeviceLogPage';

function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Navigate to="/login" />} />
        <Route path="/dashboard" element={<DashboardPage />} />
        <Route path="/login" element={<Login />} />
        <Route path="/device-log" element={<DeviceLogPage/>} />
      </Routes>
    </BrowserRouter>
  )
}

export default App;