import React, { useEffect, useState } from 'react';
import { useNavigate } from 'react-router-dom';
import Sidebar from '../../component/Sidebar/Sidebar';
import Header from '../../component/Header/Header';
import { isAuthenticated } from '../../utils/auth';
import './DeviceLogPage.css';

function DeviceLogPage() {
  const navigate = useNavigate();
  const [logData, setLogData] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [showEntries, setShowEntries] = useState(10);
  const [searchTerm, setSearchTerm] = useState('');
  const [currentPage, setCurrentPage] = useState(1);
  const logsPerPage = showEntries;
  const totalPages = Math.ceil(logData.length / logsPerPage);
  const filteredLogs = logData.filter(log =>
    Object.values(log).some(value =>
      String(value).toLowerCase().includes(searchTerm.toLowerCase())
    )
  );
  const currentLogs = filteredLogs.slice(
    (currentPage - 1) * logsPerPage,
    currentPage * logsPerPage
  );
  const deviceMapping = {
    'WP01': 'Water Pump 1',
    'L01': 'Light 1',
  };

  useEffect(() => {
    const checkAuthentication = () => {
      if (!isAuthenticated()) {
        navigate('/login');
      }
    };
    checkAuthentication();

    const fetchLogData = async () => {
      setLoading(true);
      setError(null);
      try {
        const outputIds = Object.keys(deviceMapping);
        let allLogs = [];
        for (const id of outputIds) {
          const response = await fetch(`https://dadn-242-backend.vercel.app/getActionLog?Output_ID=${id}`);
          if (!response.ok) {
            throw new Error(`Failed to fetch logs for ${id}`);
          }
          const data = await response.json();
          const mappedLogs = data.map(log => ({
            deviceName: deviceMapping[log.Output_ID] || log.Output_ID,
            status: log.Action === 'enable' ? 'on' : 'off',
            timestamp: log.Action_Time,
            outputId: log.Output_ID,
            originalLog: log
          }));
          allLogs = [...allLogs, ...mappedLogs];
        }
        allLogs.sort((a, b) => new Date(b.timestamp) - new Date(a.timestamp));
        setLogData(allLogs);
        setLoading(false);
      } catch (err) {
        setError(err.message);
        setLoading(false);
      }
    };
    fetchLogData();
    const interval = setInterval(fetchLogData, 5000);

    return () => clearInterval(interval);
    // eslint-disable-next-line
  }, [navigate]);

  const handleShowEntriesChange = (event) => {
    setShowEntries(parseInt(event.target.value, 10));
    setCurrentPage(1);
  };

  const handleSearchChange = (event) => {
    setSearchTerm(event.target.value);
    setCurrentPage(1);
  };

  const handlePageChange = (page) => {
    setCurrentPage(page);
  };

  return (
    <>
      <div className="device-config-page">
        <Sidebar />
        <div className="main-content">
          {/* Pass the pageTitle prop here */}
          <Header pageTitle="Device Log" />
          <div className="device-config-container">
            <div className="table-controls">
              <div className="show-entries">
                <span>Show</span>
                <select value={showEntries} onChange={handleShowEntriesChange}>
                  <option value={10}>10</option>
                  <option value={25}>25</option>
                  <option value={50}>50</option>
                </select>
                <span>entries</span>
              </div>
              <div className="search-input">
                <input
                  type="text"
                  placeholder="Search..."
                  value={searchTerm}
                  onChange={handleSearchChange}
                />
                <svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round">
                  <circle cx="11" cy="11" r="8"></circle>
                  <line x1="21" y1="21" x2="16.65" y2="16.65"></line>
                </svg>
              </div>
            </div>
            <div className="device-table">
              <table>
                <thead>
                   <tr>
                    <th>Device Name</th>
                    <th>Status</th>
                    <th>Timestamp</th>
                  </tr>
                </thead>
                <tbody>
                  {loading ? (
                    <tr>
                      <td colSpan="3" style={{ textAlign: 'center' }}>Loading logs...</td>
                    </tr>
                  ) : error ? (
                    <tr>
                      <td colSpan="3" style={{ textAlign: 'center', color: 'red' }}>Error: {error}</td>
                    </tr>
                  ) : currentLogs.length === 0 ? (
                    <tr>
                       <td colSpan="3" style={{ textAlign: 'center' }}>No logs found.</td>
                    </tr>
                  ) : (
                    currentLogs.map((log, index) => (
                        <tr key={index}>
                          <td>{log.deviceName || 'N/A'}</td>
                          <td>
                            <span className={log.status === 'on' ? 'status-active' : 'status-inactive'}>
                              {log.status ? log.status.toUpperCase() : 'N/A'}
                            </span>
                           </td>
                          <td>{log.timestamp ? new Date(log.timestamp).toLocaleString() : 'N/A'}</td>
                        </tr>
                    ))
                  )}
                </tbody>
              </table>
            </div>
             <div className="pagination">
              <button onClick={() => handlePageChange(currentPage - 1)} disabled={currentPage === 1}>Previous</button>
              {[...Array(totalPages)].map((_, i) => (
                <button key={i + 1} onClick={() => handlePageChange(i + 1)} className={currentPage === i + 1 ? 'active' : ''}>
                  {i + 1}
                </button>
              ))}
              <button onClick={() => handlePageChange(currentPage + 1)} disabled={currentPage === totalPages || totalPages === 0}>Next</button>
            </div>
          </div>
        </div>
      </div>
    </>
  );
}

export default DeviceLogPage;