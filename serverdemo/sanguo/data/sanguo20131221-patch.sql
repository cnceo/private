USE dnf;

DROP PROCEDURE IF EXISTS `csp_user_register`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `csp_user_register`(in p_ezplay varchar(32), p_pswd varchar(15))
BEGIN
declare p_userid int default 0;
if exists(select user_id from t_user_info where ezplay_id=p_ezplay)
then
	select 2;
else
	select count(*) into p_userid from t_user_info;
	set p_userid=p_userid+1;
	insert into t_user_info(user_id,ezplay_id,user_pwd,user_status,user_email,login_times) values(p_userid,p_ezplay,p_pswd,0,'0',current_timestamp);
	if exists(select user_id from t_user where user_id=p_userid)
	then
		delete from t_user where user_id=p_userid;
	end if;
	insert into t_user(user_id,user_pwd) values(p_userid,p_pswd);

	select 1;
end if;
END;;
