package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLDataOffer extends WLProxy {
	
	public static WLDataOffer fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLDataOffer type = new WLDataOffer();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLDataOfferListener listener);
	
	@WLRequest
	public native void accept(int serial, String mime_type);
	
	@WLRequest
	public native void receive(String mime_type, int fd);
	
	@WLRequest
	public native void destroy();
	
	@WLRequest
	public native void finish();
	
	@WLRequest
	public native void set_actions(int dnd_actions, int preferred_action);
	
	public static interface WLDataOfferListener {
		
		@WLEvent
		public void offer(String mime_type);
		
		@WLEvent
		public void source_actions(int source_actions);
		
		@WLEvent
		public void action(int dnd_action);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
