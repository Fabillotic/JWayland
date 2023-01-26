package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLOutput extends WLProxy {
	
	public static WLOutput fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLOutput type = new WLOutput();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLOutputListener listener);
	
	@WLRequest
	public native void release();
	
	public static interface WLOutputListener {
		
		@WLEvent
		public void geometry(int x, int y, int physical_width, int physical_height, int subpixel, String make, String model, int transform);
		
		@WLEvent
		public void mode(int flags, int width, int height, int refresh);
		
		@WLEvent
		public void done();
		
		@WLEvent
		public void scale(int factor);
		
		@WLEvent
		public void name(String name);
		
		@WLEvent
		public void description(String description);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
