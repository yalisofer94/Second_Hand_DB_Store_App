-- MySQL dump 10.13  Distrib 8.0.19, for Win64 (x86_64)
--
-- Host: localhost    Database: second_hand_books
-- ------------------------------------------------------
-- Server version	8.0.19

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `employees_details`
--

DROP TABLE IF EXISTS `employees_details`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `employees_details` (
  `employee_id` int NOT NULL AUTO_INCREMENT,
  `employee_first_name` varchar(45) NOT NULL,
  `employee_last_name` varchar(45) NOT NULL,
  `employee_address` varchar(45) NOT NULL,
  `employee_phone` varchar(45) NOT NULL,
  `join_date` date NOT NULL,
  `leaving_date` date DEFAULT NULL,
  PRIMARY KEY (`employee_id`)
) ENGINE=InnoDB AUTO_INCREMENT=37 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employees_details`
--

LOCK TABLES `employees_details` WRITE;
/*!40000 ALTER TABLE `employees_details` DISABLE KEYS */;
INSERT INTO `employees_details` VALUES (1,'Ravit','Shir','Hapaamon 5 Haifa','0529918811','2006-03-20','2010-01-11'),(2,'Miki','Even','Yarden 15 Tel Aviv','0529333331','2002-04-10','2008-02-14'),(3,'Mirna','Evron','Dganit 23 Raanana','0532953868','2012-11-20','2014-01-22'),(4,'Amit','David','Lenon 12 Haifa','0507716842','2014-12-20',NULL),(5,'Shaul','Snir','Chen 8 Dimona','0529714523','2004-03-20',NULL),(6,'Roy','Heler','Sofit 29 Yerucham','0521298310','2018-01-20','2020-01-14'),(7,'Shir','Hoff','Danit 77 Arad','0541210926','2006-09-29',NULL),(8,'Or','Nisan','Yam 21 Haifa','0548915263','2006-03-20','2011-11-11'),(9,'Idan','Gefen','Gilad 31 Ramat Gan','0541345363','2010-06-20',NULL),(10,'Natan','Nave','Dovnov 122 Tel Aviv','0522290765','2017-03-20','2019-01-18'),(11,'Sagi','Levi','Noach 51 Rehovot','0547729184','2001-03-20','2006-03-19');
/*!40000 ALTER TABLE `employees_details` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-08-05 14:39:41
