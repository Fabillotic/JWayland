package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLShellSurface extends WLProxy {
	
	public static WLShellSurface fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLShellSurface type = new WLShellSurface();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLShellSurfaceListener listener);
	
	@WLRequest
	public native void pong(int serial);
	
	@WLRequest
	public native void move(WLProxy seat, int serial);
	
	@WLRequest
	public native void resize(WLProxy seat, int serial, int edges);
	
	@WLRequest
	public native void set_toplevel();
	
	@WLRequest
	public native void set_transient(WLProxy parent, int x, int y, int flags);
	
	@WLRequest
	public native void set_fullscreen(int method, int framerate, WLProxy output);
	
	@WLRequest
	public native void set_popup(WLProxy seat, int serial, WLProxy parent, int x, int y, int flags);
	
	@WLRequest
	public native void set_maximized(WLProxy output);
	
	@WLRequest
	public native void set_title(String title);
	
	@WLRequest
	public native void set_class(String class_);
	
	public static interface WLShellSurfaceListener {
		
		@WLEvent
		public void ping(int serial);
		
		@WLEvent
		public void configure(int edges, int width, int height);
		
		@WLEvent
		public void popup_done();
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
