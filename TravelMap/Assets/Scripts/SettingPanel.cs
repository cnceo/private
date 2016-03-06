using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class SettingPanel : MonoBehaviour {
	public GameObject item;
	public Text About;

	void Start(){
		About.text="Vic Liu,Copyrights 2014\nData path:";//+Serializer.path;
	}

	public void init(){
		Main parent=Main.Instance;
		DetailItem di=item.GetComponent<DetailItem>();
		di.name=di.Name.text="map";
		di.Value.text=parent.mapFile;

		GameObject go=GameObject.Instantiate(item) as GameObject;
		go.transform.SetParent(item.transform.parent);
		go.transform.localScale=Vector3.one;
		di=go.GetComponent<DetailItem>();
		di.name=di.Name.text="scale";
		di.Value.text=parent.scale.ToString();

		go=GameObject.Instantiate(item) as GameObject;
		go.transform.SetParent(item.transform.parent);
		go.transform.localScale=Vector3.one;
		di=go.GetComponent<DetailItem>();
		di.name=di.Name.text="speed";
		di.Value.text=parent.speed.ToString();
	}
	
	public void onOk(){
		Main _parent=Main.Instance;
		foreach(Transform t in item.gameObject.transform.parent){
			DetailItem di=t.gameObject.GetComponent<DetailItem>();
			string name=di.gameObject.name;
			if(name=="map")			_parent.mapFile=di.Value.text;
			else if(name=="scale")	_parent.scale=float.Parse(di.Value.text);
			else if(name=="speed")	_parent.speed=float.Parse(di.Value.text);
		}
		Main.Instance.ReCalc();
		onCancel();
	}

	public void onCancel(){
		GameObject.Destroy(gameObject);
	}

	public static void Load(){
		GameObject go=GameObject.Instantiate(Resources.Load("SettingPanel")) as GameObject;
		SettingPanel info=go.GetComponent<SettingPanel>();
		if(null!=info)info.init();
	}
}
