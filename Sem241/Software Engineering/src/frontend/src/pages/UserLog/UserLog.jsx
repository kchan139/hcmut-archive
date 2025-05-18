import React, { useState, useEffect } from "react";
import { Navbar } from "../../components/Navbar/Navbar";
import { Footer } from "../../components/Footer/Footer";
import BackgroundSVG from "../../assets/background.svg";
import axios from "axios";
import "./userLog.css";
import {
    Pagination,
    PaginationPrevious,
    PaginationNext,
    PaginationList,
    PaginationPage,
    PaginationGap,
} from "primitives";
import { IconSearch } from "icons";
import { Button } from "primitives";
import { IconChevronDown, IconChevronUp, IconCopy, IconTrash2, IconEdit2 } from "icons";

function UserLog() {
    const [currentPage, setCurrentPage] = useState(1);
    const [records, setRecords] = useState([])
    const [searchQuery, setSearchQuery] = useState("");
    const print_info = JSON.parse(localStorage.getItem('print_info'))
    useEffect(() => {
        axios
            .get(`http://127.0.0.1:5000/api/records/${print_info.MSSV}`)
            .then((response) => {
                setRecords(response.data);
            })
            .catch((error) => {
                console.error("Error fetching records:", error);
                setRecords([]); // Clear previous records
            });
      }, []);
      
    const recordsPerPage = 2;
    const filteredRecords = records.filter(
        (record) =>
          record.printer.toLowerCase().includes(searchQuery.toLowerCase()) ||
          record.date.toLowerCase().includes(searchQuery.toLowerCase()) || 
          record.status.toLowerCase().includes(searchQuery.toLowerCase())
      );

    const indexOfLastRecord = currentPage * recordsPerPage;
    const indexOfFirstRecord = indexOfLastRecord - recordsPerPage;
    const currentRecords = filteredRecords.slice(indexOfFirstRecord, indexOfLastRecord);

    const totalPages = Math.ceil(filteredRecords.length / recordsPerPage);
    const handlePageChange = (page) => { setCurrentPage(page); };
    const generatePagination = () => {
        const paginationItems = [];
        const visibleRange = 2; // Number of pages around the current page

        // Always include the first page
        paginationItems.push(
            <PaginationPage
                key={1}
                href="#"
                current={currentPage === 1}
                onPress={() => handlePageChange(1)}
            >1</PaginationPage>
        );

        // Add gap if the range from the first page is too large
        if (currentPage - visibleRange > 2) {
        paginationItems.push(<PaginationGap key="gap-start" />);
        }

        // Add pages around the current page
        for (
            let page = Math.max(2, currentPage - visibleRange);
            page <= Math.min(totalPages - 1, currentPage + visibleRange);
            page++
        ){
            paginationItems.push(
                <PaginationPage
                key={page}
                href="#"
                current={currentPage === page}
                onPress={() => handlePageChange(page)}
                >{page}</PaginationPage>
            );
        }

        // Add gap if the range to the last page is too large
        if (currentPage + visibleRange < totalPages - 1) {
            paginationItems.push(<PaginationGap key="gap-end" />);
        }

        // Always include the last page
        if (totalPages > 1) {
        paginationItems.push(
            <PaginationPage
                key={totalPages}
                href="#"
                current={currentPage === totalPages}
                onPress={() => handlePageChange(totalPages)}
            >{totalPages}</PaginationPage>
        )};

        return paginationItems;
    };

    const [expandedRows, setExpandedRows] = useState([]);

    const toggleRow = (index) => {
        if (expandedRows.includes(index)) {
            // If row is already expanded, collapse it
            setExpandedRows(expandedRows.filter((i) => i !== index));
        } else {
            // Expand the row
            setExpandedRows([...expandedRows, index]);
        }
    };

  const handleSearchChange = (e) => {
    setSearchQuery(e.target.value);
    setCurrentPage(1);
  };

    return (
        <div>
            <Navbar property="Registered User" />
            <div
                style={{
                    backgroundImage: `url(${BackgroundSVG})`,
                    backgroundSize: "cover",
                    backgroundRepeat: "no-repeat",
                    backgroundPosition: "center",
                    width: "100%",
                    height: "100vh",
                    display: "flex",
                    justifyContent: "center",
                    alignItems: "center",
                }}>
                <div className="container_UserLog">
                <div className="input-wrapper_UserLog">
                    <IconSearch className="icon-search_UserLog icon-black" />
                    <input className="searchBar_UserLog" placeholder="Tìm kiếm..." value={searchQuery} onChange={handleSearchChange} style={{color:"black"}}/>
                </div>
                <table className="custom-table">
                    <thead>
                    <tr>
                        <th>
                        <Button onPress={() => alert("Máy in clicked")} variant="neutral" className="buttonTable_UserLog ">
                            Máy in<IconChevronDown />
                        </Button>
                        </th>
                        <th>
                        <Button onPress={() => alert("Ngày in clicked")} variant="neutral" className="buttonTable_UserLog">
                            Ngày in<IconChevronDown />
                        </Button>
                        </th>
                        <th>
                        <Button onPress={() => alert("Trạng thái clicked")} variant="neutral" className="buttonTable_UserLog">
                            Trạng thái<IconChevronDown />
                        </Button>
                        </th>
                        <th>
                        <Button variant="neutral" className="buttonTable_UserLog">
                            Chi tiết
                        </Button>
                        </th>
                    </tr>
                    </thead>
                    <tbody>
                    {currentRecords.map((record, index) => (
                        <React.Fragment key={index}>
                            {/* Main row */}
                            <tr>
                                <td>{record.printer}</td>
                                <td>{record.date}</td>
                                <td>{record.status}</td>
                                <td>
                                    <Button
                                        onPress={() => toggleRow(index)}
                                        variant="neutral"
                                        className="buttonTable_UserLog"
                                    >
                                        {expandedRows.includes(index) ? (
                                            <IconChevronUp />
                                        ) : (
                                            <IconChevronDown />
                                        )}
                                    </Button>
                                </td>
                            </tr>

                            {/* Dropdown row */}
                            {expandedRows.includes(index) && (
                                <tr className="dropdown-row">
                                    <td colSpan="4">
                                        <div className="dropdown-content">
                                            <p><strong>Tên file:</strong> {record.file_name}</p>
                                            <p><strong>Phần mở rộng file:</strong> {record.file_ext}</p>
                                            <p><strong>Kích thước file:</strong> {(record.file_size / (1024 * 1024)).toFixed(2)} MB</p>
                                            <p><strong>Số trang:</strong> {record.page_num}</p>
                                        </div>
                                    </td>
                                </tr>
                            )}
                        </React.Fragment>
                    ))}
                    </tbody>
                </table>
                <Pagination style={{ justifyContent: "center" }}>
                    <PaginationList>
                    <PaginationPrevious href="#" onPress={() => handlePageChange(Math.max(1, currentPage - 1))}>
                        Trước
                    </PaginationPrevious>
                    {generatePagination()}
                    <PaginationNext href="#" onPress={() => handlePageChange(Math.min(totalPages, currentPage + 1))}>
                        Tiếp theo
                    </PaginationNext>
                    </PaginationList>
                </Pagination>
                </div>
            </div>
            <Footer />
        </div>
    );
}

export default UserLog;