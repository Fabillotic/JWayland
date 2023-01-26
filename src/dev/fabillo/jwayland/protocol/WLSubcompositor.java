package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLSubcompositor extends WLProxy {
	
	public static WLSubcompositor fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLSubcompositor type = new WLSubcompositor();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLSubcompositorListener listener);
	
	@WLRequest
	public native void destroy();
	
	@WLRequest
	public native WLProxy get_subsurface(WLProxy surface, WLProxy parent);
	
	public static interface WLSubcompositorListener {
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
