import { useEffect, useState } from 'react';
import './Dashboard.css'
import Widget from './Widget.js'
import Chart from './Chart/Chart.js';


function Dashboard() {
    const [humid, setHumid] = useState(0);
    // const [temp, setTemp] = useState(0);
    const [light, setLight] = useState(0);

    // useEffect(() => {
    //     setInterval(() => {            
    //         //* get api value here
    //         const tempFeed = 10;
    //         setTemp(tempFeed);
    //     }, 2000);
    // }, [])

    useEffect(() => {
        setInterval(() => {            
            fetch('https://dadn-242-backend.vercel.app/getCurrentStat?Sensor_ID=LS01').then((response) => { ///get data for light sensor (ID: LS01)
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                return response.json();
            }).then((data) => {
                console.log(data);
                setLight(data.Measured_Stat); // Store the fetched data in state
            }).catch((e) => {
                console.error(e) // Catch and display any errors
            }); 
        }, 2000);
        setInterval(() => {            
            fetch('https://dadn-242-backend.vercel.app/getCurrentStat?Sensor_ID=SMS01').then((response) => { ///get data for soil moisture sensor (ID: SMS01)
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                return response.json();
            }).then((data) => {
                console.log(data);
                setHumid(data.Measured_Stat); // Store the fetched data in state
            }).catch((e) => {
                console.error(e) // Catch and display any errors
            }); 
        }, 2000);
    }, [])
    // let timeInterval = 2000;
    return (
        <div class="dashboard" display="inline-block">
           
            <Chart type = "histogram-container moisture-chart" /*</div>updateInterval={timeInterval}*/ title = "Moisture Chart" sensor="SMS01"></Chart>
            <Chart type = "histogram-container light-chart" /*updateInterval={timeInterval}*/ title = "Light Chart" sensor="LS01"></Chart>
    
            <Widget type = "widget metric-widget soil-moisture" value={humid} unit="%" lowest="0" highest="100">Soil Moisture</Widget>
            {/* <Widget value={temp} unit="°C" lowest="0" highest="50" >Temerature</Widget> */}   
            <Widget type = "widget metric-widget light" value={light} unit=" Lux" lowest="0" highest="100" >Light</Widget>
         
        </div>
    )
}

export default Dashboard;