using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.IO;
using System.Collections;
using System.Collections.Generic;

public class Main : MonoBehaviour,IPointerDownHandler,IPointerUpHandler,IBeginDragHandler,IDragHandler{
	string data_file="roaddata.dat";
	string map_file="roadmap.png";

	public Transform canvas;
	public Transform view;
	public Image map;
	public Button btnBrowser;
	public Button btnEdit;
	public Button btnOpen;
	public Button btnSave;
	public Button btnAbout;

	[HideInInspector]public string mapFile;
	[HideInInspector]public float scale;	//km/pixel
	[HideInInspector]public float speed;	//km/h

	float tmPointDown;
	float tmBeginDrag;
	float yZoom;
	float zoom;
	Vector2 ptBegDrag=new Vector2();
	Vector3 posBegDrag=new Vector3();
	Color normalColor;
	Color highlightColor;
	LineRenderer lr;
	Mark Head,Tail;
	int Count;

	float zoomArea;
	public static Main Instance;
	void Awake(){
		Instance=this;
	}

	void Start () {
		mapFile=map_file;
		scale=2;
		speed=100;
		zoom=1f;
		normalColor = Color.red;
		highlightColor = Color.green;
		zoomArea=Screen.width/10f;

		Canvas canvas=gameObject.GetComponent<Canvas>();
		lr=canvas.GetComponent<LineRenderer>();

		if(PlayerPrefs.GetString(data_file).Length>0)onOpen();
		if(PlayerPrefs.GetString(map_file).Length>0)onLoadMap();
	}

	void OnApplicationQuit(){
		onSave();
	}

	void Update(){
		if ( Application.platform == RuntimePlatform.Android &&(Input.GetKeyDown(KeyCode.Escape)))
			Application.Quit();
	}
	
	public void Refresh(){
		if(Head!=null){
			lr.SetColors(normalColor,highlightColor);
			lr.SetVertexCount(Count);

			int i=0;
			Mark ptr=Head;
			while(ptr!=null){
				Vector3 p=new Vector3(ptr.transform.position.x,ptr.transform.position.y,0);
				lr.SetPosition(i++,p);
				ptr=ptr.next;
				//Debug.Log("draw pos="+p.ToString());
			}
			ReCalc();
		}
	}

	public void ReCalc(){
		if(Head!=null){
			Mark ptr=Head;
			while(ptr!=null){
				if(ptr.prev!=null){
					ptr.data.distance=(int)(scale*Vector3.Distance(ptr.transform.position,ptr.prev.transform.position)/zoom);
					ptr.data.arrived=ptr.prev.data.arrived+ptr.prev.data.stay+(int)(ptr.data.distance*60f/speed);
					ptr.data.total_distance=ptr.prev.data.total_distance+ptr.data.distance;
				}
				ptr.Finish=ptr.data.finish;
				ptr.intro.text=ptr.data.intro;
				ptr=ptr.next;
			}
		}
	}
	// --------------- guesture ---------------
	bool markable=false;
	public void OnPointerDown(PointerEventData eventData){
		tmPointDown=Time.time;
		markable=true;
	}

	public void OnPointerUp(PointerEventData eventData){
		if(markable&&Time.time-tmPointDown<0.5f){
			/*
			camera size: h; equal to sreen but half local size
			screen: 0,0 ~ w,h (PointerEventData.position)
			local: -w,-h ~ w,h
			*/
			Vector2 pos=Camera.main.ScreenToWorldPoint(new Vector3(eventData.position.x,eventData.position.y,0));
			//mark using position,but store localposition
			Mark mark=Mark.Load(view);
			mark.transform.position=new Vector3(pos.x,pos.y,0);
			mark.transform.localScale=new Vector3(1/zoom,1/zoom,1);

			insert(mark,findNearest(mark));
		}
	}

	public void OnBeginDrag(PointerEventData eventData){
		ptBegDrag=eventData.position;
		if(Screen.width-eventData.position.x<zoomArea)
			yZoom=eventData.position.y;
		else{
			posBegDrag=view.localPosition;
		}
	}

	public void OnDrag(PointerEventData eventData){
		markable=false;

		bool zooming=(Screen.width-eventData.position.x<zoomArea)
			&&(Screen.width-ptBegDrag.x<zoomArea);

		if(zooming){
			//zoom
			float Y=Screen.height/3;
			float y=yZoom-eventData.position.y;
			y=Mathf.Min(Mathf.Max(-Y,y),Y)*0.01f;
			y=Mathf.Max(1,view.localScale.x*(1+y));
			zoom=y;
			view.localScale=new Vector3(zoom,zoom,1);

			Mark ptr=Head;
			while(ptr!=null){
				ptr.transform.localScale=new Vector3(1/zoom,1/zoom,1);
				ptr=ptr.next;
			}
			this.Refresh();
			yZoom=eventData.position.y;
		}else{
			//pan
			Vector3 pt0=Camera.main.ScreenToWorldPoint(new Vector3(ptBegDrag.x,ptBegDrag.y,0));
			Vector3 pt1=Camera.main.ScreenToWorldPoint(new Vector3(eventData.position.x,eventData.position.y,0));
			Vector3 delta=pt1-pt0;

			view.localPosition=posBegDrag+delta;
			this.Refresh();
		}
	}
	// --------------- toolbar ---------------
	public void onUnDo(){
	}

