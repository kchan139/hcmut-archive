import React from "react";
import PropTypes from "prop-types";
import { Logo } from "../Logo/Logo";
import "./Footer.css";

export const Footer = ({ className }) => {
    return (
        <footer className={`footer ${className}`}>
            <div className="content">
                {/* Pane Left */}
                <div className="pane-left">
                    <Logo className="footer-logo" />

                    <div className="frame-7">
                        <p className="footer-text">© Dự án SSPS 2024. Bản quyền thuộc về nhóm CC02-07.</p>
                        <p className="footer-text">
                            Quyền riêng tư — Điều khoản sử dụng
                        </p>
                        <div className="frame-icon">
                            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 16 16" fill="none">
                                <g clip-path="url(#clip0_561_584)">
                                    <path d="M6.00004 12.6668C2.66671 13.6668 2.66671 11.0001 1.33337 10.6668M10.6667 14.6668V12.0868C10.6917 11.7689 10.6488 11.4493 10.5407 11.1493C10.4327 10.8493 10.262 10.5757 10.04 10.3468C12.1334 10.1135 14.3334 9.32012 14.3334 5.68012C14.3332 4.74934 13.9752 3.85425 13.3334 3.18012C13.6373 2.36579 13.6158 1.46569 13.2734 0.666788C13.2734 0.666788 12.4867 0.433455 10.6667 1.65345C9.13871 1.23934 7.52803 1.23934 6.00004 1.65345C4.18004 0.433455 3.39337 0.666788 3.39337 0.666788C3.05096 1.46569 3.02947 2.36579 3.33337 3.18012C2.68679 3.85925 2.32839 4.76243 2.33337 5.70012C2.33337 9.31345 4.53337 10.1068 6.62671 10.3668C6.40737 10.5934 6.23822 10.8637 6.13025 11.1601C6.02228 11.4564 5.97791 11.7722 6.00004 12.0868V14.6668" stroke="#1E1E1E" stroke-width="1.6" stroke-linecap="round" stroke-linejoin="round"/>
                                </g>
                                <defs>
                                    <clipPath id="clip0_561_584">
                                    <rect width="16" height="16" fill="white"/>
                                    </clipPath>
                                </defs>
                            </svg>
                            <p className="footer-text">GitHub</p>
                        </div>
                    </div>
                </div>

                {/* Pane Right */}
                <div className="pane-right">
                    {/* First Box Links */}
                    <div className="box-links">
                        <div className="header-links">
                            <h4 className="sub-title">Thông tin</h4>
                        </div>
                        <div className="body-links-left">
                            <p className="link">Trường Đại học Bách khoa - ĐHQG TP.HCM</p>
                            <p className="link">Công nghệ phần mềm - CO3001 - HK241</p>
                            <p className="link">GVHD: Trương Thị Thái Minh</p>
                        </div>
                    </div>

                    {/* Second Box Links */}
                    <div className="box-links">
                        <div className="header-links">
                            <h4 className="sub-title">Liên hệ</h4>
                        </div>
                        <div className="body-links-right">
                            <p className="link">268 Lý Thường Kiệt, phường 14, quận 10, TP.HCM</p>
                            <div className="frame-icon">
                                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 16 16" fill="none">
                                <g clip-path="url(#clip0_561_601)">
                                    <path d="M14.6666 11.28V13.28C14.6674 13.4657 14.6294 13.6494 14.555 13.8195C14.4806 13.9897 14.3715 14.1424 14.2347 14.2679C14.0979 14.3934 13.9364 14.489 13.7605 14.5485C13.5846 14.6079 13.3982 14.63 13.2133 14.6133C11.1619 14.3904 9.19131 13.6894 7.45998 12.5667C5.84919 11.5431 4.48353 10.1774 3.45998 8.56665C2.33329 6.82745 1.63214 4.84731 1.41331 2.78665C1.39665 2.60229 1.41856 2.41649 1.47764 2.24107C1.53673 2.06564 1.63169 1.90444 1.75649 1.76773C1.88128 1.63102 2.03318 1.52179 2.2025 1.447C2.37183 1.37221 2.55487 1.33349 2.73998 1.33332H4.73998C5.06351 1.33013 5.37717 1.4447 5.62248 1.65567C5.8678 1.86664 6.02803 2.15961 6.07331 2.47998C6.15772 3.12003 6.31428 3.74847 6.53998 4.35332C6.62967 4.59193 6.64908 4.85126 6.59591 5.10057C6.54274 5.34988 6.41922 5.57872 6.23998 5.75998L5.39331 6.60665C6.34235 8.27568 7.72428 9.65761 9.39331 10.6066L10.24 9.75998C10.4212 9.58074 10.6501 9.45722 10.8994 9.40405C11.1487 9.35088 11.408 9.37029 11.6466 9.45998C12.2515 9.68568 12.8799 9.84224 13.52 9.92665C13.8438 9.97234 14.1396 10.1355 14.351 10.385C14.5624 10.6345 14.6748 10.953 14.6666 11.28Z" stroke="#1E1E1E" stroke-width="1.6" stroke-linecap="round" stroke-linejoin="round"/>
                                </g>
                                <defs>
                                    <clipPath id="clip0_561_601">
                                    <rect width="16" height="16" fill="white"/>
                                    </clipPath>
                                </defs>
                                </svg>
                                <p className="footer-text">*insert fake phone number*</p>
                            </div>
                            <div className="frame-icon">
                                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 16 16" fill="none">
                                    <path d="M14.6666 4.00008C14.6666 3.26675 14.0666 2.66675 13.3333 2.66675H2.66665C1.93331 2.66675 1.33331 3.26675 1.33331 4.00008M14.6666 4.00008V12.0001C14.6666 12.7334 14.0666 13.3334 13.3333 13.3334H2.66665C1.93331 13.3334 1.33331 12.7334 1.33331 12.0001V4.00008M14.6666 4.00008L7.99998 8.66675L1.33331 4.00008" stroke="#1E1E1E" stroke-width="1.6" stroke-linecap="round" stroke-linejoin="round"/>
                                </svg>
                                <p className="footer-text">ssps.241@hcmut.edu.vn</p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </footer>
    );
};

Footer.propTypes = {
    className: PropTypes.string,
};
