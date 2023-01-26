package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLDataDevice extends WLProxy {
	
	public static WLDataDevice fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLDataDevice type = new WLDataDevice();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLDataDeviceListener listener);
	
	@WLRequest
	public native void start_drag(WLProxy source, WLProxy origin, WLProxy icon, int serial);
	
	@WLRequest
	public native void set_selection(WLProxy source, int serial);
	
	@WLRequest
	public native void release();
	
	public static interface WLDataDeviceListener {
		
		@WLEvent
		public void data_offer(WLProxy id);
		
		@WLEvent
		public void enter(int serial, WLProxy surface, int x, int y, WLProxy id);
		
		@WLEvent
		public void leave();
		
		@WLEvent
		public void motion(int time, int x, int y);
		
		@WLEvent
		public void drop();
		
		@WLEvent
		public void selection(WLProxy id);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
