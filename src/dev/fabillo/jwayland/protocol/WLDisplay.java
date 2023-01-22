package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLDisplay extends WLProxy {
	
	public static WLDisplay fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLDisplay display = new WLDisplay();
		display.native_ptr = proxy.native_ptr;
		return display;
	}
	
	@ProxyListener
	public native void addListener(WLDisplayListener listener);
	
	@WLRequest
	public native WLProxy sync();
	
	@WLRequest
	public native WLProxy get_registry();
	
	public static interface WLDisplayListener {
		
		@WLEvent
		public void error(WLProxy object, int code, String message);
		
		@WLEvent
		public void delete_id(int id);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
