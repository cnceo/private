using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class DetailPanel : MonoBehaviour {
	public GameObject item;
	public Text desc;
	Mark _mark;

	public void initDetail(Mark mark){
		_mark=mark;
		DetailItem di=item.GetComponent<DetailItem>();
		FootPrint info=mark.data;

		di.name=di.Name.text="name";
		di.Value.text=info.name;
		_read("arrived",Utils.TimeIntToString(info.arrived));
		_read("stay",Utils.TimeIntToString(info.stay));
		_read("distance",info.distance);
		_read("fare",info.fare);
		_read("weather",info.weather);
		_read("finish",info.finish);
		if(info.desc!=null)desc.text=info.desc;
		foreach(KeyValuePair<string,string>kv in info.interest)
			_read(kv.Key,kv.Value);
	}

	void _read<T>(string name,T t){
		GameObject go=GameObject.Instantiate(item) as GameObject;
		go.transform.SetParent(item.transform.parent);
		go.transform.localScale=Vector3.one;
		DetailItem di=item.GetComponent<DetailItem>();
		di.name=di.Name.text=name;
		di.Value.text=t.ToString();
	}

	void _write(){
		Dictionary<string,string> dict=new Dictionary<string, string>();
		foreach(Transform t in item.transform.parent){
			DetailItem di=t.gameObject.GetComponent<DetailItem>();
			dict[di.Name.text]=di.Value.text;
		}

		FootPrint info=_mark.data;
		info.name=dict["name"];
		info.arrived=Utils.TimeStringToInt(dict["arrived"]);
		info.stay=Utils.TimeStringToInt(dict["stay"]);
		info.distance=int.Parse(dict["distance"]);
		info.fare=int.Parse(dict["fare"]);
		info.weather=int.Parse(dict["weather"]);
		bool finish=bool.Parse(dict["finish"]);
		_mark.Finish=finish;
		info.finish=finish;
		info.desc=desc.text;

		_mark.intro.text=info.intro;
	}

	public void onOk(){
		_write();
		Main.Instance.ReCalc();
		onCancel();
	}
	public void onCancel(){
		GameObject.Destroy(gameObject);
	}

	public static void Load(Mark mark){
		GameObject go=GameObject.Instantiate(Resources.Load("DetailPanel")) as GameObject;
		DetailPanel info=go.GetComponent<DetailPanel>();
		if(null!=info)info.initDetail(mark);
	}
}
