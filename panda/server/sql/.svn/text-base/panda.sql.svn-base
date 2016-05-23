USE panda;

DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
	`id` varchar(32) NOT NULL,
	`type` TINYINT(1) UNSIGNED DEFAULT '0',
	`udid` varchar(32) DEFAULT NULL,
	`account` varchar(32) DEFAULT NULL,
	`pswd` varchar(32) DEFAULT NULL,
	`name` varchar(32) DEFAULT NULL,
	`zid` SMALLINT(4) NOT NULL DEFAULT '100',
	`client_version` INT(6) NOT NULL DEFAULT '100',
	`last_ip` varchar(15) DEFAULT '0.0.0.0',
	`last_login` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
	PRIMARY KEY (`id`),
	KEY `account` (`account`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `player`;
CREATE TABLE `player` (
	`account` varchar(32) NOT NULL,
	`pid` TINYINT(1) UNSIGNED NOT NULL,
	`name` varchar(32) DEFAULT NULL,
	`level` INT(16) DEFAULT '0',
	`energy` SMALLINT(4) DEFAULT '100',
	`energy_time` INT(20) DEFAULT '0',
	`exp` INT(16) DEFAULT '0',
	`gold` INT(16) DEFAULT '0',
	`money` INT(16) DEFAULT '0',
	`honor` SMALLINT(8) DEFAULT '0',
	`zid` SMALLINT(4) NOT NULL DEFAULT '100',
	`px` INT(16) DEFAULT '0',
	`py` INT(16) DEFAULT '0',
	`pz` INT(16) DEFAULT '0',
	`orientation` TINYINT(3) DEFAULT '0',
	`rand_huashan` INT(16) DEFAULT '0',
	`title` varchar(32) DEFAULT NULL,
	`arena_title` varchar(32) DEFAULT NULL,
	`arena_honor` varchar(32) DEFAULT NULL,
	PRIMARY KEY (`account`,`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
