package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLBuffer extends WLProxy {
	
	public static WLBuffer fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLBuffer type = new WLBuffer();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLBufferListener listener);
	
	@WLRequest
	public native void destroy();
	
	public static interface WLBufferListener {
		
		@WLEvent
		public void release();
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
