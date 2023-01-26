package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLPointer extends WLProxy {
	
	public static WLPointer fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLPointer type = new WLPointer();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLPointerListener listener);
	
	@WLRequest
	public native void set_cursor(int serial, WLProxy surface, int hotspot_x, int hotspot_y);
	
	@WLRequest
	public native void release();
	
	public static interface WLPointerListener {
		
		@WLEvent
		public void enter(int serial, WLProxy surface, int surface_x, int surface_y);
		
		@WLEvent
		public void leave(int serial, WLProxy surface);
		
		@WLEvent
		public void motion(int time, int surface_x, int surface_y);
		
		@WLEvent
		public void button(int serial, int time, int button, int state);
		
		@WLEvent
		public void axis(int time, int axis, int value);
		
		@WLEvent
		public void frame();
		
		@WLEvent
		public void axis_source(int axis_source);
		
		@WLEvent
		public void axis_stop(int time, int axis);
		
		@WLEvent
		public void axis_discrete(int axis, int discrete);
		
		@WLEvent
		public void axis_value120(int axis, int value120);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
