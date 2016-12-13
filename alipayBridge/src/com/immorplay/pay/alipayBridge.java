package com.immorplay.pay;
import java.util.Map;

import com.unity3d.player.UnityPlayer;
import com.alipay.sdk.app.PayTask;

import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.text.TextUtils;
import android.app.Activity;

public class alipayBridge {
	
	private static final int SDK_PAY_FLAG = 1;
	
	public void __alipayBridgePay(final Activity activity, final String orderInfo,final String objName,final String callback){

		Runnable payRunnable = new Runnable() {

			@Override
			public void run() {

				Looper.prepare();

				Handler mHandler = new Handler() {

					public void handleMessage(Message msg) {
						switch (msg.what) {
						case SDK_PAY_FLAG: {
							@SuppressWarnings("unchecked")
							PayResult payResult = new PayResult((Map<String, String>) msg.obj);
							//对于支付结果，请商户依赖服务端的异步通知结果。同步通知结果，仅作为支付结束的通知。
							 
							String resultInfo = payResult.getResult();// 同步返回需要验证的信息
							String resultStatus = payResult.getResultStatus();
							// 判断resultStatus 为9000则代表支付成功
							if (TextUtils.equals(resultStatus, "9000")) {
								// 该笔订单是否真实支付成功，需要依赖服务端的异步通知。
							} else {
								// 该笔订单真实的支付结果，需要依赖服务端的异步通知。
							}
							
							//result to Unity
							UnityPlayer.UnitySendMessage(objName, callback,resultInfo);
							break;
						}
						default:
							break;
						}
					};	//handleMessage
				};	//new Handler()
				
				PayTask alipay = new PayTask(activity);
				Map<String, String> result = alipay.payV2(orderInfo, true);
				
				Message msg = new Message();
				msg.what = SDK_PAY_FLAG;
				msg.obj = result;
				mHandler.sendMessage(msg);

				Looper.loop();
			}
		};

		Thread payThread = new Thread(payRunnable);
		payThread.start();	
	}
}
