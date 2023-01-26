package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLSubsurface extends WLProxy {
	
	public static WLSubsurface fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLSubsurface type = new WLSubsurface();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLSubsurfaceListener listener);
	
	@WLRequest
	public native void destroy();
	
	@WLRequest
	public native void set_position(int x, int y);
	
	@WLRequest
	public native void place_above(WLProxy sibling);
	
	@WLRequest
	public native void place_below(WLProxy sibling);
	
	@WLRequest
	public native void set_sync();
	
	@WLRequest
	public native void set_desync();
	
	public static interface WLSubsurfaceListener {
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
