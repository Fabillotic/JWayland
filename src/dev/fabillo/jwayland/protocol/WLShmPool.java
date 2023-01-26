package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLShmPool extends WLProxy {
	
	public static WLShmPool fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLShmPool type = new WLShmPool();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLShmPoolListener listener);
	
	@WLRequest
	public native WLProxy create_buffer(int offset, int width, int height, int stride, int format);
	
	@WLRequest
	public native void destroy();
	
	@WLRequest
	public native void resize(int size);
	
	public static interface WLShmPoolListener {
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
