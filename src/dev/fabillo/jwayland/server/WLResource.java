package dev.fabillo.jwayland.server;

public class WLResource {
	
	public long native_ptr = 0;
	
	public WLResource() {
	}
	
	public WLResource(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
	@Override
	public String toString() {
		return "RESOURCE(0x" + Long.toHexString(native_ptr) + ")";
	}

}
