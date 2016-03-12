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
  `Competition_ID` int(11) NOT NULL,
  `AtRound` int(11) NOT NULL,
  `BeginDay` int(11) NOT NULL,
  `BeginTime` int(11) NOT NULL,
  `GameTime` int(11) NOT NULL,
  `IntervalTime` int(11) NOT NULL,
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
  `User_Group` int(11) unsigned zerofill NOT NULL DEFAULT '00000000000',
  `User_State` int(11) unsigned zerofill NOT NULL DEFAULT '00000000000',
  `User_CardGroupId` int(11) unsigned zerofill NOT NULL DEFAULT '00000000000',
  `User_AtRound` int(11) unsigned zerofill NOT NULL DEFAULT '00000000000',
  `User_Round_WinCount` int(11) unsigned zerofill NOT NULL DEFAULT '00000000000',
  `User_Round_LostCount` int(11) unsigned zerofill NOT NULL DEFAULT '00000000000',
  PRIMARY KEY (`TIndex`),
  KEY `index` (`Competition_ID`)
) ENGINE=InnoDB AUTO_INCREMENT=49 DEFAULT CHARSET=gbk;
