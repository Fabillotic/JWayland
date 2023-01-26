package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLShell extends WLProxy {
	
	public static WLShell fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLShell type = new WLShell();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLShellListener listener);
	
	@WLRequest
	public native WLProxy get_shell_surface(WLProxy surface);
	
	public static interface WLShellListener {
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
