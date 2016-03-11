-- MySQL dump 10.13  Distrib 5.5.32, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: dnf
-- ------------------------------------------------------
-- Server version	5.5.32-0ubuntu7

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE IF NOT EXISTS`dnf` DEFAULT CHARACTER SET utf8;
USE `dnf`;

CREATE DATABASE IF NOT EXISTS`dnf` DEFAULT CHARACTER SET utf8;
USE `dnf`;

--
-- Table structure for table `t_card_exchange`
--

DROP TABLE IF EXISTS `t_card_exchange`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_card_exchange` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(32) DEFAULT NULL,
  `card_id` int(11) DEFAULT NULL,
  `needCard_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_card_exchange`
--

LOCK TABLES `t_card_exchange` WRITE;
/*!40000 ALTER TABLE `t_card_exchange` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_card_exchange` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t_temp`
--

DROP TABLE IF EXISTS `t_temp`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_temp` (
  `user_id` int(11) NOT NULL,
  `user_card` blob
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_temp`
--

LOCK TABLES `t_temp` WRITE;
/*!40000 ALTER TABLE `t_temp` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_temp` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t_user`
--

DROP TABLE IF EXISTS `t_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_user` (
  `user_id` int(11) NOT NULL,
  `user_pwd` varchar(64) DEFAULT '111111',
  `user_nickname` varchar(64) DEFAULT NULL,
  `league_id` int(11) DEFAULT '1',
  `league_name` varchar(64) DEFAULT 'default',
  `user_win` int(11) DEFAULT '0',
  `user_lose` int(11) DEFAULT '0',
  `face_id` int(3) DEFAULT '1',
  `user_money` int(11) DEFAULT '0',
  `user_score` int(11) DEFAULT '0',
  `user_rank` int(11) DEFAULT '0',
  `user_rewardscore` int(11) NOT NULL DEFAULT '0',
  `user_flag` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_user`
--

LOCK TABLES `t_user` WRITE;
/*!40000 ALTER TABLE `t_user` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t_user_all_card`
--

DROP TABLE IF EXISTS `t_user_all_card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_user_all_card` (
  `user_id` int(11) NOT NULL,
  `user_card` blob,
  PRIMARY KEY (`user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_user_all_card`
--

LOCK TABLES `t_user_all_card` WRITE;
/*!40000 ALTER TABLE `t_user_all_card` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_user_all_card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t_user_award`
--

DROP TABLE IF EXISTS `t_user_award`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_user_award` (
  `award_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `award_status` int(1) NOT NULL COMMENT '1-ø…“‘∂“ªª£¨0-“—æ≠∂“ªª',
  `create_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '≤˙…˙∂“ªªµƒ ±º‰',
  `award_time` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT '∂“ªªµƒ ±º‰',
  PRIMARY KEY (`award_id`)
) ENGINE=MyISAM AUTO_INCREMENT=5106 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_user_award`
--

LOCK TABLES `t_user_award` WRITE;
/*!40000 ALTER TABLE `t_user_award` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_user_award` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t_user_card`
--

DROP TABLE IF EXISTS `t_user_card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_user_card` (
  `user_id` int(11) NOT NULL,
  `hero_id` int(5) DEFAULT NULL,
  `user_card` blob,
  `active_status` int(11) DEFAULT NULL,
  `card_id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`user_id`,`card_id`),
  KEY `card_id` (`card_id`)
) ENGINE=MyISAM AUTO_INCREMENT=33 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_user_card`
--

LOCK TABLES `t_user_card` WRITE;
/*!40000 ALTER TABLE `t_user_card` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_user_card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t_user_hero_config`
--

DROP TABLE IF EXISTS `t_user_hero_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_user_hero_config` (
  `hero_id` int(11) DEFAULT NULL,
  `hero_cards` blob,
  `all_cards` blob
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_user_hero_config`
--

LOCK TABLES `t_user_hero_config` WRITE;
/*!40000 ALTER TABLE `t_user_hero_config` DISABLE KEYS */;
INSERT INTO `t_user_hero_config` VALUES (101,'i\0\0i\0\0i\0\0h\0\0h\0\0h\0\0g\0\0g\0\0g\0\0f\0\0f\0\0f\0\0e\0\0e\0\0e\0\0d\0\0d\0\0d\0\0c\0\0c\0\0c\0\0b\0\0b\0\0b\0\0a\0\0a\0\0a\0\0\\\0\0\\\0\0\\\0\0','?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0ˇ\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0	\0\0\n\0\0\0\0\0\0\r\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\Z\0\0\0\0\0\0\0\0\0\0\0\0 \0\0!\0\0\"\0\0#\0\0$\0\0%\0\0&\0\0\'\0\0(\0\0)\0\0*\0\0+\0\0,\0\0-\0\0.\0\0/\0\00\0\01\0\02\0\03\0\04\0\05\0\06\0\07\0\08\0\09\0\0:\0\0;\0\0<\0\0=\0\0>\0\0?\0\0@\0\0A\0\0B\0\0C\0\0D\0\0E\0\0F\0\0G\0\0H\0\0I\0\0J\0\0K\0\0L\0\0M\0\0N\0\0O\0\0P\0\0Q\0\0R\0\0S\0\0T\0\0U\0\0V\0\0W\0\0X\0\0Y\0\0Z\0\0[\0\0\\\0]\0\0^\0\0_\0\0`\0\0a\0b\0c\0d\0e\0f\0g\0h\0i\0'),(102,'i\0\0i\0\0i\0\0h\0\0h\0\0h\0\0g\0\0g\0\0g\0\0f\0\0f\0\0f\0\0e\0\0e\0\0e\0\0d\0\0d\0\0d\0\0c\0\0c\0\0c\0\0b\0\0b\0\0b\0\0a\0\0a\0\0a\0\0\\\0\0\\\0\0\\\0\0','?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0ˇ\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0	\0\0\n\0\0\0\0\0\0\r\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\Z\0\0\0\0\0\0\0\0\0\0\0\0 \0\0!\0\0\"\0\0#\0\0$\0\0%\0\0&\0\0\'\0\0(\0\0)\0\0*\0\0+\0\0,\0\0-\0\0.\0\0/\0\00\0\01\0\02\0\03\0\04\0\05\0\06\0\07\0\08\0\09\0\0:\0\0;\0\0<\0\0=\0\0>\0\0?\0\0@\0\0A\0\0B\0\0C\0\0D\0\0E\0\0F\0\0G\0\0H\0\0I\0\0J\0\0K\0\0L\0\0M\0\0N\0\0O\0\0P\0\0Q\0\0R\0\0S\0\0T\0\0U\0\0V\0\0W\0\0X\0\0Y\0\0Z\0\0[\0\0\\\0\0]\0^\0\0_\0\0`\0\0a\0b\0c\0d\0e\0f\0g\0h\0i\0'),(103,'i\0\0i\0\0i\0\0h\0\0h\0\0h\0\0g\0\0g\0\0g\0\0f\0\0f\0\0f\0\0e\0\0e\0\0e\0\0d\0\0d\0\0d\0\0c\0\0c\0\0c\0\0b\0\0b\0\0b\0\0a\0\0a\0\0a\0\0\\\0\0\\\0\0\\\0\0','?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0ˇ\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0	\0\0\n\0\0\0\0\0\0\r\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\Z\0\0\0\0\0\0\0\0\0\0\0\0 \0\0!\0\0\"\0\0#\0\0$\0\0%\0\0&\0\0\'\0\0(\0\0)\0\0*\0\0+\0\0,\0\0-\0\0.\0\0/\0\00\0\01\0\02\0\03\0\04\0\05\0\06\0\07\0\08\0\09\0\0:\0\0;\0\0<\0\0=\0\0>\0\0?\0\0@\0\0A\0\0B\0\0C\0\0D\0\0E\0\0F\0\0G\0\0H\0\0I\0\0J\0\0K\0\0L\0\0M\0\0N\0\0O\0\0P\0\0Q\0\0R\0\0S\0\0T\0\0U\0\0V\0\0W\0\0X\0\0Y\0\0Z\0\0[\0\0\\\0\0]\0\0^\0_\0\0`\0\0a\0b\0c\0d\0e\0f\0g\0h\0i\0'),(104,'i\0\0i\0\0i\0\0h\0\0h\0\0h\0\0g\0\0g\0\0g\0\0f\0\0f\0\0f\0\0e\0\0e\0\0e\0\0d\0\0d\0\0d\0\0c\0\0c\0\0c\0\0b\0\0b\0\0b\0\0a\0\0a\0\0a\0\0\\\0\0\\\0\0\\\0\0','?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0ˇ\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0	\0\0\n\0\0\0\0\0\0\r\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\Z\0\0\0\0\0\0\0\0\0\0\0\0 \0\0!\0\0\"\0\0#\0\0$\0\0%\0\0&\0\0\'\0\0(\0\0)\0\0*\0\0+\0\0,\0\0-\0\0.\0\0/\0\00\0\01\0\02\0\03\0\04\0\05\0\06\0\07\0\08\0\09\0\0:\0\0;\0\0<\0\0=\0\0>\0\0?\0\0@\0\0A\0\0B\0\0C\0\0D\0\0E\0\0F\0\0G\0\0H\0\0I\0\0J\0\0K\0\0L\0\0M\0\0N\0\0O\0\0P\0\0Q\0\0R\0\0S\0\0T\0\0U\0\0V\0\0W\0\0X\0\0Y\0\0Z\0\0[\0\0\\\0\0]\0\0^\0\0_\0`\0\0a\0b\0c\0d\0e\0f\0g\0h\0i\0'),(105,'i\0\0i\0\0i\0\0h\0\0h\0\0h\0\0g\0\0g\0\0g\0\0f\0\0f\0\0f\0\0e\0\0e\0\0e\0\0d\0\0d\0\0d\0\0c\0\0c\0\0c\0\0b\0\0b\0\0b\0\0a\0\0a\0\0a\0\0\\\0\0\\\0\0\\\0\0','?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0?\0\0ˇ\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0	\0\0\n\0\0\0\0\0\0\r\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\Z\0\0\0\0\0\0\0\0\0\0\0\0 \0\0!\0\0\"\0\0#\0\0$\0\0%\0\0&\0\0\'\0\0(\0\0)\0\0*\0\0+\0\0,\0\0-\0\0.\0\0/\0\00\0\01\0\02\0\03\0\04\0\05\0\06\0\07\0\08\0\09\0\0:\0\0;\0\0<\0\0=\0\0>\0\0?\0\0@\0\0A\0\0B\0\0C\0\0D\0\0E\0\0F\0\0G\0\0H\0\0I\0\0J\0\0K\0\0L\0\0M\0\0N\0\0O\0\0P\0\0Q\0\0R\0\0S\0\0T\0\0U\0\0V\0\0W\0\0X\0\0Y\0\0Z\0\0[\0\0\\\0\0]\0\0^\0\0_\0\0`\0a\0b\0c\0d\0e\0f\0g\0h\0i\0');
/*!40000 ALTER TABLE `t_user_hero_config` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t_user_info`
--

DROP TABLE IF EXISTS `t_user_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_user_info` (
  `user_id` bigint(16) NOT NULL AUTO_INCREMENT,
  `ezplay_id` varchar(64) DEFAULT NULL,
  `user_pwd` varchar(100) DEFAULT '111111',
  `user_status` varchar(10) DEFAULT '0',
  `last_login_ip` varchar(15) DEFAULT '0.0.0.0',
  `user_email` varchar(64) DEFAULT 'default@x-spaces.com',
  `last_login_ts` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `login_times` bigint(16) DEFAULT '0',
  `user_from` int(2) DEFAULT '0' COMMENT 'Áî®Êà∑Êù•Ê∫ê',
  PRIMARY KEY (`user_id`),
  KEY `ezplay_id` (`ezplay_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1200 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_user_info`
--

LOCK TABLES `t_user_info` WRITE;
/*!40000 ALTER TABLE `t_user_info` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_user_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `t_user_rank`
--

DROP TABLE IF EXISTS `t_user_rank`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t_user_rank` (
  `rank_id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `user_nickname` varchar(32) NOT NULL,
  `user_score` int(11) NOT NULL DEFAULT '0',
  `user_win` int(11) DEFAULT '0',
  `user_lose` int(11) DEFAULT '0',
  PRIMARY KEY (`rank_id`)
) ENGINE=MyISAM AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `t_user_rank`
--

LOCK TABLES `t_user_rank` WRITE;
/*!40000 ALTER TABLE `t_user_rank` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_user_rank` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-12-24 14:29:11
