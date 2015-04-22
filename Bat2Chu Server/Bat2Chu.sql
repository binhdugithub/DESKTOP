-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Oct 17, 2014 at 11:03 AM
-- Server version: 5.5.38-0ubuntu0.14.04.1
-- PHP Version: 5.5.9-1ubuntu4.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `Bat2Chu`
--

-- --------------------------------------------------------

--
-- Table structure for table `Images`
--

CREATE TABLE IF NOT EXISTS `Images` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `en_result` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `vn_result` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `url` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `url` (`url`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=6 ;

--
-- Dumping data for table `Images`
--

INSERT INTO `Images` (`id`, `en_result`, `vn_result`, `url`) VALUES
(1, 'DaiGia', 'Đại Gia', 'DaiGia.jpg'),
(2, 'LyThong', 'Lý Thông', 'LyThong.jpg'),
(3, 'TamTinh', 'Tâm Tình', 'TamTinh.jpg'),
(4, 'TaoBon', 'Táo Bón', 'TaoBon.jpg'),
(5, 'AnTuong', 'Ấn Tượng', 'AnTuong.jpg');

-- --------------------------------------------------------

--
-- Table structure for table `Users`
--

CREATE TABLE IF NOT EXISTS `Users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `facebook` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `level` int(11) NOT NULL,
  `ruby` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_name` (`user_name`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1129 ;

--
-- Dumping data for table `Users`
--

INSERT INTO `Users` (`id`, `user_name`, `facebook`, `level`, `ruby`) VALUES
(1000, NULL, 'thatdaycoming@gmail.com', 5, 40),
(1068, NULL, NULL, 6, 120),
(1069, NULL, NULL, 0, 0),
(1070, NULL, NULL, 6, 120),
(1071, NULL, NULL, 6, 120),
(1072, NULL, NULL, 4, 80),
(1073, NULL, NULL, 1, 20),
(1074, NULL, NULL, 1, 20),
(1075, NULL, NULL, 1, 20),
(1076, NULL, NULL, 1, 20),
(1077, NULL, NULL, 1, 20),
(1078, NULL, NULL, 1, 20),
(1079, NULL, NULL, 1, 20),
(1080, NULL, NULL, 1, 20),
(1081, NULL, NULL, 2, 40),
(1082, NULL, NULL, 2, 40),
(1083, NULL, NULL, 0, 0),
(1084, NULL, NULL, 6, 120),
(1085, NULL, NULL, 2, 40),
(1086, NULL, NULL, 1, 20),
(1087, NULL, NULL, 1, 20),
(1088, NULL, NULL, 1, 20),
(1089, NULL, NULL, 1, 20),
(1090, NULL, NULL, 2, 40),
(1091, NULL, NULL, 4, 80),
(1092, NULL, NULL, 1, 20),
(1093, NULL, NULL, 2, 40),
(1094, NULL, NULL, 4, 80),
(1095, NULL, NULL, 1, 20),
(1096, NULL, NULL, 3, 60),
(1097, NULL, NULL, 1, 20),
(1098, NULL, NULL, 6, 120),
(1099, NULL, NULL, 2, 40),
(1100, NULL, NULL, 1, 20),
(1101, NULL, NULL, 2, 40),
(1102, NULL, NULL, 2, 40),
(1103, NULL, NULL, 1, 20),
(1104, NULL, NULL, 1, 20),
(1105, NULL, NULL, 1, 20),
(1106, NULL, NULL, 2, 40),
(1107, NULL, NULL, 1, 20),
(1108, NULL, NULL, 1, 20),
(1109, NULL, NULL, 3, 60),
(1110, NULL, NULL, 3, 60),
(1111, NULL, NULL, 20, 400),
(1112, NULL, NULL, 1, 20),
(1113, NULL, NULL, 3, 60),
(1114, NULL, NULL, 1, 20),
(1115, NULL, NULL, 1, 20),
(1116, NULL, NULL, 1, 20),
(1117, NULL, NULL, 1, 20),
(1118, NULL, NULL, 1, 20),
(1119, NULL, NULL, 1, 20),
(1120, NULL, NULL, 1, 20),
(1121, NULL, NULL, 2, 40),
(1122, NULL, NULL, 6, 120),
(1123, NULL, NULL, 11, 220),
(1124, NULL, NULL, 23, 460),
(1125, NULL, NULL, 2, 40),
(1126, NULL, NULL, 3, 60),
(1127, NULL, NULL, 5, 100),
(1128, NULL, NULL, 2, 40);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
