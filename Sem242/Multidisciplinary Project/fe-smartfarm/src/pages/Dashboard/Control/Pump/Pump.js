import { useState, useEffect } from 'react';
import './Pump.css';
import Slider from '../../Slider';

function Pump() {
    const [isActive, setIsActive] = useState(false);
    const [isLoading, setIsLoading] = useState(true);
    const [sliderValue, setSliderValue] = useState(0);

    useEffect(() => {
        fetch('https://dadn-242-backend.vercel.app/getSetting?Output_ID=WP01')
            .then(res => res.json())
            .then(data => {
                setIsActive(data.Activation === "on");
                if (data.Limit !== undefined) {
                    setSliderValue(parseInt(data.Limit));
                }
                setIsLoading(false);
            });
        setInterval(()=>{
            fetch('https://dadn-242-backend.vercel.app/getSetting?Output_ID=WP01')
            .then(res => res.json())
            .then(data => {
                setIsActive(data.Activation === "on");
            });
        },2000)
    }, []);

    const handleToggle = async () => {
        const newActivation = !isActive ? "on" : "off";
        try {
            const response = await fetch(
                'https://dadn-242-backend.vercel.app/webAction/changeWaterPumpActivation',
                {
                    method: 'PUT',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ Activation: newActivation })
                }
            );
            if (!response.ok) throw new Error('Update failed');
            setIsActive(!isActive);
        } catch (error) {
            console.error('Toggle error:', error);
        }
    };


    const handleLimitRelease = async (newValue) => {
        try {
            await fetch('https://dadn-242-backend.vercel.app/webAction/setSoilMoistureLimit', {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ Limit: newValue })
            });
            console.log('Soil moisture limit updated to:', newValue);
        } catch (error) {
            console.error('Error updating soil moisture limit:', error);
        }
    };

    return (
        <div className="widget-card">
            <div className="widget-header">
                <div className="widget-icon">
                    <svg width="24" height="24" viewBox="0 0 24 24" fill="none">
                        <path d="M12 2L12 5" stroke="#333" strokeWidth="2" strokeLinecap="round" />
                        <path d="M5 5H19C19 5 21 8 17 10C13 12 11 12 7 10C3 8 5 5 5 5Z" stroke="#333" strokeWidth="2" />
                        <path d="M7 10C7 10 7 16 7 18C7 20 9 22 12 22C15 22 17 20 17 18C17 16 17 10 17 10" stroke="#333" strokeWidth="2" />
                    </svg>
                </div>
                <div className={`toggle-switch ${isActive ? 'active' : ''}`}>
                    <input 
                        type="checkbox" 
                        id="water-toggle" 
                        className="toggle-input"
                        checked={isActive}
                        onChange={handleToggle}
                        disabled={isLoading}
                    />
                    <label htmlFor="water-toggle" className="toggle-label">
                        <span className="toggle-button"></span>
                    </label>
                </div>
            </div>
            <div>
                <div className="widget-status">
                    {isLoading ? 'Loading...' : `Pump: ${isActive ? 'ON' : 'OFF'}`}
                </div>
                <div className="threshold">
                    Threshold: {sliderValue} %
                </div>
            </div>
           
            <Slider
                lowest={0}
                highest={90}
                value={sliderValue}
                unit="%"
                onChange={setSliderValue}
                onRelease={handleLimitRelease}
                step={10}

            />
        </div>
    );
}

export default Pump;
