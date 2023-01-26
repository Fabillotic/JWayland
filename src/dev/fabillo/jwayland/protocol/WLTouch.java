package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLTouch extends WLProxy {
	
	public static WLTouch fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLTouch type = new WLTouch();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLTouchListener listener);
	
	@WLRequest
	public native void release();
	
	public static interface WLTouchListener {
		
		@WLEvent
		public void down(int serial, int time, WLProxy surface, int id, int x, int y);
		
		@WLEvent
		public void up(int serial, int time, int id);
		
		@WLEvent
		public void motion(int time, int id, int x, int y);
		
		@WLEvent
		public void frame();
		
		@WLEvent
		public void cancel();
		
		@WLEvent
		public void shape(int id, int major, int minor);
		
		@WLEvent
		public void orientation(int id, int orientation);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
