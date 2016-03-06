using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.IO;

public class FileDlg : MonoBehaviour {
	public Text Pwd;
	public Text Item;
	public Sprite[] spriteSet;
	public RectTransform Content;

	System.Action<string> handler;
	//string filter="png";
	string path="/";

	void Awake(){
		Item.name="d";
	}

	public void OnOK(){
		if(null!=handler)handler.Invoke(path);
		OnCancel();
	}

	public void OnCancel(){
		Destroy(gameObject);
	}

	public void OnSelect(Text item){
		path=item.text;
		if(item.name=="d")try{
			string dir=(item.text==".."?Directory.GetParent(Pwd.text).FullName:item.text);
			cwd(dir);
		}catch{}
	}

	void Init(System.Action<string> handler,string filter="*"){
		this.handler=handler;
		//this.filter=filter;
		cwd();
	}

	void cwd(string pwd=null){
		foreach(Transform child in Content.gameObject.transform)
			Destroy(child.gameObject);
		Content.DetachChildren();

		if(pwd==null)pwd="/";
		Pwd.text=pwd;

		string[] dirs=Directory.GetDirectories(pwd);
		string[] files=Directory.GetFiles(pwd);
		foreach(string s in dirs)_insert(s,false);
		foreach(string s in files)_insert(s);

		int count=Content.childCount;
		Content.sizeDelta=new Vector2(Content.sizeDelta.x,40*count);
	}

	void _insert(string name,bool isFile=true){
		if(isHidden(name))return;
		GameObject go=GameObject.Instantiate(Item.transform.parent.parent.gameObject) as GameObject;
		go.transform.SetParent(Content);
		go.transform.localScale=Vector3.one;
		Text text=go.GetComponentInChildren<Text>();
		text.text=name;
		text.name=(isFile?"f":"d");
	}

	bool isHidden(string path){
		int i=path.LastIndexOf('.');
		return (i==0||i>0&&path[i-1]=='/')?true:false;
	}

	public static void Load(System.Action<string> handler,string filter="*"){
		GameObject go=GameObject.Instantiate(Resources.Load("FileDlg")) as GameObject;
		FileDlg panel=go.GetComponent<FileDlg>();
		if(null!=panel)panel.Init(handler,filter);
	}
}
