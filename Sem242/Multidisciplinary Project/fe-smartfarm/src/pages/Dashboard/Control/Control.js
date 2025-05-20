import { useEffect, useState } from 'react'
import './Control.css'
import Light from './Light/Light'
import Pump from './Pump/Pump'

function Control() {
    const [isActive, setIsActive] = useState(false);
    const [isLoading, setIsLoading] = useState(true);

    useEffect(()=>{
        fetch('https://dadn-242-backend.vercel.app/getSetting?Output_ID=L01').then((response) => { 
                if (!response.ok) {
                    throw new Error('Response was not ok');
                }
                return response.json();
            }).then((data) => {
                setIsActive(data.Mode === 'auto');
                setIsLoading(false);
            }).catch((e) => {
                console.error(e);
            }); 
    },[])

    const handleToggle = async () => {
        const newMode = isActive ? "manual" : "auto";
        setIsLoading(true);
        try {
            await fetch('https://dadn-242-backend.vercel.app/webAction/changeMode', {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ Mode: newMode })
            });
            setIsActive(!isActive);
        } catch (error) {
            console.error('Toggle error:', error);
        } finally {
            setIsLoading(false);
        }
    };

    return (
        <>
            <div class="ControlHeader">
                <h2>Control</h2>
            </div>
            <div class="auto-button">  
                <span>
                        Auto
                </span>
                <div className="toggle-switch-auto active">
                    
                    <input 
                        type="checkbox" 
                        id="auto-toggle" 
                        className="toggle-input-auto"
                        checked={isActive}
                        onChange={handleToggle}
                        disabled={isLoading}
                    />
                    <label htmlFor="auto-toggle" className="toggle-label-auto">
                        <span className="toggle-button-auto"></span>
                    </label>
                </div>
            </div>

            <div class="Grid">
                <Light/>
                <Pump/>
            </div>

        </>
    )
}

export default Control