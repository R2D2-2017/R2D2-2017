-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u2
-- http://www.phpmyadmin.net
--
-- Machine: localhost
-- Gegenereerd op: 24 mei 2017 om 08:58
-- Serverversie: 5.5.54-0+deb8u1
-- PHP-versie: 5.6.30-0+deb8u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Databank: `R2D2`
--

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `RFID`
--

CREATE TABLE IF NOT EXISTS `RFID` (
`ID` int(11) NOT NULL,
  `CARD_ID` text NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;

--
-- Gegevens worden geëxporteerd voor tabel `RFID`
--

INSERT INTO `RFID` (`ID`, `CARD_ID`) VALUES
(1, '[52,188,189,222,235]'),
(2, '[51,187,188,221,233]');

--
-- Indexen voor geëxporteerde tabellen
--

--
-- Indexen voor tabel `RFID`
--
ALTER TABLE `RFID`
 ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT voor geëxporteerde tabellen
--

--
-- AUTO_INCREMENT voor een tabel `RFID`
--
ALTER TABLE `RFID`
MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=5;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
