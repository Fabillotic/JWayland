package dev.fabillo.jwayland;

public class WLProxy {
	
	public long native_ptr = 0;
	
	public WLProxy() {
	}
	
	public WLProxy(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
}
