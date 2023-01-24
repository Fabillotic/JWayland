package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLRegistry extends WLProxy {
	
	public static WLRegistry fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLRegistry type = new WLRegistry();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLRegistryListener listener);
	
	@WLRequest
	public native WLProxy bind(int name, String interface_name, int interface_version);
	
	public static interface WLRegistryListener {
		
		@WLEvent
		public void global(int name, String iface, int version);
		
		@WLEvent
		public void global_remove(int name);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
