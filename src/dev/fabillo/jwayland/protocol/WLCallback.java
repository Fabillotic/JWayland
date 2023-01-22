package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;

public class WLCallback extends WLProxy {
	
	public static WLCallback fromProxy(WLProxy proxy) {
		WLCallback callback = new WLCallback();
		callback.native_ptr = proxy.native_ptr;
		return callback;
	}
	
	@ProxyListener
	public native void addListener(WLCallbackListener listener);
	
	public static interface WLCallbackListener {
		
		@WLEvent
		public void done(int callback_data);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
