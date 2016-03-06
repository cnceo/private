package com.happylatte.nutslam;

import com.unity3d.player.UnityPlayerActivity;
import com.unity3d.player.UnityPlayer;

import android.os.Bundle;

public class NutSlamActivity extends UnityPlayerActivity {

  protected void onCreate(Bundle savedInstanceState) {
      // call UnityPlayerActivity.onCreate()
      super.onCreate(savedInstanceState);
}

  public void onLowMemory () {
	  UnityPlayer.UnitySendMessage("Startup", "DidReceiveMemoryWarning","NutSlam");
  }
}
