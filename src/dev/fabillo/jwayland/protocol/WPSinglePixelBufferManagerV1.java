package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WPSinglePixelBufferManagerV1 extends WLProxy {
	
	public static WPSinglePixelBufferManagerV1 fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WPSinglePixelBufferManagerV1 type = new WPSinglePixelBufferManagerV1();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WPSinglePixelBufferManagerV1Listener listener);
	
	@WLRequest
	public native void destroy();
	
	@WLRequest
	public native WLProxy create_u32_rgba_buffer(int r, int g, int b, int a);
	
	public static interface WPSinglePixelBufferManagerV1Listener {
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
