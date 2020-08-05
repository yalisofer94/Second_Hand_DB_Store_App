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
-- Table structure for table `order_details`
--

DROP TABLE IF EXISTS `order_details`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `order_details` (
  `order_id` int NOT NULL,
  `book_id` int NOT NULL,
  `total_amount` int NOT NULL,
  `shipping_address` varchar(45) NOT NULL,
  KEY `book_id` (`book_id`),
  KEY `order_id` (`order_id`),
  CONSTRAINT `order_details_ibfk_1` FOREIGN KEY (`book_id`) REFERENCES `books_details` (`book_id`),
  CONSTRAINT `order_details_ibfk_2` FOREIGN KEY (`order_id`) REFERENCES `orders` (`order_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `order_details`
--

LOCK TABLES `order_details` WRITE;
/*!40000 ALTER TABLE `order_details` DISABLE KEYS */;
INSERT INTO `order_details` VALUES (1,3,4,'Yael 7 Tel Aviv'),(2,4,2,'Katz 37 Ramat Gan'),(3,1,1,'Noya 63 Kfat Sabba'),(4,6,1,'Yarkon 10 Tel Afek'),(5,8,7,'Hagefen 137 Raanna'),(6,3,8,'Pinchas 19 Tel Aviv'),(7,9,2,'Gur 64 Nahariyya'),(8,5,1,'Tufin 29 Beer Sheva'),(9,11,5,'Frug 26 Tel Aviv'),(10,12,2,'Begin 5 Bat Yam'),(11,13,1,'Halutzim 13 Bnei Brak'),(12,2,2,'Doron 22 Reut'),(13,18,1,'Amnon 122 Maccabim'),(15,4,1,'Drorit 231 Shlomi'),(16,4,1,'Fogel 12 Arad'),(17,4,1,'Haon 18 Dimona'),(18,7,1,'Alonim 56 Jaffa'),(19,8,1,'Knaan 132 Tel Aviv'),(20,2,1,'Farid 121 Ramat Gan'),(21,9,1,'Harif 12 Eilat'),(22,10,1,'HaOren 221 Raanana'),(23,12,1,'Poalim 90 Beer Sheva'),(24,14,1,'Levanon 12 Yerucham'),(16,3,1,'Fogel 12 Arad'),(14,3,1,'Arizona 17 Bnei Brak'),(14,4,1,'Arizona 17 Bnei Brak'),(22,5,1,'HaOren 221 Raanana'),(12,5,1,'Doron 22 Reut'),(13,2,1,'Amnon 122 Maccabim');
/*!40000 ALTER TABLE `order_details` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-08-05 14:39:39
