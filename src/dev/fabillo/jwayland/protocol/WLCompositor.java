package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLCompositor extends WLProxy {
	
	public static WLCompositor fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLCompositor type = new WLCompositor();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLCompositorListener listener);
	
	@WLRequest
	public native WLProxy create_surface();
	
	@WLRequest
	public native WLProxy create_region();
	
	public static interface WLCompositorListener {
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
