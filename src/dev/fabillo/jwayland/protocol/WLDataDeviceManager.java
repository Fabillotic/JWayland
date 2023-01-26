package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLDataDeviceManager extends WLProxy {
	
	public static WLDataDeviceManager fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLDataDeviceManager type = new WLDataDeviceManager();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLDataDeviceManagerListener listener);
	
	@WLRequest
	public native WLProxy create_data_source();
	
	@WLRequest
	public native WLProxy get_data_device(WLProxy seat);
	
	public static interface WLDataDeviceManagerListener {
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
