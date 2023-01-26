package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLDataSource extends WLProxy {
	
	public static WLDataSource fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLDataSource type = new WLDataSource();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLDataSourceListener listener);
	
	@WLRequest
	public native void offer(String mime_type);
	
	@WLRequest
	public native void destroy();
	
	@WLRequest
	public native void set_actions(int dnd_actions);
	
	public static interface WLDataSourceListener {
		
		@WLEvent
		public void target(String mime_type);
		
		@WLEvent
		public void send(String mime_type, int fd);
		
		@WLEvent
		public void cancelled();
		
		@WLEvent
		public void dnd_drop_performed();
		
		@WLEvent
		public void dnd_finished();
		
		@WLEvent
		public void action(int dnd_action);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
