import { useState, useEffect } from 'react';
import './Light.css';
import Slider from '../../Slider';

function Light() {
    const [isActive, setIsActive] = useState(false);
    const [isLoading, setIsLoading] = useState(true);
    const [sliderValue, setSliderValue] = useState(0);

    useEffect(() => {
        fetch('https://dadn-242-backend.vercel.app/getSetting?Output_ID=L01')
            .then(res => res.json())
            .then(data => {
                setIsActive(data.Activation === "on");
                if (data.Limit !== undefined) {
                    setSliderValue(parseInt(data.Limit));
                }
                setIsLoading(false);
            });
        setInterval(()=>{
            fetch('https://dadn-242-backend.vercel.app/getSetting?Output_ID=L01')
            .then(res => res.json())
            .then(data => {
                setIsActive(data.Activation === "on");
            });
        },2000)
    }, []);

    const handleToggle = async () => {
        const newActivation = isActive ? "off" : "on";
        try {
            await fetch('https://dadn-242-backend.vercel.app/webAction/changeLightActivation', {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ Activation: newActivation })
            });
            setIsActive(!isActive);
        } catch (error) {
            console.error('Toggle error:', error);
        }
    };

    // Handler that sends the new limit to the backend on slider release
    const handleLimitRelease = async (newValue) => {
        try {
            await fetch('https://dadn-242-backend.vercel.app/webAction/setLightLimit', {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ Limit: newValue })
            });
            console.log('Light limit updated to:', newValue);
        } catch (error) {
            console.error('Error updating light limit:', error);
        }
    };

    return (
        <div className="widget-card">
            <div className="widget-header">
                <div className="widget-icon">
                    <svg width="24" height="24" viewBox="0 0 24 24" fill="none">
                        <circle cx="12" cy="12" r="5" stroke="#4CAF50" strokeWidth="2"/>
                        <path d="M12 4V2" stroke="#4CAF50" strokeWidth="2" strokeLinecap="round"/>
                        <path d="M12 22V20" stroke="#4CAF50" strokeWidth="2" strokeLinecap="round"/>
                        <path d="M20 12L22 12" stroke="#4CAF50" strokeWidth="2" strokeLinecap="round"/>
                        <path d="M2 12L4 12" stroke="#4CAF50" strokeWidth="2" strokeLinecap="round"/>
                        <path d="M17.6569 6.34315L19.0711 4.92893" stroke="#4CAF50" strokeWidth="2" strokeLinecap="round"/>
                        <path d="M4.92893 19.0711L6.34315 17.6569" stroke="#4CAF50" strokeWidth="2" strokeLinecap="round"/>
                        <path d="M17.6569 17.6569L19.0711 19.0711" stroke="#4CAF50" strokeWidth="2" strokeLinecap="round"/>
                        <path d="M4.92893 4.92893L6.34315 6.34315" stroke="#4CAF50" strokeWidth="2" strokeLinecap="round"/>
                    </svg>
                </div>
                <div className={`toggle-switch ${isActive ? 'active' : ''}`}>
                    <input
                        type="checkbox"
                        id="light-toggle"
                        className="toggle-input"
                        checked={isActive}
                        onChange={handleToggle}
                        disabled={isLoading}
                    />
                    <label htmlFor="light-toggle" className="toggle-label">
                        <span className="toggle-button"></span>
                    </label>
                </div>
            </div>
            <div>
                <div className="widget-status">
                    {isLoading ? 'Loading...' : `Light: ${isActive ? 'ON' : 'OFF'}`}
                </div>
                <div className="threshold">
                    Threshold: {sliderValue} Lux
                </div>
            </div>
            <Slider
                lowest={0}
                highest={90}
                value={sliderValue}
                unit="Lux"
                onChange={setSliderValue}
                onRelease={handleLimitRelease}
                step={10}  // Only this slider will update in steps of 10
            />
        </div>
    );
}

export default Light;
