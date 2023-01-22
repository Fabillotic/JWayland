package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WPSinglePixelBufferManagerV1 extends WLProxy {
	
	public static WPSinglePixelBufferManagerV1 fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WPSinglePixelBufferManagerV1 singlepixelbuffermanagerv1 = new WPSinglePixelBufferManagerV1();
		singlepixelbuffermanagerv1.native_ptr = proxy.native_ptr;
		return singlepixelbuffermanagerv1;
	}
	
	@WLRequest
	public native void destroy();
	
	@WLRequest
	public native WLProxy create_u32_rgba_buffer(int r, int g, int b, int a);
	
	static {
		System.loadLibrary("jwayland");
	}

}
