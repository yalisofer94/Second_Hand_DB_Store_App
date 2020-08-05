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
-- Table structure for table `books_details`
--

DROP TABLE IF EXISTS `books_details`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `books_details` (
  `book_id` int NOT NULL AUTO_INCREMENT,
  `title` varchar(45) NOT NULL,
  `interpreter` varchar(45) DEFAULT NULL,
  `publisher` varchar(45) NOT NULL,
  `publishing_year` varchar(45) NOT NULL,
  `pages` int NOT NULL,
  `weight` int NOT NULL,
  `condition` enum('new','as new','good','fair','poor') NOT NULL,
  PRIMARY KEY (`book_id`)
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `books_details`
--

LOCK TABLES `books_details` WRITE;
/*!40000 ALTER TABLE `books_details` DISABLE KEYS */;
INSERT INTO `books_details` VALUES (1,'The Doom',NULL,'Sterling','2008',120,2,'good'),(2,'In Search of Lost Time',NULL,'Penguin Random House','1913',300,2,'new'),(3,'Ulysses','arik levy','HarperCollins','1904',220,1,'as new'),(4,'Don Quixote',NULL,'Penguin Random House','2000',80,1,'good'),(5,'The Great Gatsby','shlomo zeev','Simon & Schuster','1980',600,6,'fair'),(6,'One Hundred Years of Solitude',NULL,'	Hachette Book Group','1927',352,3,'poor'),(7,'Moby Dick',NULL,'Workman','1950',124,2,'as new'),(8,'In Search of Lost Time',NULL,'Penguin Random House','1913',300,2,'new'),(9,'War and Peace','fred boyer','Penguin Random House','1923',726,5,'as new'),(10,'Lolita','tom aharon','HarperCollins','1977',427,4,'new'),(11,'Hamlet','yoni rom','Hachette Book Group','1599',144,2,'fair'),(12,'The Odyssey',NULL,'Kensington','1883',219,3,'poor'),(13,'Crime and Punishment','hen manor','Sterling','1492',485,5,'good'),(14,'Pride and Prejudice','lior dor','Simon & Schuster','2004',828,8,'fair'),(15,'Catch-22',NULL,'Penguin Random House','1943',444,4,'new'),(16,'The Stranger','dor ariel','HarperCollins','1946',70,2,'new'),(17,'The Great Gatsby','zohar yefet','Sterling','1980',600,6,'new'),(18,'In Search of Lost Time','guy orpaz','Workman','1913',300,2,'poor');
/*!40000 ALTER TABLE `books_details` ENABLE KEYS */;
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
