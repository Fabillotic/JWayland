package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLSeat extends WLProxy {
	
	public static WLSeat fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLSeat type = new WLSeat();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLSeatListener listener);
	
	@WLRequest
	public native WLProxy get_pointer();
	
	@WLRequest
	public native WLProxy get_keyboard();
	
	@WLRequest
	public native WLProxy get_touch();
	
	@WLRequest
	public native void release();
	
	public static interface WLSeatListener {
		
		@WLEvent
		public void capabilities(int capabilities);
		
		@WLEvent
		public void name(String name);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
