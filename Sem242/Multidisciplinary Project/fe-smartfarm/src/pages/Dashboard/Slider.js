import './Slider.css'
import { useRef, useState } from 'react';

function Slider({ lowest, highest, value, unit, onChange = () => {}, onRelease = () => {}, disabled = false, step = 1 }) {
    const sliderRef = useRef(null);
    const [isDragging, setIsDragging] = useState(false);

    // Helper function rounds number to nearest multiple of step
    const roundToStep = (num) => {
        return Math.round(num / step) * step;
    };

    const handleMouseDown = () => {
        if (disabled) return;
        setIsDragging(true);
    };

    const handleMouseMove = (e) => {
        if (disabled || !isDragging || !sliderRef.current) return;
        const rect = sliderRef.current.getBoundingClientRect();
        let percent = (e.clientX - rect.left) / rect.width;
        percent = Math.min(Math.max(percent, 0), 1);
        const newValueUnrounded = percent * (highest - lowest) + lowest;
        const newValue = roundToStep(newValueUnrounded);
        onChange(newValue);
    };

    const handleMouseUp = () => {
        setIsDragging(false);
        onRelease(value);
    };

    const handleTouchStart = (e) => {
        if (disabled) return;
        setIsDragging(true);
    };

    const handleTouchMove = (e) => {
        if (disabled || !isDragging || !sliderRef.current) return;
        const touch = e.touches[0];
        const rect = sliderRef.current.getBoundingClientRect();
        let percent = (touch.clientX - rect.left) / rect.width;
        percent = Math.min(Math.max(percent, 0), 1);
        const newValueUnrounded = percent * (highest - lowest) + lowest;
        const newValue = roundToStep(newValueUnrounded);
        onChange(newValue);
    };

    const handleTouchEnd = () => {
        setIsDragging(false);
        onRelease(value);
    };

    const percentage = ((value - lowest) / (highest - lowest)) * 100 + '%';

    return (
        <div
            className={`slider-container status-slider ${disabled ? 'disabled' : ''}`}
            onMouseMove={handleMouseMove}
            onMouseUp={handleMouseUp}
            onMouseLeave={handleMouseUp}
            onTouchMove={handleTouchMove}
            onTouchEnd={handleTouchEnd}
            ref={sliderRef}
        >
            <div className="slider" onMouseDown={handleMouseDown} onTouchStart={handleTouchStart}>
                <div className="slider-fill" style={{ width: percentage }}></div>
                <div className="slider-thumb" style={{ left: percentage }}></div>
            </div>
            <div className="slider-ticks">
                {[...Array(6)].map((_, i) => <div className="tick" key={i}></div>)}
            </div>
            <div className="slider-labels">
                <span>{lowest} {unit}</span>
                <span>{highest} {unit}</span>
            </div>
        </div>
    );
}

export default Slider;
