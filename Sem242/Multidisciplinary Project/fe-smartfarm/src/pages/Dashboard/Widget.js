import './Widget.css'
import Slider from './Slider';
import { useEffect, useState } from 'react';

function Widget({children, value, unit, lowest, highest, type}) {
    // eslint-disable-next-line
    const [width, setWidth] = useState("0%");
    useEffect(() => {
        const rate = (value - lowest)/(highest - lowest)*100;
        const widthRate = `${rate}%`;
        setWidth(widthRate);
    }, [value, lowest, highest])
    return (
        <>
            <div class={type}>
                <div class="metric-title">{children}</div>
                <div class="metric-value">{value}{unit}</div>
                <Slider lowest={lowest} highest={highest} value={value} unit={unit}></Slider>
            </div>
        </>
    )
}

export default Widget;