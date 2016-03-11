USE dnf;

DROP TABLE IF EXISTS `t_onlines`;
CREATE TABLE `t_onlines` (
  `day` DATE NOT NULL,
  `hour` tinyint(2) unsigned NOT NULL DEFAULT '0',
  `onlines` int(8) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`day`,`hour`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `t_stats`;
CREATE TABLE `t_stats` (
  `day` DATE NOT NULL,
  `ru` int(10) unsigned NOT NULL DEFAULT '0',
  `au` int(10) unsigned NOT NULL DEFAULT '0',
  `pu` int(10) unsigned NOT NULL DEFAULT '0',
  `tp` int(10) unsigned NOT NULL DEFAULT '0',
  `arpu` int(10) unsigned NOT NULL DEFAULT '0',
  `apa` int(10) unsigned NOT NULL DEFAULT '0',
  `pcu` int(10) unsigned NOT NULL DEFAULT '0',
  `acu` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`day`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE t_user ADD COLUMN time_login BIGINT(20) unsigned NOT NULL DEFAULT '0';
ALTER TABLE t_user ADD COLUMN time_online TINYINT(2) unsigned NOT NULL DEFAULT '0';
ALTER TABLE t_user ADD COLUMN ac_days SMALLINT(10) unsigned NOT NULL DEFAULT '0';
