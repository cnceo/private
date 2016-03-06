using UnityEngine;
using System;
using System.Collections;
using System.Reflection;
using System.Collections.Generic;
using MiniJSON;

public class FootPrint{
	public string		name="Start";
	public int			arrived=360;
	public int			stay=0;
	public int			fare=0;
	public int			weather=20;
	public bool			finish=false;
	public string		desc="";
	public Vector2		position=new Vector2();
	public Dictionary<string,string>	interest=new Dictionary<string,string>();
	public int			distance=0;
	public int			total_distance=0;

	public string intro{
		get{return
			name+"\n"+
			Utils.TimeIntToString(arrived)+"/"+Utils.TimeIntToString(arrived+stay)+"\n"+
			distance.ToString()+"/"+total_distance.ToString();
		}
	}

	/*
	MiniJSON serilizerable: object is bool,int,float,IList,IDictionary or implement ToString method;
	 */
	// serialize this class to JSON
	public string toJson(){
		Dictionary<string,object> dict=new Dictionary<string, object>();
		setBaseTypeDict(dict);
		dict["name"]=(name==null?"":name);
		dict["time"]=arrived;
		dict["stay"]=stay;
		dict["fare"]=fare;
		dict["weather"]=weather;
		dict["arrived"]=finish;
		dict["desc"]=(desc==null?"":desc);
		dict["posx"]=position.x;
		dict["posy"]=position.y;
		foreach(KeyValuePair<string,string>kv in interest)
			dict[kv.Key]=kv.Value;
		return Json.Serialize(dict);
	}

	// Json to class conversion
	public void fromJson(string jsonString){
		object obj=Json.Deserialize(jsonString);
		var dict = obj as Dictionary<string,object>;
		if(null!=dict){
			if(dict.ContainsKey("name"))	name=(string)dict["name"];
			if(dict.ContainsKey("time"))	arrived=(int)(long)dict["time"];
			if(dict.ContainsKey("stay"))	stay=(int)(long)dict["stay"];
			if(dict.ContainsKey("fare"))	fare=(int)(long)dict["fare"];
			if(dict.ContainsKey("weather"))	weather=(int)(long)dict["weather"];
			if(dict.ContainsKey("arrived"))	finish=(bool)dict["arrived"];
			if(dict.ContainsKey("desc"))	desc=(string)dict["desc"];
			if(dict.ContainsKey("posx"))	position.x=(float)(double)dict["posx"];
			if(dict.ContainsKey("posy"))	position.y=(float)(double)dict["posy"];
			/*foreach(KeyValuePair<string,object>kv in dict){
				PropertyInfo pi=this.GetType().GetProperty(kv.Key);
				if(pi!=null)pi.SetValue(this,kv.Value,null);
			}*/
		}
	}

	void setBaseTypeDict(Dictionary<string,object> dict){
		foreach(PropertyInfo pi in this.GetType().GetProperties()){
			Type t=pi.GetType();
			if(t==typeof(int)||t==typeof(bool)||t==typeof(float)||t==typeof(string)){
				object value=pi.GetConstantValue();
				if(value!=null)
					dict[pi.Name]=value;
			}
		}
	}
}
