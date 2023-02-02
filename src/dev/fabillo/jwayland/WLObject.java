package dev.fabillo.jwayland;

public abstract class WLObject {
	
	public long native_ptr = 0;
	
	public WLObject() {
	}
	
	public WLObject(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
}
