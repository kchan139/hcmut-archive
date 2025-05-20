import React from 'react';
import { useNavigate, useLocation } from 'react-router-dom';
import { logout } from '../../utils/auth';
import Logo from '../../assets/logo/logotree2.svg';
import LogoName from '../../assets/logo/logotree3.svg';
import './Sidebar.css';

function Sidebar() {
  const navigate = useNavigate();
  const location = useLocation();

  return (
    <div className="sidebar">
      <div className="logo" onClick={() => navigate('/')}>
        <img src={Logo} width="40%" height="40%" alt="icon" />
        <img src={LogoName} width="70%" alt="icon" />
      </div>

      <div
        className={`menu-item ${location.pathname === '/dashboard' ? 'active' : ''}`}
        onClick={() => navigate('/dashboard')}
      >
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none">
          <rect x="3" y="3" width="7" height="7" rx="1" fill="#4CAF50" />
          <rect x="3" y="14" width="7" height="7" rx="1" fill="#4CAF50" />
          <rect x="14" y="3" width="7" height="7" rx="1" fill="#4CAF50" />
          <rect x="14" y="14" width="7" height="7" rx="1" fill="#4CAF50" />
        </svg>
        <div className="menu-text">Dashboard</div>
      </div>

      <div
        className={`menu-item ${location.pathname === '/device-log' ? 'active' : ''}`}
        onClick={() => navigate('/device-log')}
      >
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none">
          <path d="M12 4L12 20" stroke="#333" strokeWidth="2" />
          <path d="M12 4C14 7 17 8 20 8" stroke="#333" strokeWidth="2" />
          <path d="M12 4C10 7 7 8 4 8" stroke="#333" strokeWidth="2" />
          <path d="M12 12C14 15 17 16 20 16" stroke="#333" strokeWidth="2" />
          <path d="M12 12C10 15 7 16 4 16" stroke="#333" strokeWidth="2" />
        </svg>
        <div className="menu-text">Device Log</div>
      </div>

      <div
        className="menu-item"
        onClick={() => {
          logout();
          navigate('/login');
        }}
        style={{ marginTop: 'auto' }}
      >
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none">
          <path d="M9 21H5a2 2 0 01-2-2V5a2 2 0 012-2h4" stroke="#333" strokeWidth="2" />
          <path d="M16 17l5-5-5-5" stroke="#333" strokeWidth="2" />
          <path d="M21 12H9" stroke="#333" strokeWidth="2" />
        </svg>
        <div className="menu-text">Logout</div>
      </div>
    </div>
  );
}

export default Sidebar;