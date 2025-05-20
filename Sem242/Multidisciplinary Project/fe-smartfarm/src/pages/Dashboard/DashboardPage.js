import Sidebar from '../../component/Sidebar/Sidebar';
import Header from '../../component/Header/Header';
import Dashboard from './Dashboard';
import "./DashboardPage.css"
import Control from './Control/Control';
import { useNavigate } from 'react-router-dom';
import { isAuthenticated } from '../../utils/auth';
import { useEffect } from 'react';

function DashboardPage() {
  const navigate = useNavigate();
  useEffect(()=>{
    const checkAuthentication=()=>{
      if (!isAuthenticated()){
        navigate('/');
      }
    }
    checkAuthentication();
  })
    return (
        <>
            <body>
                <Sidebar/>
                <maincontent>
                    <Header pageTitle="Dashboard"/>
                    <Dashboard/>
                    <Control/>
                </maincontent>
            </body>
        </>
    )
}

export default DashboardPage;