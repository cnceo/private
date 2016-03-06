using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections;

public class Mark : MonoBehaviour,IEndDragHandler,IDragHandler {
	public Sprite[] images;
	public Image icon;
	public Text intro;
	[HideInInspector]
	public FootPrint data=new FootPrint();

	[HideInInspector]
	public Mark prev,next;

	public bool Finish{
		set{
			data.finish=value;
			icon.sprite=images[value?1:0];
		}
	}

	public void OnClick(){
		if(dragging)return;
		DetailPanel.Load (this);
	}

	bool dragging=false;
	public void OnDrag(PointerEventData eventData){
		float trashArea=Screen.width/10f;
		Vector2 pt=eventData.position;
		if(pt.x<trashArea||pt.y<trashArea||pt.x>Screen.width-trashArea||pt.y>Screen.height-trashArea){
			Main.Instance.Remove(this);
		}else{
			//mark using position,but store localposition
			Vector2 pos=Camera.main.ScreenToWorldPoint(new Vector3(pt.x,pt.y,0));
			transform.position=new Vector3(pos.x,pos.y,0);
		}
		Main.Instance.Refresh();
		dragging=true;
	}

	public void OnEndDrag(PointerEventData eventData){
		dragging=false;
		Main.Instance.ReCalc();
	}
	// --------------- functional ---------------
	public static Mark Load(Transform parent){
		Mark mark=null;
		GameObject go=GameObject.Instantiate(Resources.Load("Mark")) as GameObject;
		if(go!=null){
			if(parent!=null)go.transform.SetParent(parent,false);
			go.transform.localScale=Vector3.one;
			mark=go.GetComponent<Mark>();
		}
		return mark;
	}
}
