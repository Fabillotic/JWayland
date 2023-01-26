package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLShm extends WLProxy {
	
	public static WLShm fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLShm type = new WLShm();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLShmListener listener);
	
	@WLRequest
	public native WLProxy create_pool(int fd, int size);
	
	public static interface WLShmListener {
		
		@WLEvent
		public void format(int format);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
