USE dnf;

ALTER TABLE t_user ADD COLUMN time_total INT(10) unsigned NOT NULL DEFAULT '0';
