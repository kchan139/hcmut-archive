import "./Header.css";

function Header ({ pageTitle }) { // Accept pageTitle as a prop
    return (
        <>
            <div class="header">
                <div class="page-title">{pageTitle}</div>
                <div class="user-profile">
                    {/* <svg class="notification-icon" width="24" height="24" viewBox="0 0 24 24" fill="none">
                        <path d="M18 8A6 6 0 0 0 6 8c0 7-3 9-3 9h18s-3-2-3-9" stroke="#333" stroke-width="2" />
                        <path d="M13.73 21a2 2 0 0 1-3.46 0" stroke="#333" stroke-width="2" />
                    </svg> */}
                    <img src="https://i.pravatar.cc/100" alt="User" class="user-avatar"/>
                    {/* <svg class="dropdown-icon" width="12" height="12" viewBox="0 0 24 24" fill="none">
                        <path d="M6 9L12 15L18 9" stroke="#333" stroke-width="2" />
                    </svg> */}
                </div>
            </div>
        </>
    )
}

export default Header;