import PropTypes from "prop-types";
import React from "react";
import LogoImage from "./01_logobachkhoatoi 2.svg";
import "./logo.css";

export const Logo = ({ property1, className }) => {
    return (
        <div className={`logo ${className}`}>
            <div className="frame">
                <img
                    className="element-logobachkhoatoi"
                    alt="Element logobachkhoatoi"
                    src={LogoImage}
                />

                <div className="text-wrapper">SSPS</div>
            </div>
        </div>
    );
};

Logo.propTypes = {
    property1: PropTypes.oneOf(["default"]),
};
