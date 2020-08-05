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
-- Table structure for table `employees_salary`
--

DROP TABLE IF EXISTS `employees_salary`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `employees_salary` (
  `employee_id` int NOT NULL,
  `year` int NOT NULL COMMENT '2008-01-01',
  `month` int NOT NULL,
  `hours_monthly` int NOT NULL,
  KEY `employee_id` (`employee_id`),
  CONSTRAINT `employees_salary_ibfk_1` FOREIGN KEY (`employee_id`) REFERENCES `employees_details` (`employee_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employees_salary`
--

LOCK TABLES `employees_salary` WRITE;
/*!40000 ALTER TABLE `employees_salary` DISABLE KEYS */;
INSERT INTO `employees_salary` VALUES (4,2019,10,60),(4,2019,11,30),(4,2019,12,40),(4,2020,1,80),(4,2020,2,70),(4,2020,3,50),(4,2020,4,60),(4,2020,5,40),(4,2020,6,90),(5,2019,10,40),(5,2019,11,30),(5,2019,12,40),(5,2020,1,70),(5,2020,2,20),(5,2020,3,50),(5,2020,4,30),(5,2020,5,40),(5,2020,6,80),(7,2019,10,80),(7,2019,11,40),(7,2019,12,20),(7,2020,1,90),(7,2020,2,60),(7,2020,3,40),(7,2020,4,30),(7,2020,5,60),(7,2020,6,70),(9,2019,10,50),(9,2019,11,30),(9,2019,12,70),(9,2020,1,90),(9,2020,2,70),(9,2020,3,90),(9,2020,4,80),(9,2020,5,50),(9,2020,6,90),(1,2010,1,80),(1,2009,12,50),(1,2009,11,30),(2,2008,2,30),(2,2008,1,70),(2,2007,12,90),(3,2014,1,30),(3,2013,12,40),(3,2013,11,50),(6,2014,1,50),(6,2013,12,50),(6,2013,11,50),(8,2011,11,30),(8,2011,10,20),(8,2011,9,30),(11,2019,1,30),(11,2018,12,10),(11,2018,11,30);
/*!40000 ALTER TABLE `employees_salary` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-08-05 14:39:42
