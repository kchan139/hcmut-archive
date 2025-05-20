import "./Chart.css"
import { useState, useEffect, useRef } from 'react';

function Chart({type, title, sensor}){
  const histogramRef = useRef(null);
  const [initialized, setInitialized] = useState(false);
  const [selectedDate, setSelectedDate] = useState('2025-04-23'); // default date
  
  const timePeriods = [
    "12-2 AM", "2-4 AM", "4-6 AM", "6-8 AM", 
    "8-10 AM", "10-12 PM", "12-2 PM", "2-4 PM", 
    "4-6 PM", "6-8 PM", "8-10 PM", "10-12 AM"
  ];
   // Initialize the histogram
  const initHistogram = () => {
    if (!histogramRef.current) return;
    
    const histogram = histogramRef.current;
    
    // Clear existing bars if any
    const existingBars = histogram.querySelectorAll('.bar-container');
    existingBars.forEach(bar => bar.remove());
    
    // Create bar containers for each time period
    timePeriods.forEach((time, index) => {
      const barContainer = document.createElement('div');
      barContainer.className = 'bar-container';
      
      const bar = document.createElement('div');
      bar.className = 'bar';
      bar.style.height = '0%';
      
      const valueLabel = document.createElement('div');
      valueLabel.className = 'value-label';
      valueLabel.textContent = '0';
      
      const timeLabel = document.createElement('div');
      timeLabel.className = 'time-label';
      timeLabel.textContent = time;
      
      barContainer.appendChild(bar);
      bar.appendChild(valueLabel);
      barContainer.appendChild(timeLabel);
      histogram.appendChild(barContainer);
    });
    
    setInitialized(true);
  };
  
  // Update the histogram with new data
  const updateHistogram = (data) => {
    if (!histogramRef.current) return;
    
    const bars = histogramRef.current.querySelectorAll('.bar');
    
    bars.forEach((bar, index) => {
      const value = data[index];
      const valueLabel = bar.querySelector('.value-label');
      
      // Animate the height change
      setTimeout(() => {
        bar.style.height = `calc(${value}% - 40px)`;
        valueLabel.textContent = value;
      }, index * 100);
    });
  };
  
  // Handle date change
  const handleDateChange = (e) => {
    setSelectedDate(e.target.value);
  };
  
  const fetchData = () => {
        fetch(`https://dadn-242-backend.vercel.app/webAction/getDailyStat?Sensor_ID=${sensor}&date=${selectedDate}`)
        .then((response) => { ///get data for light sensor (ID: LS01 (light sensor), SMS01 (soil moist sensor))
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        }).then((data) => {
            const fixedData = data.map(function(num){

              return num === 0 ? num : num.toFixed(2);
            })
            console.log(data);
            if (initialized) {
                updateHistogram(fixedData);
            } // Store the fetched data in state
        }).catch((e) => {
            console.error(e) // Catch and display any errors
        }); 
      
    }

  // Initialize chart on component mount
  useEffect(() => {
    initHistogram();
    
    // Initial update
    if (initialized) {
      updateHistogram([0,0,0,0,0,0,0,0,0,0,0,0]); // init will all 0s
      fetchData()
    }
    
    // Set up interval for updates
    // const intervalId = setInterval(fetchData, updateInterval);
    
    // Clean up on unmount
    // return () => {
    //   clearInterval(intervalId);
    // };
    // eslint-disable-next-line
  }, [initialized, selectedDate]);
    return (
        <>
            <div class = {type} >
                <h1>{title}</h1>
                <div className="date-picker-container">
                  <input 
                    type="date" 
                    value={selectedDate}
                    onChange={handleDateChange}
                    className="date-picker"
                  />
                </div>
                <div class="histogram" ref={histogramRef}>
                    <div class="y-axis">
                        <span class="y-axis-label">100</span>
                        <span class="y-axis-label">80</span>
                        <span class="y-axis-label">60</span>
                        <span class="y-axis-label">40</span>
                        <span class="y-axis-label">20</span>
                        <span class="y-axis-label">0</span>
                    </div>
                    <div class="x-axis"></div>
                </div>
            </div>
        </>
    )

}

export default Chart