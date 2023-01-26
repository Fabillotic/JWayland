package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLRegion extends WLProxy {
	
	public static WLRegion fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLRegion type = new WLRegion();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLRegionListener listener);
	
	@WLRequest
	public native void destroy();
	
	@WLRequest
	public native void add(int x, int y, int width, int height);
	
	@WLRequest
	public native void subtract(int x, int y, int width, int height);
	
	public static interface WLRegionListener {
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
