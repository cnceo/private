using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class Utils {
	public static Component UIClone<T>(GameObject src,string name="temp_ui"){
		Component co=null;
		GameObject go=GameObject.Instantiate(src) as GameObject;
		if(null!=go){
			go.SetActive(true);
			go.transform.SetParent(src.transform.parent,false);
			go.transform.localScale=Vector3.one;
			if(name!=null){
				go.name=name;
				Text txt=go.GetComponentInChildren<Text>();
				if(null!=txt)txt.text=name;
			}
			co=go.GetComponent(typeof(T));
		}
		return co;//default(T);
	}

	static public string TimeIntToString(int minutes){
		//hh:mm
		int hour=minutes/60%24;
		int min=minutes%60;
		return hour.ToString()+":"+min.ToString();
	}

	static public int TimeStringToInt(string time){
		string[] str=time.Split(':');
		return int.Parse(str[0])*60+(str.Length==2?int.Parse(str[1]):0);
	}
}