	public void onReverse(){
		if(Head==null)return;
		//save arrived
		int start=Head.data.arrived;

		Mark tmp;
		Mark ptr=Head;
		while(ptr!=null){
			ptr.Finish=false;
			tmp=ptr.next;
			ptr.next=ptr.prev;
			ptr.prev=tmp;
			ptr=tmp;
		}
		tmp=Head;
		Head=Tail;
		Tail=tmp;
		Head.Finish=true;
		Head.data.arrived=start;
		Head.data.stay=0;
		Head.data.distance=Head.data.total_distance=0;
		Refresh();
	}

	public void onOpen(){
		string file=PlayerPrefs.GetString(data_file);
		if(file.Length>0)
			_open (file);
		else
			FileDlg.Load(delegate(string path){
				path=Path.Combine(path,data_file);
				_open(path);
			});
	}
	void _open(string path){
		List<FootPrint> temp=Serializer.load(path);
		if(temp!=null){
			foreach(FootPrint f in temp){
				Mark mark=Mark.Load(view);
				mark.data=f;
				mark.intro.text=f.intro;
				mark.transform.localPosition=new Vector3(mark.data.position.x,mark.data.position.y,0);
				insert(mark);
			}
			PlayerPrefs.SetString(data_file,path);
		}
	}
	public void onSave(){
		string file=PlayerPrefs.GetString(data_file);
		if(file.Length>0)
			_save (file);
		else
			FileDlg.Load(delegate(string path){
				path=Path.Combine(path,data_file);
				_save(path);
			});
	}
	void _save(string path){
		List<FootPrint> foot=new List<FootPrint>();
		Mark ptr=Head;
		while(ptr!=null){
			ptr.data.position=ptr.transform.localPosition;
			foot.Add(ptr.data);
			ptr=ptr.next;
		}
		Serializer.save(foot,path);
		PlayerPrefs.SetString(data_file,path);
	}
	
	public void onLoadMap(){
		string file=PlayerPrefs.GetString(map_file);
		if(file.Length>0)
			StartCoroutine(loadMap(file));
		else
			FileDlg.Load(delegate(string path){
				path="file://"+Path.Combine(path,map_file);
				StartCoroutine(loadMap(path));
			});
	}

	IEnumerator loadMap(string url){
		WWW www=new WWW(url);
		yield return www;
		if(www.error==null&&www.texture!=null){
			Texture2D tex=www.texture;
			Sprite sprite=Sprite.Create(tex,new Rect(0,0,tex.width,tex.height),new Vector2(0.5f,0.5f),1f);
			map.sprite=sprite;
			map.rectTransform.sizeDelta=new Vector2(tex.width,tex.height);

			PlayerPrefs.SetString(map_file,url);
		}
	}

	public void onSetting(){
		SettingPanel.Load();
	}
	// --------------- functional ---------------
	void insert(Mark mark,Mark pos=null){
		if(Head==null){
			Head=Tail=mark;
			Head.Finish=true;
		}else{
			if(pos==null)pos=Tail;
			mark.prev=pos;
			mark.next=pos.next;
			pos.next=mark;
			if(mark.next!=null)mark.next.prev=mark;
			else Tail=mark;
		}
		mark.name=mark.data.name="City"+Count.ToString();
		++Count;
		Refresh();
	}
	Mark findNearest(Mark mark){
		if(Count==0)return null;
		else if(Count==1)return Head;

		float dist=1e15f;
		Mark nearest=null;
		Mark ptr=Head;
		//find the nearest
		while(ptr!=null){
			float d=Vector3.Distance(ptr.transform.position,mark.transform.position);
			if(d<dist){
				dist=d;
				nearest=ptr;
			}
			ptr=ptr.next;
		}
		//calc the shortest path from p0-p-p1-p2 and p0-p1-p-p2
		Mark p0=nearest.prev,p1=nearest,p2=nearest.next,p=mark;
		if(p0==null)return p1;

		float d0=Vector3.Distance(p0.transform.position,p.transform.position)
				+Vector3.Distance(p.transform.position,p1.transform.position);
		float d1=Vector3.Distance(p0.transform.position,p1.transform.position)
				+Vector3.Distance(p1.transform.position,p.transform.position);
		if(p2!=null){
			d0+=Vector3.Distance(p1.transform.position,p2.transform.position);
			d1+=Vector3.Distance(p.transform.position,p2.transform.position);
		}
		return d0<=d1?p0:p1;
	}

	public void Remove(Mark mark){
		if(mark.prev!=null)mark.prev.next=mark.next;
		if(mark.next!=null)mark.next.prev=mark.prev;
		GameObject.Destroy(mark.gameObject);
		if(0==--Count)Head=Tail=null;
	}
}
