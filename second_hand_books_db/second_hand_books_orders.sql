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
-- Table structure for table `orders`
--

DROP TABLE IF EXISTS `orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `orders` (
  `order_id` int NOT NULL AUTO_INCREMENT,
  `customer_id` int NOT NULL,
  `order_date` date NOT NULL,
  `payment_method` int NOT NULL,
  `shipping_method` int NOT NULL,
  `shipping_status` enum('Preparing for shipping','Sent','Arrived and wait for pick up','Collected','Pendding') NOT NULL,
  `order_status` enum('Contacted client 14 days ago or more') DEFAULT NULL,
  PRIMARY KEY (`order_id`),
  KEY `customer_id` (`customer_id`),
  KEY `shipping_method` (`shipping_method`),
  KEY `payment_method` (`payment_method`),
  CONSTRAINT `orders_ibfk_2` FOREIGN KEY (`shipping_method`) REFERENCES `shipping_types` (`shipping_type_id`),
  CONSTRAINT `orders_ibfk_3` FOREIGN KEY (`customer_id`) REFERENCES `customers` (`customer_id`),
  CONSTRAINT `orders_ibfk_4` FOREIGN KEY (`payment_method`) REFERENCES `payment_method` (`payment_method_id`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders`
--

LOCK TABLES `orders` WRITE;
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;
INSERT INTO `orders` VALUES (1,1,'2020-03-05',2,4,'Collected',NULL),(2,1,'2020-07-25',1,1,'Preparing for shipping',NULL),(3,2,'2019-07-21',2,2,'Collected',NULL),(4,3,'2020-07-05',3,3,'Arrived and wait for pick up',NULL),(5,4,'2020-07-19',3,3,'Arrived and wait for pick up',NULL),(6,5,'2020-06-25',1,2,'Sent',NULL),(7,5,'2019-12-25',1,4,'Collected',NULL),(8,6,'2020-05-05',3,5,'Sent',NULL),(9,7,'2020-07-27',3,1,'Preparing for shipping',NULL),(10,8,'2020-06-21',2,5,'Sent',NULL),(11,8,'2020-06-21',1,4,'Sent',NULL),(12,9,'2019-02-10',1,3,'Collected',NULL),(13,9,'2019-02-10',2,3,'Collected',NULL),(14,1,'2020-07-01',1,4,'Pendding','Contacted client 14 days ago or more'),(15,2,'2020-06-14',2,1,'Pendding','Contacted client 14 days ago or more'),(16,5,'2019-01-09',2,3,'Collected',NULL),(17,8,'2019-03-20',3,2,'Collected',NULL),(18,3,'2019-04-17',2,4,'Collected',NULL),(19,11,'2019-05-13',2,1,'Collected',NULL),(20,5,'2019-06-14',1,2,'Collected',NULL),(21,8,'2019-08-19',2,3,'Collected',NULL),(22,10,'2019-09-11',3,4,'Collected',NULL),(23,4,'2019-10-10',2,3,'Collected',NULL),(24,7,'2019-11-08',3,1,'Collected',NULL);
/*!40000 ALTER TABLE `orders` ENABLE KEYS */;
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
