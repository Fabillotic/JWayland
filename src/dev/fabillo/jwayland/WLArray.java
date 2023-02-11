package dev.fabillo.jwayland;

import java.nio.ByteBuffer;

public class WLArray extends WLObject {
	
	public WLArray() {
	}
	
	public WLArray(long native_ptr) {
		super(native_ptr);
	}
	
	public static native WLArray init();
	public native ByteBuffer getData();
	public native void release();
	public native void add(int bytes);
	
	@Override
	public String toString() {
		return "ARRAY(0x" + Long.toHexString(getPointer()) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLArray) {
			if(((WLArray) obj).getPointer() == getPointer()) return true;
		}
		return false;
	}
	
	static {
		JWayland.loadLibrary();
	}
	
}
