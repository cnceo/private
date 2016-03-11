/*
MySQL Data Transfer
Source Host: localhost
Source Database: dnf
Target Host: localhost
Target Database: dnf
Date: 2014/2/13 15:25:37
*/
USE dnf;
-- ----------------------------
-- Table structure for t_competition
-- ----------------------------
DROP TABLE IF EXISTS `t_competition`;
CREATE TABLE `t_competition` (
  `Index` int(11) NOT NULL AUTO_INCREMENT,
  `Competition_ID` int(8) NOT NULL,
  `AtRound` int(2) NOT NULL,
  `BeginDay` int(8) NOT NULL,
  `BeginTime` int(4) NOT NULL,
  `GameTime` int(4) NOT NULL,
  `IntervalTime` int(4) NOT NULL,
  `IsGameOver` INT(1) DEFAULT 0,
  PRIMARY KEY (`Index`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=gbk;

-- ----------------------------
-- Table structure for t_competition_userlist
-- ----------------------------
DROP TABLE IF EXISTS `t_competition_userlist`;
CREATE TABLE `t_competition_userlist` (
  `TIndex` bigint(20) NOT NULL AUTO_INCREMENT,
  `Competition_ID` int(11) NOT NULL,
  `User_ID` int(11) NOT NULL,
  `User_Group` int(1) unsigned zerofill NOT NULL DEFAULT '0',
  `User_State` int(1) unsigned zerofill NOT NULL DEFAULT '0',
  `User_CardGroupId` int(3) unsigned zerofill NOT NULL DEFAULT '0',
  `User_AtRound` int(2) unsigned zerofill NOT NULL DEFAULT '0',
  `User_Round_WinCount` int(1) unsigned zerofill NOT NULL DEFAULT '0',
  `User_Round_LostCount` int(1) unsigned zerofill NOT NULL DEFAULT '0',
  PRIMARY KEY (`TIndex`),
  KEY `index` (`Competition_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=49 DEFAULT CHARSET=gbk;
