using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using MiniJSON;

public class Serializer {
	//public static string path=Path.Combine(Application.persistentDataPath,"travelmap.dat");

	public static void save(List<FootPrint> foot,string path){
		List<string> l=new List<string>();

		l.Add(Main.Instance.mapFile);
		l.Add(Main.Instance.scale.ToString());
		l.Add(Main.Instance.speed.ToString());

		foreach(FootPrint f in foot)
			l.Add(f.toJson());
		string json=Json.Serialize(l);

		try{
			StreamWriter sw=new StreamWriter(path);
			sw.Write(json);
			sw.Close();
			//Debug.Log("write: "+json);
		}catch{
			Debug.Log("path error");
		}
	}
	public static List<FootPrint> load(string path){
		StreamReader sr;
		try{
			sr=new StreamReader(path);
		}catch{
			Debug.Log("path error");
			return null;
		}
		string jsonString=sr.ReadToEnd();
		//Debug.Log("read: "+jsonString);

		object obj=Json.Deserialize(jsonString);
		var list=obj as List<object>;
		List<FootPrint> foot=new List<FootPrint>();
		if(null!=list){
			Main.Instance.mapFile=(string)list[0];
			Main.Instance.scale=float.Parse((string)list[1]);
			Main.Instance.speed=float.Parse((string)list[2]);
			list.RemoveRange(0,3);

			foreach(object str in list){
				FootPrint f=new FootPrint();
				f.fromJson((string)str);
				foot.Add(f);
			}
		}
		return foot;
	}
}
