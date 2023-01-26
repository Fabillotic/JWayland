package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLSurface extends WLProxy {
	
	public static WLSurface fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLSurface type = new WLSurface();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLSurfaceListener listener);
	
	@WLRequest
	public native void destroy();
	
	@WLRequest
	public native void attach(WLProxy buffer, int x, int y);
	
	@WLRequest
	public native void damage(int x, int y, int width, int height);
	
	@WLRequest
	public native WLProxy frame();
	
	@WLRequest
	public native void set_opaque_region(WLProxy region);
	
	@WLRequest
	public native void set_input_region(WLProxy region);
	
	@WLRequest
	public native void commit();
	
	@WLRequest
	public native void set_buffer_transform(int transform);
	
	@WLRequest
	public native void set_buffer_scale(int scale);
	
	@WLRequest
	public native void damage_buffer(int x, int y, int width, int height);
	
	@WLRequest
	public native void offset(int x, int y);
	
	public static interface WLSurfaceListener {
		
		@WLEvent
		public void enter(WLProxy output);
		
		@WLEvent
		public void leave(WLProxy output);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
