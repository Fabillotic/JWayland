package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLCallback extends WLProxy {
	
	public static WLCallback fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLCallback type = new WLCallback();
		type.native_ptr = proxy.native_ptr;
		return type;
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
