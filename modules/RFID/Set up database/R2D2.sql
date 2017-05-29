-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 29, 2017 at 03:01 PM
-- Server version: 5.5.54-0+deb8u1
-- PHP Version: 5.6.30-0+deb8u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `R2D2`
--

-- --------------------------------------------------------

--
-- Table structure for table `EMPLOYEE`
--

CREATE TABLE IF NOT EXISTS `EMPLOYEE` (
  `ID` int(11) NOT NULL,
  `NAAM` text NOT NULL,
  `FUNCTIE` text NOT NULL,
  `ADRESS` text NOT NULL,
  `POSTALCODE` text NOT NULL,
  `STREET` text NOT NULL,
  `CITY` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `RFID`
--

CREATE TABLE IF NOT EXISTS `RFID` (
`ID` int(11) NOT NULL,
  `CARD_ID` text NOT NULL,
  `AUTHORIZED` tinyint(1) NOT NULL DEFAULT '1'
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `RFID`
--

INSERT INTO `RFID` (`ID`, `CARD_ID`, `AUTHORIZED`) VALUES
(5, '[51,187,188,221,233]', 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `EMPLOYEE`
--
ALTER TABLE `EMPLOYEE`
 ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `RFID`
--
ALTER TABLE `RFID`
 ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `RFID`
--
ALTER TABLE `RFID`
MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=6;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
