package dev.fabillo.jwayland;

public class WLProxy {
	
	public long native_ptr = 0;
	
	public WLProxy() {
	}
	
	public WLProxy(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
	@Override
	public String toString() {
		return "PROXY(0x" + Long.toHexString(native_ptr) + ")";
	}
	
}
